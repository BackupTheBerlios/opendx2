//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ToggleDefinition.C,v 1.1 1999/03/31 22:35:18 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "ToggleDefinition.h"
#include "ToggleNode.h"

Node *ToggleDefinition::newNode(Network *net, int inst)
{
    ToggleNode *n = new ToggleNode(this, net, inst);
    return n;
}

NodeDefinition *
ToggleDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ToggleDefinition;
}

