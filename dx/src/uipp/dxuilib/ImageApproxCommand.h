//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageApproxCommand.h,v 1.1 1999/03/24 15:17:41 gda Exp $
 */


#ifndef _ImageApproxCommand_h
#define _ImageApproxCommand_h


#include "defines.h"
#include "NoUndoCommand.h"
#include "ImageWindow.h"


//
// Class name definition:
//
#define ClassImageApproxCommand	"ImageApproxCommand"

//
// Referenced classes.
//

//
// ImageApproxCommand class definition:
//				
class ImageApproxCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;
    boolean    up;
    ApproxMode mode;

  protected:
    //
    // Protected member data:
    //

    virtual boolean doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageApproxCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   ImageWindow  *w,
		   boolean      up,
		   ApproxMode   mode);

    //
    // Destructor:
    //
    ~ImageApproxCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageApproxCommand;
    }
};


#endif // _ImageApproxCommand_h
