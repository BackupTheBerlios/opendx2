//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageSoftwareCommand.C,v 1.1 1999/03/24 15:17:42 gda Exp $
 */


#include "defines.h"
#include "ImageSoftwareCommand.h"
#include "ImageWindow.h"

ImageSoftwareCommand::ImageSoftwareCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

boolean ImageSoftwareCommand::doIt(CommandInterface *ci)
{
    Boolean set;
    XtVaGetValues(ci->getRootWidget(), XmNset, &set, NULL);
    this->imageWindow->setSoftware(set);
    return TRUE;
}
