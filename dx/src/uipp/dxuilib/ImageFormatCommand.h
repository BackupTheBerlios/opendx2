//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageFormatCommand.h,v 1.1 1999/03/24 15:17:41 gda Exp $
 */


#ifndef _ImageFormatCommand_h
#define _ImageFormatCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassImageFormatCommand	"ImageFormatCommand"

//
// Referenced classes.
//
class ImageFormatDialog;

//
// ImageFormatCommand class definition:
//				
class ImageFormatCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageFormatDialog *dialog;
    int commandType;

  protected:
    //
    // Protected member data:
    //

    virtual boolean doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageFormatCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   ImageFormatDialog  *dialog,
		   int commandType);

    enum {
	AllowRerender	= 1,
	SaveCurrent	= 2,
	SaveContinuous	= 3,
	DelayedColors	= 4,
	SelectFile	= 99 
    };

    //
    // Destructor:
    //
    ~ImageFormatCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageFormatCommand;
    }
};


#endif // _ImageFormatCommand_h
