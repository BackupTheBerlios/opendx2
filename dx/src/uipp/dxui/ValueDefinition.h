//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ValueDefinition.h,v 1.1 1999/03/31 22:35:42 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _ValueDefinition_h
#define _ValueDefinition_h

#include "UIConfig.h"
#include "defines.h"
#include "InteractorDefinition.h"


//
// Class name definition:
//
#define ClassValueDefinition	"ValueDefinition"

//
// Forward definitions 
//
class ParameterDefinition;
class Interactor;

//
// ValueDefinition class definition:
//				
class ValueDefinition : public InteractorDefinition 
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
    ValueDefinition() { }

    //
    // Destructor:
    //
    ~ValueDefinition() { }
	
    //
    // Allocate a new ValueDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() { return ClassValueDefinition; }
};


#endif // _ValueDefinition_h
