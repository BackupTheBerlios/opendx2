// Completed 4/04/2006
// Last Edited 4/04/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    class ApplicIF : PacketIF
    {
        #region protected Methods

        protected static void ApplicationMessage(Object clientData, int id, String line)
        {
            // blank method in current C++ version
        }
        protected static void ApplicationInformation(Object clientData, int id, String line)
        {
            // blank method in current C++ version
        }
        protected static void ApplicationError(Object clientData, int id, String line)
        {
            // blank method in current C++ version
        }
        protected static void ApplicationCompletion(Object clientData, int id, String line)
        {
            // blank method in current C++ version
        }
        protected static void ApplicationForeground(Object clientData, int id, String line)
        {
            // blank method in current C++ version
        }
        protected static void ApplicationQuery(Object clientData, int id, String line)
        {
            // blank method in current C++ version
        }
        protected static void ApplicationLink(Object clientData, int id, String line)
        {
            ApplicIF app_if = (ApplicIF)clientData;
            app_if.executeLinkCommand(line, id);
        }
        protected static void HandleApplicationError(Object clientData, String message)
        {
            DXApplication app = (DXApplication)clientData;
            if (app != null)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post(message, null);
                app.disconnectFromApplication(true);
            }
        }
        protected static void PassThruDXL(Object clientData, int id, String line)
        {
            ApplicIF ai = (ApplicIF)clientData;
            ai.sendPacket(PacketIF.PacketType.LINK, 0, line);
        }

        protected override void installLinkHandler()
        {
            linkHandler = new DXLinkHandler(this);
        }

        protected override void parsePacket()
        {
            Regex rx = new Regex(@"^\s+\$.*$");
            if (rx.IsMatch(line))
            {
                Object data = null;
                PacketIFCallback cb = this.getEchoCallback(ref data);
                if (cb != null)
                {
                    cb(data, "Received " + line);
                }
                this.executeLinkCommand(line, 0);
            }
            else
                base.parsePacket();
        }


        #endregion
        #region public Methods

        public ApplicIF(String server, int port, bool local)
            : base(server, port, local, false)
        {
            DXPacketIF pif = DXApplication.theDXApplication.getPacketIF();
            if (pif != null)
                this.handleServerConnection();
        }

        //
        // Initializer
        //
        public override void initializePacketIO()
        {
            this.setHandler(PacketIF.PacketType.MESSAGE,
                ApplicIF.ApplicationMessage, this);
            this.setHandler(PacketIF.PacketType.INFORMATION,
                ApplicIF.ApplicationInformation, this);
            this.setHandler(PacketIF.PacketType.PKTERROR,
                ApplicIF.ApplicationError, this);
            this.setHandler(PacketIF.PacketType.COMPLETE,
                ApplicIF.ApplicationCompletion, this);
            this.setHandler(PacketIF.PacketType.FOREGROUND,
                ApplicIF.ApplicationForeground, this);
            this.setHandler(PacketIF.PacketType.LINQUIRY,
                ApplicIF.ApplicationQuery, this);
            this.setHandler(PacketIF.PacketType.LINK,
                ApplicIF.ApplicationLink, this);
            this.setErrorCallback(ApplicIF.HandleApplicationError,
                DXApplication.theDXApplication);
        }

        //
        // Do what ever is necessary when a connection to the server
        // (theDXApplication->getPacketIF()) has been established.
        //
        public void handleServerConnection()
        {
            DXPacketIF pif = DXApplication.theDXApplication.getPacketIF();
            if (pif != null)
            {
                pif.setHandler(PacketIF.PacketType.LINK,
                    ApplicIF.PassThruDXL,
                    this, "LINK:  DXLOutput");
            }
        }

        public void send(PacketIF.PacketType type, String data)
        {
            this.sendPacket(type, 0, data);
        }

        #endregion

    }

}
