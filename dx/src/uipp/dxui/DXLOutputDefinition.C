///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/DXLOutputDefinition.C,v 1.1 1999/03/31 22:31:03 gda Exp $
 *
 */


#include "UIConfig.h"
#include "defines.h"
#include "DXLOutputDefinition.h"
#include "DXLOutputNode.h"
#include "ItalicLabeledStandIn.h"

NodeDefinition *DXLOutputDefinition::AllocateDefinition()
{
    return new DXLOutputDefinition;
}


DXLOutputDefinition::DXLOutputDefinition() : 
    DrivenDefinition()
{
}

Node *DXLOutputDefinition::newNode(Network *net, int instance)
{
    DXLOutputNode *d = new DXLOutputNode(this, net, instance);
    return d;
}

SIAllocator DXLOutputDefinition::getSIAllocator()
{
   return ItalicLabeledStandIn::AllocateStandIn;
}
