//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// XmUtility.h - 		                                            //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/XmUtility.h,v 1.1 1999/03/24 15:17:25 gda Exp $
 *
 */

#ifndef _XmUtility_h
#define _XmUtility_h

#include <Xm/Text.h>

#include "defines.h"

#define RES_CONVERT(res, str) XtVaTypedArg, res, XmRString, str, strlen(str)+1

//
// Return values used by VerifyNameText().
//
#define  XmU_TEXT_VALID		0
#define  XmU_TEXT_INVALID	1		
#define  XmU_TEXT_DELETE	2

extern void SetTextSensitive(Widget w, Boolean sens, Pixel foreground);

extern int  VerifyNameText(Widget text, XmTextVerifyCallbackStruct* cbs);

extern int  VerifyGridText(Widget text, XmTextVerifyCallbackStruct* cbs);

extern Widget CreateFormDialog(Widget parent, String name, ArgList arglist, Cardinal argcount);

#endif /* _XmUtility_h */

