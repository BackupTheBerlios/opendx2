/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



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
