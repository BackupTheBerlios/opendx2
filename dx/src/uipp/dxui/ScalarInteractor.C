//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ScalarInteractor.C,v 1.1 1999/03/31 22:34:11 gda Exp $
 */


#include "UIConfig.h"

#include <Xm/MainW.h>

#include "defines.h"
#include "ScalarInteractor.h"
#include "ScalarNode.h"
#include "ScalarInstance.h"
#include "../widgets/Number.h"
#include "WarningDialogManager.h"


extern "C" void ScalarInteractor_NumberWarningCB(Widget  widget,
                        XtPointer clientData,
                        XtPointer callData)
{
    XmNumberWarningCallbackStruct* warning;

#if 1
    while(NOT XmIsMainWindow(widget))
    {
        widget = XtParent(widget);
    }
#endif
    warning = (XmNumberWarningCallbackStruct*)callData;
    // FIXME: this should be modal
    // ModalWarningMessage(widget, warning->message);
    WarningMessage(warning->message);
}


