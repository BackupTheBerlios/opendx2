/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#include "UIConfig.h"
#include "defines.h"
#include "ColormapDefinition.h"
#include "ColormapNode.h"

NodeDefinition *ColormapDefinition::AllocateDefinition()
{
    return new ColormapDefinition;
}


ColormapDefinition::ColormapDefinition() : DrivenDefinition()
{
}

Node *ColormapDefinition::newNode(Network *net, int instance)
{
    ColormapNode *n = new ColormapNode(this, net, instance);
    return n;
}
