//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ImageFormatMIF.h,v 1.1 1999/03/24 15:17:41 gda Exp $
 *
 */

#ifndef _ImageFormatMIF_h
#define _ImageFormatMIF_h


#include "PixelImageFormat.h"

//
// Class name definition:
//
#define ClassImageFormatMIF	"ImageFormatMIF"

//
// SaveImageDialog class definition:
//				
class ImageFormatMIF : public PixelImageFormat
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
    ImageFormatMIF(ImageFormatDialog *dialog);

    static ImageFormat* Allocator (ImageFormatDialog* dialog) 
	{ return  new ImageFormatMIF(dialog); }


    //
    // Destructor:
    //
    ~ImageFormatMIF();

    virtual const char*		paramString() { return "miff"; }
    virtual const char*		menuString() { return "MIFF"; }
    virtual const char*		fileExtension() { return ".miff"; }
    virtual boolean             supportsAppend() { return TRUE; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassImageFormatMIF; }
    virtual boolean isA(Symbol classname);
};


#endif // _ImageFormatMIF_h
