/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



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
