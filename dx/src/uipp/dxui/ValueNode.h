//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ValueNode.h,v 1.1 1999/03/31 22:35:57 gda Exp $
 */


#ifndef _ValueNode_h
#define _ValueNode_h


#include "defines.h"
#include "NondrivenInteractorNode.h"

class InteractorInstance;
class NodeDefinition;
class Network;

//
// Class name definition:
//
#define ClassValueNode	"ValueNode"

//
// ValueNode class definition:
//				
class ValueNode : public NondrivenInteractorNode
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
    ValueNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~ValueNode();

    virtual boolean initialize();

    //
    // Determine if this node is a node of the given class
    //
    virtual boolean isA(Symbol classname);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassValueNode;
    }
};


#endif // _ValueNode_h