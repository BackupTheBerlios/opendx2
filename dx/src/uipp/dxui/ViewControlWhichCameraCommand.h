//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ViewControlWhichCameraCommand.h,v 1.1 1999/03/31 22:36:06 gda Exp $
 */


#ifndef _ViewControlWhichCameraCommand_h
#define _ViewControlWhichCameraCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassViewControlWhichCameraCommand	"ViewControlWhichCameraCommand"

//
// Referenced classes.
//
class ViewControlDialog;

//
// ViewControlWhichCameraCommand class definition:
//				
class ViewControlWhichCameraCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ViewControlDialog *viewControlDialog;

  protected:
    //
    // Protected member data:
    //

    virtual boolean doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ViewControlWhichCameraCommand(const char   *name,
		   CommandScope      *scope,
		   boolean            active,
		   ViewControlDialog *w);

    //
    // Destructor:
    //
    ~ViewControlWhichCameraCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassViewControlWhichCameraCommand;
    }
};


#endif // _ViewControlWhichCameraCommand_h
