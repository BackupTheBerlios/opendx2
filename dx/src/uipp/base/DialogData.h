//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// DialogData.h -							    //
//                                                                          //
// Definition for the DialogData class.					    //
//                                                                          //
// This class is intended to be used by the DialogManger class as callback  //
// client data structure.  To this end, the entire class is declared to be  //
// private, only accessible by DialogManager class objects.		    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/DialogData.h,v 1.1 1999/03/24 15:17:23 gda Exp $
 */


#ifndef _DialogData_h
#define _DialogData_h


#include <Xm/Xm.h>

#include "defines.h"
#include "Base.h"

//
// Class name definition:
//
#define ClassDialogData	"DialogData"


//
// DialogCallback type definition:
//
typedef void (*DialogCallback)(void*);


//
// Referenced classes:
//
class DialogManager;


//
// DialogData class definition:
//				
class DialogData : public Base
{

    //
    // Friend classes:
    //
    friend class DialogManager;

  public:
    //
    // Data access routines:
    //
    void* getClientData()
    {
        return this->clientData;
    }

    DialogCallback getOkCallback()
    {
        return this->okCallback;
    }

    DialogCallback getDismissCallback()
    {
	switch (this->cancelBtnNum) {
	    case 3:
        	return this->helpCallback;
	    case 2:
        	return this->cancelCallback;
	}
        return this->cancelCallback;
    }

    DialogCallback getCancelCallback()
    {
        return this->cancelCallback;
    }

    DialogCallback getHelpCallback()
    {
        return this->helpCallback;
    }
    Widget getOwnerDialog()
    {
        return this->dialog;
    }


    //
    // Constructor:
    //   Made private to prevent general instantiation.
    //   Intended to be instantiated by DialogManager class objects only.
    //
    DialogData(Widget	      owner,
	       void*          clientData,
	       DialogCallback okCallback,
	       DialogCallback cancelCallback,
	       DialogCallback helpCallback,
	       int 	      cancelBtnNum = 2
	   )
    {
	this->clientData     = clientData;
	this->dialog	     = owner;
	this->okCallback     = okCallback;
	this->cancelCallback = cancelCallback;
	this->helpCallback   = helpCallback;
	this->cancelBtnNum   = cancelBtnNum;
    }

    //
    // Destructor:
    //
    ~DialogData(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDialogData;
    }
  private:
    //
    // Private member data:
    //
    Widget	   dialog;		// Dialog that owns this data.
    void*          clientData;          // client data for callbacks
    DialogCallback okCallback;          // ok button callback
    DialogCallback cancelCallback;      // cancel button callback
    DialogCallback helpCallback;        // help button callback
    int 	   cancelBtnNum;

};


#endif // _DialogData_h
