/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#include "UIConfig.h"
#include "defines.h"
#include "TransmitterDefinition.h"
#include "TransmitterNode.h"
#include "ItalicLabeledStandIn.h"

NodeDefinition *TransmitterDefinition::AllocateDefinition()
{
    return new TransmitterDefinition;
}


TransmitterDefinition::TransmitterDefinition() : 
    NodeDefinition()
{
}


Node *TransmitterDefinition::newNode(Network *net, int instance)
{
    TransmitterNode *d = new TransmitterNode(this, net, instance);
    return d;
}

SIAllocator TransmitterDefinition::getSIAllocator()
{
   return ItalicLabeledStandIn::AllocateStandIn;
}

