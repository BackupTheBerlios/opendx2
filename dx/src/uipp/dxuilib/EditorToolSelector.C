//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// EditorToolSelector.C -						    //
//                                                                          //
// EditorToolSelector Class methods and other related functions/procedures. //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/EditorToolSelector.C,v 1.1 1999/03/24 15:17:40 gda Exp $
 */


#include "defines.h"
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
