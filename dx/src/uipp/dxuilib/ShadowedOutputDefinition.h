//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
// This class does not define any methods but is defined so that the 
// NodeDefinition class hierarchy matches that of the Node class.
//
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ShadowedOutputDefinition.h,v 1.1 1999/03/24 15:17:47 gda Exp $
 *
 */


#ifndef _ShadowedOutputDefinition_h
#define _ShadowedOutputDefinition_h

// #include <Xm/Xm.h>

#include "UIConfig.h"
#include "defines.h"
#include "DrivenDefinition.h"

//
// Class name definition:
//
#define ClassShadowedOutputDefinition	"ShadowedOutputDefinition"

//
// Forward definitions 
//

//
// ShadowedOutputDefinition class definition:
//				
class ShadowedOutputDefinition : public DrivenDefinition 
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
    ShadowedOutputDefinition() { }

    //
    // Destructor:
    //
    ~ShadowedOutputDefinition() { }
	
    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() { return ClassShadowedOutputDefinition; }
};


#endif // _ShadowedOutputDefinition_h
