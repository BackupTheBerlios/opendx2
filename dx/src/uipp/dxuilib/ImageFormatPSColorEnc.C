//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ImageFormatPSColorEnc.C,v 1.1 1999/03/24 15:17:41 gda Exp $
 *
 */

#include "ImageFormatPSColorEnc.h"
#include "Application.h"

boolean ImageFormatPSColorEnc::ClassInitialized = FALSE;

String ImageFormatPSColorEnc::DefaultResources[] = {
    NUL(char*)
};


ImageFormatPSColorEnc::ImageFormatPSColorEnc (ImageFormatDialog* dialog) : 
    PostScriptImageFormat("PSColorEncformat", dialog)
{

}

ImageFormatPSColorEnc::~ImageFormatPSColorEnc()
{
}


void ImageFormatPSColorEnc::initialize()
{
    if (!ImageFormatPSColorEnc::ClassInitialized) {
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    PostScriptImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormatPSColorEnc::DefaultResources);
	ImageFormatPSColorEnc::ClassInitialized = TRUE;
    }
}

boolean ImageFormatPSColorEnc::isA (Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatPSColorEnc);
    if (s == classname)
        return TRUE;
    else
        return PostScriptImageFormat::isA(classname);
}

