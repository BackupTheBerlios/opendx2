/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#include "UIConfig.h"
#include "defines.h"
#include "DXLInputDefinition.h"
#include "DXLInputNode.h"
#include "ItalicLabeledStandIn.h"

NodeDefinition *DXLInputDefinition::AllocateDefinition()
{
    return new DXLInputDefinition;
}


DXLInputDefinition::DXLInputDefinition() : 
    NodeDefinition()
{
}

Node *DXLInputDefinition::newNode(Network *net, int instance)
{
    DXLInputNode *d = new DXLInputNode(this, net, instance);
    return d;
}

SIAllocator DXLInputDefinition::getSIAllocator()
{
   return ItalicLabeledStandIn::AllocateStandIn;
}
