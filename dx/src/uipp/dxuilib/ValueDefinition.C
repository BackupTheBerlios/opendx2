//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ValueDefinition.C,v 1.1 1999/03/24 15:17:48 gda Exp $
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

