//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// Link.h -								    //
//                                                                          //
// Definition for the Link class.					    //
//                                                                          //
// The instances of this class serve as individual link/element	containers  //
// within a list, implmented by the List class and iterated via ListItera-  //
// tor class; e.g., this class is intended to be used by the List and List- //
// Iterator classes.  To this end, the entire class is declared to be pri-  //
// vate.								    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/Link.h,v 1.1 1999/03/24 15:17:23 gda Exp $
 */


#ifndef _Link_h
#define _Link_h


#include "defines.h"
#include "Base.h"


//
// Class name definition:
//
#define ClassLink	"Link"


//
// Referenced classes:
//
class List;
class ListIterator;

//
// Link class definition:
//				
class Link : public Base
{
    //
    // Friend classes:
    //
    friend class List;
    friend class ListIterator;
    friend class DictionaryIterator;
    friend class FindStack;

  private:
    //
    // Private member data:
    //
    const void* element; // pointer to the element
    Link*       next;	 // pointer to the next link

    //
    // Constructor:
    //   Made private to prevent general instantiation.
    //   Intended to be instantiated by List class objects only.
    //
    Link()
    {	
	//
	// Initialize instance data.
	//
	this->element = NUL(void*);
	this->next    = 0;
    }



    //
    // Destructor:
    //
    ~Link(){}

    //
    // Sets the element pointer.
    //
    void setElement(const void* element);

    //
    // Sets the pointer to the next link.
    //
    void setNext(Link* next);

    //
    // Returns the element pointer;
    //
    const void* getElement()
    {
	return this->element;
    }

    //
    // Returns a pointer to the next link.
    //
    Link* getNext()
    {
	ASSERT(this);
	return this->next;
    }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassLink;
    }
};


#endif // _Link_h
