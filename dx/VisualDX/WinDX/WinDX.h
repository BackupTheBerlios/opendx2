// WinDX.h

#pragma once

#include "../../src/exec/dpexec/dxThreadMain.h"
#include "../../src/exec/dpexec/tmainUtil.h"
#include "_vcclrit.h"

#using <mscorlib.dll>
using namespace System;

typedef struct DXLConnection DXLConnection;
typedef int DXLError;

namespace WinDX
{

	public __gc class DXExec
	{
	private:
		DXEnvironment __nogc* dxe;
		DXExecThread __nogc* dx;
		void SetupCommandLine(System::String *args[]);
		void InitSockets();

	
	public:

		int Start();
		IntPtr StartThread();
		IntPtr StartThread(System::String *args[]);
		bool isExecOnly();
		int ExitThread();
		IntPtr GetImageWindowHandle(System::String *name);
		DXExec();
		~DXExec();
	};

}
