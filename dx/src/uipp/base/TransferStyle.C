//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/TransferStyle.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */

#include <Xm/Xm.h>
#include <Xm/AtomMgr.h>

#include "TransferStyle.h"
#include "Application.h"

TransferStyle::TransferStyle (int tag, const char *name, boolean preferred)
{
    ASSERT(name);
    this->preferred = preferred;
    this->atom = XmInternAtom (theApplication->getDisplay(), (String)name, False);
    this->atomName = theSymbolManager->registerSymbol(name);
    this->name = new char[1+strlen(name)];
    this->tag = tag;
    strcpy (this->name, name);
}


TransferStyle::~TransferStyle()
{
    delete this->name;
}

