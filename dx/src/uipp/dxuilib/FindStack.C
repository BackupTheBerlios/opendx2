//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// FindStack.C -			        		 	    //
//                                                                          //
// Definition for the Stack class.					    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/FindStack.C,v 1.1 1999/03/24 15:17:40 gda Exp $
 *
 */



#include <string.h> 
#include "defines.h"
#include "FindStack.h"

//
// FindStackElement class definition
//
class FindStackElement
{
  friend class FindStack;

  private:

    char   name[64];		// FIXME: these should be duplicated
    char   label[64];		// FIXME: these should be duplicated
    int    instance;

  public:

    FindStackElement(char* name, int instance, char *label)
    {
        strcpy(this->name, name);
        strcpy(this->label, label);
        this->instance = instance;
    };

    ~FindStackElement() { };
};



void FindStack::push(char* name, int instance, char* label)
{
    FindStackElement* element = new FindStackElement(name, instance, label);
    this->Stack::push((const void*)element);
}

boolean FindStack::pop(char* name, int* instance, char* label)
{
    FindStackElement* element;

    element = (FindStackElement*)this->Stack::pop();
    if (element) {
       strcpy(name, element->name);
       strcpy(label, element->label);
       *instance = element->instance;
       delete element;
       return (TRUE); 
    }  

    return (FALSE);
}
    
void FindStack::clear()
{
    FindStackElement *element;

    while (element = (FindStackElement *)this->Stack::pop())
       delete element;

    this->Stack::clear();
}

