//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/StepperInteractor.h,v 1.1 1999/03/31 22:35:11 gda Exp $
 */


#ifndef _StepperInteractor_h
#define _StepperInteractor_h


#include <X11/Intrinsic.h>
 
#include "defines.h"
#include "ScalarInteractor.h"
#include "List.h"


//
// Class name definition:
//
#define ClassStepperInteractor	"StepperInteractor"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
extern "C" void StepperInteractor_StepperCB(Widget, XtPointer, XtPointer);


class InteractorInstance;


//
// StepperInteractor class definition:
//				
class StepperInteractor : public ScalarInteractor
{
     friend class ScalarListInstance;	// For buildValueFromComponents()

  private:
    //
    // Private member data:
    //

    //
    // One widget for each component (scalar or n-vector).
    //
    List	componentWidgets;
    Widget	componentForm;	// Holds the steppers for a vector interactor


    static boolean StepperInteractor::StepperInteractorClassInitialized;

    // Call the virtual callback for value changes. 
    //
    friend void StepperInteractor_StepperCB(Widget                  widget,
               			XtPointer                clientData,
               			XtPointer                callData);


  protected:
    //
    // Protected member data:
    //

    static String StepperInteractor::DefaultResources[];

    //
    //
    // Get the nth widget. 
    //
    Widget getComponentWidget(int i) 
		{ ASSERT(i>0); 
		  return (Widget)this->componentWidgets.getElement(i); 
		}
    boolean appendComponentWidget(Widget w) 
		{ return this->componentWidgets.appendElement((const void*) w);
	 	}

    //
    // Accepts value changes and reflects them into other interactors, cdbs
    // and off course the interactor node output.
    //
    virtual void stepperCallback(Widget widget, int component, 
						XtPointer clientData);

    //
    // Create and complete the steppers 
    //
    virtual Widget createInteractivePart(Widget p);
    virtual void   completeInteractivePart();

    //
    // Update the displayed values for the stepper(s).
    // Does the work on behalf of updateDisplayedInteractorValue().
    //
    void updateStepperValue();

  public:
    //
    // Allocate an interactor the given instance.
    //
    static Interactor *AllocateInteractor(const char *name,
					InteractorInstance *ii);

    //
    // Constructor:
    //
    StepperInteractor(const char *name, InteractorInstance *ii) ;

    //
    // Destructor:
    //
    ~StepperInteractor(){}

    //
    // Update the displayed values for this interactor.
    //
    virtual void updateDisplayedInteractorValue(void);

    //
    // Make sure the resources (including the value) match the attributes 
    // for the widgets. 
    //
    virtual void handleInteractivePartStateChange(
					InteractorInstance *src_ii,
					boolean major_change);

    //
    // Need special handling for laying out because it must
    // set XmNalignment in the stepper(s)
    //
    virtual void layoutInteractorHorizontally();
    virtual void layoutInteractorVertically();


    //
    // One time initialize for the class.
    //
    void initialize();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassStepperInteractor;
    }
};


#endif // _StepperInteractor_h