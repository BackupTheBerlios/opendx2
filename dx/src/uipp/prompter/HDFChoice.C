/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#include "HDFChoice.h"
#include "GARApplication.h"


boolean HDFChoice::ClassInitialized = FALSE;
String HDFChoice::DefaultResources[] =
{
    NUL(char*)
};


void HDFChoice::initialize() 
{
    if (HDFChoice::ClassInitialized) return ;
    HDFChoice::ClassInitialized = TRUE;
    this->setDefaultResources
	(theApplication->getRootWidget(), TypeChoice::DefaultResources);
    this->setDefaultResources
	(theApplication->getRootWidget(), ImportableChoice::DefaultResources);
    this->setDefaultResources
	(theApplication->getRootWidget(), HDFChoice::DefaultResources);
}



