//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// PickDefinition.C -							    //
//                                                                          //
// PickDefinition Class methods and other related functions/procedures.    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/PickDefinition.C,v 1.1 1999/03/24 15:17:44 gda Exp $
 *
 */

#include "UIConfig.h"
#include "defines.h"
#include "PickDefinition.h"
#include "PickNode.h"

NodeDefinition *PickDefinition::AllocateDefinition()
{
    return new PickDefinition;
}


PickDefinition::PickDefinition() : ProbeDefinition()
{
}

Node *PickDefinition::newNode(Network *net, int instance)
{
    return new PickNode(this, net, instance);
}
