//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ValueInstance.C,v 1.1 1999/03/24 15:17:48 gda Exp $
 */


#include "UIConfig.h"
#include "defines.h"
#include "ValueInstance.h"
#include "ValueNode.h"


ValueInstance::ValueInstance(ValueNode *n) : InteractorInstance(n)
{ 
}
	
ValueInstance::~ValueInstance() 
{ 
} 

#if 0  // This is moved to ValueInteractor on 4/9/93
//
// Get the current text value. For String and Value nodes, this is saved
// globally with the node, but for String/ValueListNodes, this is stored
// with the instance and is probably the currenlty selected list item.
//
const char *ValueInstance::getCurrentTextValue()
{
    Node *n = this->getNode();
    return n->getOutputValueString(1);
}

#endif
