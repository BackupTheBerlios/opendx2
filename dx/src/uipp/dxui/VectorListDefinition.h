//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/VectorListDefinition.h,v 1.1 1999/03/31 22:36:03 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _VectorListDefinition_h
#define _VectorListDefinition_h

#include <Xm/Xm.h>

#include "UIConfig.h"
#include "defines.h"
#include "ScalarListDefinition.h"


//
// Class name definition:
//
#define ClassVectorListDefinition	"VectorListDefinition"


//
// VectorListDefinition class definition:
//				
class VectorListDefinition : public ScalarListDefinition 
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
    VectorListDefinition() { }

    //
    // Destructor:
    //
    ~VectorListDefinition() { }
	
    //
    // Allocate a new VectorListDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() 
		{ return ClassVectorListDefinition; }
};


#endif // _VectorListDefinition_h
