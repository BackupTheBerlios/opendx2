/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _SelectorInstance_h
#define _SelectorInstance_h


#include <Xm/Xm.h> 

#include "defines.h"
#include "Strings.h"
#include "SelectorNode.h"
#include "SelectionInstance.h"

class SelectorInteractor;


//
// Class name definition:
//
#define ClassSelectorInstance	"SelectorInstance"


//
// Describes an instance of an interactor in a control Panel.
//
class SelectorInstance : public SelectionInstance {

  private:


  protected:

    virtual const char* javaName() { return "pdown"; }

  public:
    SelectorInstance(InteractorNode *node) : SelectionInstance(node) {}
	
    ~SelectorInstance()  {}

    int 	getSelectedOptionIndex();

    void setSelectedOptionIndex(int index, boolean update_outputs = TRUE);

    virtual boolean printAsJava(FILE* );

    const char *getClassName() 
		{ return ClassSelectorInstance; }
};

#endif // _SelectorInstance_h

