//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImageSoftwareCommand.h,v 1.1 1999/03/31 22:32:27 gda Exp $
 */


#ifndef _ImageSoftwareCommand_h
#define _ImageSoftwareCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassImageSoftwareCommand	"ImageSoftwareCommand"

//
// Referenced classes.
//
class ImageWindow;

//
// ImageSoftwareCommand class definition:
//				
class ImageSoftwareCommand : public NoUndoCommand
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
    ImageSoftwareCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   ImageWindow  *w);

    //
    // Destructor:
    //
    ~ImageSoftwareCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageSoftwareCommand;
    }
};


#endif // _ImageSoftwareCommand_h
