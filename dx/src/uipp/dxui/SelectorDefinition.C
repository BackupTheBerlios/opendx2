//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/SelectorDefinition.C,v 1.1 1999/03/31 22:34:30 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "SelectorDefinition.h"
#include "SelectorNode.h"

Node *SelectorDefinition::newNode(Network *net, int inst)
{
    SelectorNode *n = new SelectorNode(this, net, inst);
    return n;
}

NodeDefinition *SelectorDefinition::AllocateDefinition()
{
    return new SelectorDefinition;
}
