//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/VectorDefinition.h,v 1.1 1999/03/24 15:17:48 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _VectorDefinition_h
#define _VectorDefinition_h

#include <Xm/Xm.h>

#include "UIConfig.h"
#include "defines.h"
#include "ScalarDefinition.h"


//
// Class name definition:
//
#define ClassVectorDefinition	"VectorDefinition"

//
// Forward definitions 
//
class ParameterDefinition;
class Interactor;

//
// VectorDefinition class definition:
//				
class VectorDefinition : public ScalarDefinition 
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
    VectorDefinition() { }

    //
    // Destructor:
    //
    ~VectorDefinition() { }
	
    //
    // Allocate a new VectorDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() 
		{ return ClassVectorDefinition; }
};


#endif // _VectorDefinition_h
