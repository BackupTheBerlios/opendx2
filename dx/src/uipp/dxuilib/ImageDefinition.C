///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageDefinition.C,v 1.1 1999/03/24 15:17:41 gda Exp $
 *
 */


#include "UIConfig.h"
#include "defines.h"
#include "ImageDefinition.h"
#include "ImageNode.h"
#include "ImageCDB.h"
#include "ParameterDefinition.h"

NodeDefinition *ImageDefinition::AllocateDefinition()
{
    return new ImageDefinition;
}


ImageDefinition::ImageDefinition() : 
    NodeDefinition()
{
    this->defaultInternalCacheability = InternalsFullyCached;
}

void ImageDefinition::finishDefinition()
{
}


Node *ImageDefinition::newNode(Network *net, int instance)
{
    ImageNode *d = new ImageNode(this, net, instance);
    return d;
}

//
// Define the function that allocates CDB's for this node.
//
CDBAllocator ImageDefinition::getCDBAllocator()
{
   return ImageCDB::AllocateConfigurationDialog;
}

