/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#ifndef _ProbeDefinition_h
#define _ProbeDefinition_h


#include "UIConfig.h"
#include "defines.h"
#include "NodeDefinition.h"


//
// Class name definition:
//
#define ClassProbeDefinition	"ProbeDefinition"

//
// Referenced classes
class Network;

//
// ProbeDefinition class definition:
//				
class ProbeDefinition : public NodeDefinition
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //
    virtual SIAllocator getSIAllocator();


    //
    // Allocate a new Node of the corresponding type.
    //
    virtual Node *newNode(Network *net, int instance = -1); 

  public:
    //
    // Constructor:
    //
    ProbeDefinition();

    //
    // Destructor:
    //
    ~ProbeDefinition(){}

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
	return ClassProbeDefinition;
    }
};


#endif // _ProbeDefinition_h
