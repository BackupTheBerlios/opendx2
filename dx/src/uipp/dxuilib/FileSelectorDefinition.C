//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/FileSelectorDefinition.C,v 1.1 1999/03/24 15:17:40 gda Exp $
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

