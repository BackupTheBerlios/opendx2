/*  Open Visualization Data Explorer Source File */



#include "Link.h"


inline void Link::setElement(const void* element)
{
    this->element = element;
}


inline void Link::setNext(Link* next)
{
    this->next = next;
}


