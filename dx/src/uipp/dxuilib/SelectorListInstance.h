/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _SelectorListInstance_h
#define _SelectorListInstance_h


#include <Xm/Xm.h> 

#include "defines.h"
#include "Strings.h"
#include "SelectorListNode.h"
#include "SelectionInstance.h"

class SelectorListInteractor;


//
// Class name definition:
//
#define ClassSelectorListInstance	"SelectorListInstance"


//
// Describes an instance of an interactor in a control Panel.
//
class SelectorListInstance : public SelectionInstance {

  private:


  protected:

    virtual const char* javaName() { return "slist"; }

  public:
    SelectorListInstance(InteractorNode *node) : SelectionInstance(node) {}
	
    ~SelectorListInstance()  {}

    virtual boolean printAsJava(FILE* );

    const char *getClassName() 
		{ return ClassSelectorListInstance; }
};

#endif // _SelectorListInstance_h

