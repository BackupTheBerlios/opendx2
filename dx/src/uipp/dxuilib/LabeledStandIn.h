//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/LabeledStandIn.h,v 1.1 1999/03/24 15:17:43 gda Exp $
 */



#ifndef _LabeledStandIn_h
#define _LabeledStandIn_h


#include "defines.h"
#include "StandIn.h"


//
// Class name definition:
//
#define ClassLabeledStandIn	"LabeledStandIn"

//
// LabeledStandIn class definition:
//				

class LabeledStandIn : public StandIn
{
  private:
    static boolean ClassInitialized;

    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //
    static String  DefaultResources[];
    virtual const char *getButtonLabel();

    //
    // Constructor:
    //
    LabeledStandIn(WorkSpace *w, Node *node);

  public:
    //
    // Allocator that is installed in theSIAllocatorDictionary
    //
    static StandIn *AllocateStandIn(WorkSpace *w, Node *n);

    //
    // Destructor:
    //
    ~LabeledStandIn();

    virtual void initialize();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassLabeledStandIn;
    }
};


#endif // _LabeledStandIn_h
