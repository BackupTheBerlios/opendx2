/*  Open Visualization Data Explorer Source File */



#include "DXChoice.h"
#include "GARApplication.h"


boolean DXChoice::ClassInitialized = FALSE;
String DXChoice::DefaultResources[] =
{
    NUL(char*)
};


void DXChoice::initialize() 
{
    if (!DXChoice::ClassInitialized) {
	DXChoice::ClassInitialized = TRUE;
	this->setDefaultResources
	    (theApplication->getRootWidget(), TypeChoice::DefaultResources);
	this->setDefaultResources
	    (theApplication->getRootWidget(), ImportableChoice::DefaultResources);
	this->setDefaultResources
	    (theApplication->getRootWidget(), DXChoice::DefaultResources);
    }
}

