//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// ValueListNode.C -							    //
//                                                                          //
// ValueListNode Class methods and other related functions/procedures.	    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ValueListNode.C,v 1.1 1999/03/24 15:17:48 gda Exp $
 */


#include "UIConfig.h"
#include "defines.h"
#include "ValueListNode.h"
#include "ValueListInstance.h"

//
// The Constructor... 
//
ValueListNode::ValueListNode(NodeDefinition *nd, Network *net, int instnc) :
                        ValueNode(nd, net, instnc)
{ 
}

//
// Destructure: needs to delete all its instances. 
//
ValueListNode::~ValueListNode()
{
}
InteractorInstance* ValueListNode::newInteractorInstance()
{
    ValueListInstance *ii;

    ii = new ValueListInstance(this);

    return ii;
}
//
// Determine if this node is of the given class.
//
boolean ValueListNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassValueListNode);
    if (s == classname)
	return TRUE;
    else
	return this->ValueNode::isA(classname);
}
