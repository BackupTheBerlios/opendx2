/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#include "UIConfig.h"
#include "defines.h"
#include "ValueDefinition.h"
#include "ValueNode.h"

Node *ValueDefinition::newNode(Network *net, int inst)
{
    InteractorNode *n = new ValueNode(this, net, inst);
    return n;
}

NodeDefinition *ValueDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ValueDefinition();
}

