//////////////////////////////////////////////////////////////////////////////
// ColormapFileCommand.h -						    //
//                                                                          //
// Definition for the ColormapFileCommand class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ColormapFileCommand.h,v 1.1 1999/03/31 22:30:42 gda Exp $
 *
 */

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
