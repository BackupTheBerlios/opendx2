/*  Open Visualization Data Explorer Source File */


//////////////////////////////////////////////////////////////////////////////

#include "UIConfig.h"
#include "defines.h"
#include "InteractorDefinition.h"
//#include "InteractorNode.h"
#include "SIAllocatorDictionary.h"
#include "InteractorStandIn.h"
//#include "ParameterDefinition.h"
//#include "List.h"
//#include "ListIterator.h"


//
// Define the stand-in that is used for InteractorNode and derived classes.
//
SIAllocator InteractorDefinition::getSIAllocator()
{
    return InteractorStandIn::AllocateStandIn;
}
