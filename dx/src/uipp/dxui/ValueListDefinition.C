//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ValueListDefinition.C,v 1.1 1999/03/31 22:35:47 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "ValueListDefinition.h"
#include "ValueListNode.h"

Node *ValueListDefinition::newNode(Network *net, int inst)
{
    InteractorNode *n = new ValueListNode(this, net, inst);
    return n;
}

NodeDefinition *ValueListDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ValueListDefinition();
}

