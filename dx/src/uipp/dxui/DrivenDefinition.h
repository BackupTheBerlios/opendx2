//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/DrivenDefinition.h,v 1.1 1999/03/31 22:31:25 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef _DrivenDefinition_h
#define _DrivenDefinition_h

#include <Xm/Xm.h>

#include "UIConfig.h"
#include "defines.h"
#include "NodeDefinition.h"
#include "SIAllocatorDictionary.h"


//
// Class name definition:
//
#define ClassDrivenDefinition	"DrivenDefinition"

//
// Forward definitions 
//
class Parameter;
class ParameterDefinition;
class Node;

//
// DrivenDefinition class definition:
//				
class DrivenDefinition : public NodeDefinition 
{
  private:
	
  protected:
    //
    // Protected member data:
    //

    //
    // Driven nodes use AttributeParameters as input parameteters.
    //
    virtual Parameter *newParameter(ParameterDefinition *pd, 
							Node *n, int index);
    //
    // Mark all outputs as cache once with read-only cache attributes
    // (as per the semantics of data-driven interactors).
    // This helps to force an execution when inputs change that must have
    // their values communicated back to the User Interface.
    //
    void finishDefinition();

  public:
    //
    // Constructor:
    //
    DrivenDefinition() { }

    //
    // Destructor:
    //
    ~DrivenDefinition() { }
	
    virtual boolean isAllowedInMacro() { return FALSE; }

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() 
	{ return ClassDrivenDefinition; }
};


#endif // _DrivenDefinition_h
