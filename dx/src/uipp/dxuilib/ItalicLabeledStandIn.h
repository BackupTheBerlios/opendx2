//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ItalicLabeledStandIn.h,v 1.1 1999/03/24 15:17:43 gda Exp $
 */



#ifndef _ItalicLabeledStandIn_h
#define _ItalicLabeledStandIn_h


#include "defines.h"
#include "LabeledStandIn.h"


//
// Class name definition:
//
#define ClassItalicLabeledStandIn	"ItalicLabeledStandIn"

//
// ItalicLabeledStandIn class definition:
//				

class ItalicLabeledStandIn : public LabeledStandIn
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
    static String DefaultResources[];
    virtual const char *getButtonLabelFont();

    //
    // Constructor:
    //
    ItalicLabeledStandIn(WorkSpace *w, Node *node);

  public:
    //
    // Allocator that is installed in theSIAllocatorDictionary
    //
    static StandIn *AllocateStandIn(WorkSpace *w, Node *n);

    //
    // Destructor:
    //
    ~ItalicLabeledStandIn();

    virtual void initialize();

    virtual const char *getPostScriptLabelFont();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassItalicLabeledStandIn;
    }
};


#endif // _ItalicLabeledStandIn_h
