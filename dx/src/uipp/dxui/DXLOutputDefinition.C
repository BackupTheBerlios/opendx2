/*  Open Visualization Data Explorer Source File */



#include "UIConfig.h"
#include "defines.h"
#include "DXLOutputDefinition.h"
#include "DXLOutputNode.h"
#include "ItalicLabeledStandIn.h"

NodeDefinition *DXLOutputDefinition::AllocateDefinition()
{
    return new DXLOutputDefinition;
}


DXLOutputDefinition::DXLOutputDefinition() : 
    DrivenDefinition()
{
}

Node *DXLOutputDefinition::newNode(Network *net, int instance)
{
    DXLOutputNode *d = new DXLOutputNode(this, net, instance);
    return d;
}

SIAllocator DXLOutputDefinition::getSIAllocator()
{
   return ItalicLabeledStandIn::AllocateStandIn;
}
