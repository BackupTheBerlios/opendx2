//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ImageFormatRGB.h,v 1.1 1999/03/24 15:17:41 gda Exp $
 *
 */

#ifndef _ImageFormatRGB_h
#define _ImageFormatRGB_h


#include "PixelImageFormat.h"

//
// Class name definition:
//
#define ClassImageFormatRGB	"ImageFormatRGB"

//
// SaveImageDialog class definition:
//				
class ImageFormatRGB : public PixelImageFormat
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
    ImageFormatRGB(ImageFormatDialog *dialog);

    static ImageFormat* Allocator (ImageFormatDialog* dialog) 
	{ return  new ImageFormatRGB(dialog); }

    //
    // Destructor:
    //
    ~ImageFormatRGB();

    virtual const char*		paramString() { return "rgb"; }
    virtual const char*		menuString() { return "RGB"; }
    virtual const char*		fileExtension() { return ".rgb"; }
    virtual boolean 		supportsAppend() { return TRUE; }
    virtual boolean		supportsDelayedColors() { return FALSE; }
    virtual void		eraseOutputFile(const char *srcfile);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassImageFormatRGB; }
    virtual boolean isA(Symbol classname);
};


#endif // _ImageFormatRGB_h
