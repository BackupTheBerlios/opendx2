/*  Open Visualization Data Explorer Source File */


//////////////////////////////////////////////////////////////////////////////

#ifndef _ScalarListDefinition_h
#define _ScalarListDefinition_h

#include <Xm/Xm.h>

#include "UIConfig.h"
#include "defines.h"
#include "ScalarDefinition.h"


//
// Class name definition:
//
#define ClassScalarListDefinition	"ScalarListDefinition"


//
// ScalarListDefinition class definition:
//				
class ScalarListDefinition : public ScalarDefinition 
{
  private:
	
  protected:
    //
    // Protected member data:
    //

    //
    // Allocate a new Node of the corresponding type.
    //
    virtual Node *newNode(Network *net, int instance = -1); 


  public:
    //
    // Constructor:
    //
    ScalarListDefinition() { }

    //
    // Destructor:
    //
    ~ScalarListDefinition() { }
	
    //
    // Allocate a new ScalarListDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() 
		{ return ClassScalarListDefinition; }
};


#endif // _ScalarListDefinition_h
