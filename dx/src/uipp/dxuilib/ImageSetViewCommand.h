//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageSetViewCommand.h,v 1.1 1999/03/24 15:17:42 gda Exp $
 */


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
