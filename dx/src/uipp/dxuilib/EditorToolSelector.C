/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "../base/defines.h"
#include "../base/defines.h"




#include "EditorToolSelector.h"
#include "EditorWindow.h"
#include "EditorWorkSpace.h"


EditorToolSelector::EditorToolSelector(const char *name, EditorWindow *editor) :
    ToolSelector(name)
{
    this->editor = editor;
}

EditorToolSelector::~EditorToolSelector()
{
}

void EditorToolSelector::toolSelect(Widget widget,
				    XmListCallbackStruct *callData)
{
    
    this->ToolSelector::toolSelect(widget, callData);

    if (this->getCurrentSelection())
        this->editor->setCursor(UPPER_LEFT);
    else
        this->editor->resetCursor();
}
void EditorToolSelector::categorySelect(Widget widget,
					XmListCallbackStruct *callData)
{
    //
    // Make sure the widget is realized.  This callback is called after the
    // category lists are initialized to get the active stuff straight.
    //
    if (XtIsRealized(widget))
	this->editor->resetCursor();

    this->ToolSelector::categorySelect(widget, callData);
}
