//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/SelectorListDefinition.C,v 1.1 1999/03/31 22:34:36 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "SelectorListDefinition.h"
#include "SelectorListNode.h"

Node *SelectorListDefinition::newNode(Network *net, int inst)
{
    SelectorListNode *n = new SelectorListNode(this, net, inst);
    return n;
}

NodeDefinition *SelectorListDefinition::AllocateDefinition()
{
    return new SelectorListDefinition;
}
