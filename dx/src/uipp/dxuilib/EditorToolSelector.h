/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "../base/defines.h"




#ifndef _EditorToolSelector_h
#define _EditorToolSelector_h


#include "ToolSelector.h"


//
// Class name definition:
//
#define ClassEditorToolSelector	"EditorToolSelector"

class EditorWindow;

//
// EditorToolSelector class definition:
//				
class EditorToolSelector : public ToolSelector
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //
    EditorWindow *editor;

    virtual void toolSelect(Widget widget, XmListCallbackStruct* callData);
    virtual void categorySelect(Widget widget, XmListCallbackStruct* callData);


  public:
    //
    // Constructor:
    //
    EditorToolSelector(const char *name, EditorWindow *editor);

    //
    // Destructor:
    //
    ~EditorToolSelector();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassEditorToolSelector;
    }
};


#endif // _EditorToolSelector_h
