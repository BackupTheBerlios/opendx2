///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/MacroParameterDefinition.h,v 1.1 1999/03/31 22:32:47 gda Exp $
 *
 */


#ifndef _MacroParameterDefinition_h
#define _MacroParameterDefinition_h


#include "UIConfig.h"
#include "defines.h"
#include "List.h"
#include "NodeDefinition.h"


//
// Class name definition:
//
#define ClassMacroParameterDefinition	"MacroParameterDefinition"

//
// Referenced classes
class Network;
class MacroParameterNode;

//
// MacroParameterDefinition class definition:
//				
class MacroParameterDefinition : public NodeDefinition
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //
    virtual CDBAllocator getCDBAllocator();

    //
    // Allocate a new Node of the corresponding type.
    //
    virtual Node *newNode(Network *net, int instance = -1); 

  public:
    //
    // Constructor:
    //
    MacroParameterDefinition();

    //
    // Destructor:
    //
    ~MacroParameterDefinition();

    //
    // Create a new Module of 'this' type. 
    //
    static NodeDefinition *AllocateDefinition();

    void finishDefinition();
    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassMacroParameterDefinition;
    }
};


#endif // _MacroParameterDefinition_h
