//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ImageFormatYUV.C,v 1.1 1999/03/24 15:17:42 gda Exp $
 *
 */

#include "ImageFormatYUV.h"
#include "Application.h"
#include "Strings.h"
#if defined(DXD_WIN) || defined(OS2)
#define unlink _unlink
#endif
#ifndef  DXD_DO_NOT_REQ_UNISTD_H
#include <unistd.h>
#endif


boolean ImageFormatYUV::ClassInitialized = FALSE;

String ImageFormatYUV::DefaultResources[] = {
    NUL(char*)
};


ImageFormatYUV::ImageFormatYUV (ImageFormatDialog* dialog) : 
    PixelImageFormat("YUVformat", dialog)
{

}

ImageFormatYUV::~ImageFormatYUV()
{
}


void ImageFormatYUV::initialize()
{
    if (!ImageFormatYUV::ClassInitialized) {
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    PixelImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormatYUV::DefaultResources);
	ImageFormatYUV::ClassInitialized = TRUE;
    }
}


void ImageFormatYUV::eraseOutputFile(const char *fname)
{
    char *cp;
    char *srcfile = DuplicateString(fname);
    char *file_to_delete = new char[strlen(fname) + 8];
    if (cp = strstr (srcfile, ".yuv")) cp[0] = '\0';
    sprintf (file_to_delete, "%s.yuv", srcfile);
    unlink (file_to_delete);
    sprintf (file_to_delete, "%s.size", srcfile);
    unlink (file_to_delete);

    delete file_to_delete;
    delete srcfile;
}

boolean ImageFormatYUV::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatYUV);
    if (s == classname)
	return TRUE;
    else
	return this->ImageFormat::isA(classname);
}

