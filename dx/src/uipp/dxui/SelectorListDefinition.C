/*  Open Visualization Data Explorer Source File */


//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "SelectorListDefinition.h"
#include "SelectorListNode.h"

Node *SelectorListDefinition::newNode(Network *net, int inst)
{
    SelectorListNode *n = new SelectorListNode(this, net, inst);
    return n;
}

NodeDefinition *SelectorListDefinition::AllocateDefinition()
{
    return new SelectorListDefinition;
}
