//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ScalarListDefinition.C,v 1.1 1999/03/31 22:34:14 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "ScalarListDefinition.h"
#include "ScalarListNode.h"

Node *ScalarListDefinition::newNode(Network *net, int inst)
{
    ScalarListNode *n = new ScalarListNode(this, net, inst, FALSE, 1);
    return n;
}

NodeDefinition *
ScalarListDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ScalarListDefinition;
}
