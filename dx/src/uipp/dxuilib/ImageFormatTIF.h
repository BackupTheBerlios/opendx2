//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ImageFormatTIF.h,v 1.1 1999/03/24 15:17:42 gda Exp $
 *
 */

#ifndef _ImageFormatTIF_h
#define _ImageFormatTIF_h


#include "PixelImageFormat.h"

//
// Class name definition:
//
#define ClassImageFormatTIF	"ImageFormatTIF"

//
// SaveImageDialog class definition:
//				
class ImageFormatTIF : public PixelImageFormat
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
    ImageFormatTIF(ImageFormatDialog *dialog);

    static ImageFormat* Allocator (ImageFormatDialog* dialog) 
	{ return  new ImageFormatTIF(dialog); }


    //
    // Destructor:
    //
    ~ImageFormatTIF();

    virtual const char*		paramString() { return "tiff"; }
    virtual const char*		menuString() { return "TIFF"; }
    virtual const char*		fileExtension() { return ".tiff"; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassImageFormatTIF; }
    virtual boolean isA(Symbol classname);
};


#endif // _ImageFormatTIF_h
