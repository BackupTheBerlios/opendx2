/*  Open Visualization Data Explorer Source File */



#include "NetCDFChoice.h"
#include "GARApplication.h"

boolean NetCDFChoice::ClassInitialized = FALSE;
String NetCDFChoice::DefaultResources[] =
{
    NUL(char*)
};

void NetCDFChoice::initialize() 
{
    if (NetCDFChoice::ClassInitialized) return ;
    NetCDFChoice::ClassInitialized = TRUE;
    this->setDefaultResources
	(theApplication->getRootWidget(), TypeChoice::DefaultResources);
    this->setDefaultResources
	(theApplication->getRootWidget(), ImportableChoice::DefaultResources);
    this->setDefaultResources
	(theApplication->getRootWidget(), NetCDFChoice::DefaultResources);
}

