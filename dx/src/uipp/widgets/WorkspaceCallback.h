/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/widgets/WorkspaceCallback.h,v 1.1 1999/03/24 15:17:37 gda Exp $
 */
#ifndef _WorkspaceCallback_h
#define _WorkspaceCallback_h

#if (XmVersion >= 1001)
#include <X11/Intrinsic.h>
#else
#include <X11/IntrinsicI.h>
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif


/*
 *  Declare subroutines used for callbacks in a child's core->constraint field
 */

/*  Define structs like those of Callback.c & CallbackI.h  */
typedef struct _WsCallbackRec {
    struct _WsCallbackRec* next;
    Widget               widget;
    XtCallbackProc       callback;
    caddr_t              closure;
} WsCallbackRec;

typedef struct _WsCallbackRec *WsCallbackList;

extern void  AddConstraintCallback	(Widget widget,
					 register WsCallbackList *callbacks,
					 XtCallbackProc callback,
					 caddr_t closure);
extern void  RemoveConstraintCallbacks  (WsCallbackList *callbacks);
extern void  CallConstraintCallbacks	(Widget widget,
					 WsCallbackList callbacks,
					 XmAnyCallbackStruct *call_data);
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
