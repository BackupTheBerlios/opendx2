/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _ImageUndoCommand_h
#define _ImageUndoCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassImageUndoCommand	"ImageUndoCommand"

//
// Referenced classes.
//
class ImageWindow;

//
// ImageUndoCommand class definition:
//				
class ImageUndoCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;

  protected:
    //
    // Protected member data:
    //

    virtual boolean doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageUndoCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   ImageWindow  *w);

    //
    // Destructor:
    //
    ~ImageUndoCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageUndoCommand;
    }
};


#endif // _ImageUndoCommand_h
