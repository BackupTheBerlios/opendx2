//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// DeferrableAction.h -							    //
//                                                                          //
// Definition for the DeferrableAction class.				    //
//
// This class is meant to implement actions (function calls) which can
// be deferred for a period of time through the use of the un/deferAction()
// methods below.  Deferrals are implemented through the un/deferAction()
// and requestAction() calls.  requestAction() will perform the action 
// if there are no current deferrals, otherwise the action is performed
// on the last undefAction() call (un/deferAction() can be nested).
// requestAction() takes a void* that is passed to the ActionFunction if it
// is called.  However, if the action is deferred and later the ActionFunction
// is called by undeferAction(), the void* passed to the ActionFunction
// will be NULL.  This provides a mechanism for the ActionFunction to 
// determine if it is called by a direct request or by an undeferral.
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/DeferrableAction.h,v 1.1 1999/03/24 15:17:23 gda Exp $
 */


#ifndef _DeferrableAction_h
#define _DeferrableAction_h


#include "defines.h"
#include "Base.h"


//
// Class name definition:
//
#define ClassDeferrableAction	"DeferrableAction"

typedef void (*DeferrableActionFunction)(void *staticData, void *requestData);

//
// DeferrableAction class definition:
//				
class DeferrableAction : public Base
{
  private:
    //
    // Private member data:
    //
    boolean	required;	// flag if the action is required.
    int		deferrals;	// Number of pending action deferrals
    DeferrableActionFunction actionFunction;
    void		*staticData;

  protected:
    //
    // Protected member data:
    //

    //
    // Flag that the action is required. 
    //
    void    setActionRequired()	{ this->required = TRUE; }

  public:
    //
    // Constructor:
    //
    DeferrableAction(DeferrableActionFunction daf, void *data = NULL);

    //
    // Destructor:
    //
    ~DeferrableAction(){}

    //
    // Request that the action be taken.  If it is currently deferred, then
    // the action won't be taken.
    //
    void    requestAction(void *requestData);
				
    //
    // Defer the action, assuming that the caller uses isActionDeferred()
    // and setActionRequired() when attempting the action. 
    // This meant to be called in pairs with undeferAction().
    // 
    void deferAction()   { this->deferrals++; }

    //
    // Undefer the action, which results in the action being performed if
    // it was requested prior to the undeferral.   If the action is called,
    // then the requestData parameter passed to the action function is NULL.
    // This meant to be called in pairs with deferAction().
    //
    void undeferAction();

    //
    // See if the action is currently deferred.
    //
    boolean isActionDeferred() { return this->deferrals != 0;}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDeferrableAction;
    }
};


#endif // _DeferrableAction_h
