//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/SelectorToggleInteractor.h,v 1.1 1999/03/24 15:17:46 gda Exp $
 */


#ifndef _SelectorToggleInteractor_h
#define _SelectorToggleInteractor_h


#include <Xm/Xm.h>
 
#include "defines.h"
#include "ToggleInteractor.h"


//
// Class name definition:
//
#define ClassSelectorToggleInteractor	"SelectorToggleInteractor"


//
// SelectorToggleInteractor class definition:
//				
class SelectorToggleInteractor : public ToggleInteractor
{
  private:
    //
    // Private member data:
    //
    static boolean SelectorToggleInteractor::SelectorToggleInteractorClassInitialized;

  protected:
    //
    // Protected member data:
    //

    static String SelectorToggleInteractor::DefaultResources[];

    //
    // Accepts value changes and reflects them into other interactors, cdbs
    // and of course the interactor node output.
    //
    virtual void toggleCallback(Widget w, Boolean set, XtPointer cb);

  public:
    //
    // Allocate an interactor for the given instance.
    //
    static Interactor *AllocateInteractor(const char *name,
					InteractorInstance *ii);

    //
    // Constructor:
    //
    SelectorToggleInteractor(const char *name, InteractorInstance *ii);

    //
    // Destructor:
    //
    ~SelectorToggleInteractor(){}

    //
    // One time initialize for the class.
    //
    virtual void initialize();

#if 0	// 1/25/94	- Move to ToggleInteractor
    //
    // Set the displayed label of the interactor and do a layout if
    // indicated to handle a significant change in label width.
    //
    virtual void setLabel(const char *labelString, boolean re_layout = TRUE);
#endif

    //
    // Update the displayed values for this interactor.
    //
    virtual void updateDisplayedInteractorValue(void);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSelectorToggleInteractor;
    }
};


#endif // _SelectorToggleInteractor_h
