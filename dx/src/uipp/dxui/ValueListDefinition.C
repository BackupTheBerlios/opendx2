/*  Open Visualization Data Explorer Source File */

#include "UIConfig.h"
#include "defines.h"
#include "ValueListDefinition.h"
#include "ValueListNode.h"

Node *ValueListDefinition::newNode(Network *net, int inst)
{
    InteractorNode *n = new ValueListNode(this, net, inst);
    return n;
}

NodeDefinition *ValueListDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ValueListDefinition();
}

