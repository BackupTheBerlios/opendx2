//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageHardwareCommand.h,v 1.1 1999/03/24 15:17:42 gda Exp $
 */

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
