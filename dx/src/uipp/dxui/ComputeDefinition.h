///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ComputeDefinition.h,v 1.1 1999/03/31 22:30:48 gda Exp $
 *
 */

#ifndef _ComputeDefinition_h
#define _ComputeDefinition_h


#include "UIConfig.h"
#include "defines.h"
#include "NodeDefinition.h"


//
// Class name definition:
//
#define ClassComputeDefinition	"ComputeDefinition"

//
// Referenced classes
class Network;

//
// ComputeDefinition class definition:
//				
class ComputeDefinition : public NodeDefinition
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
    // Defines the function that allocates CDBs for this node.
    //
    virtual CDBAllocator getCDBAllocator();

    //
    // Allocate a new Node of the corresponding type.
    //
    virtual Node *newNode(Network *net, int instance = -1); 

  public:
    //
    // Constructor:
    //
    ComputeDefinition();

    //
    // Destructor:
    //
    ~ComputeDefinition(){}

    //
    // Create a new Module and NodeDefinition of 'this' type. 
    //
    static NodeDefinition *AllocateDefinition();

    virtual void finishDefinition();


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassComputeDefinition;
    }
};


#endif // _ComputeDefinition_h