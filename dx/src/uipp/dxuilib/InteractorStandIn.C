//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/InteractorStandIn.C,v 1.1 1999/03/24 15:17:43 gda Exp $
 */


#include "defines.h"
#include "InteractorNode.h"
#include "InteractorStandIn.h"
#include "Interactor.h"
#include "ControlPanel.h"
#include "Network.h"

//
// Static allocator found in theSIAllocatorDictionary
//
StandIn *InteractorStandIn::AllocateStandIn(WorkSpace *w, Node *node)
{
    StandIn *si = new InteractorStandIn(w,node);
    si->createStandIn();
    return si;
}
//
// Called when the StandIn has been selected by the Editor.
//
void InteractorStandIn::handleSelectionChange(boolean selected)
{
    int i;
    Node *n = this->node;
    Network *net = n->getNetwork();
    ControlPanel *cp;

    //
    // Tell all the network's control panel's that the selection
    // has changed.
    //
    for (i=1 ; cp = net->getPanelByIndex(i) ; i++) {
	cp->handleNodeStatusChange(node, selected ? 
				Interactor::InteractorSelected : 
				Interactor::InteractorDeselected);
    }

    // And finally, call the super class's method. 
    this->StandIn::handleSelectionChange(selected);
}


