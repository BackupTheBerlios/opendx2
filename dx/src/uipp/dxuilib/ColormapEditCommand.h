//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// ColormapEditCommand.h -						    //
//                                                                          //
// Definition for the ColormapEditCommand class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ColormapEditCommand.h,v 1.1 1999/03/24 15:17:38 gda Exp $
 * 
 */


#ifndef _ColormapEditCommand_h
#define _ColormapEditCommand_h


#include "defines.h"
#include "NoUndoCommand.h"
#include <Xm/Xm.h>

class  ColormapEditor;

//
// ColormapEditCommand class definition:
//				

#define ClassColormapEditCommand  "ColormapEditCommand"

#define DISPLAY_OFF 0
#define DISPLAY_ALL 1
#define DISPLAY_SELECTED 2

class ColormapEditCommand : public NoUndoCommand 
{
  private:

    static  String	DefaultResources[];
    ColormapEditor* 	editor;
    int     option;

  protected:
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    ColormapEditCommand(const char*,
		CommandScope*,
		boolean active,
                ColormapEditor*,
		int option);

    enum {
           New,
           Undo,
           Copy,
           Paste,
           AddControl,
           NBins,
           Waveform,
           DeleteSelected,
           SelectAll,
           SetBackground,
           Ticks,
           Histogram,
           LogHistogram,
           ConstrainH,
           ConstrainV,
	   DisplayCPOff,
	   DisplayCPAll,
	   DisplayCPSelected,
	   ResetAll,
	   ResetMin,
	   ResetMax,
	   ResetMinMax,
	   ResetHSV,
	   ResetOpacity,
	   SetColormapName
    };

	
    //
    // Destructor:
    //
    ~ColormapEditCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassColormapEditCommand;
    }
};


#endif // _ColormapEditCommand_h
