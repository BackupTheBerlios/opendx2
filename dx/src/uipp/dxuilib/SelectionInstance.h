//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// SelectionInstance.h -						    //
//                                                                          //
// Definition for the SelectionInstance class.				    //
//
// 
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/SelectionInstance.h,v 1.1 1999/03/24 15:17:46 gda Exp $
 */


#ifndef _SelectionInstance_h
#define _SelectionInstance_h


#include <Xm/Xm.h> 

#include "defines.h"
//#include "Strings.h"
#include "SelectionNode.h"
#include "InteractorInstance.h"

class SelectionInteractor;


//
// Class name definition:
//
#define ClassSelectionInstance	"SelectionInstance"


//
// Describes an instance of an interactor in a control Panel.
//
class SelectionInstance : public InteractorInstance {

    friend class SelectionAttrDialog;

  private:


  protected:


    boolean appendOptionPair(const char *value, const char *name);

    //
    // Create the default  set attributes dialog box for this class of
    // Interactor.
    //
    virtual SetAttrDialog *newSetAttrDialog(Widget parent);

  public:
    SelectionInstance(InteractorNode *node) : InteractorInstance(node) {}
	
    ~SelectionInstance()  {}

    int 	getOptionCount();
    int 	getSelectedOptionIndex();
    const char	*getValueOptionsAttribute();
    char	*getOptionValueString(int optind);
    char	*getOptionNameString(int optind, boolean keep_quotes = FALSE);

    virtual boolean hasSetAttrDialog();

    const char *getClassName() 
		{ return ClassSelectionInstance; }
};

#endif // _SelectionInstance_h

