//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/VectorListDefinition.C,v 1.1 1999/03/24 15:17:48 gda Exp $
 *
 */

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

