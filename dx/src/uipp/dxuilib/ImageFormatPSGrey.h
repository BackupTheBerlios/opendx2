/*  Open Visualization Data Explorer Source File */


#ifndef _ImageFormatPSGrey_h
#define _ImageFormatPSGrey_h


#include "PostScriptImageFormat.h"

//
// Class name definition:
//
#define ClassImageFormatPSGrey	"ImageFormatPSGrey"

//
// SaveImageDialog class definition:
//				
class ImageFormatPSGrey : public PostScriptImageFormat
{
  private:

    static String  DefaultResources[];
    static boolean ClassInitialized;

  protected:

    virtual void	initialize();

  public:

    //
    // Constructor:
    //
    ImageFormatPSGrey(ImageFormatDialog *dialog);

    static ImageFormat* Allocator (ImageFormatDialog* dialog) 
	{ return  new ImageFormatPSGrey(dialog); }

    //
    // Destructor:
    //
    ~ImageFormatPSGrey();

    virtual const char*		paramString() { return "ps gray"; }
    virtual const char*		menuString() { return "Grey PostScript"; }
    virtual const char*		fileExtension() { return ".ps"; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassImageFormatPSGrey; }
    virtual boolean isA(Symbol classname);
};


#endif // _ImageFormatPSGrey_h
