//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ValueListNode.h,v 1.1 1999/03/31 22:35:54 gda Exp $
 */


#ifndef _ValueListNode_h
#define _ValueListNode_h


#include "UIConfig.h"
#include "defines.h"
#include "ValueNode.h"

//
// Class name definition:
//
#define ClassValueListNode	"ValueListNode"

//
// ValueListNode class definition:
//				
class ValueListNode : public ValueNode
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
    // Get a new interactor instance for this class.
    // Derived classes can override this to allocated subclasses of 
    // InteractorInstance which may be specific to the derived class.
    //
    virtual	InteractorInstance *newInteractorInstance();

  public:
    //
    // Constructor:
    //
    ValueListNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~ValueListNode();

    //
    // Determine if this node is a node of the given class
    //
    virtual boolean isA(Symbol classname);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassValueListNode;
    }
};


#endif // _ValueListNode_h
