/*  Open Visualization Data Explorer Source File */


//////////////////////////////////////////////////////////////////////////////

#ifndef _ScalarDefinition_h
#define _ScalarDefinition_h

#include <Xm/Xm.h>

#include "UIConfig.h"
#include "defines.h"
#include "InteractorDefinition.h"


//
// Class name definition:
//
#define ClassScalarDefinition	"ScalarDefinition"

//
// Forward definitions 
//
class ParameterDefinition;
class Interactor;

//
// ScalarDefinition class definition:
//				
class ScalarDefinition : public InteractorDefinition 
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
    ScalarDefinition() { }

    //
    // Destructor:
    //
    ~ScalarDefinition() { }
	
    //
    // Allocate a new ScalarDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() 
		{ return ClassScalarDefinition; }
};


#endif // _ScalarDefinition_h
