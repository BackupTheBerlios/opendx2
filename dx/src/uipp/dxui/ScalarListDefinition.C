/*  Open Visualization Data Explorer Source File */

#include "UIConfig.h"
#include "defines.h"
#include "ScalarListDefinition.h"
#include "ScalarListNode.h"

Node *ScalarListDefinition::newNode(Network *net, int inst)
{
    ScalarListNode *n = new ScalarListNode(this, net, inst, FALSE, 1);
    return n;
}

NodeDefinition *
ScalarListDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ScalarListDefinition;
}
