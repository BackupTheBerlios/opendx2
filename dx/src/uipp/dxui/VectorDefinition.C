//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/VectorDefinition.C,v 1.1 1999/03/31 22:35:58 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "VectorDefinition.h"
#include "ScalarNode.h"

Node *VectorDefinition::newNode(Network *net, int inst)
{
    ScalarNode *n = new ScalarNode(this, net, inst, TRUE, 3);
    return n;
}

NodeDefinition *
VectorDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new VectorDefinition;
}
