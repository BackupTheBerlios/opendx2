//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
/////////////////////////////////////////////////////////////////////////////
// ColormapFileCommand.C -						    //
//                                                                          //
// ColormapFileCommand Class methods and other related functions/procedures.//
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ColormapFileCommand.C,v 1.1 1999/03/31 22:30:40 gda Exp $
 *
 */

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

