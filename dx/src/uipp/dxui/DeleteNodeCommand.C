/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#include "DeleteNodeCommand.h"
#include "Application.h"
#include "EditorWindow.h"


DeleteNodeCommand::DeleteNodeCommand(const char*   name,
			             CommandScope* scope, 
				     boolean active,
                                     EditorWindow *editor) 
                      : NoUndoCommand(name, scope, active)
{
    ASSERT(editor);
    this->editor = editor;
}


boolean DeleteNodeCommand::doIt(CommandInterface *ci)
{
    EditorWindow *editor = this->editor;

    editor->removeSelectedNodes();

    return TRUE;
}

