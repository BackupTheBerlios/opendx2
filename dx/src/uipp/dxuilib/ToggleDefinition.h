//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ToggleDefinition.h,v 1.1 1999/03/24 15:17:48 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _ToggleDefinition_h
#define _ToggleDefinition_h

#include <Xm/Xm.h>

#include "UIConfig.h"
#include "defines.h"
#include "InteractorDefinition.h"


//
// Class name definition:
//
#define ClassToggleDefinition	"ToggleDefinition"

//
// Forward definitions 
//
class ParameterDefinition;
class Interactor;

//
// ToggleDefinition class definition:
//				
class ToggleDefinition : public InteractorDefinition 
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
    ToggleDefinition() { }

    //
    // Destructor:
    //
    ~ToggleDefinition() { }
	
    //
    // Allocate a new ToggleDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

#if SYSTEM_MACROS // 3/13/95 not yet
    virtual const char *getExecModuleNameString() { return "ToggleMacro"; }
#endif

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() 
		{ return ClassToggleDefinition; }
};


#endif // _ToggleDefinition_h
