/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#include "UndoRepeatableTab.h"
//#include "EditorWindow.h"
#include "Node.h"
#include "StandIn.h"
#include "Ark.h"


char UndoRepeatableTab::OperationName[] = "repeats";

UndoRepeatableTab::UndoRepeatableTab 
    (EditorWindow* editor, Node* n, bool adding, bool input) : UndoNode(editor, n)
{
    this->adding = !adding;
    this->input = input;
}

//
//
void UndoRepeatableTab::undo(bool first_in_list) 
{
    Node* n = this->lookupNode();
    if (!n) return ;
    if (this->adding) {
	if (input) {
	    n->addInputRepeats();
	} else {
	    n->addOutputRepeats();
	}
    } else {
	if (input) {
	    n->removeInputRepeats();
	} else {
	    n->removeOutputRepeats();
	}
    }
}

//
//
bool UndoRepeatableTab::canUndo()
{
    Node* n = this->lookupNode();
    if (!n) return false;
    if (this->adding) {
	if (this->input) {
	    if (!n->isInputRepeatable()) return false;
	} else {
	    if (!n->isOutputRepeatable()) return false;
	}
    } else {
	if (this->input) {
	    if (!n->hasRemoveableInput()) return false;
	} else {
	    if (!n->hasRemoveableOutput()) return false;
	}
    }
    return true;
}
