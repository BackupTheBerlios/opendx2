// WinDXL.h

#pragma once
#pragma unmanaged
#include "../../dx/include/dxl.h"
#include "../../dx/src/uipp/dxl/dxlP.h"
#include "string.h"
#pragma managed
using namespace System;

#ifdef ERROR
#undef ERROR
#endif
#ifdef OK
#undef OK
#endif

namespace WinDXL
{

	public ref class DXLink {
	private:
		DXLConnection * connection;

	public:
		static const int ERROR = 0;
		static const int OK = 1;
		~DXLink();
		DXLink() { connection = 0; }
		//DXLink(int port, string *host) { ConnectToRunningServer(port, host); }
		void CloseConnection();

		bool ConnectToRunningServer(int port, System::String ^host);
		bool ConnectToRunningServer(int port);

		DXLError ExitDX();
		bool StartDX(System::String ^commandline, System::String ^host);
		bool StartDX(System::String ^commandline);
		
		//int DXLGetSocket(DXLConnection *conn);
		int SetMessageDebugging(bool on);
		//void DXLSetSynchronization(DXLConnection *conn, const int onoff);
		//DXLConnection *DXLStartDX(const char *string, char *host);
		//void DXLSetBrokenConnectionCallback(DXLConnection *conn, void (*proc) (DXLConnection *, void *), void *data);

		DXLError LoadVisualProgram(System::String^ file);
		DXLError ExecuteOnce();
		bool IsMessagePending();
		DXLError GetExecutionStatus(int ^state);
		DXLError HandlePendingMessages();
		void RegisterErrorHandler();
	};
}