/*  Open Visualization Data Explorer Source File */


#ifndef _ImageSetModeCommand_h
#define _ImageSetModeCommand_h


#include "defines.h"
#include "NoUndoCommand.h"
#include "ImageWindow.h"


//
// Class name definition:
//
#define ClassImageSetModeCommand	"ImageSetModeCommand"

//
// Referenced classes.
//

//
// ImageSetModeCommand class definition:
//				
class ImageSetModeCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;
    DirectInteractionMode mode;

  protected:
    //
    // Protected member data:
    //

    virtual boolean doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageSetModeCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   ImageWindow  *w,
		   DirectInteractionMode mode);

    //
    // Destructor:
    //
    ~ImageSetModeCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageSetModeCommand;
    }
};


#endif // _ImageSetModeCommand_h
