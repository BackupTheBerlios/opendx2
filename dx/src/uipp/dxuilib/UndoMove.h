/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#ifndef _UndoMove_h
#define _UndoMove_h
#include "../base/defines.h"

#include "Base.h"

class UIComponent;
class EditorWindow;
class Node;
class StandIn;

//
// In order to track movements in the canvas we'll store
// things in this object and keep them in a list.  It would be
// better to make this a generic Undo object and then make UndoMove
// a subclass of Undo, but I'm not planning on really implementing Undo/Redo.
//
#define UndoMoveClassName "UndoMove"
class UndoMove : public Base
{
    private:
	int x,y;
    protected:
	EditorWindow* editor;
	UIComponent* component;
    public:
	virtual ~UndoMove(){}
	UndoMove (EditorWindow* editor, UIComponent* uic);
	virtual void undo();
	virtual const char* getClassName() { return UndoMoveClassName; }
};

class UndoStandInMove : public UndoMove
{
    private:
       	Node* node;
    public:
	UndoStandInMove (EditorWindow* editor, Node* n, StandIn* standIn);
	virtual void undo();
};
#endif // _UndoMove_h
