//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImageSetViewCommand.h,v 1.1 1999/03/31 22:32:24 gda Exp $
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
