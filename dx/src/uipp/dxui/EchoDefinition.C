/*  Open Visualization Data Explorer Source File */


//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "EchoDefinition.h"
#include "EchoNode.h"

Node *EchoDefinition::newNode(Network *net, int inst)
{
    EchoNode *n = new EchoNode(this, net, inst);
    return n;
}

NodeDefinition *EchoDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new EchoDefinition();
}

