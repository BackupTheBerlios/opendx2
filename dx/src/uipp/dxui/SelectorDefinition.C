/*  Open Visualization Data Explorer Source File */

#include "UIConfig.h"
#include "defines.h"
#include "SelectorDefinition.h"
#include "SelectorNode.h"

Node *SelectorDefinition::newNode(Network *net, int inst)
{
    SelectorNode *n = new SelectorNode(this, net, inst);
    return n;
}

NodeDefinition *SelectorDefinition::AllocateDefinition()
{
    return new SelectorDefinition;
}
