///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ModuleMessagingNode.C,v 1.1 1999/03/24 15:17:43 gda Exp $
 *
 */


#include "UIConfig.h"
#include "defines.h"
#include "ModuleMessagingNode.h"

//
// Determine if this node is of the given class.
//
boolean ModuleMessagingNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassModuleMessagingNode);
    if (s == classname)
	return TRUE;
    else
	return this->Node::isA(classname);
}
