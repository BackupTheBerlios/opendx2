/*  Open Visualization Data Explorer Source File */



#ifndef _ImagePerspectiveCommand_h
#define _ImagePerspectiveCommand_h


#include "defines.h"
#include "UndoCommand.h"


//
// Class name definition:
//
#define ClassImagePerspectiveCommand	"ImagePerspectiveCommand"

//
// Referenced Classes
//
class ImageWindow;

//
// ImagePerspectiveCommand class definition:
//				
class ImagePerspectiveCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;
    boolean      enablePerspective;	// True for enabling, false for dis...

  protected:
    //
    // Protected member data:
    //
    virtual boolean doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImagePerspectiveCommand(const char   *name,
		     CommandScope *scope,
		     boolean       active,
		     ImageWindow  *w,
		     boolean       enable);

    //
    // Destructor:
    //
    ~ImagePerspectiveCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImagePerspectiveCommand;
    }
};


#endif // _ImagePerspectiveCommand_h
