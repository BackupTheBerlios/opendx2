//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ImageFormatYUV.h,v 1.1 1999/03/24 15:17:42 gda Exp $
 *
 */

#ifndef _ImageFormatYUV_h
#define _ImageFormatYUV_h


#include "PixelImageFormat.h"

//
// Class name definition:
//
#define ClassImageFormatYUV	"ImageFormatYUV"

//
// SaveImageDialog class definition:
//				
class ImageFormatYUV : public PixelImageFormat
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
    ImageFormatYUV(ImageFormatDialog *dialog);

    static ImageFormat* Allocator (ImageFormatDialog* dialog) 
	{ return  new ImageFormatYUV(dialog); }

    //
    // Destructor:
    //
    ~ImageFormatYUV();

    virtual const char*		paramString() { return "yuv"; }
    virtual const char*		menuString() { return "YUV"; }
    virtual const char*		fileExtension() { return ".yuv"; }
    virtual boolean 		supportsAppend() { return TRUE; }
    virtual void		eraseOutputFile(const char *fname);
    virtual boolean		supportsDelayedColors() { return FALSE; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassImageFormatYUV; }
    virtual boolean isA(Symbol classname);
};


#endif // _ImageFormatYUV_h
