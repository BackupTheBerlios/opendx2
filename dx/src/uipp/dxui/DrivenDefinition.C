/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#include "UIConfig.h"
#include "defines.h"
#include "DrivenDefinition.h"
#include "AttributeParameter.h" 
#include "List.h"
#include "ListIterator.h"

// 
// Driven nodes use two valued parameters with the second value
// maintaing the attribute as set from the 'Set Attributes' dialog.
// The first value maintains the values set in the CDB.
//
Parameter *DrivenDefinition::newParameter(
		ParameterDefinition *pd, Node *n, int index)
{
    if (pd->isInput())
        return new AttributeParameter(pd, n, index);
    else
        return new Parameter(pd);
}

//
// Mark all outputs as cache once with read-only cache attributes
// (as per the semantics of data-driven interactors).
// This helps to force an execution when inputs change that must have
// their values communicated back to the User Interface.
//
void DrivenDefinition::finishDefinition()
{
    NodeDefinition::finishDefinition();
    ParameterDefinition *pd;

    ListIterator iterator(this->outputDefs);
    while (pd = (ParameterDefinition*)iterator.getNext()) {
        pd->setWriteableCacheability(FALSE);
        pd->setDefaultCacheability(OutputCacheOnce);
    }
}

