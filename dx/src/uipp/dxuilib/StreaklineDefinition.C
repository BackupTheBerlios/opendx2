//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/StreaklineDefinition.C,v 1.1 1999/03/24 15:17:48 gda Exp $
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "StreaklineDefinition.h"
#include "StreaklineNode.h"

Node *StreaklineDefinition::newNode(Network *net, int inst)
{
    StreaklineNode *n = new StreaklineNode(this, net, inst);
    return n;
}

NodeDefinition *StreaklineDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new StreaklineDefinition();
}

