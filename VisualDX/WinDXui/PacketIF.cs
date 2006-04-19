// Last Edited 4/03/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace WinDX.UI
{
    class PacketIF
    {
        
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
        public static String[] PacketTypes;

        #endregion

        #region public Methods

        public PacketIF(String server, int port, bool local, bool asClient)
        {
            throw new Exception("Not Yet Implemented.");
        }

        public virtual void initializePacketIO()
        {
            throw new Exception("Not Yet Implemented.");
        }

        public int inError() { return this.error; }

        public void setHandler(PacketIF.PacketType type, PacketHandlerCallback callback, Object clientdata)
        {
            this.setHandler(type, callback, clientdata, null);
        }
        public void setHandler(PacketIF.PacketType type, PacketHandlerCallback callback,
            Object clientData,
            String matchString)
        {
            throw new Exception("Not Yet Implemented");
        }

        //
        // Error and echo handling callbacks.  Echos are not performed if no
        // callback has been set up.  Errors are dumped to stderr if nothing
        // has been set up.
        //
        public void setErrorCallback(PacketIFCallback callback, Object clientData)
        {
            throw new Exception("Not Yet Implemented");
        }
        public PacketIFCallback getErrorCallback(ref Object clientData)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setEchoCallback(PacketIFCallback callback, Object clientData)
        {
            throw new Exception("Not Yet Implemented");
        }
        public PacketIFCallback getEchoCallback(ref Object clientData)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void sendBytes(String str)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void sendImmediate(String str)
        {
            throw new Exception("Not Yet Implemented");
        }

        //
        // Return TRUE if there was NOT a packet error.
        // If returning TRUE and data!=NULL, then *data is set to the value 
        // passed to the endReceiveContinuous() call.
        //
        public bool receiveContinuous(ref String data)
        {
            throw new Exception("Not Yet Implemented");
        }

        //
        // Terminates receiveContinuous() and causes it to set its *data to
        // the data value passed in.
        //
        public void endReceiveContinuous(String data)
        {
            throw new Exception("Not Yet Implemented");
        }


        public void executeLinkCommand(String c, int id)
        {
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
        }
        public bool isPacketHandlingStalled()
        {
            throw new Exception("Not Yet Implemented");
        }

        public void sendPacket(int type, int packetId, String data, int length)
        {
            throw new Exception("Not Yet Implemented.");
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

        int error;
        Socket socket;
        //XtInputId inputHandlerId;
        bool deferPacketHandling;
        int line_length;
        int alloc_line_length;

        bool endReceiving;

        #endregion

        #region private Methods


        // Open a socket port and wait for a client to connect.
        // This opens 2 sockets (except on the server), one internet domain, and
        // one unix domain.  It then selects on both sockets to see to which one the
        // app connects, and returns the new connection, closing the one not
        // selected.

        private void connectAsServer(int pport)
        {
            throw new Exception("Not Yet Implemented.");
        }

        private void connectAsClient(String host, int port, bool local)
        {
            throw new Exception("Not Yet Implemented.");
        }

        #endregion

        #region protected Instance Variables

        protected String line;

        #endregion

        #region protected Methods

        protected virtual void parsePacket()
        {
            throw new Exception("Not Yet Implemented.");
        }

        //
        // Handle stream read/write errors.  We handle SIGPIPE/EPIPE specially.
        // SIGPIPE is ignored and then if we get an EPIPE on a write, then we
        // know the server or other connect has gone away.
        // The errnum is passed in for portability, but is ignored on UNIX
        // systems.
        //
        protected void handleStreamError(int errnum, String msg)
        {
            throw new Exception("Not Yet Implemented.");
        }

        //
        // Receive a packet.
        // If readSocket is FALSE, then we just process packets that are still
        // in the line buffer.
        //
        protected void packetReceive(bool readSocket)
        {
            throw new Exception("Not Yet Implemented.");
        }

        //
        // Routines to handle PacketIF messages.
        //
        protected static void ProcessMessage(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected static void ProcessInformation(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected static void ProcessError(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected static void ProcessErrorWARNING(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected static void ProcessErrorERROR(Object clientData, int id, Object p)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected static void ProcessCompletion(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected static void ProcessInterrupt(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected static void ProcessBeginExecNode(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected static void ProcessEndExecNode(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected static void ProcessLinkCommand(Object clientData, int id, Object p)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected static void HandleError(Object clientData, String message)
        {
            throw new Exception("Not Yet Implemented.");
        }

        protected LinkHandler linkHandler;
        protected virtual void installLinkHandler()
        {
            throw new Exception("Not Yet Implemented");
        }

        //
        // Queue outgoing messages in order to avoid deadlock with dxexec
        //
        protected void _sendBytes(String str)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected void _sendImmediate(String str)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected void _sendPacket(int type, int packetId, String data, int length)
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected bool sendQueuedPackets()
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected bool isSocketInputReady()
        {
            throw new Exception("Not Yet Implemented.");
        }
        protected List<QueuedPacket> output_queue;
        protected int output_queue_wpid;

        #endregion

    }
}
