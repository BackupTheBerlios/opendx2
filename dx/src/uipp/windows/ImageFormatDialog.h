/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#ifndef _ImageFormatDialog_h
#define _ImageFormatDialog_h


#include "Dialog.h"
#include "NoOpCommand.h"

//
// Class name definition:
//
#define ClassImageFormatDialog	"ImageFormatDialog"
#define CM_PER_INCH     2.54

//extern "C" void ImageFormatDialog_ChoiceCB(Widget, XtPointer, XtPointer);
////extern "C" void ImageFormatDialog_UnitsCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageFormatDialog_DirtyGammaCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageFormatDialog_RestoreCB(Widget, XtPointer, XtPointer);

class ImageNode;
class ImageFormat;
class Command;
class ToggleButtonInterface;
class CommandScope;
class List;

//
// SaveImageDialog class definition:
//				
class ImageFormatDialog : public Dialog, public NoOpCommand
{
  private:

    static bool ClassInitialized;
    //static String  DefaultResources[];
    //static Cursor  WatchCursor;

    static void ImageOutputCompletePH (void* , int, void* );

    friend class ImageFormat;

    List*		image_formats;
    CommandScope*	commandScope;

//    Widget		format_om;
//    Widget		format_pd;
//#if 0
//    Widget		units;
//    Widget		units_om;
//    Widget		units_pd;
//    Widget		pixels_button;
//    Widget		inches_button;
//    Widget		cms_button;
//    Widget		chosen_units;
//#endif
//    Widget		aboveBody;
//    Widget		belowBody;
//    Widget		gamma_number;
//    Widget		restore;
//
    int 		dirty;
    int			busyCursors;
    bool		resetting;

  protected:

    ImageFormat*		choice;
    ImageNode*			node;

    ToggleButtonInterface*	rerenderOption;
    ToggleButtonInterface*	delayedOption;

    Command*			rerenderCmd;
    Command*			delayedCmd;

    virtual void createDialog();

    virtual bool 		okCallback(Dialog *);
    virtual void 		cancelCallback(Dialog *);
    virtual void		restoreCallback();

    virtual const char*		getOutputFile() = 0;


    virtual bool		isPrinting() = 0;
    //virtual Widget		createControls(Widget parent) = 0;

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    //virtual void installDefaultResources(Widget baseWidget);

    //
    // Constructor:
    //
    ImageFormatDialog(char* name, ImageNode* node, 
	CommandScope* commandScope);

    //friend void ImageFormatDialog_ChoiceCB(Widget, XtPointer, XtPointer);
    ////friend void ImageFormatDialog_UnitsCB(Widget, XtPointer, XtPointer);
    //friend void ImageFormatDialog_DirtyGammaCB(Widget, XtPointer, XtPointer);
    //friend void ImageFormatDialog_RestoreCB(Widget, XtPointer, XtPointer);

    enum {
	DirtyFormat     = 1,
	DirtyEnabled    = 2,
	DirtyRerender   = 4,
	DirtyGamma	= 8,
	DirtyDelayed	= 16
    };

    bool 			isMetric();
    void			setChoice(ImageFormat*);
    virtual void		parseRecordFormat (const char *);
    virtual int			getRequiredWidth() { return 455; }
    virtual int			getRequiredHeight() = 0;

  public:

    //
    // manage activation of OK and Apply buttons
    //
    virtual void 		activate();
    virtual void 		deactivate(const char* msg=NULL);
    virtual void 		setCommandActivation();
    virtual void 		manage();
    virtual void		currentImage();
    virtual void    		update();
    virtual bool 		postFileSelectionDialog() { return true; }

    void associateNode(ImageNode* node) { this->node = node; }
    bool makeExecOutputImage(const char *, int , float , const char *, const char *);
    bool makeExecOutputImage(const char *, const char *, const char *);

    bool 	allowRerender();
    bool	isRerenderAllowed();
    bool	dirtyGamma() { return (this->dirty & ImageFormatDialog::DirtyGamma); }
    bool	delayedColors();
    double	getGamma();
    void	setGamma(double gamma);
    ImageNode* 	getNode() { return this->node; }
    bool	getDelayedColors();
    bool     dirtyFormat() { return (this->dirty & ImageFormatDialog::DirtyFormat); }
    void	setBusyCursor(bool busy);
    bool	isResetting() { return this->resetting; }

    //
    // Destructor:
    //
    ~ImageFormatDialog();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassImageFormatDialog; }
};


#endif // _ImageFormatDialog_h
