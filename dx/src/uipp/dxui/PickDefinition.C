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
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/PickDefinition.C,v 1.1 1999/03/31 22:33:37 gda Exp $
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
