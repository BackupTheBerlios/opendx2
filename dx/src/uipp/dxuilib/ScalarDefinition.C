//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ScalarDefinition.C,v 1.1 1999/03/24 15:17:45 gda Exp $
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

