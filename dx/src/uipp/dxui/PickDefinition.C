/*  Open Visualization Data Explorer Source File */


#include "UIConfig.h"
#include "defines.h"
#include "PickDefinition.h"
#include "PickNode.h"

NodeDefinition *PickDefinition::AllocateDefinition()
{
    return new PickDefinition;
}


PickDefinition::PickDefinition() : ProbeDefinition()
{
}

Node *PickDefinition::newNode(Network *net, int instance)
{
    return new PickNode(this, net, instance);
}
