/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#include "Notebook.h"
#include "ListIterator.h"
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/ToggleB.h>
#include <Xm/ScrolledW.h>
#include <Xm/ScrollBar.h>
#include "DXStrings.h"
#include "Application.h"

#include "top_shadow60.bm"
#include "top_shadow_pc60.bm"
#include "bottom_shadow60.bm"

#define HUMMINGBIRD "Hummingbird"

boolean Notebook::ClassInitialized = 0;
Pixmap Notebook::TopShadowPixmap = 0;
Pixmap Notebook::BottomShadowPixmap = 0;

// same problem as in dxuilib/PageTab.  I don't have any way to
// figure out if the bug in the Hummingbird X server still exists or not.
boolean Notebook::BrokenServer = FALSE;

Notebook::Notebook(Widget parent) : UIComponent("notebook")
{
    if (!Notebook::ClassInitialized) {
	Pixel bg, sh, bsh, hi;
	int depth;
	XtVaGetValues (parent,
	    XmNbackground, &bg,
	    XmNtopShadowColor, &sh,
	    XmNbottomShadowColor, &bsh,
	    XmNdepth, &depth,
	    XmNhighlightColor, &hi,
	NULL);
	const char* vendor = ServerVendor(XtDisplay(parent));
	if (strstr(vendor, HUMMINGBIRD))
	    Notebook::BrokenServer = TRUE;

	if (Notebook::BrokenServer) {
	    Notebook::TopShadowPixmap = XCreatePixmapFromBitmapData(
		XtDisplay(theApplication->getRootWidget()),
		XtWindow(theApplication->getRootWidget()), 
		top_shadow_pc_bits, top_shadow_pc_width, 
		top_shadow_pc_height, bg, sh, depth);
	} else {
	    Notebook::TopShadowPixmap = XCreatePixmapFromBitmapData(
		XtDisplay(theApplication->getRootWidget()),
		XtWindow(theApplication->getRootWidget()), 
		top_shadow_bits, top_shadow_width, 
		top_shadow_height, bg, sh, depth);
	    Notebook::BottomShadowPixmap = XCreatePixmapFromBitmapData(
		XtDisplay(theApplication->getRootWidget()),
		XtWindow(theApplication->getRootWidget()), 
		bottom_shadow_bits, bottom_shadow_width, 
		bottom_shadow_height, bg, bsh, depth);
	}

	Notebook::ClassInitialized = TRUE;
    }

    Widget form = XtVaCreateManagedWidget (this->name, xmFormWidgetClass, parent, NULL);

    this->page_tab_form = XtVaCreateManagedWidget (
	    "pageTabForm", xmFormWidgetClass, form,
	    XmNtopAttachment, 		XmATTACH_FORM,
	    XmNleftAttachment, 		XmATTACH_FORM,
	    XmNrightAttachment, 	XmATTACH_NONE,
	    XmNbottomAttachment, 	XmATTACH_OPPOSITE_FORM,
	    XmNtopOffset, 		0,
	    XmNleftOffset, 		0,
	    XmNbottomOffset, 		-26,
	    XmNtraversalOn, 		FALSE,
	NULL);

    this->scrolled_window = XtVaCreateManagedWidget (
	    "swindow", xmScrolledWindowWidgetClass, form,
	    XmNtopAttachment,		XmATTACH_FORM,
	    XmNleftAttachment,		XmATTACH_FORM,
	    XmNrightAttachment,		XmATTACH_FORM,
	    XmNbottomAttachment,	XmATTACH_FORM,
	    XmNtopOffset,		25,
	    XmNleftOffset,		0,
	    XmNrightOffset,		0,
	    XmNbottomOffset,		0,
	    XmNscrollBarDisplayPolicy,	XmAS_NEEDED,
	    XmNscrollingPolicy,		XmAUTOMATIC,
	    XmNvisualPolicy,		XmVARIABLE,
	    XmNtraversalOn,		FALSE,
    NULL);

    this->manager = XtVaCreateManagedWidget ("manager", xmFormWidgetClass, 
	this->scrolled_window, XmNshadowThickness, 0, XmNtraversalOn, FALSE,
    NULL);

    // I don't think this is necessary but it does follow the doc.
    XtVaSetValues (this->scrolled_window, 
	XmNworkWindow, this->manager, 
	XmNscrolledWindowChildType, XmWORK_AREA,
    NULL);

    this->index_of_selection = -1;
    this->setRootWidget(form);

}

Notebook::~Notebook()
{
    ListIterator iter(this->names);
    char* name;
    while ((name = (char*)iter.getNext()) != NULL) {
	delete name;
    }
}

void Notebook::addPage (const char* name, Widget page)
{
    Widget tab = XmCreateToggleButton (this->page_tab_form, (char*)name, 0,0);
    XmString xmstr = XmStringCreateLtoR((char*)name, "small_bold");
    XtVaSetValues (tab,
	XmNindicatorOn, XmINDICATOR_NONE,
	XmNset, FALSE,
	XmNfillOnSelect, FALSE,
	XmNwidth, 60,
	XmNrecomputeSize, FALSE,
	XmNtopShadowPixmap, Notebook::TopShadowPixmap,
	XmNlabelString, xmstr,
    NULL);
    if (Notebook::BrokenServer) {
	XtVaSetValues (tab,
	    XmNshadowThickness, 1,
	NULL);
    } else {
	XtVaSetValues (tab,
	    XmNbottomShadowPixmap, Notebook::BottomShadowPixmap,
	    XmNshadowThickness, 3,
	NULL);
    }
    XmStringFree(xmstr);
    int tab_cnt = this->tabs.getSize();
    if (tab_cnt == 0) {
	XtVaSetValues (tab,
	    XmNtopAttachment,	XmATTACH_FORM,
	    XmNleftAttachment,	XmATTACH_FORM,
	    XmNrightAttachment, XmATTACH_NONE,
	    XmNbottomAttachment,XmATTACH_FORM,
	    XmNtopOffset, 0,
	    XmNleftOffset, 0,
	    XmNbottomOffset, 0,
	NULL);
    } else {
	Widget prev = (Widget)this->tabs.getElement(tab_cnt);
	XtVaSetValues (tab,
	    XmNtopAttachment,	XmATTACH_FORM,
	    XmNleftAttachment,	XmATTACH_WIDGET,
	    XmNrightAttachment, XmATTACH_NONE,
	    XmNbottomAttachment,XmATTACH_FORM,
	    XmNleftWidget,	prev,
	    XmNtopOffset, 0,
	    XmNleftOffset, 0,
	    XmNbottomOffset, 0,
	NULL);
    }
    XtVaSetValues (page,
	XmNtopAttachment, XmATTACH_FORM,
	XmNleftAttachment, XmATTACH_FORM,
	XmNrightAttachment, XmATTACH_FORM,
	XmNbottomAttachment, XmATTACH_FORM,
    NULL);
    if (tab_cnt == 0) {
	if (!XtIsManaged(page)) XtManageChild (page);
	XtVaSetValues (tab, XmNset, TRUE, NULL);
	this->index_of_selection = 1;
    } else {
	if (XtIsManaged(page)) XtUnmanageChild(page);
    }
    XtAddCallback (tab, XmNvalueChangedCallback, Notebook_TabCB, this);
    XtAddEventHandler (tab, ButtonPressMask|ButtonReleaseMask, False,
	(XtEventHandler)Notebook_TabEH, (XtPointer)this);
    this->tabs.appendElement(tab);
    this->pages.appendElement(page);
    this->names.appendElement(DuplicateString(name));
    XtManageChild(tab);
}

void Notebook::showPage (int pageId)
{
    // if pageId == this->index_of_selection, then we
    // still have to keep processing because the user may
    // have tried to unselect the tab of the current page
    // which has to be prevented.
    int cnt = this->tabs.getSize();
    Widget page_to_manage=0;
    Widget page_to_unmanage=0;
    for (int i=1; i<=cnt; i++) {
	Widget tab = (Widget)this->tabs.getElement(i);
	Widget page = (Widget)this->pages.getElement(i);
	if (i==pageId) {
	    if (!XmToggleButtonGetState(tab))
		XmToggleButtonSetState (tab, TRUE, FALSE);
	    page_to_manage = page; 
	} else {
	    if (XmToggleButtonGetState(tab))
		XmToggleButtonSetState (tab, FALSE, FALSE);
	    if (XtIsManaged(page))
		page_to_unmanage = page;
	}
	if ((page_to_manage)&&(page_to_unmanage)) break;
    }

    //
    // bug here:  I unmanage the page going away and manage the page
    // arriving.  Problem is that the parent of the 2 pages collapses
    // itself to 0 width and height.  I use setValues to return the
    // parent to its proper size.
    //
    if (pageId != this->index_of_selection) {
	Dimension w,h;
	XtVaGetValues (page_to_manage, XmNwidth,&w,XmNheight,&h,NULL);
	ASSERT(page_to_unmanage);
	ASSERT(page_to_manage);
	ASSERT(page_to_manage != page_to_unmanage);
	XtUnmanageChild(page_to_unmanage);
	XtManageChild(page_to_manage);
	XtVaSetValues (this->manager, XmNwidth,w,XmNheight,h,NULL);
    }
    this->index_of_selection = pageId;
}

Widget Notebook::getSelectedPage()
{
    return (Widget)this->pages.getElement(this->index_of_selection);
}

Widget Notebook::getPage (const char* name)
{
    ListIterator iter(this->names);
    const char* cp;
    int i = 1;
    while (cp=(const char*)iter.getNext()) {
	if (EqualString(cp, name)) 
	    return (Widget)this->pages.getElement(i);
	i++;
    }
    return NUL(Widget);
}

void Notebook::showPage (const char* name)
{
    ListIterator iter(this->names);
    const char* cp;
    int ndx = 1;
    int selection = -1;
    while (cp=(const char*)iter.getNext()) {
	if (EqualString(cp, name)) {
	    selection = ndx;
	    break;
	}
	ndx++;
    }
    ASSERT(selection != -1);
    this->showPage(selection);
}

void Notebook::showRectangle(int x1, int y1, int x2, int y2)
{
    Widget vbar, clip;
    XtVaGetValues (this->scrolled_window,
	XmNverticalScrollBar, &vbar,
	XmNclipWindow, &clip,
    NULL);
    ASSERT(vbar);
    ASSERT(clip);

    Dimension clip_height;
    XtVaGetValues (clip, XmNheight, &clip_height, NULL);
    int value, slider_size, min, max, incr, page_incr;
    boolean adjusted = FALSE;

    XtVaGetValues (vbar, 
	XmNsliderSize, &slider_size,
	XmNminimum, &min,
	XmNmaximum, &max,
	XmNvalue, &value,
	XmNincrement, &incr,
	XmNpageIncrement, &page_incr,
    NULL);


    if (y2 > (value + clip_height)) {
	adjusted = TRUE;
	value = y2-clip_height;
    } else if (y1 < value) {
	adjusted = TRUE;
	value = y1;
    }

    if (adjusted)
	XmScrollBarSetValues (vbar, value, slider_size, incr, page_incr, TRUE);
}

extern "C" {
void Notebook_TabCB (Widget tab, XtPointer cdata, XtPointer udata)
{
    Notebook* notebook = (Notebook*)cdata;
    const char* cp = XtName(tab);
    notebook->showPage(cp);
}

Boolean Notebook_ManagerWP (XtPointer cdata)
{
    Widget manager = (Widget)cdata;
    XtVaSetValues (manager, XmNresizePolicy, XmRESIZE_ANY,NULL);
    return TRUE;
}

void Notebook_TabEH(Widget w, XtPointer cdata, XEvent *xev, Boolean* doit)
{
    Notebook* notebook = (Notebook*)cdata;
    if (notebook->tabs.getSize() <= 1) *doit = False;
    else *doit = True;
}
} // extern "C"
