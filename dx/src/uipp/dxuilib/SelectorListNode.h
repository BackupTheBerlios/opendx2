//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// SelectorListNode.h -							    //
//                                                                          //
// Definition for the SelectorListNode class which implements Scalar,  	    //
// Integer, Vector and List version of these types of interactors	    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/SelectorListNode.h,v 1.1 1999/03/24 15:17:46 gda Exp $
 */


#ifndef _SelectorListNode_h
#define _SelectorListNode_h


#include "defines.h"
#include "SelectionNode.h"
#include "List.h"

class Network;

//
// Class name definition:
//
#define ClassSelectorListNode	"SelectorListNode"

//
// SelectorListNode class definition:
//				
class SelectorListNode : public SelectionNode 
{
    friend class SelectorListToggleInteractor;// For [un]deferVisualNotification().

  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //

    //
    // Get a a SelectorListInstance instead of an InteractorInstance.
    //
    virtual InteractorInstance *newInteractorInstance();

    //
    // These define the initial values
    //
    virtual const char *getInitialValueList();
    virtual const char *getInitialStringList();

  public:
    //
    // Constructor:
    //
    SelectorListNode(NodeDefinition *nd, Network *net, int instnc);


    //
    // Destructor:
    //
    ~SelectorListNode();

    //
    // Determine if this node is a node of the given class
    //
    virtual boolean isA(Symbol classname);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSelectorListNode;
    }
};


#endif // _SelectorListNode_h


