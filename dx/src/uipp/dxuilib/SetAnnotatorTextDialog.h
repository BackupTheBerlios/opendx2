//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/SetAnnotatorTextDialog.h,v 1.1 1999/03/24 15:17:47 gda Exp $
 *
 */


#ifndef _SetAnnotatorTextDialog_h
#define _SetAnnotatorTextDialog_h


#include "SetDecoratorTextDialog.h"

//
// Class name definition:
//
#define ClassSetAnnotatorTextDialog	"SetAnnotatorTextDialog"

class LabelDecorator;
class DecoratorStyle;


extern "C" void SetAnnotatorTextDialog_HideShowCB (Widget , XtPointer , XtPointer);


//
// SetAnnotatorTextDialog class definition:
//				

class SetAnnotatorTextDialog : public SetDecoratorTextDialog
{
  private:
    //
    // Private member data:
    //
    static boolean ClassInitialized;
    static String  DefaultResources[];

    DecoratorStyle* hide_style;
    DecoratorStyle* show_style;

  protected:
    //
    // Protected member data:
    //
    Widget hide_show;
    virtual Widget createDialog(Widget);
    virtual void hideCallback();

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    virtual void installDefaultResources(Widget baseWidget);

    friend void SetAnnotatorTextDialog_HideShowCB (Widget , XtPointer , XtPointer);

    //
    // The string returned must match what's in VPEAnnotator::DefaultResources
    //
    virtual const char* defaultJustifySetting();

  public:

    //
    // Constructor:
    //
    SetAnnotatorTextDialog(Widget parent, boolean readonly, 
	LabelDecorator *dec);

    //
    // Destructor:
    //
    ~SetAnnotatorTextDialog();

    virtual void setDecorator(LabelDecorator*);
    virtual void manage();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSetAnnotatorTextDialog;
    }
};


#endif // _SetAnnotatorTextDialog_h
