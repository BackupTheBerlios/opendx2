// This is the main DLL file.

#include "stdafx.h"
#include "WinDX.h"

using namespace System;
using namespace WinDX;
using namespace System::Runtime::InteropServices;

void DXExec::SetupCommandLine(System::String *args[]) {
	if(dxe)
		delete dxe;

	System::String __gc* allargs[];
	dxe = new DXEnvironment();

	if(args != NULL) {
		System::String* arguments[] = Environment::GetCommandLineArgs();
		allargs = __gc new System::String*[arguments->Length + args->Length];
		for(int i=0; i < arguments->Length; i++)
			allargs[i] = arguments[i];
		for(int i=0; i < args->Length; i++)
			allargs[i+arguments->Length] = args[i];
	} else {
		allargs = Environment::GetCommandLineArgs();
	}

	char **argv = new char*[allargs->Length];

	for(int i=0; i< allargs->Length; i++) {
		argv[i] = new char[allargs[i]->Length + 1];
		strncpy(argv[i], 
			(const char*) (Marshal::StringToHGlobalAnsi(allargs[i])).ToPointer(),
			allargs[i]->Length);
		argv[i][allargs[i]->Length] = '\0';
	}
	dxe->Setup(allargs->Length, argv);
}

void DXExec::InitSockets() {
	WSADATA wsadata;
	int i;

	i = WSAStartup(MAKEWORD(1,1),&wsadata);
	if (i!=0) {
		MessageBox(NULL, TEXT("Unable to initalize executive networking. Now exiting."),
			TEXT("Network Error"), MB_OK | MB_ICONERROR);
		throw "Unable to initialize sockets" ;
	}

}

int DXExec::Start() {

	SetupCommandLine(NULL);
	InitSockets();

	dx = new DXExecThread();

	int exargc; char **exargv = NULL;
	exargc = dxe->getExArgs(exargv);


	dx->Start(exargc, exargv);
	return 0;
}

IntPtr DXExec::StartThread() {
	if(!dxe)
		SetupCommandLine(NULL);

	InitSockets();

	if(dx)
		return dx->GetThreadHandle();

	dx = new DXExecThread();

	int exargc; char __nogc **exargv = NULL;
	exargc = dxe->getExArgs(exargv);

	return dx->StartAsThread(exargc, exargv);
}

IntPtr DXExec::StartThread(System::String *args[]) {
	SetupCommandLine(args);

	InitSockets();

	if(dx)
		return dx->GetThreadHandle();

	dx = new DXExecThread();

	int exargc; char **exargv = NULL;
	exargc = dxe->getExArgs(exargv);

	return dx->StartAsThread(exargc, exargv);
}

bool DXExec::isExecOnly() {
	if(!dxe)
		SetupCommandLine(NULL);

	return dxe->isExecOnly();
}

int DXExec::ExitThread() {
	dx->Terminate();
	return 0;
}

IntPtr DXExec::GetImageWindowHandle(System::String *name) {

	const char* str = (const char*) (Marshal::StringToHGlobalAnsi(name)).ToPointer();

	return dx->GetImageWindowHandle(str);
}

DXExec::DXExec() { 
	try {
		__crt_dll_initialize();
	} catch(System::Exception* e) {
		Console::WriteLine(e->Message);
	}
	dxe = NULL;
	dx = NULL;
}

DXExec::~DXExec() {
	if(dxe)
		delete dxe;
	if(dx)
		delete dx;
	try {
		__crt_dll_terminate();
	} catch(System::Exception* e) {
		Console::WriteLine(e->Message);
	}
}



BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID 
lpvReserved) {
	// This exists to provide the entry point into the DLL. It must
	// exist even though it performs nothing.
	return TRUE;
} /* DllMain */
