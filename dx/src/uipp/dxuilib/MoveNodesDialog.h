// 
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
// 
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
// 

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/MoveNodesDialog.h,v 1.1 1999/03/24 15:17:43 gda Exp $
 */


#ifndef _MoveNodesDialog_h
#define _MoveNodesDialog_h


#include "defines.h"
#include "Dialog.h"

extern "C" void MoveNodesDialog_ApplyCB (Widget, XtPointer clientData, XtPointer);
extern "C" void MoveNodesDialog_ModifyNameCB (Widget , XtPointer , XtPointer );


//
// Class name definition:
//
#define ClassMoveNodesDialog	"MoveNodesDialog"

class PageSelector;
class TextSelector;
class PageTab;
class EditorWorkSpace;
class CommandScope;
class Command;
class CommandInterface;

//
// MoveNodesDialog class definition:
//				
class MoveNodesDialog : public Dialog
{
  private:
    friend class MoveNodesCommand;
    //
    // Private member data:
    //
    char* page_name;
    int position;
    int max;

    Widget apply;

    static boolean ClassInitialized;

    EditorWorkSpace* workspace;
    PageSelector* selector;
    TextSelector* selector_menu;

    boolean stop_updates;
    boolean applyCallback(Dialog *d);

    CommandScope* scope;
    Command* apply_cmd;
    CommandInterface* ok_option;
    CommandInterface* apply_option;

  protected:
    //
    // Protected member data:
    //
    static String DefaultResources[];

    virtual boolean okCallback(Dialog *d);
    virtual Widget createDialog(Widget parent);

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    virtual void installDefaultResources(Widget baseWidget);

    void update();

    friend void MoveNodesDialog_ApplyCB (Widget, XtPointer clientData, XtPointer);
    friend void MoveNodesDialog_ModifyNameCB (Widget , XtPointer , XtPointer );

  public:
    //
    // Constructor:
    //
    MoveNodesDialog(Widget parent, PageSelector* selector);

    //
    // Destructor:
    //
    ~MoveNodesDialog();

    void setWorkSpace(const char* );

    virtual void manage();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName()
    {
	return ClassMoveNodesDialog;
    }
};


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassMoveNodesCommand	"MoveNodesCommand"

//
// ImageResetCommand class definition:
//				
class MoveNodesCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    MoveNodesDialog *moveNodes;

  protected:
    //
    // Protected member data:
    //

    virtual boolean doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    MoveNodesCommand(const char   *name,
		   CommandScope *scope,
		   boolean       active,
		   MoveNodesDialog  *w);

    //
    // Destructor:
    //
    ~MoveNodesCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassMoveNodesCommand;
    }
};


#endif // _MoveNodesDialog_h
