///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/PickDefinition.h,v 1.1 1999/03/31 22:33:38 gda Exp $
 *
 */


#ifndef _PickDefinition_h
#define _PickDefinition_h


#include "UIConfig.h"
#include "defines.h"
#include "ProbeDefinition.h"


//
// Class name definition:
//
#define ClassPickDefinition	"PickDefinition"

//
// Referenced classes
class Network;

//
// PickDefinition class definition:
//				
class PickDefinition : public ProbeDefinition
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

  public:
    //
    // Constructor:
    //
    PickDefinition();

    //
    // Destructor:
    //
    ~PickDefinition(){}

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
	return ClassPickDefinition;
    }
};


#endif // _PickDefinition_h
