/*  Open Visualization Data Explorer Source File */

#ifndef _ImageFormatPSColor_h
#define _ImageFormatPSColor_h


#include "PostScriptImageFormat.h"

//
// Class name definition:
//
#define ClassImageFormatPSColor	"ImageFormatPSColor"

//
// SaveImageDialog class definition:
//				
class ImageFormatPSColor : public PostScriptImageFormat
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
    ImageFormatPSColor(ImageFormatDialog *dialog);

    static ImageFormat* Allocator (ImageFormatDialog* dialog) 
	{ return  new ImageFormatPSColor(dialog); }

    //
    // Destructor:
    //
    ~ImageFormatPSColor();

    virtual const char*		paramString() { return "ps color"; }
    virtual const char*		menuString() { return "Color PostScript"; }
    virtual const char*		fileExtension() { return ".ps"; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassImageFormatPSColor; }
    virtual boolean isA(Symbol classname);
};


#endif // _ImageFormatPSColor_h
