//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ValueDefinition.C,v 1.1 1999/03/31 22:35:41 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "ValueDefinition.h"
#include "ValueNode.h"

Node *ValueDefinition::newNode(Network *net, int inst)
{
    InteractorNode *n = new ValueNode(this, net, inst);
    return n;
}

NodeDefinition *ValueDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ValueDefinition();
}

