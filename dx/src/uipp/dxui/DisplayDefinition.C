/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#include "UIConfig.h"
#include "defines.h"
#include "DisplayDefinition.h"
#include "DisplayNode.h"

NodeDefinition *DisplayDefinition::AllocateDefinition()
{
    return new DisplayDefinition;
}


DisplayDefinition::DisplayDefinition() : 
    DrivenDefinition()
{
}


Node *DisplayDefinition::newNode(Network *net, int instance)
{
    DisplayNode *d = new DisplayNode(this, net, instance);
    return d;
}

