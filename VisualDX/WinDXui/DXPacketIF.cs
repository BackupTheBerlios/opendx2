using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class DXPacketIF : PacketIF
    {
        protected int id;

        #region protected Methods
        //
        // Routines to handle dxexec messages.
        //
        protected static void DXProcessMessage(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected static void DXProcessInformation(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected static void DXProcessError(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected static void DXProcessErrorWARNING(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected static void DXProcessErrorERROR(Object clientData, int id, Object p)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected static void DXProcessCompletion(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected static void DXProcessInterrupt(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected static void DXProcessBeginExecNode(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected static void DXProcessEndExecNode(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected static void DXProcessLinkCommand(Object clientData, int id, Object p)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected static void DXHandleServerError(Object clientData, String message)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected override void installLinkHandler()
        {
            throw new Exception("Not Yet Implemented");
        }

        #endregion

        #region public

        //
        // Constructor:
        //
        public DXPacketIF(String server, int port, bool local) :
            base (server, port, local, true)
        {
            throw new Exception("Not Yet Implemented");
        }


        //
        // Initializer
        //
        public virtual void initializePacketIO()
        {
            throw new Exception("Not Yet Implemented");
        }

        public int send(int type) { return send(type, null, null, null); }
        public int send(int type, String data) { return send(type, data, null, null); }
        public int send(int type, String data, PacketHandlerCallback callback)
        {
            return send(type, data, callback, null);
        }
        public int send(int type, String data,
                 PacketHandlerCallback callback, Object clientData)
        {
            throw new Exception("Not Yet Implemented");
        }
        //
        // Routine to format a message and send it
        //
        public int sendFormat(int type, String fmt, params Object[] par)
        {
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
        }
        public void sendMacroEnd()
        {
            throw new Exception("Not Yet Implemented");
        }

        public void setWaiter(int type, int number,
                       PacketHandlerCallback callback,
                       Object clientData)
        {
            throw new Exception("Not Yet Implemented");
        }



        #endregion
    }
}
