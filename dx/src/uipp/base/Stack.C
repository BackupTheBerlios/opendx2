//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// Stack.C -			        		 	    //
//                                                                          //
// Definition for the Stack class.					    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/Stack.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 *
 *
 */



#include <string.h> 
#include "defines.h"
#include "Stack.h"


void Stack::push(const void *datum)
{
    this->insertElement(datum,1);  
}

const void *Stack::peek()
{
    return this->getElement(1);
}
const void *Stack::pop()
{
    const void *datum = this->peek();

    if (this->deleteElement(1))
	return datum;
    else
	return NULL;
}
    
void Stack::clear()
{
    this->List::clear();
}




