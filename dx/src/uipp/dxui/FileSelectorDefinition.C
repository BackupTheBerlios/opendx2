/*  Open Visualization Data Explorer Source File */
//////////////////////////////////////////////////////////////////////////////

#include <dxconfig.h>


#include "UIConfig.h"
#include "defines.h"
#include "FileSelectorDefinition.h"
#include "FileSelectorNode.h"

Node *FileSelectorDefinition::newNode(Network *net, int inst)
{
    InteractorNode *n = new FileSelectorNode(this, net, inst);
    return n;
}

NodeDefinition *FileSelectorDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new FileSelectorDefinition();
}

