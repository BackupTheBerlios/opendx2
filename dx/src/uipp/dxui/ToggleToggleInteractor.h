/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _ToggleToggleInteractor_h
#define _ToggleToggleInteractor_h


#include <Xm/Xm.h>
 
#include "defines.h"
#include "ToggleInteractor.h"


//
// Class name definition:
//
#define ClassToggleToggleInteractor	"ToggleToggleInteractor"


//
// ToggleToggleInteractor class definition:
//				
class ToggleToggleInteractor : public ToggleInteractor
{
  private:
    //
    // Private member data:
    //
    static boolean ToggleToggleInteractor::ToggleToggleInteractorClassInitialized;

  protected:
    //
    // Protected member data:
    //

    static String ToggleToggleInteractor::DefaultResources[];

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
    ToggleToggleInteractor(const char *name, InteractorInstance *ii);

    //
    // Destructor:
    //
    ~ToggleToggleInteractor(){}

    //
    // One time initialize for the class.
    //
    virtual void initialize();

    //
    // Update the displayed values for this interactor.
    //
    virtual void updateDisplayedInteractorValue(void);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassToggleToggleInteractor;
    }
};


#endif // _ToggleToggleInteractor_h
