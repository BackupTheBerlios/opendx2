/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#ifndef _NOTEBOOKTAB_H_
#define _NOTEBOOKTAB_H_

#include "UIComponent.h"

//extern "C" void NotebookTab_ExposeCB(Widget, XtPointer, XtPointer);
//extern "C" void NotebookTab_ArmCB(Widget, XtPointer, XtPointer);
//extern "C" void NotebookTab_DisarmCB(Widget, XtPointer, XtPointer);
//extern "C" void NotebookTab_ActivateCB(Widget, XtPointer, XtPointer);
//extern "C" void NotebookTab_ButtonEH(Widget, XtPointer, XEvent*, Boolean*);
//extern "C" void NotebookTab_MultiClickTO(XtPointer, XtIntervalId*);
//extern "C" void NotebookTab_RepaintTO(XtPointer, XtIntervalId*);

#define ClassNotebookTab "NotebookTab"

class NotebookTab : public UIComponent
{
    private:
	static int CornerSize;
	static bool ClassInitialized;
	//static XmFontList FontList;
	//static XPoint LeftCorner[];
	//static XPoint TopCorner[];
	//static XPoint RightCorner[];

	bool dirty;
	//Pixmap dbl_buffer;
	bool armed;

	//XtIntervalId repaint_timer;

	//XtIntervalId multiclick_timer;
	void multiClickTimer();

    protected:
	bool set;
	//XmString label;
	char* label_str;

	virtual void expose();
	virtual void arm();
	virtual void disarm();
	virtual bool isArmed() { return this->armed; }
	virtual void activate();
	virtual void multiClick(){}
	virtual void setLabel(const char* cp);
	virtual bool isDirty() { return this->dirty; }
	virtual void setDirty(bool d=true, bool repaint=true);
	virtual void repaint();
	virtual const char* getFont() { return "small_bold"; }

	//friend void NotebookTab_ExposeCB(Widget, XtPointer, XtPointer);
	//friend void NotebookTab_ArmCB(Widget, XtPointer, XtPointer);
	//friend void NotebookTab_DisarmCB(Widget, XtPointer, XtPointer);
	//friend void NotebookTab_ActivateCB(Widget, XtPointer, XtPointer);
	//friend void NotebookTab_ButtonEH(Widget, XtPointer, XEvent*, Boolean*);
	//friend void NotebookTab_MultiClickTO(XtPointer, XtIntervalId*);
	//friend void NotebookTab_RepaintTO(XtPointer, XtIntervalId*);

    public:
	NotebookTab (const char*);
	virtual ~NotebookTab();

	//virtual void createButton(Widget parent);

	virtual void setState(bool s=true);
	bool getState() { return this->set; }

	const char* getLabel() { return this->label_str; }

	//
	// Returns a pointer to the class name.
	//
	const char* getClassName()
	{
	    return ClassNotebookTab;
	}
};

#endif //_NOTEBOOKTAB_H_
