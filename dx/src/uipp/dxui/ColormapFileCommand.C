/*  Open Visualization Data Explorer Source File */

#include "Command.h"
#include "Application.h"
#include "NoUndoCommand.h"
#include "ColormapFileCommand.h"
#include "ColormapEditor.h"




ColormapFileCommand::ColormapFileCommand(const char*   name,
                         CommandScope*   scope,
                         boolean         active,
                         ColormapEditor* editor,
			 boolean	opening) 
 			:NoUndoCommand(name,scope,active)	
{
    this->editor = editor;
    this->opening = opening;

}

ColormapFileCommand::~ColormapFileCommand()
{
}


boolean ColormapFileCommand::doIt(CommandInterface *ci)
{
   editor->postOpenColormapDialog(this->opening);
   return TRUE;
}

