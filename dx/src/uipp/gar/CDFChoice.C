//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/gar/Attic/CDFChoice.C,v 1.1 1999/03/24 15:17:27 gda Exp $
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
