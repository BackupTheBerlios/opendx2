//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/GlobalLocalDefinition.C,v 1.1 1999/03/31 22:31:46 gda Exp $
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "GlobalLocalDefinition.h"
#include "GlobalLocalNode.h"

Node *GlobalLocalDefinition::newNode(Network *net, int inst)
{
    GlobalLocalNode *n = new GlobalLocalNode(this, net, inst);
    return n;
}

NodeDefinition *GlobalLocalDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new GlobalLocalDefinition();
}

