//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ScalarDefinition.C,v 1.1 1999/03/31 22:34:08 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "ScalarDefinition.h"
#include "ScalarNode.h"

Node *ScalarDefinition::newNode(Network *net, int inst)
{
    ScalarNode *n = new ScalarNode(this, net, inst);
    return n;
}

NodeDefinition *
ScalarDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ScalarDefinition;
}

