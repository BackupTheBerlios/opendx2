/*  Open Visualization Data Explorer Source File */

#ifndef _ImageFormatPSGreyEnc_h
#define _ImageFormatPSGreyEnc_h


#include "PostScriptImageFormat.h"

//
// Class name definition:
//
#define ClassImageFormatPSGreyEnc	"ImageFormatPSGreyEnc"

//
// SaveImageDialog class definition:
//				
class ImageFormatPSGreyEnc : public PostScriptImageFormat
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
    ImageFormatPSGreyEnc(ImageFormatDialog *dialog);

    static ImageFormat* Allocator (ImageFormatDialog* dialog) 
	{ return  new ImageFormatPSGreyEnc(dialog); }

    //
    // Destructor:
    //
    ~ImageFormatPSGreyEnc();

    virtual const char*		paramString() { return "eps gray"; }
    virtual const char*		menuString() { return "Grey PostScript (enc)"; }
    virtual const char*		fileExtension() { return ".epsf"; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassImageFormatPSGreyEnc; }
    virtual boolean isA(Symbol classname);
};


#endif // _ImageFormatPSGreyEnc_h
