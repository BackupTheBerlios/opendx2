//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImageLookCommand.h,v 1.1 1999/03/31 22:32:07 gda Exp $
 */


#ifndef _ImageLookCommand_h
#define _ImageLookCommand_h


#include "defines.h"
#include "NoUndoCommand.h"
#include "ImageWindow.h"


//
// Class name definition:
//
#define ClassImageLookCommand	"ImageLookCommand"

//
// Referenced classes.
//

//
// ImageLookCommand class definition:
//				
class ImageLookCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;
    LookDirection direction;

  protected:
    //
    // Protected member data:
    //

    virtual boolean doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageLookCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   ImageWindow  *w,
		   LookDirection dir);

    //
    // Destructor:
    //
    ~ImageLookCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageLookCommand;
    }
};


#endif // _ImageLookCommand_h
