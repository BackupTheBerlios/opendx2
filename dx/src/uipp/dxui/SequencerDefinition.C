//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// SequencerDefinition.C -						    //
//                                                                          //
// SequencerDefinition Class methods and other related functions/procedures.//
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/SequencerDefinition.C,v 1.1 1999/03/31 22:34:56 gda Exp $
 *
 */

#include "defines.h"
#include "SequencerDefinition.h"
#include "SequencerNode.h"
#include "ErrorDialogManager.h"
#include "Network.h"

NodeDefinition *SequencerDefinition::AllocateDefinition()
{
    return new SequencerDefinition;
}

Node *SequencerDefinition::newNode(Network *net, int instance)
{
    const char *node_name = this->getNameString();

    if (net->findNode(theSymbolManager->registerSymbol(node_name),0))
    {
        ErrorMessage("Only one %s is allowed in a network.",node_name);
        return NULL;
    }
    SequencerNode *d = new SequencerNode(this, net, instance);

    return d;
}
