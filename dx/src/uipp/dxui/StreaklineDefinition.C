/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "StreaklineDefinition.h"
#include "StreaklineNode.h"

Node *StreaklineDefinition::newNode(Network *net, int inst)
{
    StreaklineNode *n = new StreaklineNode(this, net, inst);
    return n;
}

NodeDefinition *StreaklineDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new StreaklineDefinition();
}

