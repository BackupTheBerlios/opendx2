/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*
 * $Header: /a/spline/homes/spline/jgv/ui/uix/RCS/VCRControl.h,v 1.8 91/03/07 14
:13:10 jgv Exp Locker: jgv $
 * $Log: VCRControl.h,v $
 * Revision 1.1  1999/03/24 15:17:37  gda
 * Initial revision
 *
 * Revision 1.1.1.1  1999/03/19 20:59:41  gda
 * Initial CVS
 *
 * Revision 10.1  1999/02/24 13:24:41  gda
 * OpenDX Baseline
 *
 * Revision 9.1  1997/05/22 18:48:43  svs
 * Copy of release 3.1.4 code
 *
 * Revision 8.0  1995/10/03  18:50:18  nsc
 * Copy of release 3.1 code
 *
 * Revision 7.1  1994/01/18  19:02:56  svs
 * changes since release 2.0.1
 *
 * Revision 6.1  93/11/16  10:51:16  svs
 * ship level code, release 2.0
 * 
 * Revision 1.1  93/02/26  16:29:18  danz
 * Initial revision
 * 
 *
 */

#ifndef _VCRControl_h
#define _VCRControl_h

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif


#include "XmDX.h"

extern  WidgetClass                   xmVCRControlWidgetClass;
typedef struct _XmVCRControlClassRec  *XmVCRControlWidgetClass;
typedef struct _XmVCRControlRec       *XmVCRControlWidget;

typedef struct {
    int     action;
    Boolean on;
    char    which;
    int     detent;
    short     value;
} VCRCallbackStruct;

extern Widget XmCreateVCRControl(Widget parent, String name, 
                                 ArgList args, Cardinal num_args);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
