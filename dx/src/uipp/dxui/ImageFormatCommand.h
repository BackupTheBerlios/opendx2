/*  Open Visualization Data Explorer Source File */



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
