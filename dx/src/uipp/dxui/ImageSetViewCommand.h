/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _ImageSetViewCommand_h
#define _ImageSetViewCommand_h


#include "defines.h"
#include "NoUndoCommand.h"
#include "ImageWindow.h"


//
// Class name definition:
//
#define ClassImageSetViewCommand	"ImageSetViewCommand"

//
// Referenced classes.
//

//
// ImageSetViewCommand class definition:
//				
class ImageSetViewCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;
    ViewDirection direction;

  protected:
    //
    // Protected member data:
    //

    virtual boolean doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageSetViewCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   ImageWindow  *w,
		   ViewDirection dir);

    //
    // Destructor:
    //
    ~ImageSetViewCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageSetViewCommand;
    }
};


#endif // _ImageSetViewCommand_h
