//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// SelectorListNode.C -							    //
//                                                                          //
// Definition for the SelectorListNode class which implements Scalar,	    //
// Integer, Vector and List version of these types of interactors	    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/SelectorListNode.C,v 1.1 1999/03/31 22:34:42 gda Exp $
 */


#include "UIConfig.h"
#include "defines.h"
#include "SelectorListNode.h"
#include "SelectorListInstance.h"


SelectorListNode::SelectorListNode(NodeDefinition *nd, 
			Network *net, int instnc) : 
				SelectionNode(nd, net, instnc,TRUE) 
{ 
}
SelectorListNode::~SelectorListNode()
{
}
//
// Get a a SelectorListInstance instead of an InteractorInstance.
//
InteractorInstance *SelectorListNode::newInteractorInstance()
{
    SelectorListInstance *si = new SelectorListInstance(this);
    return (SelectorListInstance*)si;
}

//
// Determine if this node is of the given class.
//
boolean SelectorListNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassSelectorListNode);
    if (s == classname)
	return TRUE;
    else
	return this->InteractorNode::isA(classname);
}
//
// These define the initial values
//
const char *SelectorListNode::getInitialValueList()
{
    return "{ 0 1 2}";
}
const char *SelectorListNode::getInitialStringList()
{
    return "{ \"0\" \"1\" \"2\" }";
}

