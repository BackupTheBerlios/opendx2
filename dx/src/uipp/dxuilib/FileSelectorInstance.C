/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>




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

