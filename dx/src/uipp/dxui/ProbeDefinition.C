/*  Open Visualization Data Explorer Source File */


#include "UIConfig.h"
#include "defines.h"
#include "ProbeDefinition.h"
#include "ProbeNode.h"
#include "LabeledStandIn.h"

NodeDefinition *ProbeDefinition::AllocateDefinition()
{
    return new ProbeDefinition;
}


ProbeDefinition::ProbeDefinition() : 
    NodeDefinition()
{
}

SIAllocator ProbeDefinition::getSIAllocator()
{
   return LabeledStandIn::AllocateStandIn;
}


Node *ProbeDefinition::newNode(Network *net, int instance)
{
    return new ProbeNode(this, net, instance);
}
