//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/FileSelectorDefinition.h,v 1.1 1999/03/31 22:31:39 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _FileSelectorDefinition_h
#define _FileSelectorDefinition_h

#include "UIConfig.h"
#include "defines.h"
#include "ValueDefinition.h"


//
// Class name definition:
//
#define ClassFileSelectorDefinition	"FileSelectorDefinition"

//
// Forward definitions 
//
class ParameterDefinition;
class Interactor;

//
// FileSelectorDefinition class definition:
//				
class FileSelectorDefinition : public ValueDefinition 
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
    FileSelectorDefinition() { }

    //
    // Destructor:
    //
    ~FileSelectorDefinition() { }
	
    //
    // Allocate a new FileSelectorDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() { return ClassFileSelectorDefinition; }
};


#endif // _FileSelectorDefinition_h
