//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/SelectorListToggleInteractor.h,v 1.1 1999/03/31 22:34:46 gda Exp $
 */


#ifndef _SelectorListToggleInteractor_h
#define _SelectorListToggleInteractor_h


#include <X11/Intrinsic.h>
 
#include "defines.h"
#include "Interactor.h"
#include "List.h"

//
// Class name definition:
//
#define ClassSelectorListToggleInteractor	"SelectorListToggleInteractor"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
extern "C" void SelectorListToggleInteractor_ToggleCB(Widget, 
				XtPointer, XtPointer);


//
// SelectorListToggleInteractor class definition:
//				
class SelectorListToggleInteractor : public Interactor
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //

    //
    // One widget for each component (scalar or n-vector).
    //
    Widget      toggleForm;
    List	toggleWidgets;

    static boolean SelectorListToggleInteractor::ClassInitialized;

    static String SelectorListToggleInteractor::DefaultResources[];

    friend void SelectorListToggleInteractor_ToggleCB(
		Widget widget, XtPointer clientData, XtPointer callData);

    //
    // Get the nth widget. 
    //
    Widget getOptionWidget(int i) 
		{ ASSERT(i>0); 
		  return (Widget)this->toggleWidgets.getElement(i); 
		}
    boolean appendOptionWidget(Widget w) 
		{ return this->toggleWidgets.appendElement((const void*) w); }

    //
    // [Re]load the options into this->pulldown.
    //
    void reloadMenuOptions();

  public:
    //
    // Allocate this class 
    //
    static Interactor *AllocateInteractor(const char *name,
					InteractorInstance *ii);


    //
    // Accepts value changes and reflects them into other interactors, cdbs
    // and off course the interactor node output.
    //
    virtual void applyCallback(Widget w, XtPointer cb);

    //
    // Constructor:
    //
    SelectorListToggleInteractor(const char *name, InteractorInstance *ii);

    //
    // Destructor:
    //
    ~SelectorListToggleInteractor(){}

    //
    // Update the displayed values for this interactor.
    //
    void updateDisplayedInteractorValue(void);

    //
    // 
    //
    Widget createInteractivePart(Widget p);
    void   completeInteractivePart();

    //
    // Make sure the attributes match the resources for the widgets. 
    //
    void handleInteractivePartStateChange(InteractorInstance *src_ii,
						boolean major_change);

    virtual void layoutInteractorHorizontally ();
    virtual void layoutInteractorVertically ();

    //
    // One time initialize for the class.
    //
    void initialize();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSelectorListToggleInteractor;
    }
};


#endif // _SelectorListToggleInteractor_h
