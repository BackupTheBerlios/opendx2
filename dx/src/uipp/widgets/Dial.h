/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/widgets/Dial.h,v 1.1 1999/03/24 15:17:35 gda Exp $
 */

/******************************************************
 * Dial.h: Public header file for Dial Widget Class.
 ******************************************************/
#ifndef	DIAL_H
#define DIAL_H

#include "XmDX.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern	WidgetClass	xmDialWidgetClass;
extern	Widget		XmCreateDial(Widget, String, ArgList, Cardinal);

typedef	struct	_XmDialClassRec	*XmDialWidgetClass;
typedef struct  _XmDialRec	*XmDialWidget;

typedef	struct	
	{
	int	reason;
	XEvent	*event;
	double	position;
	}	XmDialCallbackStruct;

typedef int    ClockDirection;

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif
