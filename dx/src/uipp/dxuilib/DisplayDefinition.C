///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/DisplayDefinition.C,v 1.1 1999/03/24 15:17:39 gda Exp $
 *
 */


#include "UIConfig.h"
#include "defines.h"
#include "DisplayDefinition.h"
#include "DisplayNode.h"

NodeDefinition *DisplayDefinition::AllocateDefinition()
{
    return new DisplayDefinition;
}


DisplayDefinition::DisplayDefinition() : 
    DrivenDefinition()
{
}


Node *DisplayDefinition::newNode(Network *net, int instance)
{
    DisplayNode *d = new DisplayNode(this, net, instance);
    return d;
}

