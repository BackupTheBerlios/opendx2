//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// NoUndoCommand.C -							    //
//                                                                          //
// NoUndoCommand Class methods and other related functions/procedures.	    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/NoUndoCommand.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


#include "NoUndoCommand.h"


NoUndoCommand::NoUndoCommand(const char*   name,
			     CommandScope* scope,
			     boolean       active): Command(name, scope, active)
{
    this->hasUndo = FALSE;
}


