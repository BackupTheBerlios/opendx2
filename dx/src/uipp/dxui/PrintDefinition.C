/*  Open Visualization Data Explorer Source File */


#include "UIConfig.h"
#include "defines.h"
#include "PrintDefinition.h"
#include "PrintNode.h"

Node *PrintDefinition::newNode(Network *net, int inst)
{
    PrintNode *n = new PrintNode(this, net, inst);
    return n;
}

NodeDefinition *PrintDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new PrintDefinition();
}

