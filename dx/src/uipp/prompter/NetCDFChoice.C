//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/NetCDFChoice.C,v 1.1 1999/04/05 13:33:38 gda Exp $
 */


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

