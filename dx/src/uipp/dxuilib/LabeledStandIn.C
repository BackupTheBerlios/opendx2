//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/LabeledStandIn.C,v 1.1 1999/03/24 15:17:43 gda Exp $
 */


#include <Xm/Xm.h>

#include "StandIn.h"
#include "LabeledStandIn.h"
#include "Node.h"
#include "DXApplication.h"


boolean LabeledStandIn::ClassInitialized = FALSE;

String LabeledStandIn::DefaultResources[]  =  {
	NULL
};

//
// Static allocator found in theSIAllocatorDictionary
//
StandIn 
*LabeledStandIn::AllocateStandIn(WorkSpace *w, Node *node)
{
    StandIn *si = new LabeledStandIn(w,node);
    si->createStandIn();
    return si;

}

LabeledStandIn::LabeledStandIn(WorkSpace *w, Node *node):
                 StandIn(w,node)
{
}

//
// Destructor
//
LabeledStandIn::~LabeledStandIn()
{
}

void LabeledStandIn::initialize()
{
    if (!LabeledStandIn::ClassInitialized) {
        LabeledStandIn::ClassInitialized = TRUE;
        this->setDefaultResources(theApplication->getRootWidget(),
                                  LabeledStandIn::DefaultResources);
        this->setDefaultResources(theApplication->getRootWidget(),
                                  StandIn::DefaultResources);
    }

    //
    // Call the superclass initialize()
    //
    StandIn::initialize();

}

const char *LabeledStandIn::getButtonLabel()
{
   return this->node->getLabelString();
}
