//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/CDFChoice.C,v 1.1 1999/04/05 13:33:33 gda Exp $
 */

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
