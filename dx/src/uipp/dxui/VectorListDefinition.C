/*  Open Visualization Data Explorer Source File */


//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "VectorListDefinition.h"
#include "ScalarListNode.h"

Node *VectorListDefinition::newNode(Network *net, int inst)
{
    ScalarListNode *n = new ScalarListNode(this, net, inst, TRUE, 3);
    return n;
}

NodeDefinition *
VectorListDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new VectorListDefinition;
}

