//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// XmUtility.C - 		                                            //
//                                                                          //
// XmUtility Class methods and other related  functions/procedures.         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/XmUtility.C,v 1.1 1999/03/24 15:17:25 gda Exp $
 *
 */

#include <string.h>
#include <X11/IntrinsicP.h>
#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/DialogS.h>
#include <Xm/Form.h>

#include "Strings.h"
#include "lex.h"
#include "XmUtility.h"

#define  ValidNameCharSet  "abcdefghijklmnopqrstuvwxyz" \
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                           "1234567890"			\
                           "- _"

#define  ValidDimensionCharSet  "1234567890"                 \
 			   	".x"


//
// Set a text widget's sensitivity.
//
void SetTextSensitive(Widget w, Boolean sens, Pixel fg)
{
    XtVaSetValues(w,
        XmNforeground, fg,
        XmNsensitive, sens,
        NULL);
}

//
// Verify a name string input from the text widget.
// The leading spaces are not allowed for a name.
//
int VerifyNameText(Widget text, XmTextVerifyCallbackStruct* cbs)
{
    int i;

    if(cbs->text->ptr == NULL) //delete
        return XmU_TEXT_DELETE;

    char *cp = XmTextGetString(text);
    if (IsBlankString(cp)
        AND IsBlankString(cbs->text->ptr))
    {
        cbs->doit = False;
	XtFree(cp);
        return XmU_TEXT_INVALID;
    }
    XtFree(cp);

    if(cbs->currInsert == 0 AND IsWhiteSpace(cbs->text->ptr))
    {
        cbs->doit = False;
        return XmU_TEXT_INVALID;
    }

    for(i = 0; i < cbs->text->length; i++)
    {
        if(NOT strchr(ValidNameCharSet,cbs->text->ptr[i]))
        {
            cbs->doit = False;
            return XmU_TEXT_INVALID;
        }
    }

    return XmU_TEXT_VALID;
}

//
// Verify a grid definition string(eg. 240x550) input from the text widget.
//
int VerifyGridText(Widget text, XmTextVerifyCallbackStruct* cbs)
{
    int i;

    if(cbs->text->ptr == NULL) 		//delete
        return XmU_TEXT_DELETE;

    char *cp = XmTextGetString(text);
    char *x = strchr(cp,'x');  //already has 'x'?
    XtFree(cp);

    for(i = 0; i < cbs->text->length; i++)
    {
        if(NOT strchr(ValidDimensionCharSet,cbs->text->ptr[i])
	   OR (x AND cbs->text->ptr[i] =='x'))
        {
            cbs->doit = False;
            return XmU_TEXT_INVALID;
        }
    }

    return XmU_TEXT_VALID;
}

//
// Used by CreateFormDialog().
//
extern "C" {
void _XmDestroyParentCallback
        (Widget w, caddr_t client_data, caddr_t call_data);
}

//
//  This is a fix of XmCreateFormDialog() which causes memory fault 
//  on SGI indigo with Motif 1.1 and X11R4.
//  The original code was copied from Xm/Form.c.
//  NOTE:  This function creates a form contained by a shell which
//  	   takes popup/popdownCallback resources BUT minWidth/Height. 
//
Widget CreateFormDialog(Widget parent, String name, 
			ArgList arglist, Cardinal argcount)
{
   Widget form_shell;
   Widget form;
   Arg shell_arglist[25];
   int shell_argcount = 0;


   /*  Create a pop-up shell for the form box.  */

   XtSetArg (shell_arglist[shell_argcount], XmNallowShellResize, True);
   shell_argcount++;
   /* This function causes problem on indigo.
   form_shell = XmCreateDialogShell (parent, "Popup",
                                     shell_arglist, shell_argcount);
   */
   /* Use the following instead of the above */
   form_shell = XtCreateWidget("Popup", xmDialogShellWidgetClass,
				parent, shell_arglist, shell_argcount);

   /*  Create the widget  */

   form = XtCreateWidget (name, xmFormWidgetClass,
                          form_shell, arglist, argcount);
   XtAddCallback (form, XmNdestroyCallback, (XtCallbackProc)_XmDestroyParentCallback, NULL);
   return (form);

}

