//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/VPEPage.h,v 1.1 1999/03/24 15:17:48 gda Exp $
 */


#ifndef _VPEPage_h
#define _VPEPage_h

#include <Xm/Xm.h>

#include "defines.h"
#include "EditorWorkSpace.h"
#include "WorkSpacePage.h"
#include "SymbolManager.h"


//
// Class name definition:
//
#define ClassVPEPage	"VPEPage"

class WorkSpaceInfo;
class WorkSpaceRoot;
class EditorWindow;

//
// EditorWorkSpace class definition:
//				
class VPEPage : public EditorWorkSpace, public WorkSpacePage
{
  private:

  protected:

    virtual boolean isRoot() { return FALSE; }

    virtual void saveWorkSpaceParams(WorkSpace*);

  public:

    VPEPage(const char *name, Widget parent, WorkSpaceInfo *info, 
			EditorWindow *editor, WorkSpaceRoot* root);
 
    ~VPEPage(){
	this->getWorkSpaceRoot()->removePage(this);
    }

    virtual void resize() {}

    const char* getClassName() { return ClassVPEPage; }
    virtual boolean isA (Symbol classname);
    boolean isA (const char* classname);
};


#endif // _VPEPage_h
