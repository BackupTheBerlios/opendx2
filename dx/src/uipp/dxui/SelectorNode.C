//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// SelectorNode.C -							    //
//                                                                          //
// Definition for the SelectorNode class which implements Scalar,	    //
// Integer, Vector and List version of these types of interactors	    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/SelectorNode.C,v 1.1 1999/03/31 22:34:47 gda Exp $
 */


#include "UIConfig.h"
#include "defines.h"
#include "SelectorNode.h"
#include "SelectorInstance.h"


SelectorNode::SelectorNode(NodeDefinition *nd, Network *net, int instnc) :
                SelectionNode(nd, net, instnc) 
{ 
}
SelectorNode::~SelectorNode()
{
}
//
// Get a a SelectorInstance instead of an InteractorInstance.
//
InteractorInstance *SelectorNode::newInteractorInstance()
{
    SelectorInstance *si = new SelectorInstance(this);
    return (SelectorInstance*)si;
}

//
// Determine if this node is of the given class.
//
boolean SelectorNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassSelectorNode);
    if (s == classname)
	return TRUE;
    else
	return this->InteractorNode::isA(classname);
}
//
// Deselect all current selections and make the given index
// the current selection.
//
void SelectorNode::setSelectedOptionIndex(int index, boolean send)
{
    if (this->getSelectedOptionIndex() == index)
	return;

    this->setSelectedOptions(&index,1,send,send);
}
//
// If there is only one item selectegd, then return its index.
// otherwise return 0. 
//
int SelectorNode::getSelectedOptionIndex()
{
    if (this->getSelectedOptionCount() != 1)
	return 0;

    return (int)this->selectedOptions.getElement(1);
}

//
// These define the initial values
//
const char *SelectorNode::getInitialValueList()
{
    return "{ 1 0 }";
}
const char *SelectorNode::getInitialStringList()
{
    return "{ \"on\" \"off\" }";
}

