//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/gar/Attic/HDFChoice.C,v 1.1 1999/03/24 15:17:27 gda Exp $
 */

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



