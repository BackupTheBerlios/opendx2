/*  Open Visualization Data Explorer Source File */


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
