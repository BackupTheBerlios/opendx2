/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#include "PageTab.h"
#include "PageGroupManager.h"
#include "Application.h"
#include "PageSelector.h"
#include "top_shadow_pc.bm"
#include "top_shadow.bm"
#include "bottom_shadow.bm"
#include "EditorWindow.h"

//
// In order to use EditorWorkSpace::DXDropSite methods
//
#include "EditorWorkSpace.h"

#include <Xm/ToggleB.h>

String PageTab::DefaultResources[] = {
    ".indicatorOn:	False",
    ".recomputeSize:	False",
    ".topOffset:	0",
    ".leftOffset:	0",
    ".bottomOffset:	0",
    NUL(char*)
};

// gethostname is needed by decodeDropType which is part of drag-n-drop
#if defined(NEEDS_GETHOSTNAME_DECL)
extern "C" int gethostname(char *address, int address_len);
#endif

#if defined(DXD_WIN)
#include <winsock.h>
#endif

//
// The pc platforms are unable to use the XmN{top,bottom}ShadowPixmap resources
// which I need in order to make things look nice.  So I detect at run time
// if I'm displaying on a pc so that I can use special run time only tricks
// to make the unix tabs look rounded on the edges and yet leave the pc tab
// looking OK.  If I make this a compile time switch, then if you run on
// unix and display on a pc you get something really ugly.
//
boolean PageTab::BrokenServer = TRUE;

Pixmap PageTab::TopShadowPixmap = NUL(Pixmap);
Pixmap PageTab::BottomShadowPixmap = NUL(Pixmap);
Pixmap PageTab::AnimationPixmap = NUL(Pixmap);
Pixmap PageTab::AnimationMaskPixmap = NUL(Pixmap);
boolean PageTab::ClassInitialized = FALSE;
Dictionary* PageTab::DropTypeDictionary = new Dictionary;
Dictionary* PageTab::DragTypeDictionary = new Dictionary;
Widget PageTab::DragIcon = NUL(Widget);

#include "pagedrag.bm"
#include "pagedragmask.bm"
#include "animation.bm"
#include "anim_mask.bm"

#define DXPAGETRASH "DXPAGETRASH"
#define DXPAGENAME  "DXPAGENAME"
#define DXMODULES "DXMODULES"

PageTab::PageTab(Widget parent, PageSelector* sel, WorkSpace* ws, PageGroupRecord* prec) :
    UIComponent("pageTab")
{
    this->workSpace = ws;
    this->selector = sel;
    this->set = FALSE;
    this->position = 0;
    this->has_desired_position = TRUE;
    this->desired_position = prec->order_in_list;
    this->toggle_timer = 0;
    this->color_timer = 0;
    this->group_name = NUL(char*);
    this->createButton(parent);
    this->setGroup (prec);
}

PageTab::PageTab(Widget parent, PageSelector* sel, WorkSpace* ws, const char* group) :
    UIComponent("pageTab")
{
    this->workSpace = ws;
    this->selector = sel;
    this->set = FALSE;
    this->group_rec = NUL(PageGroupRecord*);
    this->position = 0;
    this->has_desired_position = FALSE;
    this->toggle_timer = 0;
    this->color_timer = 0;
    this->createButton(parent);
    this->group_name = DuplicateString(group);
    XmString xmstr = XmStringCreateLtoR (this->group_name, "small_bold");
    XtVaSetValues (this->getRootWidget(), XmNlabelString, xmstr, NULL);
    XmStringFree(xmstr);
}

int PageTab::getDesiredPosition()
{
    ASSERT(this->hasDesiredPosition());
    return this->desired_position;
}

void PageTab::createButton (Widget p)
{
    if (!PageTab::ClassInitialized) {
	this->setDefaultResources (theApplication->getRootWidget(),
	    PageTab::DefaultResources);
        this->DXDropSite::addSupportedType (PageTab::PageName, DXPAGENAME, TRUE);

	this->DXDropSite::addSupportedType (PageTab::Modules, DXMODULES, TRUE);
        this->DragSource::addSupportedType (PageTab::PageName, DXPAGENAME, TRUE);
        //this->DragSource::addSupportedType (PageTab::PageTrash, DXPAGETRASH, FALSE);

        PageTab::DragIcon = this->createDragIcon(pagedrag_width, pagedrag_height,
	     (char *)pagedrag_bits, (char *)pagedragmask_bits);

	PageTab::ClassInitialized = TRUE;

	int depth;
	Pixel hi, bg, sh, bsh;
	XtVaGetValues (p, 
	    XmNbackground, &bg, 
	    XmNtopShadowColor, &sh, 
	    XmNbottomShadowColor, &bsh, 
	    XmNdepth, &depth,
	    XmNhighlightColor, &hi,
	NULL);

	//
	// The pc platforms aren't able to use a shadowPixmap.  Don't know why,
	// it's just a bug I assume.  So we want to detect at runtime if we're
	// displaying on a pc because we want to have pretty tabs when running
	// on a pc and displaying on unix and we musn't try to get pretty tab
	// when running on unix and displaying on a pc because you would get
	// real ugliness.
	//
	static char* unix_servers[] = {
	    "International Business Machines",
	    "Silicon",
	    "Sun Microsystems",
	    "Data General",
	    "Digital",
	    "Hewlett-Packard",
	    "X Consortium",
	    NUL(char*)
	};
	int i;
	const char* vendor = ServerVendor(XtDisplay(p));
	i = 0;
	while (unix_servers[i]) {
	    if (strstr (vendor, unix_servers[i])) {
		PageTab::BrokenServer = FALSE;
		break;
	    }
	    i++;
	}
	if (PageTab::BrokenServer) {
	    PageTab::TopShadowPixmap = XCreatePixmapFromBitmapData(XtDisplay(p), 
		XtWindow(p), top_shadow_pc_bits, top_shadow_pc_width, 
		top_shadow_pc_height, bg, sh, depth);
	} else {
	    PageTab::TopShadowPixmap = XCreatePixmapFromBitmapData(XtDisplay(p), 
		XtWindow(p), top_shadow_bits, top_shadow_width, top_shadow_height, 
		bg, sh, depth);
	    PageTab::BottomShadowPixmap = XCreatePixmapFromBitmapData(XtDisplay(p), 
		XtWindow(p), bottom_shadow_bits, bottom_shadow_width, 
		bottom_shadow_height, bg, bsh, depth);
	}
#if 0
	//
	// The zeroed out part is what I would like to use, but Motif won't let
	// me.  It results in Xlib warnings to stdout.  I don't know what the
	// problem is.
	//
	PageTab::AnimationPixmap = XCreatePixmapFromBitmapData(XtDisplay(p), 
	    XtWindow(p), animation_bits, animation_width, animation_height, 
	    bg, hi, depth);
	PageTab::AnimationMaskPixmap = XCreatePixmapFromBitmapData(XtDisplay(p), 
	    XtWindow(p), anim_mask_bits, anim_mask_width, anim_mask_height, 
	    bg, hi, depth);
#else
	PageTab::AnimationPixmap = XCreateBitmapFromData(XtDisplay(p), 
	    XtWindow(p), animation_bits, animation_width, animation_height);
	PageTab::AnimationMaskPixmap = XCreateBitmapFromData(XtDisplay(p), 
	    XtWindow(p), anim_mask_bits, anim_mask_width, anim_mask_height);
#endif
    }

    Widget w = XtVaCreateWidget (this->name,
	xmToggleButtonWidgetClass,	p,
	XmNset,				this->set,
	XmNtopShadowPixmap,	PageTab::TopShadowPixmap,
#if defined(aviion)
	XmNheight,			23,
#endif
    NULL);
    if (PageTab::BrokenServer == FALSE) 
	XtVaSetValues (w, 
	    XmNbottomShadowPixmap, PageTab::BottomShadowPixmap, 
	    XmNshadowThickness, 3,
	NULL);
    else
	XtVaSetValues (w, 
	    XmNshadowThickness, 1,
	NULL);

    this->setRootWidget(w);
    this->setDragWidget(w);
    this->setDragIcon(PageTab::DragIcon);
    this->setIntraShellBehavior(TRUE);

    XtAddCallback (w, XmNvalueChangedCallback, (XtCallbackProc)
	PageTab_SetStateCB, (XtPointer)this);
    XtAddEventHandler (w, ButtonPressMask|ButtonReleaseMask,
	False, (XtEventHandler)PageTab_TogglePageEH, (XtPointer)this);
}

PageTab::~PageTab()
{
    if ((this->getRootWidget()) && (this->isManaged()))
	this->unmanage();
    if (this->group_name) delete this->group_name;
    if (this->toggle_timer) XtRemoveTimeOut(this->toggle_timer);
    if (this->color_timer) XtRemoveTimeOut(this->color_timer);
}

void PageTab::setState(boolean value)
{
    Widget b = this->getRootWidget();
    if (b) {
	if (XmToggleButtonGetState(b) != value) 
	    XmToggleButtonSetState(b, value, False);
    } 
    this->set = value;
    if (this->group_rec) this->group_rec->showing = this->set;
}

boolean PageTab::getState()
{
    Widget b = this->getRootWidget();
    if (b) this->set = (boolean)XmToggleButtonGetState (b);
    return this->set;
}

void PageTab::setGroup(PageGroupRecord* rec)
{
    if (this->group_name) delete this->group_name;
    this->group_rec = rec;
    const char* rec_name = rec->getName();
    this->group_name = DuplicateString(rec_name);
    XmString xmstr = XmStringCreateLtoR (this->group_name, "small_bold");
    XtVaSetValues (this->getRootWidget(), XmNlabelString, xmstr, NULL);
    XmStringFree(xmstr);
    this->setPosition (this->position);
}

void PageTab::setPosition (int order, boolean designated_by_user)
{
    this->position = order;

    if (designated_by_user) this->has_desired_position = FALSE;
    if (this->group_rec) this->group_rec->order_in_list = order;
}

int PageTab::getPosition ()
{
    if (this->group_rec) 
	this->position = this->group_rec->order_in_list;
    return this->position;
}

//
// It might be nice to set a timer to set the color because we're really going
// to just walk thru the net turning things on, then off, then moving to the
// next node.  If you're turning lots of nodes in 1 page on/off, then we would
// save some time by not changing the color of the page's tab.
//
void PageTab::setColor (Pixel fg)
{
    if (this->color_timer)
	XtRemoveTimeOut(this->color_timer);

    XtAppContext apcxt = theApplication->getApplicationContext();
    this->pending_fg = fg;
    this->color_timer = 
	XtAppAddTimeOut (apcxt, 100, (XtTimerCallbackProc)
		PageTab_ColorTimerTO, (XtPointer)this);
}

//
// Does the saved info for this group say the page should be visible?
// This is used to put up the same page which was showing when the net
// was saved.
//
boolean PageTab::getDesiredShowing() 
{
    return (this->group_rec?this->group_rec->showing:FALSE);
}

extern "C"
void PageTab_ColorTimerTO (XtPointer clientData, XtIntervalId* )
{
    PageTab* pt = (PageTab*)clientData;
    ASSERT(pt);
    XtVaSetValues (pt->getRootWidget(), XmNforeground, pt->pending_fg, NULL);
    pt->color_timer = 0;
}

// Called to consumate a dnd operation
boolean PageTab::decodeDropType 
(int tag, char *type, XtPointer value, unsigned long len, int, int)
{
boolean retVal;
const char* gname;
int x,y;
int width,height;
EditorWorkSpace* ews = (EditorWorkSpace*)this->getWorkSpace();

    switch (tag) {

	case PageTab::Modules:

	    //
	    // Put the new nodes below whatever net we already have.
	    //
	    ews->getMaxWidthHeight (&width, &height);
	    if ((height > width) && (width < 400)) {
		y = 0;
		x = width + 10;
	    } else {
		x = 0;
		y = height + 10;
	    }
	    retVal = this->transfer(type, value, len, x,y);
	    break;

	case PageTab::PageName:
	    //
	    // A page name is held in *value.  Notify the PageSelector to move
	    // the corresponding tab right after me.
	    //
	    retVal = this->selector->changeOrdering (this, (char*)value);
	    break;
	default:
	    retVal = FALSE;
	    break;
    }
    return retVal;
}

boolean PageTab::decodeDragType (int tag,
	char *a, XtPointer *value, unsigned long *length, long operation)
{
boolean retVal;

    if (this->isIntraShell() == FALSE) 
	return FALSE;

    const char* gname = this->getGroupName();
    char* cp = DuplicateString(gname);

    switch(tag) {

#if 0
	case PageTab::PageTrash:
	    gname = this->getGroupName();
	    if (!gname) 
		retVal = FALSE;
	    else if (EqualString(gname, "Untitled"))
		retVal = FALSE;
	    else {
		*value = (XtPointer)cp;
		*length = strlen(cp);
		retVal = TRUE;
	    }
	    break;
#endif
	case PageTab::PageName:
	    //
	    // get some space and put a string there.  The string says the name
	    // of the button which is being moved.  The drop site will move me.
	    //
	    *value = (XtPointer)cp;
	    *length = strlen(cp);
	    retVal = TRUE;
	    break;

	default:
	    retVal = FALSE;
	    break;
    }
    return retVal;
}

#if 0
void PageTab::dropFinish(long operation, int tag, unsigned char status)
{
    if (tag == PageTab::PageTrash) {
	const char* gname = this->getGroupName();
	if (gname)
	    this->selector->requestPageDeletion (gname);
    }
}
#endif


void PageTab::manage()
{
    if (this->isManaged()) return ;
    this->setDropWidget(this->getRootWidget(), XmDROP_SITE_SIMPLE,
	PageTab::AnimationPixmap, PageTab::AnimationMaskPixmap);
    this->UIComponent::manage();
}

void PageTab::unmanage()
{
    this->UIComponent::unmanage();
    XmDropSiteUnregister (this->getRootWidget());
}

//
// A drop has deposited a network for placement in the workspace corresponding
// to this tab.  We already set x,y to lead us to empty space in the page.
// In order to get the drop to hit our page, we must remove its page group info
// and replace it with our own.
//
boolean PageTab::mergeNetElements (Network* tmpnet, List* tmppanels, int x, int y)
{
    EditorWorkSpace* ews = (EditorWorkSpace*)this->getWorkSpace();
    EditorWindow* ew = this->selector->getEditor();
    ASSERT(ew);
    if (!ew->pagifyNetNodes (tmpnet, ews)) return FALSE;
    boolean retVal = ews->mergeNetElements (tmpnet, tmppanels, x, y);
    if (retVal) ews->setMembersInitialized(FALSE);
    return retVal;
}



extern "C" {
//
// If the button is pushed in then start looking for a double click so we
// can prompt for a new page name.  If the button is pulled out, then just
// let it push it.
//
void PageTab_TogglePageEH(Widget w, XtPointer clientData, XEvent* xev, Boolean* doit)
{
    *doit = True;
    if (!xev) return ;
    if ((xev->type != ButtonPress) && (xev->type != ButtonRelease)) return ;
    if (xev->xbutton.button != 1) return ;
    PageTab* ptab = (PageTab*)clientData;
    ASSERT(ptab);

    Boolean set;
    XtVaGetValues (w, XmNset, &set, NULL);
    if (set) *doit = False;

    if (xev->type == ButtonRelease) {
	if (ptab->toggle_timer) {
	    XtRemoveTimeOut (ptab->toggle_timer);
	    ptab->toggle_timer = 0;
	    ptab->selector->postPageNamePrompt(ptab);
	} else {
	    XtAppContext apcxt = theApplication->getApplicationContext();
	    int millis = XtGetMultiClickTime (XtDisplay(w));
	    ptab->toggle_timer = XtAppAddTimeOut (apcxt, millis, (XtTimerCallbackProc)
		PageTab_ToggleTimerTO, (XtPointer)ptab);
	}
    }
}

void PageTab_ToggleTimerTO (XtPointer clientData, XtIntervalId* )
{
    PageTab* ptab = (PageTab*)clientData;
    ASSERT(ptab);
    ptab->toggle_timer = 0;
}

void PageTab_SetStateCB (Widget, XtPointer clientData, XtPointer)
{
    PageTab* ptab = (PageTab*)clientData;
    ASSERT(ptab);
    ptab->getState();
    ptab->setState(ptab->set);
}

}




