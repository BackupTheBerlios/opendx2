//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// Stack.h -			        		 	    //
//                                                                          //
// Definition for the Stack class.					    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/Stack.h,v 1.1 1999/03/24 15:17:24 gda Exp $
 *
 *
 */


#ifndef _Stack_h
#define _Stack_h


#include "defines.h"
#include "List.h"


//
// Class name definition:
//
#define ClassStack	"Stack"

//
// Stack class definition:
//				
class Stack : protected List
{

  public:

    Stack() { };

    ~Stack() { };

    void push(const void *datum);

    const void *peek();
    const void *pop();
    
    void clear();

    int getSize() { return this->List::getSize(); }

    const char* getClassName()
    {
        return ClassStack;
    }
}; 



#endif // _Stack_h
