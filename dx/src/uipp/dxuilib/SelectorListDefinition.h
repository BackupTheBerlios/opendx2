//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/SelectorListDefinition.h,v 1.1 1999/03/24 15:17:46 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _SelectorListDefinition_h
#define _SelectorListDefinition_h

#include "UIConfig.h"
#include "defines.h"
#include "SelectionDefinition.h"


//
// Class name definition:
//
#define ClassSelectorListDefinition	"SelectorListDefinition"

//
// Forward definitions 
//


//
// SelectorListDefinition class definition:
//				
class SelectorListDefinition : public SelectionDefinition 
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
    SelectorListDefinition() { }

    //
    // Destructor:
    //
    ~SelectorListDefinition() { }
	
    //
    // Allocate a new SelectorListDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();


    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() 
		{ return ClassSelectorListDefinition; }
};


#endif // _SelectorListDefinition_h
