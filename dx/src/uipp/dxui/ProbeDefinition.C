///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ProbeDefinition.C,v 1.1 1999/03/31 22:33:48 gda Exp $
 *
 */

#include "UIConfig.h"
#include "defines.h"
#include "ProbeDefinition.h"
#include "ProbeNode.h"
#include "LabeledStandIn.h"

NodeDefinition *ProbeDefinition::AllocateDefinition()
{
    return new ProbeDefinition;
}


ProbeDefinition::ProbeDefinition() : 
    NodeDefinition()
{
}

SIAllocator ProbeDefinition::getSIAllocator()
{
   return LabeledStandIn::AllocateStandIn;
}


Node *ProbeDefinition::newNode(Network *net, int instance)
{
    return new ProbeNode(this, net, instance);
}
