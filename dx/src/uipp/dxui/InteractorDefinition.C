//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/InteractorDefinition.C,v 1.1 1999/03/31 22:32:34 gda Exp $
 *
 */

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
