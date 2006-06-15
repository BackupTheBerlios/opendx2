// This is the main DLL file.

#include "stdafx.h"
#include "WinDX.h"

#using <mscorlib.dll>

using namespace System;
using namespace WinDX;
using namespace System::Runtime::InteropServices;

// Pass in the array of args from the command line. 
// If args is null, then we will query the command line
// args and build it from that.
void DXExec::SetupCommandLine(array<String^> ^args) {
	if(dxe)
		delete dxe;

	array<System::String^> ^ allargs;
	dxe = new DXEnvironment();

	if(args && args->GetLength(0) != 0) {
		allargs = args;
	} else {
		allargs = Environment::GetCommandLineArgs();
	}

	char **argv = new char*[allargs->GetLength(0)];

	for(int i=0; i< allargs->GetLength(0); i++) {
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

	SetupCommandLine(nullptr);
	InitSockets();

	dx = new DXExecThread();

	int exargc; char **exargv = NULL;
	exargc = dxe->getExArgs(exargv);


	dx->Start(exargc, exargv);
	return 0;
}

IntPtr DXExec::StartThread() {
	if(!dxe)
		SetupCommandLine(nullptr);

	InitSockets();

	if(dx)
		return (IntPtr) dx->GetThreadHandle();

	dx = new DXExecThread();

	int exargc; char **exargv = NULL;
	exargc = dxe->getExArgs(exargv);

	return (IntPtr) dx->StartAsThread(exargc, exargv);
}

IntPtr DXExec::StartThread(array<String ^> ^args) {
	SetupCommandLine(args);

	InitSockets();

	if(dx)
		return (IntPtr) dx->GetThreadHandle();

	dx = new DXExecThread();

	int exargc; char **exargv = NULL;
	exargc = dxe->getExArgs(exargv);

	return (IntPtr) dx->StartAsThread(exargc, exargv);
}

bool DXExec::isExecOnly() {
	if(!dxe)
		SetupCommandLine(nullptr);

	return dxe->isExecOnly();
}

int DXExec::ExitThread() {
	dx->Terminate();
	return 0;
}

IntPtr DXExec::GetImageWindowHandle(String ^name) {

	const char* str = (const char*) (Marshal::StringToHGlobalAnsi(name)).ToPointer();

	return (IntPtr) dx->GetImageWindowHandle(str);
}

DXExec::DXExec() { 
	dxe = NULL;
	dx = NULL;
}

DXExec::~DXExec() {
	dx->Terminate();

	if(dxe)
		delete dxe;
	if(dx)
		delete dx;
}
