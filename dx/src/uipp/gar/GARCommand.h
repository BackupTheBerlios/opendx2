//////////////////////////////////////////////////////////////////////////////
// GARCommand.h -						    //
//                                                                          //
// Definition for the GARCommand class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/gar/Attic/GARCommand.h,v 1.1 1999/03/24 15:17:27 gda Exp $
 */

#ifndef _GARCommand_h
#define _GARCommand_h


#include "../base/defines.h"
#include "../base/NoUndoCommand.h"
#include <Xm/Xm.h>

class  GARMainWindow;

//
// GARCommand class definition:
//				

#define ClassGARCommand  "GARCommand"

class GARCommand : public NoUndoCommand 
{
  private:

    static  String	DefaultResources[];
    GARMainWindow* 	gmw;
    int			option;

  protected:
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    GARCommand(const char*,
		CommandScope*,
		boolean active,
                GARMainWindow*,
		int option);

    //
    // Destructor:
    //
    ~GARCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassGARCommand;
    }
};


#endif // _GARCommand_h
