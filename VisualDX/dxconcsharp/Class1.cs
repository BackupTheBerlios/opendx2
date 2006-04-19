using System;
using System.Threading;
using System.Windows.Forms;
using WinDX;
using WinDXL;

namespace dxconcsharp
{
    /// <summary>
    /// Summary description for Class1.
    /// </summary>
    class Class1
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]

        static void SyncAfterExecute(ref WinDXL.DXLink dxl) {
            int status = 1;
            while(status == 1) {
            System.Threading.Thread.Sleep(1000);
                if (dxl.IsMessagePending()) {
                    dxl.HandlePendingMessages();
                    dxl.GetExecutionStatus(status);
                }
            }
        }

        static void Main(string[] args)
        {
            WinDX.DXExec dx = new DXExec();
            if (dx.isExecOnly())
            {
                dx.Start();
            }
            else
            {
                string[] addargs = { "-execonly" };
                dx.StartThread(addargs);
                WinDXL.DXLink dxl = new DXLink();
                if (dxl.ConnectToRunningServer(1900))
                {
                    dxl.RegisterErrorHandler();
                    Console.WriteLine("Connected to Server");
                    if (dxl.LoadVisualProgram("C:/Progra~1/OpenDX/samples/programs/AutoColor.net") == DXLink.OK)
                        if (dxl.ExecuteOnce() == DXLink.OK)
                        {
                            SyncAfterExecute(ref dxl);
                            MessageBox.Show("Image Displayed.", "Hold",
                                MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                            dxl.CloseConnection();
                        }

                }
                else
                    Console.WriteLine("Didn't connect to Server");


            }
        }
    }
}
