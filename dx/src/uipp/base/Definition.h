//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header
 *
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/Definition.h,v 1.1 1999/03/24 15:17:23 gda Exp $
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _Definition_h
#define _Definition_h


#include "UIConfig.h"
#include "defines.h"
#include "Base.h"
#include "SymbolManager.h"


//
// Forward declarations 
//


//
// Definition class definition:
//				
class Definition : public Base 
{
  private:
    //
    // Private member data:
    //
    Symbol	key;	// Key to look up item by (symbol value found in
			// symbol table returned by getSymbolManager().

  protected:
    //
    // Protected member data:
    //

  public:
    //
    // Constructor(s):
    //
    Definition() { key = 0; }
    Definition(Symbol k) { key = k; }

    //
    // Destructor:
    // We don't free any string symbols because we don't know who references 
    // them.
    //
    virtual ~Definition() { } 


    //
    // Get the key for this definition 
    //
    Symbol getNameSymbol() { return key; }

    const char *getNameString() 
			{ return theSymbolManager->getSymbolString(key); }

    //
    // Set the key for this definition 
    //
    Symbol setName(const char *name)
	{
	    this->key = theSymbolManager->registerSymbol(name);
	    return this->key;
	}

    //
    // Make this pure virtual so no instances of this class are created. 
    //
    virtual const char* getClassName() = 0; 
};


#endif // _Definition_h
