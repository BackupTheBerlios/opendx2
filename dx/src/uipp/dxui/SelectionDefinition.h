//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/SelectionDefinition.h,v 1.1 1999/03/31 22:34:26 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _SelectionDefinition_h
#define _SelectionDefinition_h

#include "UIConfig.h"
#include "defines.h"
#include "InteractorDefinition.h"


//
// Class name definition:
//
#define ClassSelectionDefinition	"SelectionDefinition"


//
// SelectionDefinition class definition:
//				
class SelectionDefinition : public InteractorDefinition 
{
  private:
	
  protected:
    //
    // Protected member data:
    //

  public:
    //
    // Constructor:
    //
    SelectionDefinition() { }

    //
    // Destructor:
    //
    ~SelectionDefinition() { }
	
    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() 
		{ return ClassSelectionDefinition; }
};


#endif // _SelectionDefinition_h
