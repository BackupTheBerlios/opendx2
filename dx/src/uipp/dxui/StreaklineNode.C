///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/StreaklineNode.C,v 1.1 1999/03/31 22:35:15 gda Exp $
 *
 */



#include "UIConfig.h"
#include "defines.h"
#include "StreaklineNode.h"

#define NAME_NUM 1

StreaklineNode::StreaklineNode(NodeDefinition *nd, Network *net, int instnc) :
    Node(nd, net, instnc)
{
    this->setInputValue(NAME_NUM,this->getModuleMessageIdString(),
				DXType::StringType,FALSE);
}

StreaklineNode::~StreaklineNode()
{
}

//
// Determine if this node is of the given class.
//
boolean StreaklineNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassStreaklineNode);
    if (s == classname)
        return TRUE;
    else
        return this->Node::isA(classname);
}

int StreaklineNode::assignNewInstanceNumber()
{
    boolean isConnected = this->isInputConnected(NAME_NUM);
    int instance_number = this->Node::assignNewInstanceNumber();

    if (!isConnected)
	this->setInputValue(NAME_NUM,this->getModuleMessageIdString(), 
	    DXType::StringType,FALSE);

    return instance_number;
}

