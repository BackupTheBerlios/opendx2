//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/StreaklineDefinition.h,v 1.1 1999/03/31 22:35:13 gda Exp $
 *
 * 
 */
//////////////////////////////////////////////////////////////////////////////


#ifndef _StreaklineDefinition_h
#define _StreaklineDefinition_h

#include <Xm/Xm.h>

#include "UIConfig.h"
#include "defines.h"
#include "NodeDefinition.h"


//
// Class name definition:
//
#define ClassStreaklineDefinition	"StreaklineDefinition"

//
// StreaklineDefinition class definition:
//				
class StreaklineDefinition : public NodeDefinition 
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
    StreaklineDefinition() { }

    //
    // Destructor:
    //
    ~StreaklineDefinition() { }
	
    //
    // Allocate a new StreaklineDefinition.  
    // This function is intended to be used as an allocator in
    // theNDAllocatorDictionary.
    //
    static NodeDefinition *AllocateDefinition();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() { return ClassStreaklineDefinition; }
};


#endif // _StreaklineDefinition_h