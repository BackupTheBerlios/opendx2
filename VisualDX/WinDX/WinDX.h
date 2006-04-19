// WinDX.h

#pragma once
#pragma unmanaged
#include "../../dx/src/exec/dpexec/dxThreadMain.h"
#include "../../dx/src/exec/dpexec/tmainUtil.h"
#pragma managed

#include <windows.h>

using namespace System;

typedef struct DXLConnection DXLConnection;
typedef int DXLError;


namespace WinDX
{

	public ref class DXExec
	{
	private:
		DXEnvironment * dxe;
		DXExecThread * dx;
		void SetupCommandLine(array<String^> ^args);
		void InitSockets();

	
	public:

		int Start();
		IntPtr StartThread();
		IntPtr StartThread(array<String^> ^args);
		bool isExecOnly();
		int ExitThread();
		IntPtr GetImageWindowHandle(String ^name);
		DXExec();
		~DXExec();
	};

}
