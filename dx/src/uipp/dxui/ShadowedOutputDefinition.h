/*  Open Visualization Data Explorer Source File */


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
