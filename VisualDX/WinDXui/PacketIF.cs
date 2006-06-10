// Last Edited 4/03/2006
// Completed 4/24/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Diagnostics;
using System.Windows.Forms;
using System.Threading;
using System.IO;

namespace WinDX.UI
{
    public class PacketIF
    {
        class ThreadSender
        {
            private PacketIF p;

            public ThreadSender(PacketIF pin)
            {
                p = pin;
            }

            public void ThreadSendProc()
            {
                while (p.output_queue.Count > 0 && !p.Deleting)
                {
                    QueuedBytes qp = p.output_queue[0];
                    p.output_queue.Remove(qp);
                    qp.send(p);
                }
                p.packetSender = false;
            }
        }

        class ThreadWorker
        {
            private PacketIF p;
            public ThreadWorker(PacketIF pin)
            {
                p = pin;
            }

            public void managedProcessSocketInputICB()
            {
                p.ProcessSocketInputICB();
            }

            public void managedInputIdleWP()
            {
                p.InputIdleWP();
            }

            public void watchForActivity()
            {
                MethodInvoker processSocket = new MethodInvoker(this.managedProcessSocketInputICB);
                MethodInvoker idleProcess = new MethodInvoker(this.managedInputIdleWP);
                while (!p.deleting)
                {
                    if (p.socket.Available > 0)
                    {
                        if (p.DeferPacketHandling)
                        {
                            Thread.Sleep(1000);
                            if (p.DeferPacketHandling)
                                MainProgram.theApplication.getRootForm().BeginInvoke(idleProcess);
                        }
                        else
                        {
                            MainProgram.theApplication.getRootForm().BeginInvoke(processSocket);
                        }
                    }
                    Thread.Sleep(1000);
                }
            }
        }


        #region Enums/Structs

        public delegate void PacketHandlerCallback(Object obj, int id, String line);
        public delegate void PacketIFCallback(Object obj, String line);
        public delegate bool StallingHandler(Object clientData);

        public enum PacketType
        {
            INTERRUPT = 1,
            SYSTEM = 2,
            ACK = 3,
            MACRODEF = 4,
            FOREGROUND = 5,
            BACKGROUND = 6,
            PKTERROR = 7,
            MESSAGE = 8,
            INFORMATION = 9,
            LINQUIRY = 10,
            LRESPONSE = 11,
            LDATA = 12,
            SINQUIRY = 13,
            SRESPONSE = 14,
            SDATA = 15,
            VINQUIRY = 16,
            VRESPONSE = 17,
            VDATA = 18,
            COMPLETE = 19,
            IMPORT = 20,
            IMPORTINFO = 21,
            LINK = 22
        };

        #endregion

        #region public Instance Variables

        public static String[] PacketTypes = {
            	"UNKNOWN",
	            "$int",		/* PacketIF::INTERRUPT	*/
	            "$sys",		/* PacketIF::SYSTEM		*/
	            "$ack",		/* PacketIF::ACK		*/
	            "$mac",		/* PacketIF::MACRODEF		*/
	            "$for",		/* PacketIF::FOREGROUND	*/
	            "$bac",		/* PacketIF::BACKGROUND	*/
	            "$err",		/* PacketIF::PKTERROR		*/
	            "$mes",		/* PacketIF::MESSAGE		*/
	            "$inf",		/* PacketIF::INFO		*/
	            "$lin",		/* PacketIF::LINQUIRY		*/
	            "$lre",		/* PacketIF::LRESPONSE	*/
	            "$dat",		/* PacketIF::LDATA		*/
	            "$sin",		/* PacketIF::SINQUIRY		*/
	            "$sre",		/* PacketIF::SRESPONSE	*/
	            "$dat",		/* PacketIF::SDATA		*/
	            "$vin",		/* PacketIF::VINQUIRY		*/
	            "$vre",		/* PacketIF::VRESPONSE	*/
	            "$dat",		/* PacketIF::VDATA		*/
	            "$com",		/* PacketIF::COMPLETE		*/
	            "$imp",		/* PacketIF::IMPORT		*/
	            "$imi",		/* PacketIF::IMPORTINFO	*/
	            "$lnk",		/* PacketIF::LINK		*/
	            "UNKNOWN"
        };

        public Socket MySocket
        {
            get { return socket; }
        }

        public bool Deleting
        {
            get { return deleting; }
        }

        public bool Error
        {
            get { return error; }
        }

        public bool DeferPacketHandling
        {
            get { return deferPacketHandling; }
        }

        public StreamWriter getStreamWriter()
        {
            if (streamWriter == null)
            {
                NetworkStream networkStream = new NetworkStream(socket);
                streamWriter = new StreamWriter(networkStream);
            }
            return streamWriter;
        }

        #endregion

        #region public Methods

        public PacketIF(String server, int port, bool local, bool asClient)
        {
            Debug.Assert(server != null);

            wpClientData = this;
            workProcInstalled = false;

            socket = null;
            error = false;
            deferPacketHandling = false;
            deleting = false;
            packetSender = false;

            line = "";

            echoCallback = null;
            echoClientData = null;
            endReceiving = true;

            linkHandler = null;
            stallingWorker = null;
            stallingWorkerData = null;

            if (asClient)
                connectAsClient(server, port, local);
            else
                connectAsServer(port);

            output_queue = new List<QueuedBytes>();

            if (!error)
            {
                installInputHandler();
            }
        }

        ~PacketIF()
        {
            this.deleting = true;
            Thread.Sleep(1000);

            if (socket != null)
            {
                socket.Close();
                socket = null;
            }

            removeInputHandler();

            socket = null;
            
            if (linkHandler != null)
                linkHandler = null;

            foreach (PacketHandler h in handlers)
            {
                handlers.Remove(h);
            }

            foreach (QueuedPacket qp in output_queue)
                output_queue.Remove(qp);

        }

        public virtual void initializePacketIO()
        {
            setHandler(PacketType.MESSAGE,
                PacketIF.ProcessMessage,
                this);
            setHandler(PacketType.INFORMATION,
                PacketIF.ProcessInformation,
                this);
            setHandler(PacketType.INTERRUPT,
                PacketIF.ProcessInterrupt,
                this);
            setHandler(PacketType.PKTERROR,
                PacketIF.ProcessError,
                this, "WARNING");
            setHandler(PacketType.INTERRUPT,
                PacketIF.ProcessBeginExecNode,
                this, "begin ");
            setHandler(PacketType.INTERRUPT,
                PacketIF.ProcessEndExecNode,
                this, "end ");
            setHandler(PacketType.PKTERROR,
                PacketIF.ProcessErrorERROR,
                this, "ERROR");
            setHandler(PacketType.LINK,
                PacketIF.ProcessLinkCommand,
                this);

            setErrorCallback(PacketIF.HandleError,
                this);
        }

        public void setHandler(PacketIF.PacketType type, PacketHandlerCallback callback, Object clientdata)
        {
            this.setHandler(type, callback, clientdata, null);
        }
        public void setHandler(PacketIF.PacketType type, PacketHandlerCallback callback,
            Object clientData,
            String matchString)
        {
            if (clientData == null)
                Console.WriteLine("null client data\n");

            foreach (PacketHandler p in handlers)
            {
                if (p.Type == type && p.match(matchString))
                    break;
                if (callback == null)
                {
                    if (p != null)
                    {
                        handlers.Remove(p);
                    }
                }
                else
                {
                    PacketHandler h = new PacketHandler(true, type, 0, callback,
                        clientData, matchString);
                    if (p != null)
                    {
                        handlers.Remove(p);
                        handlers.Add(h);
                    }
                    else
                        handlers.Add(h);
                }
            }
        }

        //
        // Error and echo handling callbacks.  Echos are not performed if no
        // callback has been set up.  Errors are dumped to stderr if nothing
        // has been set up.
        //
        public void setErrorCallback(PacketIFCallback callback, Object clientData)
        {
            errorCallback = callback;
            errorClientData = clientData;
        }
        public PacketIFCallback getErrorCallback(out Object clientData)
        {
            clientData = errorClientData;
            return errorCallback;
        }
        public void setEchoCallback(PacketIFCallback callback, Object clientData)
        {
            echoCallback = callback;
            echoClientData = clientData;
        }
        public PacketIFCallback getEchoCallback(ref Object clientData)
        {
            clientData = echoClientData;
            return echoCallback;
        }

        public void sendBytes(String str)
        {
            // checking the queue size protects us in the case that we've queued
            // something up but in the meantime, we've emptied the input side
            // of the socket.

            if (isSocketInputReady() || output_queue.Count > 0)
            {
                //
                // Record our information and queue writing it (via a workproc)
                //
                QueuedBytes item = new QueuedBytes(str);
                output_queue.Add(item);
                QueuedPacketWP();
                return;
            }
            _sendBytes(str);
        }
        public void sendImmediate(String str)
        {
            if (isSocketInputReady() || output_queue.Count > 0)
            {
                QueuedImmediate item = new QueuedImmediate(str);
                output_queue.Add(item);
                QueuedPacketWP();
                return;
            }
            _sendImmediate(str);
        }

        //
        // Return TRUE if there was NOT a packet error.
        // If returning TRUE and data!=NULL, then *data is set to the value 
        // passed to the endReceiveContinuous() call.
        //
        public bool receiveContinuous(ref String data)
        {
            bool noerr = true;
            endReceiving = false;
            endReceiveData = null;
            while (!endReceiving)
            {
                Debug.Assert(!deferPacketHandling);
                packetReceive();
                if (error)
                {
                    handleStreamError("PacketIF.receiveContinuous");
                    noerr = false;
                    break;
                }
            }
            if (noerr)
                data = endReceiveData;
            return noerr;
        }

        //
        // Terminates receiveContinuous() and causes it to set its *data to
        // the data value passed in.
        //
        public void endReceiveContinuous(String data)
        {
            endReceiving = true;
            endReceiveData = data;
        }

        public void executeLinkCommand(String c, int id)
        {
            if (linkHandler == null)
                installLinkHandler();

            linkHandler.executeLinkCommand(c, id);
        }

        //
        // Defer handing of messages until the function h is called (periodically)
        // and returns TRUE.  At that point handling is reenabled.
        // If stalling was not already enabled and there are no other problems,
        // then we return TRUE, otherwise FALSE.
        // Use isPacketHandlingStalled() to determine if handling is currently 
        // stalled.
        //
        public bool stallPacketHandling(StallingHandler h, Object data)
        {
            if (isPacketHandlingStalled())
                return false;

            deferPacketHandling = true;

            stallingWorker = h;
            stallingWorkerData = data;

            return true;
        }

        public bool isPacketHandlingStalled()
        {
            return (!(stallingWorker == null));
        }

        public void sendPacket(PacketType type, int packetId, String data)
        {
            if (this.isSocketInputReady() || this.output_queue.Count > 0)
            {
                QueuedPacket qp = new QueuedPacket(type, packetId, data);
                output_queue.Add(qp);
                this.QueuedPacketWP();
                return;
            }
            this._sendPacket(type, packetId, data);
        }

        public void QueuedPacketWP()
        {
            if (this.packetSender)
                return;

            this.packetSender = true;

            ThreadSender ts = new ThreadSender(this);
            Thread t = new Thread(
                new ThreadStart(ts.ThreadSendProc));
            t.Priority = ThreadPriority.BelowNormal;
            t.IsBackground = true;
            t.Name = "SendPackets";
            t.Start();
        }

        #endregion

        #region private Instance Variables
        //
        // Private member data:
        //

        //
        // I hate this... on some AIX systems, it seems that the work proc can
        // get called even after the PacketIF deletion method is called.  When this
        // happens, the work proc receives a deleted PacketIF, and all hell breaks 
        // loose.  Instead, I'm going to use double indirection... I'll allocate a
        // pointer when the PacketIF is created, set it to point to the PacketIF
        // itselfkeep a pointer to it in the PacketIF, and pass its address as the
        // work proc client data.  When the PacketIF is deleted, the pointer is set
        // to NULL, but not freed.  So if the pointer that the work proc receives as 
        // its client data points to NULL, we know that the PacketIF has been deleted
        // and the work proc returns immediately.  Unfortunately, this leaks space 
        // for a pointer for each packetIF created.
        //


        // This is going to be significantly different than the C++ version.
        // Since we're not using X as the loop, the eventHandlers will need to be added
        // to the main programs loop.

        private PacketIF wpClientData;

        private static int pif_count = 0;

        private bool error;
        private Socket socket;
        private StreamWriter streamWriter;
        private bool deferPacketHandling;
        private bool endReceiving;
        private PacketIFCallback echoCallback;
        private Object echoClientData;
        private PacketIFCallback errorCallback;
        private Object errorClientData;
        private String endReceiveData;
        private StallingHandler stallingWorker;
        private Object stallingWorkerData;
        private bool workProcInstalled;
        private bool packetSender;
        private bool deleting;

        #endregion

        #region private Methods


        // Open a socket port and wait for a client to connect.
        // This opens 2 sockets (except on the server), one internet domain, and
        // one unix domain.  It then selects on both sockets to see to which one the
        // app connects, and returns the new connection, closing the one not
        // selected.

        private void connectAsServer(int pport)
        {
            IPAddress address;
            int port = pport;

            Socket sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream,
                ProtocolType.Tcp);
            if (sock == null)
            {
                Console.WriteLine("Error instantiating Tcp socket for server.");
                return;
            }
            LingerOption lingerOption = new LingerOption(true, 0);
            sock.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, lingerOption);

            int tries = 0;
            address = IPAddress.Parse("127.0.0.1");
            IPEndPoint ep = new IPEndPoint(address, pport);
            while (tries < 10)
            {
                try
                {
                    sock.Bind(ep);
                    break;
                }
                catch (SocketException se)
                {
                    if (se.ErrorCode == 10048)
                    {
                        tries++;
                        port++;
                        ep.Port = port;
                        continue;
                    }
                    else
                        throw;
                }
            }
            if (tries == 10)
            {
                Console.WriteLine("Error: bind");
                return;
            }

            try
            {
                sock.Listen(1);
            }
            catch (SocketException se)
            {
                sock.Close();
                Console.WriteLine("Error: listen");
                return;
            }

            Console.WriteLine("port = {0}", ((IPEndPoint)sock.RemoteEndPoint).Port.ToString());
            if (!sock.Poll(60 * 1000, SelectMode.SelectRead))
            {
                Console.WriteLine("Error: select");
                sock.Close();
                return;
            }

            Socket asock = sock.Accept();

            if (asock == null)
            {
                Console.WriteLine("Error: accept");
                sock.Close();
                return;
            }

            sock.Close();

            // Got a valid connection to a socket. Now set it for PacketIF.
            socket = asock;

            return;

        }

        private void connectAsClient(String host, int port, bool local)
        {
            Debug.Assert(host != null);

            if (socket == null)
                socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream,
                        ProtocolType.Tcp);

            try
            {
                socket.Connect(host, port);
            }
            catch (Exception e)
            {
                socket.Close();
                socket = null;
                error = true;
                return;
            }

            // May need to set some of the socket behavior here.

        }

        private void installInputHandler() {
            Debug.Assert(Deleting == false);
            Debug.Assert(socket != null);

            ThreadWorker tw = new ThreadWorker(this);
            Thread t = new Thread(new ThreadStart(tw.watchForActivity));
            t.Priority = ThreadPriority.BelowNormal;
            t.IsBackground = true;
            t.Name = "WatchActivity";
            t.Start();
        }

        private void removeInputHandler()
        {
            deleting = true;
        }

        public bool InputIdleWP()
        {
            if (isPacketHandlingStalled())
            {
                Debug.Assert(stallingWorker != null);
                Debug.Assert(deferPacketHandling);
                if (stallingWorker(stallingWorkerData))
                {
                    stallingWorker = null;
                    deferPacketHandling = false;
                    packetReceive(false);
                }
            }
            else
                deferPacketHandling = false;

            PacketIF pif = DXApplication.theDXApplication.getPacketIF();
            if (pif.output_queue.Count != 0)
                pif.QueuedPacketWP();

            return (!deferPacketHandling);
        }

        public void ProcessSocketInputICB()
        {
            if (socket == null)
                return;

            packetReceive();

            if (socket == null)
                return;

            if (error)
            {
                handleStreamError("ProcessSocketInputICB");
                deferPacketHandling = false;
            }
            else
            {
                deferPacketHandling = true;
                InputIdleWP();
            }
        }


        #endregion

        #region protected Instance Variables

        protected String line;
        protected List<PacketHandler> handlers = new List<PacketHandler>();

        #endregion

        #region protected Methods

        protected virtual void parsePacket()
        {
            int id;
            int type;
            int data_length;
            int i = 0;
            int j;
            int k;

            List<String> toks = Utils.StringTokenizer(line, "|", null);

            if (toks.Count < 4)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Format error encountered in packet.");
                return;
            }

            id = Convert.ToInt32(toks[0]);

            for (type = 0; i < PacketTypes.Length; type++)
            {
                if (toks[1] == PacketTypes[type])
                    break;
            }
            if (type >= PacketTypes.Length)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Unknown packet type \"{0}\" encountered", toks[1]);
                return;
            }

            data_length = Convert.ToInt32(toks[2]);

            // Skip past the fourth vertical bar and extract the data.
            bool iocerr = false;
            int ioc = line.IndexOf('|');
            if (ioc < 0)
                iocerr = true;
            ioc = line.IndexOf('|', ioc + 1);
            if (ioc < 0)
                iocerr = true;
            ioc = line.IndexOf('|', ioc + 1);
            if (ioc < 0)
                iocerr = true;
            ioc = line.IndexOf('|', ioc + 1);
            if (ioc < 0)
                iocerr = true;
             
            String data = line.Substring(ioc+1, data_length);

            if ((line.ToCharArray())[ioc + data_length + 1] != '|' || iocerr)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Unknown packet type \"{0}\" encountered", toks[1]);
                return;
            }


            if (echoCallback != null)
            {
                String s = String.Format("Received {0}:{1}: {2}",
                    PacketIF.PacketTypes[type], id, data);
                echoCallback(echoClientData, s);
            }

            char [] pakws = {' ', ':'};
            data.TrimStart(pakws);

            PacketHandler ph = null;

            //
            // Check for strings that exactly match the handler's match string 
            // (In the case of data-driven interactors, there will never be an
            // exact match.)
            //
            foreach (PacketHandler h in handlers)
            {
                if (h.MatchString != null &&
                    ((h.Number == id && ((int) h.Type == type || (int) h.Type == -1)) ||
                    (h.Number == 0 && (int) h.Type == type)) &&
                    h.match(data))
                {
                    ph = h;
                    break;
                }
            }

            //
            // If we didn't find an exact match, then check for strings that match 
            // the handler's match string for the length of the match string.
            //
            if (ph == null)
            {
                int longest_match_so_far = 0;
                PacketHandler best_handler = null;
                foreach (PacketHandler h in handlers)
                {
                    if (h.MatchString != null &&
                        (((int) h.Type == id && ((int)h.Type == type || (int)h.Type == -1)) ||
                        (h.Number == 0 && (int)h.Type == type)) &&
                        h.matchFirst(data))
                    {
                        int len = h.MatchString.Length;
                        if (len > longest_match_so_far)
                        {
                            best_handler = h;
                            longest_match_so_far = len;
                        }
                    }
                }
                ph = best_handler;
            }

            //
            // If we still didn't find an match, then check for handlers that don't
            // have match string specified, implying they match any string.
            //
            if (ph == null)
            {
                foreach (PacketHandler h in handlers)
                {
                    if (h.MatchString == null &&
                        ((h.Number == id && ((int)h.Type == type || (int)h.Type == -1)) ||
                        (h.Number == 0 && (int)h.Type == type)))
                    {
                        ph = h;
                        break;
                    }
                }
            }

            if (ph != null)
            {
                ph.callCallback(id, data);
                if (!ph.Linger)
                {
                    handlers.Remove(ph);
                }
            }
        }

        //
        // Handle stream read/write errors.  We handle SIGPIPE/EPIPE specially.
        // SIGPIPE is ignored and then if we get an EPIPE on a write, then we
        // know the server or other connect has gone away.
        // The errnum is passed in for portability, but is ignored on UNIX
        // systems.
        //
        protected void handleStreamError(String msg)
        {
            Object errorData;
            PacketIFCallback cb = getErrorCallback(out errorData);
            if (cb != null)
            {
                cb(errorData, "Connection to the server has been broken.");
            }
            else
                Console.WriteLine("Connection to the server has been broken.");

            error = true;

            socket.Close();
            socket = null;

        }

        //
        // Receive a packet.
        // If readSocket is FALSE, then we just process packets that are still
        // in the line buffer.
        //
        protected void packetReceive()
        {
            packetReceive(true);
        }

        protected void packetReceive(bool readSocket)
        {
            byte [] buffer = new byte[4097];
            int buflen;

            if (readSocket)
            {

                if (socket.Available <= 0)
                    return;

                buflen = socket.Receive(buffer);
                if (buflen <= 0)
                {
                    error = true;
                    return;
                }
            }
            else
            {
                Debug.Assert(!deferPacketHandling);
                buffer = Encoding.ASCII.GetBytes(line);
                buflen = line.Length;
                line = "";
            }

            // Got the buffer, now look for a new line character.
            // If it exists then we now have a complete line that 
            // needs to be parsed. If we don't, just add the buffer
            // to line. Don't forget about the left over data in
            // buffer.

            String curline = Encoding.ASCII.GetString(buffer).TrimEnd(new char[] { '\0' });


            while (!deferPacketHandling)
            {
                if (curline.Length <= 0)
                    break;

                if (curline.Contains("\n"))
                {
                    int posN = curline.IndexOf('\n');
                    line += curline.Substring(0, posN);
                    curline = curline.Substring(posN + 1);
                    parsePacket();
                    line = "";
                }
                else
                    line += curline;
            }

            //
            // If we didn't finish the buffer (because of a stalling of the packet
            // handling), then concatenate onto the existing
            // line for retrieve later (see above).
            //
            if (curline.Length > 0)
            {
                Debug.Assert(isPacketHandlingStalled());
                Debug.Assert(line.Length == 0);
                line = curline;
            }
        }

        //
        // Routines to handle PacketIF messages.
        //
        protected static void ProcessMessage(Object clientData, int id, Object line)
        {
            throw new Exception("Never Implemented.");
        }
        protected static void ProcessInformation(Object clientData, int id, Object line)
        {
            throw new Exception("Never Implemented.");
        }
        protected static void ProcessError(Object clientData, int id, Object line)
        {
            throw new Exception("Never Implemented.");
        }
        protected static void ProcessErrorWARNING(Object clientData, int id, Object line)
        {
            throw new Exception("Never Implemented.");
        }
        protected static void ProcessErrorERROR(Object clientData, int id, Object p)
        {
            throw new Exception("Never Implemented.");
        }
        protected static void ProcessCompletion(Object clientData, int id, Object line)
        {
            throw new Exception("Never Implemented.");
        }
        protected static void ProcessInterrupt(Object clientData, int id, Object line)
        {
            throw new Exception("Never Implemented.");
        }
        protected static void ProcessBeginExecNode(Object clientData, int id, Object line)
        {
            throw new Exception("Never Implemented.");
        }
        protected static void ProcessEndExecNode(Object clientData, int id, Object line)
        {
            throw new Exception("Never Implemented.");
        }
        protected static void ProcessLinkCommand(Object clientData, int id, Object p)
        {
            throw new Exception("Never Implemented.");
        }
        protected static void HandleError(Object clientData, String message)
        {
            throw new Exception("Never Implemented.");
        }

        protected LinkHandler linkHandler;
        protected virtual void installLinkHandler()
        {
            linkHandler = new LinkHandler(this);
        }

        //
        // Queue outgoing messages in order to avoid deadlock with dxexec
        //
        public void _sendBytes(String str)
        {
            if (socket == null)
                return;

            try
            {
                if (!socket.Poll(10000, SelectMode.SelectWrite))
                {
                    handleStreamError("Unable to write to socket.");
                }
                socket.Send(Encoding.ASCII.GetBytes(str));
            }
            catch (SocketException se)
            {
                handleStreamError(se.Message);
            }

            if (echoCallback != null)
                echoCallback(echoClientData, str);
        }

        public void _sendImmediate(String str)
        {
            if (socket == null)
                return;

            String newStr = "$" + str + "\n";
            try
            {
                socket.Send(Encoding.ASCII.GetBytes(newStr));
            }
            catch (Exception e)
            {
                handleStreamError(e.Message);
            }
            if (echoCallback != null)
            {
                String echo_string = "-1: " + newStr + newStr.Length;
                echoCallback(echoClientData, echo_string);
            }
        }

        public void _sendPacket(PacketType type, int packetId, String data)
        {
            if (socket == null)
                return;

            String s;
            if (data.Length > 0)
                s = String.Format("{0}|{1}|{2}|{3}\n", packetId,
                PacketIF.PacketTypes[(int)type],
                data.Length,
                data);
            else
                s = String.Format("{0}|{1}|{2}\n", packetId,
                    PacketIF.PacketTypes[(int)type], 0);
            try
            {
                socket.Send(Encoding.ASCII.GetBytes(s));
            }
            catch (Exception e)
            {
                this.handleStreamError(e.Message);
            }

            if (echoCallback != null)
            {
                String echo_string =
                    String.Format("(0} [{1}]: ", packetId, PacketIF.PacketTypes[(int)type]);
                if (data != null && data.Length > 0)
                    echo_string += data + data.Length;
                echoCallback(echoClientData, echo_string);
            }
        }

        protected bool isSocketInputReady()
        {
            return (socket.Available > 0);
        }

        protected List<QueuedBytes> output_queue;

        #endregion

    }
}
