//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/DXChoice.C,v 1.1 1999/04/05 13:33:34 gda Exp $
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

