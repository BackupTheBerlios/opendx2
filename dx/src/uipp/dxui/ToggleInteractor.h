//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ToggleInteractor.h,v 1.1 1999/03/31 22:35:22 gda Exp $
 */


#ifndef _ToggleInteractor_h
#define _ToggleInteractor_h

#include <Xm/Xm.h>
 
#include "defines.h"
#include "Interactor.h"

#define ClassToggleInteractor "ToggleInteractor"

//
//
//
extern "C" void ToggleInteractor_ToggleCB(Widget, XtPointer, XtPointer); 


//
// ToggleInteractor class definition:
//				
class ToggleInteractor : public Interactor
{
  private:
    //
    // Private member data:
    //
    static String WWTable;
    static XtTranslations WWTranslations;

  protected:
    //
    // Protected member data:
    //

    Widget      toggleButton;

    static String ToggleInteractor::DefaultResources[];

    friend void ToggleInteractor_ToggleCB(Widget widget, XtPointer clientData, 
				     XtPointer callData);

    // 
    // Function to handle toggle button state change.
    // 'set' is set to True if the button is set, False otherwise.
    // 
    virtual void toggleCallback(Widget w, Boolean set, XtPointer data) = 0;

    virtual void completeInteractivePart();

    //
    // Layout ourself when resized
    //
    virtual void layoutInteractorHorizontally();
    virtual void layoutInteractorVertically();

  public:
    //
    // Constructor:
    //
    ToggleInteractor(const char *name, InteractorInstance *ii);

    //
    // ... because there is no such that as a vertical toggle interactor
    //
    virtual boolean acceptsLayoutChanges() { return FALSE; }

    //
    // Destructor:
    //
    ~ToggleInteractor(){}

    //
    //  Build the toggle button and add the value changed callback.
    //
    virtual Widget createInteractivePart(Widget p);

    //
    // Just call updateDisplayedInteractorValue(); 
    //
    virtual void handleInteractivePartStateChange(InteractorInstance *src_ii,
						boolean major_change);

    //
    // Set the displayed label of the interactor and do a layout if
    // indicated to handle a significant change in label width.
    // We override the default to always set the toggle label instead
    // and set the interactor label to "".
    //
    virtual void setLabel(const char *labelString, boolean re_layout);

    const char *getClassName() { return ClassToggleInteractor; }


};

#endif // _ToggleInteractor_h