/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#include "UndoMove.h"
#include "EditorWindow.h"
#include "UIComponent.h"
#include "StandIn.h"
#include "Node.h"
#include "List.h"
#include "ListIterator.h"
#include "Ark.h"
#include "ArkStandIn.h"

//
// In order to track movements in the canvas we'll store
// things in this object and keep them in a list.  It would be
// better to make this a generic Undo object and then make UndoMove
// a subclass of Undo, but I'm not planning on really implementing Undo/Redo.
//
UndoMove::UndoMove (EditorWindow* editor, UIComponent* uic)
{
    this->component = uic;
    this->component->getXYPosition (&this->x, &this->y);
    this->editor = editor;
}

void UndoMove::undo() 
{
    // must clear out the undo list if the current
    // workspace page changes.
    this->component->setXYPosition (this->x, this->y);

}

UndoStandInMove::UndoStandInMove(EditorWindow* editor, Node* n, StandIn* standIn) : UndoMove(editor, standIn)
{
    this->node = n;
}
void UndoStandInMove::undo()
{
    this->UndoMove::undo();
    int input_count = this->node->getInputCount();
    StandIn* si = (StandIn*)this->component;
    Ark* arc;
    for (int i=1; i<=input_count; i++) {
	if (!this->node->isInputVisible(i)) continue;
	List* arcs = (List*)this->node->getInputArks(i);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	while (arc = (Ark*)iter.getNext()) {
	    ArkStandIn* asi = arc->getArkStandIn();
	    delete asi;
	    si->addArk (this->editor, arc);
	}
    }

    int output_count = this->node->getOutputCount();
    for (int i=1; i<=output_count; i++) {
	if (!this->node->isOutputVisible(i)) continue;
	List* arcs = (List*)this->node->getOutputArks(i);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	while (arc = (Ark*)iter.getNext()) {
	    ArkStandIn* asi = arc->getArkStandIn();
	    delete asi;
	    si->addArk(this->editor, arc);
	}
    }
}
