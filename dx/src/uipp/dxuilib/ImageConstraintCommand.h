//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageConstraintCommand.h,v 1.1 1999/03/24 15:17:41 gda Exp $
 */


#ifndef _ImageConstraintCommand_h
#define _ImageConstraintCommand_h


#include "defines.h"
#include "NoUndoCommand.h"
#include "ImageWindow.h"


//
// Class name definition:
//
#define ClassImageConstraintCommand	"ImageConstraintCommand"

//
// Referenced classes.
//

//
// ImageConstraintCommand class definition:
//				
class ImageConstraintCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;
    ConstraintDirection direction;

  protected:
    //
    // Protected member data:
    //

    virtual boolean doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageConstraintCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   ImageWindow  *w,
		   ConstraintDirection dir);

    //
    // Destructor:
    //
    ~ImageConstraintCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageConstraintCommand;
    }
};


#endif // _ImageConstraintCommand_h
