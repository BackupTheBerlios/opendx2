/*  Open Visualization Data Explorer Source File */


//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "VectorDefinition.h"
#include "ScalarNode.h"

Node *VectorDefinition::newNode(Network *net, int inst)
{
    ScalarNode *n = new ScalarNode(this, net, inst, TRUE, 3);
    return n;
}

NodeDefinition *
VectorDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new VectorDefinition;
}
