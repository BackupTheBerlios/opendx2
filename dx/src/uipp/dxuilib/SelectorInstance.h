//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// SelectorInstance.h -						    //
//                                                                          //
// Definition for the SelectorInstance class.				    //
//
// 
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/SelectorInstance.h,v 1.1 1999/03/24 15:17:46 gda Exp $
 */


#ifndef _SelectorInstance_h
#define _SelectorInstance_h


#include <Xm/Xm.h> 

#include "defines.h"
#include "Strings.h"
#include "SelectorNode.h"
#include "SelectionInstance.h"

class SelectorInteractor;


//
// Class name definition:
//
#define ClassSelectorInstance	"SelectorInstance"


//
// Describes an instance of an interactor in a control Panel.
//
class SelectorInstance : public SelectionInstance {

  private:


  protected:

    virtual const char* javaName() { return "pdown"; }

  public:
    SelectorInstance(InteractorNode *node) : SelectionInstance(node) {}
	
    ~SelectorInstance()  {}

    int 	getSelectedOptionIndex();

    void setSelectedOptionIndex(int index, boolean update_outputs = TRUE);

    virtual boolean printAsJava(FILE* );

    const char *getClassName() 
		{ return ClassSelectorInstance; }
};

#endif // _SelectorInstance_h

