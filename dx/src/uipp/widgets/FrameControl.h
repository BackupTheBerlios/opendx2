/*  Open Visualization Data Explorer Source File */


/*
 * $Log: FrameControl.h,v $
 * Revision 1.2  1999/04/29 20:45:40  gda
 * New UI code snapshot
 *
 * Revision 1.3  1999/04/30 13:10:06  gda
 * After re-snapshotting, ripping out headers and adding linux changes
 *
 * Revision 9.1  1997/05/22 18:47:22  svs
 * Copy of release 3.1.4 code
 *
 * Revision 8.0  1995/10/03  18:49:24  nsc
 * Copy of release 3.1 code
 *
 * Revision 7.1  1994/01/18  19:02:22  svs
 * changes since release 2.0.1
 *
 * Revision 6.1  93/11/16  10:50:38  svs
 * ship level code, release 2.0
 * 
 * Revision 1.1  93/02/26  15:46:40  danz
 * Initial revision
 * 
 * 
 */

#ifndef FrameControl_H
#define FrameControl_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#include "XmDX.h"

/*  Declare types for convenience routine to create the widget  */
extern Widget XmCreateFrameControl
  (Widget parent, String name, ArgList args, Cardinal num_args);

extern WidgetClass xmFrameControlWidgetClass;

typedef struct _XmFrameControlClassRec * XmFrameControlWidgetClass;
typedef struct _XmFrameControlRec      * XmFrameControlWidget;


typedef struct {
    unsigned char reason;
    short value;
} FrameControlCallbackStruct;

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
