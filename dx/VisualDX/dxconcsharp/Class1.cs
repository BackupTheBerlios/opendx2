using System;
using System.Threading;
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
		static void Main(string[] args)
		{
			WinDX.DXExec dx = new DXExec();
			if(dx.isExecOnly()) 
			{
				dx.Start();
			} 
			else 
			{
				string[] addargs = {"-execonly"};
				dx.StartThread(addargs);
				WinDXL.DXLink dxl = new DXLink();
				if(dxl.ConnectToRunningServer(1900)) 
				{
					Console.WriteLine("Connected to Server");
					if(dxl.LoadVisualProgram("C:/Progra~1/OpenDX/samples/programs/AutoColor.net") == DXLink.OK)
						if(dxl.ExecuteOnce() == DXLink.OK)
							while(true);
					dxl.CloseConnection();

				}
				else
					Console.WriteLine("Didn't connect to Server");
				
				
			}
		}
	}
}
