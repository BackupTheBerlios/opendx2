/*  Open Visualization Data Explorer Source File */


#include "CDFChoice.h"
#include "GARApplication.h"

boolean CDFChoice::ClassInitialized = FALSE;
String CDFChoice::DefaultResources[] =
{
    NUL(char*)
};

void CDFChoice::initialize()
{
    if (!CDFChoice::ClassInitialized) {
	CDFChoice::ClassInitialized = TRUE;
	this->setDefaultResources
	    (theApplication->getRootWidget(), TypeChoice::DefaultResources);
	this->setDefaultResources
	    (theApplication->getRootWidget(), ImportableChoice::DefaultResources);
	this->setDefaultResources
	    (theApplication->getRootWidget(), CDFChoice::DefaultResources);
    }
}
