//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageLookCommand.h,v 1.1 1999/03/24 15:17:42 gda Exp $
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
