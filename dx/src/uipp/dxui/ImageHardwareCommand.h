/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#ifndef _ImageHardwareCommand_h
#define _ImageHardwareCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassImageHardwareCommand	"ImageHardwareCommand"

//
// Referenced classes.
//
class ImageWindow;

//
// ImageHardwareCommand class definition:
//				
class ImageHardwareCommand : public NoUndoCommand
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
    ImageHardwareCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   ImageWindow  *w);

    //
    // Destructor:
    //
    ~ImageHardwareCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageHardwareCommand;
    }
};


#endif // _ImageHardwareCommand_h
