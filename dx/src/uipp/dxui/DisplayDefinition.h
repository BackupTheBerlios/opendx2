///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/DisplayDefinition.h,v 1.1 1999/03/31 22:31:19 gda Exp $
 *
 */


#ifndef _DisplayDefinition_h
#define _DisplayDefinition_h


#include "UIConfig.h"
#include "defines.h"
#include "DrivenDefinition.h"


//
// Class name definition:
//
#define ClassDisplayDefinition	"DisplayDefinition"

//
// Referenced classes
class Network;

//
// DisplayDefinition class definition:
//				
class DisplayDefinition : public DrivenDefinition
{
  private:
    //
    // Private member data:
    //

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
    DisplayDefinition();

    //
    // Destructor:
    //
    ~DisplayDefinition(){}

    //
    // Create a new Module and NodeDefinition of 'this' type. 
    //
    static NodeDefinition *AllocateDefinition();

    virtual boolean isAllowedInMacro() { return TRUE; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDisplayDefinition;
    }
};


#endif // _DisplayDefinition_h
