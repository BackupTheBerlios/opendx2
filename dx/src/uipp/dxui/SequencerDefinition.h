///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/SequencerDefinition.h,v 1.1 1999/03/31 22:34:58 gda Exp $
 *
 */


#ifndef _SequencerDefinition_h
#define _SequencerDefinition_h


#include "UIConfig.h"
#include "defines.h"
#include "ShadowedOutputDefinition.h"


//
// Class name definition:
//
#define ClassSequencerDefinition	"SequencerDefinition"

//
// Referenced classes
class Network;

//
// SequencerDefinition class definition:
//				
class SequencerDefinition : public ShadowedOutputDefinition
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //

    //
    // Allocate a new Node of the corresponding type.
    //
    virtual Node *newNode(Network *net, int instance = -1); 


  public:
    //
    // Constructor:
    //
    SequencerDefinition() { }

    //
    // Destructor:
    //
    ~SequencerDefinition() { }

    //
    // Create a new Module and NodeDefinition of 'this' type. 
    //
    static NodeDefinition *AllocateDefinition();

#if 0 // Moved to DrivenNode 6/30/93
    virtual boolean isAllowedInMacro() { return FALSE; }
#endif

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSequencerDefinition;
    }
};


#endif // _SequencerDefinition_h
