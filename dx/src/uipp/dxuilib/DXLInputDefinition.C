///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/DXLInputDefinition.C,v 1.1 1999/03/24 15:17:39 gda Exp $
 *
 */


#include "UIConfig.h"
#include "defines.h"
#include "DXLInputDefinition.h"
#include "DXLInputNode.h"
#include "ItalicLabeledStandIn.h"

NodeDefinition *DXLInputDefinition::AllocateDefinition()
{
    return new DXLInputDefinition;
}


DXLInputDefinition::DXLInputDefinition() : 
    NodeDefinition()
{
}

Node *DXLInputDefinition::newNode(Network *net, int instance)
{
    DXLInputNode *d = new DXLInputNode(this, net, instance);
    return d;
}

SIAllocator DXLInputDefinition::getSIAllocator()
{
   return ItalicLabeledStandIn::AllocateStandIn;
}
