// The DXLink wrapper code.

#include "stdafx.h"
#include "WinDXL.h"
#include <stdio.h>

using namespace System;
using namespace WinDXL;
using namespace System::Runtime::InteropServices;

DXLink::~DXLink() {
	if(connection)
		ExitDX();
}

void DXLink::CloseConnection() {
	if(connection) {
		DXLCloseConnection(connection);
		connection = 0;
	}
}

#pragma unmanaged
void ErrorPrinter(DXLConnection *conn, const char *msg, void *data) {
	printf("DXLError: %s\n", msg);
	throw "DXL Error";
}
#pragma managed

void DXLink::RegisterErrorHandler() {
	int ret = DXLSetErrorHandler(connection, ErrorPrinter, NULL);
	printf("Error Handler Set: %d\n", ret);
}

bool DXLink::ConnectToRunningServer(int port) {
	connection = DXLConnectToRunningServer(port, NULL);
	if(connection){
		connection->in = -1;
		connection->out = -1;
		connection->err = -1;
		return true;
	}		
	else
		return false;
}

bool DXLink::ConnectToRunningServer(int port, System::String ^host) {
	char *hs = new char[host->Length+1];
	strncpy(hs, (const char*)(Marshal::StringToHGlobalAnsi(host)).ToPointer(),
		host->Length);
	hs[host->Length] = '\0';
	connection = DXLConnectToRunningServer(port, hs);
	if (connection) {
		connection->in = -1;
		connection->out = -1;
		connection->err = -1;
		return true;
	}		
	else
		return false;
}

DXLError DXLink::ExitDX() {
	if(connection) {
		DXLError ret = DXLExitDX(connection);
		connection = 0;
		return ret;
	}
	return OK;
}

int DXLink::SetMessageDebugging(bool on) {
	return DXLSetMessageDebugging(connection, on);
}

bool DXLink::StartDX(System::String ^commandline, System::String ^host) {

	char * cl = new char[commandline->Length+1];
	strncpy(cl, (const char*)(Marshal::StringToHGlobalAnsi(commandline)).ToPointer(),
		commandline->Length);
	cl[commandline->Length] = '\0';
	char *hs = new char[host->Length+1];
	strncpy(hs, (const char*)(Marshal::StringToHGlobalAnsi(host)).ToPointer(),
		host->Length);
	hs[host->Length] = '\0';

	connection = DXLStartDX(cl, hs);
	if(connection)
		return true;
	else
		return false;
}

bool DXLink::StartDX(System::String ^commandline) {

	char * cl = new char[commandline->Length+1];
	strncpy(cl, (const char*)(Marshal::StringToHGlobalAnsi(commandline)).ToPointer(),
		commandline->Length);
	cl[commandline->Length] = '\0';

	connection = DXLStartDX(cl, NULL);
	if(connection)
		return true;
	else
		return false;
}

DXLError DXLink::LoadVisualProgram(System::String ^ file) {
	if(connection) {
		char * filec = new char[file->Length+1];
		strncpy(filec, (const char*)(Marshal::StringToHGlobalAnsi(file)).ToPointer(),
			file->Length);
		filec[file->Length] = '\0';

		if(DXLLoadVisualProgram(connection, filec)==ERROR) {
			DXLHandlePendingMessages(connection);
			return ERROR;
		}
		return OK;
	} else
		return ERROR;
}

DXLError DXLink::ExecuteOnce() {
	if(connection)
		return DXLExecuteOnce(connection);
	else
		return ERROR;
}

bool DXLink::IsMessagePending() {
	if(connection){ 
		int ret = DXLIsMessagePending(connection);
		if (ret==0)
			return false;
		else
			return true;
	}
	return false;
}

DXLError DXLink::GetExecutionStatus(int ^state) {
	int a = 0;
	DXLError err = DXLGetExecutionStatus(connection, &a);
	if (err == OK) {
		state = a;
		return OK;
	}

	return ERROR;
}

DXLError DXLink::HandlePendingMessages() {
	return DXLHandlePendingMessages(connection);
}
