/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#ifndef _DeleteNodeCommand_h
#define _DeleteNodeCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassDeleteNodeCommand	"DeleteNodeCommand"


class EditorWindow;
class List;

//
// DeleteNodeCommand class definition:
//				
class DeleteNodeCommand : public NoUndoCommand
{
  private:

  protected:

    EditorWindow *editor;
    List	*toDelete;	// Buffer of nodes to restore on undo. 

    virtual boolean doIt(CommandInterface *ci);
   
  public:
    //
    // Constructor:
    //
    DeleteNodeCommand(const char*   name,
		      CommandScope* scope, 
		      boolean	active,
                      EditorWindow* editor);

    //
    // Destructor:
    //
    ~DeleteNodeCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDeleteNodeCommand;
    }
};


#endif // _DeleteNodeCommand_h
