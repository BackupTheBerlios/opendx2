/*  Open Visualization Data Explorer Source File */

#ifndef _PrintDefinition_h
#define _PrintDefinition_h

#include <Xm/Xm.h>

#include "UIConfig.h"
#include "defines.h"
#include "NodeDefinition.h"


//
// Class name definition:
//
#define ClassPrintDefinition	"PrintDefinition"

//
// Forward definitions 
//
class Network;

//
// PrintDefinition class definition:
//				
class PrintDefinition : public NodeDefinition 
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
    PrintDefinition() { }

    //
    // Destructor:
    //
    ~PrintDefinition() { }
	
    //
    // Allocate a new PrintDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() { return ClassPrintDefinition; }
};


#endif // _PrintDefinition_h
