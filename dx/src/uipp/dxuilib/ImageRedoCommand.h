//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageRedoCommand.h,v 1.1 1999/03/24 15:17:42 gda Exp $
 */


#ifndef _ImageRedoCommand_h
#define _ImageRedoCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassImageRedoCommand	"ImageRedoCommand"

//
// Referenced classes.
//
class ImageWindow;

//
// ImageRedoCommand class definition:
//				
class ImageRedoCommand : public NoUndoCommand
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
    ImageRedoCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   ImageWindow  *w);

    //
    // Destructor:
    //
    ~ImageRedoCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageRedoCommand;
    }
};


#endif // _ImageRedoCommand_h
