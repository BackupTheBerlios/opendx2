/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#include "UIConfig.h"
#include "defines.h"
#include "ResetDefinition.h"
#include "ResetNode.h"

Node *ResetDefinition::newNode(Network *net, int inst)
{
    ResetNode *n = new ResetNode(this, net, inst);
    return n;
}

NodeDefinition *
ResetDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ResetDefinition;
}

