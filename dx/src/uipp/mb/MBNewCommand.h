/////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/mb/MBNewCommand.h,v 1.1 1999/03/24 15:17:33 gda Exp $
 */


#ifndef _MBNewCommand_h
#define _MBNewCommand_h


#include "../base/defines.h"
#include "../base/OptionalPreActionCommand.h"

//
// Class name definition:
//
#define ClassMBNewCommand	"MBNewCommand"

class  MBMainWindow;

//
// MBNewCommand class definition:
//				
class MBNewCommand : public OptionalPreActionCommand
{
  private:
    //
    // Private member data:
    //
    MBMainWindow *mbmw;

  protected:
    //
    // Protected member data:
    //
    virtual boolean needsConfirmation();
    virtual void    doPreAction();

    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    MBNewCommand(const char      *name,
	       CommandScope    *scope,
	       boolean		active,
	       MBMainWindow   *mbmw, 
		Widget		dialogParent);


    //
    // Destructor:
    //
    ~MBNewCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassMBNewCommand;
    }
};


#endif // _MBNewCommand_h
