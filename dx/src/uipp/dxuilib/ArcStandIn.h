/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _ArcStandIn_h
#define _ArcStandIn_h


#include "defines.h"
#include "Base.h"
#include <../widgets/WorkspaceW.h>


//
// Class name definition:
//
#define ClassArcStandIn	"ArcStandIn"

//
// referenced classes
//

//
// ArcStandIn class definition:
//				
class ArcStandIn : public Base
{
  private:
    //
    // Private member data:
    //
    XmWorkspaceWidget parent;
    XmWorkspaceLine line;

  protected:
    //
    // Protected member data:
    //


  public:
    //
    // Constructor:
    //
    ArcStandIn(XmWorkspaceWidget w, XmWorkspaceLine l)
    {
       this->line = l;
       this->parent = w;
    }

    //
    // Destructor:
    //
    ~ArcStandIn()
    {
        XmDestroyWorkspaceLine((XmWorkspaceWidget) this->parent, 
                               this->line, FALSE);
    }
    void setWorkSpaceLine(XmWorkspaceLine l)
    {
        this->line = l;
    }
    XmWorkspaceLine getWorkSpaceLine()
    {
        return this->line;
    }

    //
    // Print a representation of the stand in on a PostScript device.  We
    // assume that the device is in the same coordinate space as the parent
    // of this uicomponent (i.e. we send the current geometry to the 
    // PostScript output file).  
    //
    boolean printAsPostScript(FILE *f);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassArcStandIn;
    }
};


#endif // _ArcStandIn_h
