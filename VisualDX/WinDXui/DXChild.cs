using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Net;
using WinDX;

namespace WinDX.UI
{
    public class DXChild
    {
        private String server;
        private StreamReader stdin;
        private StreamWriter stdout;
        private StreamWriter stderr;
        private int child;
        private DXExec dxexec; 
        private int queued;
        private String errorString = null;
        private int lineSize;
        private String outLine;
        private String errLine;
        private bool input_handlers_stalled;

        private int ConnectTo(String host, String user, String cwd, String[] av, ref String errstr)
        {
            if (!HostIsLocal(host))
                throw new Exception("Remote hosting not yet available.");

            if (user != null)
                Console.WriteLine("Different user on local machine ignored.");

            dxexec = new DXExec();
            try
            {
                //child = (int) dxexec.StartThread(av);
            }
            catch (Exception)
            {
                errstr = "Unable to start Exec.";
                return (-1);
            }

            return child;
        }

        private void MakeLine(String str, String newStr)
        {
            throw new Exception("Not Yet Implemented");
        }

        private bool StartExecutive(String host, String user, String cwd, String[] args,
            bool block)
        {
            String errStr = null;
            bool result = false;
            int child = -1;

            // Break up command over spaces and quotes.

            child = ConnectTo(host, user, cwd, args, ref errStr);

            if (errStr != null && errStr.Length > 0)
                this.errorString = errStr;

            if (!block)
            {
                result = (child != -1);
            }

            if (block && result)
                queued = 1;
            else
                queued = 0;

            return result;
        }

        public DXChild(String host, String[] args)
        {
            lineSize = 1000;
            outLine = "";
            errLine = "";
            input_handlers_stalled = false;
            server = host;
            StartExecutive(host, null, null, args, false);
        }
        public DXChild(String host, String[] args, bool block)
        {
            lineSize = 1000;
            outLine = "";
            errLine = "";
            input_handlers_stalled = false;
            server = host;
            StartExecutive(host, null, null, args, block);
        }
        public DXChild(String host, String[] args, bool block, String user)
        {
            lineSize = 1000;
            outLine = "";
            errLine = "";
            input_handlers_stalled = false;
            server = host;
            StartExecutive(host, user, null, args, block);
        }
        public DXChild(String host, String[] args, bool block, String user, String cwd)
        {
            lineSize = 1000;
            outLine = "";
            errLine = "";
            input_handlers_stalled = false;
            server = host;
            StartExecutive(host, user, cwd, args, block);
        }

        ~DXChild()
        {
            throw new Exception("Not Yet Implemented");
        }

        public StreamReader StdInput { get { return stdin; } }
        public StreamWriter StdOutput { get { return stdout; } }
        public StreamWriter StdErr { get { return stderr; } }

        public void closeOutput() { closeOutput(true); }
        public void closeOutput(bool closeConnection)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void closeError() { closeError(true); }
        public void closeError(bool closeConnection)
        {
            throw new Exception("Not Yet Implemented");
        }

        public int waitForConnection()
        {
            return 0;
        }

        public int IsQueued { get { return queued; } }
        public void unQueue() { throw new Exception("Not Yet Implemented"); }
        public String failed() { return errorString; }
        public String getServer() { return server; }
        public static bool HostIsLocal(String host)
        {
            if (host == "localhost" || host == "localPC")
                return true;

            if (Dns.GetHostName() == host)
                return true;

            IPAddress[] ips = Dns.GetHostAddresses("localhost");
            IPHostEntry iphe = Dns.GetHostEntry(host);

            foreach (IPAddress ipa in ips)
            {
                foreach (IPAddress iph in iphe.AddressList)
                    if (iph == ipa)
                        return true;
            }

            return false;
        }
        public void setServer(String s)
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
