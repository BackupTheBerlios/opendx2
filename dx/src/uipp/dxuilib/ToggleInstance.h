//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ToggleInstance.h,v 1.1 1999/03/24 15:17:48 gda Exp $
 */

#ifndef _ToggleInstance_h
#define _ToggleInstance_h


#include "defines.h"
#include "InteractorInstance.h"
#include "ToggleNode.h"

//
// Class name definition:
//
#define ClassToggleInstance	"ToggleInstance"

//
// Describes an instance of an scalar interactor in a control Panel.
//
class ToggleInstance : public InteractorInstance  {

    friend ToggleNode;

  private:

  protected:

    //
    // Create the default  set attributes dialog box for this class of
    // Interactor.
    //
    virtual SetAttrDialog *newSetAttrDialog(Widget parent);

    virtual boolean defaultVertical() { return FALSE; }

    virtual const char* javaName() { return "toggle"; }

  public:
    ToggleInstance(ToggleNode *n);

    ~ToggleInstance();

    virtual boolean hasSetAttrDialog();

    virtual void setVerticalLayout(boolean val = TRUE);

    virtual boolean printAsJava (FILE* );

    const char *getClassName() { return ClassToggleInstance; }
	
};

#endif // _ToggleInstance_h

