//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ValueListDefinition.h,v 1.1 1999/03/31 22:35:48 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _ValueListDefinition_h
#define _ValueListDefinition_h

#include "UIConfig.h"
#include "defines.h"
#include "ValueDefinition.h"


//
// Class name definition:
//
#define ClassValueListDefinition	"ValueListDefinition"

//
// Forward definitions 
//
class ParameterDefinition;
class Interactor;

//
// ValueListDefinition class definition:
//				
class ValueListDefinition : public ValueDefinition 
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
    ValueListDefinition() { }

    //
    // Destructor:
    //
    ~ValueListDefinition() { }
	
    //
    // Allocate a new ValueListDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() { return ClassValueListDefinition; }
};


#endif // _ValueListDefinition_h
