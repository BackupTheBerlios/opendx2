///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/TransmitterDefinition.h,v 1.1 1999/03/24 15:17:48 gda Exp $
 *
 */


#ifndef _TransmitterDefinition_h
#define _TransmitterDefinition_h


#include "UIConfig.h"
#include "defines.h"
#include "NodeDefinition.h"


//
// Class name definition:
//
#define ClassTransmitterDefinition	"TransmitterDefinition"

//
// Referenced classes
class Network;

//
// TransmitterDefinition class definition:
//				
class TransmitterDefinition : public NodeDefinition
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
    TransmitterDefinition();

    //
    // Destructor:
    //
    ~TransmitterDefinition(){}

    //
    // Create a new Module and NodeDefinition of 'this' type. 
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassTransmitterDefinition;
    }
};


#endif // _TransmitterDefinition_h
