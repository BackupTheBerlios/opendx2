/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#ifndef _NOTEBOOK_H_
#define _NOTEBOOK_H_

#include "UIComponent.h"
#include "List.h"

extern "C" void Notebook_TabCB(Widget, XtPointer, XtPointer);
extern "C" Boolean Notebook_ManagerWP (XtPointer );
extern "C" void Notebook_TabEH(Widget, XtPointer, XEvent* , Boolean* );

#define ClassNotebook "Notebook"

class Notebook : public UIComponent
{
    private:
	int index_of_selection;

	static Pixmap TopShadowPixmap;
	static Pixmap BottomShadowPixmap;
	static boolean ClassInitialized;

	XtWorkProcId manager_wpid;

	Widget text;

    protected:
	friend Boolean Notebook_ManagerWP (XtPointer );
	friend void Notebook_TabEH(Widget, XtPointer, XEvent* , Boolean* );

	Widget page_tab_form;
	Widget scrolled_window;
	Widget manager;

	// list of toggle buttons
	List tabs;

	// list of form widgets
	List pages;

	// list of names of the tabs
	List names;

	virtual Widget getSelectedPage();

	// the shadow pixmap problem first encountered in dxuilib/PageTab.
	// The bug might not exist any more but I have no way to test for it.
	static boolean BrokenServer;

    public:
	Notebook (Widget parent);

	virtual ~Notebook();

	Widget getTabManager() { return this->page_tab_form; }
	Widget getPageManager() { return this->manager; }

	virtual void addPage (const char* name, Widget page);
	virtual void showPage (int page);
	virtual void showPage (const char* name);
	virtual Widget getPage(const char* name);
	
	void showRectangle(int x1, int y1, int x2, int y2);

	//
	// Returns a pointer to the class name.
	//
	const char* getClassName()
	{
	    return ClassNotebook;
	}
};

#endif //_NOTEBOOK_H_
