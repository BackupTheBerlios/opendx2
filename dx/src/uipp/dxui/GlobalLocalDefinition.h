//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/GlobalLocalDefinition.h,v 1.1 1999/03/31 22:31:48 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _GlobalLocalDefinition_h
#define _GlobalLocalDefinition_h

#include <Xm/Xm.h>

#include "UIConfig.h"
#include "defines.h"
#include "NodeDefinition.h"


//
// Class name definition:
//
#define ClassGlobalLocalDefinition	"GlobalLocalDefinition"

//
// Forward definitions 
//
class Network;

//
// GlobalLocalDefinition class definition:
//				
class GlobalLocalDefinition : public NodeDefinition 
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
    GlobalLocalDefinition() { }

    //
    // Destructor:
    //
    ~GlobalLocalDefinition() { }
	
    //
    // Allocate a new GlobalLocalDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() { return ClassGlobalLocalDefinition; }
};


#endif // _GlobalLocalDefinition_h
