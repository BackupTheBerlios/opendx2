///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/UniqueNameNode.C,v 1.1 1999/03/31 22:35:38 gda Exp $
 *
 */

#include "UniqueNameNode.h"
#include "SymbolManager.h"

boolean UniqueNameNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol (ClassUniqueNameNode);
    if (s == classname)
	return TRUE;
    else
	return this->Node::isA(classname);
}

boolean UniqueNameNode::namesConflict 
    (const char* his_label, const char* my_label, const char* his_classname)
{
    return EqualString(his_label, my_label); 
}
