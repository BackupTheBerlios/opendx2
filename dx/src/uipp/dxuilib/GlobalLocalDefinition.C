//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/GlobalLocalDefinition.C,v 1.1 1999/03/24 15:17:40 gda Exp $
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

