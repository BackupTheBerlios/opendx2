/*  Open Visualization Data Explorer Source File */


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
