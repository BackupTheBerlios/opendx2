/*  Open Visualization Data Explorer Source File */


#ifndef _ColormapFileCommand_h
#define _ColormapFileCommand_h


#include "defines.h"
#include "NoUndoCommand.h"

#include <Xm/Xm.h>


//
// Class name definition:
//
#define ClassColormapFileCommand	"ColormapFileCommand"

class ColormapEditor;

//
// ColormapFileCommand class definition:
//				
class ColormapFileCommand : public NoUndoCommand
{

  private:
    ColormapEditor    *editor;
    boolean		opening;

  protected:
    //
    // Implements the command:

    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    ColormapFileCommand(const char*     name,
                        CommandScope*   scope,
                        boolean         active,
                        ColormapEditor* editor,
			boolean		opening);


    //
    // Destructor:
    //
    ~ColormapFileCommand();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassColormapFileCommand;
    }
};


#endif // _ColormapFileCommand_h
