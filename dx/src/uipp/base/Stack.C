/*  Open Visualization Data Explorer Source File */




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




