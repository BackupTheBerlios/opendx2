//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/DialInteractor.h,v 1.1 1999/03/31 22:31:14 gda Exp $
 */


#ifndef _DialInteractor_h
#define _DialInteractor_h


#include <X11/Intrinsic.h>
 
#include "defines.h"
#include "ScalarInteractor.h"
#include "List.h"


//
// Class name definition:
//
#define ClassDialInteractor	"DialInteractor"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
extern "C" void DialInteractor_DialCB(Widget, XtPointer, XtPointer);


class InteractorInstance;


//
// DialInteractor class definition:
//				
class DialInteractor : public ScalarInteractor
{
  private:
    //
    // Private member data:
    //

    //
    // One widget for each component (scalar or n-vector).
    //
    Widget	componentForm;	// Holds the steppers for a vector interactor
    Widget	dialWidget;
    Widget 	numberWidget;

    static boolean DialInteractor::DialInteractorClassInitialized;

    // Call the virtual callback for value changes. 
    //
    friend void DialInteractor_DialCB(Widget                  widget,
               			XtPointer                clientData,
               			XtPointer                callData);

  protected:
    //
    // Protected member data:
    //

    static String DialInteractor::DefaultResources[];

    //
    // Accepts value changes and reflects them into other interactors, cdbs
    // and off course the interactor node output.
    //
    void dialCallback(Widget widget, int component, 
						XtPointer clientData);

    //
    // Create and complete the steppers 
    //
    virtual Widget createInteractivePart(Widget p);
    virtual void   completeInteractivePart();

    //
    // Update the displayed values for the dial. 
    // Does the work on behalf of updateDisplayedInteractorValue().
    //
    void updateDialValue();


  public:
    //
    // Allocate an n-dimensional stepper for the given instance.
    //
    static Interactor *AllocateInteractor(const char *name, 
						InteractorInstance *ii);

    //
    // Constructor:
    //
    DialInteractor(const char *name, InteractorInstance *ii) ;

    //
    // Destructor:
    //
    ~DialInteractor(){}

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
    // One time initialize for the class.
    //
    void initialize();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDialInteractor;
    }
};

Widget createNumberComponent(Widget  parent,
                             boolean isInteger,
                             double  min,
                             double  max,
                             double  value,
                             int     decimalPlaces,
                             XtCallbackProc valueChangedCallback,
                             int     comp_index,
                             caddr_t clientData);

#endif // _DialInteractor_h