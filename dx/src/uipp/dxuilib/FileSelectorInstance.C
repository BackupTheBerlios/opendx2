//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/FileSelectorInstance.C,v 1.1 1999/03/24 15:17:40 gda Exp $
 */


#include "UIConfig.h"
#include "defines.h"
#include "FileSelectorInstance.h"
#include "FileSelectorNode.h"


FileSelectorInstance::FileSelectorInstance(FileSelectorNode *n) : 
				ValueInstance(n)
{ 
    this->fileFilter = NULL;
}
	
FileSelectorInstance::~FileSelectorInstance() 
{ 
    if (this->fileFilter)
	delete this->fileFilter;
} 
void FileSelectorInstance::setFileFilter(const char *filter) 
{
    if (this->fileFilter)
	delete this->fileFilter;
    this->fileFilter = DuplicateString(filter);
}

