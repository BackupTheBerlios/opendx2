///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/TransmitterDefinition.C,v 1.1 1999/03/24 15:17:48 gda Exp $
 *
 */


#include "UIConfig.h"
#include "defines.h"
#include "TransmitterDefinition.h"
#include "TransmitterNode.h"
#include "ItalicLabeledStandIn.h"

NodeDefinition *TransmitterDefinition::AllocateDefinition()
{
    return new TransmitterDefinition;
}


TransmitterDefinition::TransmitterDefinition() : 
    NodeDefinition()
{
}


Node *TransmitterDefinition::newNode(Network *net, int instance)
{
    TransmitterNode *d = new TransmitterNode(this, net, instance);
    return d;
}

SIAllocator TransmitterDefinition::getSIAllocator()
{
   return ItalicLabeledStandIn::AllocateStandIn;
}

