//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// SelectorNode.h -							    //
//                                                                          //
// Definition for the SelectorNode class which implements Scalar,  	    //
// Integer, Vector and List version of these types of interactors	    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/SelectorNode.h,v 1.1 1999/03/24 15:17:46 gda Exp $
 */


#ifndef _SelectorNode_h
#define _SelectorNode_h


#include "defines.h"
#include "SelectionNode.h"
#include "List.h"

class Network;

//
// Class name definition:
//
#define ClassSelectorNode	"SelectorNode"

//
// SelectorNode class definition:
//				
class SelectorNode : public SelectionNode 
{
    friend class SelectorInstance;	// For setSelectedOptionIndex().
    friend class SelectorInteractor;	// For [un]deferVisualNotification().
    friend class SelectorToggleInteractor;// For [un]deferVisualNotification().

  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //

    //
    // Get a a SelectorInstance instead of an InteractorInstance.
    //
    InteractorInstance *newInteractorInstance();

    //
    // These define the initial values
    //
    virtual const char *getInitialValueList();
    virtual const char *getInitialStringList();

  public:
    //
    // Constructor:
    //
    SelectorNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~SelectorNode();

    //
    // Deselect all current selections and make the given index
    // the current selection.
    //
    void setSelectedOptionIndex(int index, boolean send = TRUE);

    //
    // If there is only one item selected, then return its index,
    // otherwise return 0.
    //
    int getSelectedOptionIndex();

    //
    // Determine if this node is a node of the given class
    //
    virtual boolean isA(Symbol classname);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSelectorNode;
    }
};


#endif // _SelectorNode_h


