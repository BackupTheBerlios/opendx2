/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _OpenColormapDialog_h
#define _OpenColormapDialog_h


#include "FileDialog.h"


//
// Class name definition:
//
#define ClassOpenColormapDialog	"OpenColormapDialog"

class Dialog;
class ColormapEditor;

//
// OpenColormapDialog class definition:
//				
class OpenColormapDialog : public dxui::FileDialog
{
  private:

    static bool ClassInitialized;
    //static String  DefaultResources[];
    ColormapEditor *editor;
    bool	   opening;

  protected:
    virtual void okFileWork(const char *string);

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    //virtual void installDefaultResources(Widget baseWidget);

  public:
    //
    // Constructor:
    //
    OpenColormapDialog(
		       ColormapEditor* editor,
		       int             mode);


    //
    // Destructor:
    //
    ~OpenColormapDialog(){}

    void setMode(bool openMode);

    //
    // Set the correct title 'Open/Close Colormap...'
    //
    virtual void manage();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassOpenColormapDialog;
    }
};


#endif // _OpenColormapDialog_h
