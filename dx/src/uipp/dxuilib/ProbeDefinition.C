///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ProbeDefinition.C,v 1.1 1999/03/24 15:17:45 gda Exp $
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
