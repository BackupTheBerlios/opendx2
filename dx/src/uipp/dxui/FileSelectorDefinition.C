//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/FileSelectorDefinition.C,v 1.1 1999/03/31 22:31:37 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "FileSelectorDefinition.h"
#include "FileSelectorNode.h"

Node *FileSelectorDefinition::newNode(Network *net, int inst)
{
    InteractorNode *n = new FileSelectorNode(this, net, inst);
    return n;
}

NodeDefinition *FileSelectorDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new FileSelectorDefinition();
}

