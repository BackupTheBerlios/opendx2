//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ImageFormatMIF.C,v 1.1 1999/03/24 15:17:41 gda Exp $
 *
 */

#include "ImageFormatMIF.h"
#include "Application.h"

boolean ImageFormatMIF::ClassInitialized = FALSE;

String ImageFormatMIF::DefaultResources[] = {
    NUL(char*)
};


ImageFormatMIF::ImageFormatMIF (ImageFormatDialog* dialog) : 
    PixelImageFormat("MIFformat", dialog)
{

}

ImageFormatMIF::~ImageFormatMIF()
{
}


void ImageFormatMIF::initialize()
{
    if (!ImageFormatMIF::ClassInitialized) {
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    PixelImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormatMIF::DefaultResources);
	ImageFormatMIF::ClassInitialized = TRUE;
    }
}

boolean ImageFormatMIF::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatMIF);
    if (s == classname)
	return TRUE;
    else
	return this->ImageFormat::isA(classname);
}

