//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/PrintDefinition.C,v 1.1 1999/03/31 22:33:42 gda Exp $

 $Log: PrintDefinition.C,v $
 Revision 1.1  1999/03/31 22:33:42  gda
 moved from dxuilib

 Revision 1.1.1.1  1999/03/24 15:17:44  gda
 Initial CVS Version

 Revision 1.1.1.1  1999/03/19 20:59:34  gda
 Initial CVS

 Revision 10.1  1999/02/23 22:05:22  gda
 OpenDX Baseline

 Revision 9.1  1997/05/22 19:37:45  svs
 Copy of release 3.1.4 code

Revision 8.0  1995/10/03  19:19:19  nsc
Copy of release 3.1 code

Revision 7.2  1994/07/12  22:51:07  dawood
Remove rcs log messages and make sure there is a header message.

Revision 7.1  1994/01/18  19:18:00  svs
changes since release 2.0.1

Revision 6.1  93/11/16  11:06:35  svs
ship level code, release 2.0

Revision 1.1  93/07/15  16:08:08  cpv
Initial revision

Revision 1.2  93/04/09  12:13:38  dawood
Added NodeDefinition::createNewNode() to supersede newNode().

Revision 1.1  93/03/24  15:49:39  dawood
Initial revision

 
 
 */

//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "PrintDefinition.h"
#include "PrintNode.h"

Node *PrintDefinition::newNode(Network *net, int inst)
{
    PrintNode *n = new PrintNode(this, net, inst);
    return n;
}

NodeDefinition *PrintDefinition::AllocateDefinition()
{
    return (NodeDefinition*) new PrintDefinition();
}

