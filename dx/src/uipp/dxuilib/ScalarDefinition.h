//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ScalarDefinition.h,v 1.1 1999/03/24 15:17:45 gda Exp $
 *
 */

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
