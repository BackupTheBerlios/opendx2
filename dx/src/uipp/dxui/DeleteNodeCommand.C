//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/DeleteNodeCommand.C,v 1.1 1999/03/31 22:31:09 gda Exp $
 */


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

