//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ImageFormatGIF.h,v 1.1 1999/03/24 15:17:41 gda Exp $
 *
 */

#ifndef _ImageFormatGIF_h
#define _ImageFormatGIF_h


#include "PixelImageFormat.h"

//
// Class name definition:
//
#define ClassImageFormatGIF	"ImageFormatGIF"

//
// SaveImageDialog class definition:
//				
class ImageFormatGIF : public PixelImageFormat
{
  private:

    static String  DefaultResources[];
    static boolean ClassInitialized;

  protected:

    virtual void	initialize();

    virtual boolean		supportsPrinting() { return TRUE; }

  public:

    //
    // Constructor:
    //
    ImageFormatGIF(ImageFormatDialog *dialog);

    static ImageFormat* Allocator (ImageFormatDialog* dialog) 
	{ return  new ImageFormatGIF(dialog); }


    //
    // Destructor:
    //
    ~ImageFormatGIF();

    virtual const char*		paramString() { return "gif"; }
    virtual const char*		menuString() { return "GIF"; }
    virtual const char*		fileExtension() { return ".gif"; }
    virtual boolean		supportsDelayedColors() { return FALSE; }
    virtual boolean		requiresDelayedColors() { return TRUE; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassImageFormatGIF; }
    virtual boolean isA(Symbol classname);
};


#endif // _ImageFormatGIF_h
