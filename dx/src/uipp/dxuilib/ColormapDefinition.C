//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// ColormapDefinition.C -						    //
//                                                                          //
// ColormapDefinition Class methods and other related 		    //
// functions/procedures.						    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ColormapDefinition.C,v 1.1 1999/03/24 15:17:38 gda Exp $
 *
 */

#include "UIConfig.h"
#include "defines.h"
#include "ColormapDefinition.h"
#include "ColormapNode.h"

NodeDefinition *ColormapDefinition::AllocateDefinition()
{
    return new ColormapDefinition;
}


ColormapDefinition::ColormapDefinition() : DrivenDefinition()
{
}

Node *ColormapDefinition::newNode(Network *net, int instance)
{
    ColormapNode *n = new ColormapNode(this, net, instance);
    return n;
}
