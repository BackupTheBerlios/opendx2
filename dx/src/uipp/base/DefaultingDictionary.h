/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _DefaultingDictionary_h
#define _DefaultingDictionary_h


#include "defines.h"
#include "List.h"
#include "Dictionary.h"


//
// Class name definition:
//
#define ClassDefaultingDictionary	"DefaultingDictionary"


//
// DefaultingDictionary class definition:
//				
class DefaultingDictionary : public Dictionary
{
  private:
    //
    // Private member data:
    //
    List	default_stack;	// First element contains the current default

  protected:
    //
    // Protected member data:
    //


  public:
    //
    // Constructor:
    //
    DefaultingDictionary(){}

    //
    // Destructor:
    //
    ~DefaultingDictionary(){ default_stack.clear(); }


    boolean pushDefaultDefinition(const void *def)
		{ return default_stack.insertElement(def,1); }

    const void *popDefaultDefinition()
		{ const void *v = default_stack.getElement(1);
		  if (v) default_stack.deleteElement(1);
		  return v; }

    void *findDefinition(Symbol name)
		{ void *v = Dictionary::findDefinition(name); 
		  if (!v) v = (void*)default_stack.getElement(1);
		  return v; }
		
    void *findDefinition(const char *name)
		{ void *v = Dictionary::findDefinition(name); 
		  if (!v) v = (void*)default_stack.getElement(1);
		  return v; }
    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDefaultingDictionary;
    }
};


#endif // _DefaultingDictionary_h
