/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#ifndef _ImageFormatREX_h
#define _ImageFormatREX_h


#include "PixelImageFormat.h"

//
// Class name definition:
//
#define ClassImageFormatREX	"ImageFormatREX"

//
// SaveImageDialog class definition:
//				
class ImageFormatREX : public PixelImageFormat
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
    ImageFormatREX(ImageFormatDialog *dialog);

    static ImageFormat* Allocator (ImageFormatDialog* dialog) 
	{ return  new ImageFormatREX(dialog); }

    //
    // Destructor:
    //
    ~ImageFormatREX();

    virtual const char*		paramString() { return "r+g+b"; }
    virtual const char*		menuString() { return "R+G+B"; }
    virtual const char*		fileExtension() { return ".r"; }
    virtual boolean 		supportsAppend() { return TRUE; }
    virtual void		eraseOutputFile(const char *fname);
    virtual boolean		supportsDelayedColors() { return FALSE; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassImageFormatREX; }
    virtual boolean isA(Symbol classname);
};


#endif // _ImageFormatREX_h
