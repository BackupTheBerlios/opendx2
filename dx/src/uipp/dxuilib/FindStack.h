//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// FindStack.h -			        		 	    //
//                                                                          //
// Definition for the Stack class.					    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/FindStack.h,v 1.1 1999/03/24 15:17:40 gda Exp $
 *
 */


#ifndef _FindStack_h
#define _FindStack_h


#include "defines.h"
#include "Stack.h"


//
// Class name definition:
//
#define ClassFindStack	"FindStack"

//
// FindStack class definition:
//				
class FindStack : protected Stack 
{

  public:

    FindStack() : Stack() { };

    ~FindStack() { this->clear(); };

    void push(char* name, int instance, char *label);

    boolean pop(char* name, int* instance, char *label);
    
    void clear();

    int getSize() { return this->Stack::getSize(); }

    const char* getClassName()
    {
        return ClassFindStack;
    }
}; 



#endif // _FindStack_h
