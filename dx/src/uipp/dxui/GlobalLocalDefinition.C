/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "GlobalLocalDefinition.h"
#include "GlobalLocalNode.h"

Node *GlobalLocalDefinition::newNode(Network *net, int inst)
{
    GlobalLocalNode *n = new GlobalLocalNode(this, net, inst);
    return n;
}

NodeDefinition *GlobalLocalDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new GlobalLocalDefinition();
}

