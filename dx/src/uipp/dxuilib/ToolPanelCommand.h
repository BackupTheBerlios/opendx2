//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// Node.C -                                                                 //
//                                                                          //
// Node Class methods and other related functions/procedures.               //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ToolPanelCommand.h,v 1.1 1999/03/24 15:17:48 gda Exp $
 */


#ifndef _ToolPanelCommand_h
#define _ToolPanelCommand_h


#include "defines.h"
#include "Command.h"


//
// Class name definition:
//
#define ClassToolPanelCommand	"ToolPanelCommand"


//
// Referenced classes:
//
class ToggleButtonInterface;
class EditorWindow;


//
// ToolPanelCommand class definition:
//				
class ToolPanelCommand : public Command
{
  protected:
    //
    // Protected member data:
    //
    EditorWindow* editor;
    boolean       setting;

    //
    // Implements the command:
    //   Toggles the tool panel to be visible/invisible.
    //
    virtual boolean doIt(CommandInterface *ci);


    //
    // Undoes the command.
    //
    virtual boolean undoIt();


  public:
    //
    // Constructor:
    //
    ToolPanelCommand(const char*     name,
		     CommandScope*   scope,
		     boolean         active,
		     EditorWindow* editor);

    //
    // Destructor:
    //
    ~ToolPanelCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassToolPanelCommand;
    }
};


#endif //  _ToolPanelCommand_h
