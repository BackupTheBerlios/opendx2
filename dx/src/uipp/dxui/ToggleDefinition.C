/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#include "UIConfig.h"
#include "defines.h"
#include "ToggleDefinition.h"
#include "ToggleNode.h"

Node *ToggleDefinition::newNode(Network *net, int inst)
{
    ToggleNode *n = new ToggleNode(this, net, inst);
    return n;
}

NodeDefinition *
ToggleDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ToggleDefinition;
}

