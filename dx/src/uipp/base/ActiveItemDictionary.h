//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/ActiveItemDictionary.h,v 1.1 1999/03/24 15:17:22 gda Exp $
 */


#ifndef _ActiveItemDictionary_h
#define _ActiveItemDictionary_h


#include "defines.h"
#include "Dictionary.h"


//
// Class name definition:
//
#define ClassActiveItemDictionary	"ActiveItemDictionary"


//
// ActiveItemDictionary class definition:
//				
class ActiveItemDictionary : public Dictionary 
{
    friend DictionaryIterator;

  private:
    //
    // Private member data:
    //
    Symbol active;		// The 'active' item in the Dictionary.

  protected:
    //
    // Protected member data:
    //


  public:
    //
    // Constructor:
    //
    ActiveItemDictionary() { active = 0; }

    //
    // Destructor:
    //
    ~ActiveItemDictionary() {} 

    void setActiveItem(Symbol s) 
		{ ASSERT(this->findDefinition(s)); this->active = s;}
    Symbol getActiveItem() { return this->active; }
    int isActive() { return this->active != 0; }

    void *getActiveDefinition() { return this->findDefinition(this->active); }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassActiveItemDictionary;
    }
};


#endif // _ActiveItemDictionary_h
