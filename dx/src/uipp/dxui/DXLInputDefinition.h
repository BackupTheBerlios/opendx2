/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#ifndef _DXLInputDefinition_h
#define _DXLInputDefinition_h


#include "UIConfig.h"
#include "defines.h"
#include "NodeDefinition.h"


//
// Class name definition:
//
#define ClassDXLInputDefinition	"DXLInputDefinition"

//
// Referenced classes

//
// DXLInputDefinition class definition:
//				
class DXLInputDefinition : public NodeDefinition
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //

    //
    // Allocate a new Node of the corresponding type.
    //
    virtual Node *newNode(Network *net, int instance = -1); 

    virtual SIAllocator getSIAllocator();

  public:
    //
    // Constructor:
    //
    DXLInputDefinition();

    //
    // Destructor:
    //
    ~DXLInputDefinition(){}

    //
    // Create a new Module and NodeDefinition of 'this' type. 
    //
    static NodeDefinition *AllocateDefinition();


    virtual boolean isAllowedInMacro() { return FALSE; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDXLInputDefinition;
    }
};


#endif // _DXLInputDefinition_h
