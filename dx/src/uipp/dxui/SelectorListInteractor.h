//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/SelectorListInteractor.h,v 1.1 1999/03/31 22:34:40 gda Exp $
 */


#ifndef _SelectorListInteractor_h
#define _SelectorListInteractor_h


#include <X11/Intrinsic.h>
 
#include "defines.h"
#include "Interactor.h"
#include "List.h"

//
// Class name definition:
//
#define ClassSelectorListInteractor	"SelectorListInteractor"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
extern "C" void SelectorListInteractor_SelectCB(Widget, XtPointer, XtPointer);


//
// SelectorListInteractor class definition:
//				
class SelectorListInteractor : public Interactor
{
  private:
    //
    // Private member data:
    //
    Widget list_widget;
    boolean single_select;

    void enableCallbacks (boolean enab = TRUE);
    void disableCallbacks () { this->enableCallbacks(FALSE); }

  protected:
    //
    // Protected member data:
    //

    //
    // One widget for each component (scalar or n-vector).
    //

    static boolean SelectorListInteractor::ClassInitialized;

    static String SelectorListInteractor::DefaultResources[];

    friend void SelectorListInteractor_SelectCB(Widget , XtPointer , XtPointer );

    //
    // [Re]load the options into this->pulldown.
    //
    void reloadListOptions();

    virtual void completeInteractivePart(){}

  public:
    //
    // Constructor:
    //
    SelectorListInteractor(const char *name, InteractorInstance *ii);

    //
    // Allocate this class 
    //
    static Interactor *AllocateInteractor(const char *name, InteractorInstance *ii) {
	return new SelectorListInteractor(name, ii);
    }

    //
    // Accepts value changes and reflects them into other interactors, cdbs
    // and off course the interactor node output.
    //
    void applyCallback();

    //
    // Destructor:
    //
    ~SelectorListInteractor(){}

    //
    // Update the displayed values for this interactor.
    //
    void updateDisplayedInteractorValue(void);

    //
    // 
    //
    Widget createInteractivePart(Widget p);

    //
    // Make sure the attributes match the resources for the widgets. 
    //
    void handleInteractivePartStateChange(InteractorInstance *, boolean );

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSelectorListInteractor;
    }
};


#endif // _SelectorListInteractor_h