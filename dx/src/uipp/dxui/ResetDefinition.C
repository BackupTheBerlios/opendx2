//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ResetDefinition.C,v 1.1 1999/03/31 22:34:00 gda Exp $
 *
 * 
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "ResetDefinition.h"
#include "ResetNode.h"

Node *ResetDefinition::newNode(Network *net, int inst)
{
    ResetNode *n = new ResetNode(this, net, inst);
    return n;
}

NodeDefinition *
ResetDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new ResetDefinition;
}

