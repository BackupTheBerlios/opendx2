//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/SelectorDefinition.h,v 1.1 1999/03/31 22:34:32 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _SelectorDefinition_h
#define _SelectorDefinition_h

#include "UIConfig.h"
#include "defines.h"
#include "SelectionDefinition.h"


//
// Class name definition:
//
#define ClassSelectorDefinition	"SelectorDefinition"

//
// Forward definitions 
//


//
// SelectorDefinition class definition:
//				
class SelectorDefinition : public SelectionDefinition 
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
    SelectorDefinition() { }

    //
    // Destructor:
    //
    ~SelectorDefinition() { }
	
    //
    // Allocate a new SelectorDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();


    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() 
		{ return ClassSelectorDefinition; }
};


#endif // _SelectorDefinition_h
