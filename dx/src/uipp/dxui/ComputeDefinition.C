///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ComputeDefinition.C,v 1.1 1999/03/31 22:30:46 gda Exp $
 *
 */


#include "UIConfig.h"
#include "defines.h"
#include "ComputeDefinition.h"
#include "ComputeNode.h"
#include "ParameterDefinition.h"
#include "ComputeCDB.h"
#include "CDBAllocatorDictionary.h"

NodeDefinition *ComputeDefinition::AllocateDefinition()
{
    return new ComputeDefinition;
}


ComputeDefinition::ComputeDefinition() : 
    NodeDefinition()
{
}


Node *ComputeDefinition::newNode(Network *net, int instance)
{
    ComputeNode *c = new ComputeNode(this, net, instance);
    return c;
}


void ComputeDefinition::finishDefinition()
{
    ParameterDefinition *p = this->getInputDefinition(1);
    p->setDefaultVisibility(FALSE);
}


//
// Define the function that allocates CDB's for this node.
//
CDBAllocator ComputeDefinition::getCDBAllocator()
{
   return ComputeCDB::AllocateConfigurationDialog;
}

