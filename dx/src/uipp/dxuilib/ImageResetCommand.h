//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageResetCommand.h,v 1.1 1999/03/24 15:17:42 gda Exp $
 */

#ifndef _ImageResetCommand_h
#define _ImageResetCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassImageResetCommand	"ImageResetCommand"

//
// Referenced classes.
//
class ImageWindow;

//
// ImageResetCommand class definition:
//				
class ImageResetCommand : public NoUndoCommand
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
    ImageResetCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   ImageWindow  *w);

    //
    // Destructor:
    //
    ~ImageResetCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageResetCommand;
    }
};


#endif // _ImageResetCommand_h
