//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/gar/Attic/DXChoice.C,v 1.1 1999/03/24 15:17:27 gda Exp $
 */


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

