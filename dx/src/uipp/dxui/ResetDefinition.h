/*  Open Visualization Data Explorer Source File */

#ifndef _ResetDefinition_h
#define _ResetDefinition_h

#include <Xm/Xm.h>

#include "UIConfig.h"
#include "defines.h"
#include "ToggleDefinition.h"


//
// Class name definition:
//
#define ClassResetDefinition	"ResetDefinition"

//
// Forward definitions 
//
//class ParameterDefinition;
//class Interactor;

//
// ResetDefinition class definition:
//				
class ResetDefinition : public ToggleDefinition 
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
    ResetDefinition() { }

    //
    // Destructor:
    //
    ~ResetDefinition() { }
	
    //
    // Allocate a new ResetDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() 
		{ return ClassResetDefinition; }
};


#endif // _ResetDefinition_h
