/*  Open Visualization Data Explorer Source File */

#include "UIConfig.h"
#include "defines.h"
#include "ScalarDefinition.h"
#include "ScalarNode.h"

Node *ScalarDefinition::newNode(Network *net, int inst)
{
    ScalarNode *n = new ScalarNode(this, net, inst);
    return n;
}

NodeDefinition *
ScalarDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ScalarDefinition;
}

