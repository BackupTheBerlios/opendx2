// Completed 4/22

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    public class DXPacketIF : PacketIF
    {
        protected int id;

        #region protected Methods
        //
        // Routines to handle dxexec messages.
        //
        protected static void DXProcessMessage(Object clientData, int id, String line)
        {
            String fds = Utils.FindDelimitedString(line, ':', ':', null);
            if (fds != null && fds.IndexOf("POPUP") >= 0)
            {
                int ioc = line.IndexOf(':');
                ioc = line.IndexOf(':', ioc + 1);
                String msg = line.Substring(ioc + 1);
                InfoDialog idg = new InfoDialog();
                idg.post(msg);
            }
            DXApplication.theDXApplication.MessageWindow.addInformation(line);
        }
        protected static void DXProcessInformation(Object clientData, int id, String line)
        {
            DXApplication.theDXApplication.MessageWindow.addInformation(line);
        }
        protected static void DXProcessError(Object clientData, int id, String line)
        {
            DXApplication.theDXApplication.MessageWindow.addError(line);
        }
        protected static void DXProcessErrorWARNING(Object clientData, int id, String line)
        {
            String fds = Utils.FindDelimitedString(line, ':', ':', null);
            if (fds != null && fds.IndexOf("POPUP") >= 0)
            {
                int ioc = line.IndexOf(':');
                ioc = line.IndexOf(':', ioc + 1);
                String msg = line.Substring(ioc + 1);
                WarningDialog wd = new WarningDialog();
                wd.post(msg);
            }

            if (fds != null && fds.IndexOf("MSGERRUP") >= 0)
            {
                if (DXApplication.theDXApplication.doesErrorOpenMessage &&
                    !DXApplication.theDXApplication.MessageWindow.Visible)
                {
                    DXApplication.theDXApplication.MessageWindow.Visible = true;
                    int ioc = line.IndexOf("MSGERRUP");
                    line = line.Substring(ioc + 8);
                }
            }

            DXApplication.theDXApplication.MessageWindow.addWarning(line);

        }
        protected static void DXProcessErrorERROR(Object clientData, int id, String line)
        {
            String fds = Utils.FindDelimitedString(line, ':', ':', null);
            if (fds != null && fds.IndexOf("POPUP") >= 0)
            {
                int ioc = line.IndexOf(':');
                ioc = line.IndexOf(':', ioc + 1);
                String msg = line.Substring(ioc + 1);
                ErrorDialog ed = new ErrorDialog();
                ed.post(msg);
            }

            DXApplication.theDXApplication.addErrorList(line);
            DXApplication.theDXApplication.MessageWindow.addError(line);
        }

        protected static void DXProcessCompletion(Object clientData, int id, String line)
        {
            // No functionality added - same as C++
        }
        protected static void DXProcessInterrupt(Object clientData, int id, String line)
        {
            Console.WriteLine("DX Interrupt({0}): {1}", id, line);
        }
        protected static void DXProcessBeginExecNode(Object clientData, int id, String line)
        {
            int ioc = line.IndexOf('/');
            Debug.Assert(ioc >= 0);

            line = line.Substring(ioc + 1);
            String name = DXApplication.theDXApplication.network.NameString;
            if (line.StartsWith(name))
                return;
            ioc = line.IndexOf('/');
            Debug.Assert(ioc >= 0);

            line = line.Substring(ioc + 1);

            DXApplication.theDXApplication.highlightNodes(line, 
                DXApplication.HighlightType.EXECUTEHIGHLIGHT);
        }
        protected static void DXProcessEndExecNode(Object clientData, int id, String line)
        {
            int ioc = line.IndexOf('/');
            Debug.Assert(ioc >= 0);

            line = line.Substring(ioc + 1);
            String name = DXApplication.theDXApplication.network.NameString;
            if (line.StartsWith(name))
                return;
            ioc = line.IndexOf('/');
            Debug.Assert(ioc >= 0);

            line = line.Substring(ioc + 1);

            DXApplication.theDXApplication.highlightNodes(line,
                DXApplication.HighlightType.REMOVEHIGHLIGHT);

        }
        protected static void DXProcessLinkCommand(Object clientData, int id, String line)
        {
            DXPacketIF pif = (DXPacketIF)clientData;

            //
            // Skip first two comma-separated args (processor num and LINK)
            //

            int ioc = line.IndexOf(':');
            ioc = line.IndexOf(':', ioc + 1);
            line = line.Substring(ioc + 1);
            line.TrimStart(null);

            if (pif.linkHandler == null)
                pif.installLinkHandler();

            pif.executeLinkCommand(line, id);
        }
        protected static void DXHandleServerError(Object clientData, String message)
        {
            DXPacketIF pif = (DXPacketIF)clientData;

            // Reset the internal application state.
            DXApplication.theDXApplication.packetIFCancel(pif);

            // Report the disconnection in the anchor window.
            ErrorDialog ed = new ErrorDialog();
            ed.post(message);
        }

        protected override void installLinkHandler()
        {
            linkHandler = new DXLinkHandler(this);
        }

        #endregion

        #region public

        //
        // Constructor:
        //
        public DXPacketIF(String server, int port, bool local) :
            base (server, port, local, true)
        {
            id = 0;
        }


        //
        // Initializer
        //
        public override void initializePacketIO()
        {
            setHandler(DXPacketIF.PacketType.MESSAGE,
                DXPacketIF.DXProcessMessage,
                this);
            setHandler(DXPacketIF.PacketType.INFORMATION,
                DXPacketIF.DXProcessInformation,
                this);
            setHandler(DXPacketIF.PacketType.INTERRUPT,
                DXPacketIF.DXProcessInterrupt,
                this);
            setHandler(DXPacketIF.PacketType.PKTERROR,
                DXPacketIF.DXProcessError,
                this);
            setHandler(DXPacketIF.PacketType.PKTERROR,
                DXPacketIF.DXProcessErrorWARNING,
                this,
                "WARNING");
            setHandler(DXPacketIF.PacketType.INTERRUPT,
                DXPacketIF.DXProcessBeginExecNode,
                this,
                "begin ");
            setHandler(DXPacketIF.PacketType.INTERRUPT,
                DXPacketIF.DXProcessEndExecNode,
                this,
                "end ");
            setHandler(DXPacketIF.PacketType.PKTERROR,
                DXPacketIF.DXProcessErrorERROR,
                this, "ERROR");
            setHandler(DXPacketIF.PacketType.LINK,
                DXPacketIF.DXProcessLinkCommand,
                this);
            setErrorCallback(DXPacketIF.DXHandleServerError,
                this);
        }

        public int send(PacketType type) { return send(type, null, null, null); }
        public int send(PacketType type, String data) { return send(type, data, null, null); }
        public int send(PacketType type, String data, PacketHandlerCallback callback)
        {
            return send(type, data, callback, null);
        }
        public int send(PacketType type, String data,
                 PacketHandlerCallback callback, Object clientData)
        {
            if (MySocket == null)
                return 0;

            id++;
            if (callback != null)
            {
                setWaiter(PacketType.COMPLETE, id, callback, clientData);
            }

            switch (type)
            {
                case PacketType.INTERRUPT:
                    sendPacket(type, id, "0");
                    break;
                case PacketType.MACRODEF:
                    break;
                default:
                    sendPacket(type, id, data);
                    break;
            }
            return id;
        }
        //
        // Routine to format a message and send it
        //
        public int sendFormat(PacketType type, String fmt, params Object[] par)
        {
            String buf = String.Format(fmt, par);
            int result = send(type, buf);

            return result;
        }

        public int sendMacroStart()
        {
            return sendMacroStart(null, null);
        }
        public int sendMacroStart(PacketHandlerCallback callback)
        {
            return sendMacroStart(callback, null);
        }
        public int sendMacroStart(PacketHandlerCallback callback, Object clientData)
        {
            if (MySocket == null)
                return 0;

            id++;

            if (callback != null)
            {
                setWaiter(PacketType.COMPLETE, id, callback, clientData);
            }

            String tmpbuf = String.Format("|{0}|{1}|{2}|", id, PacketTypes[(int)PacketType.MACRODEF],
                0);

            sendImmediate(tmpbuf);

            return id;
        }

        public void sendMacroEnd()
        {
            if (MySocket == null)
                return;

            sendImmediate("|\n");
        }

        public void setWaiter(PacketType type, int number,
                       PacketHandlerCallback callback,
                       Object clientData)
        {
            PacketHandler p = new PacketHandler(false,
                type, number, callback, clientData);

            handlers.Add(p);
        }

        #endregion
    }
}
