//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ImageFormatPSColor.C,v 1.1 1999/03/24 15:17:41 gda Exp $
 *
 */

#include "ImageFormatPSColor.h"
#include "Application.h"

boolean ImageFormatPSColor::ClassInitialized = FALSE;

String ImageFormatPSColor::DefaultResources[] = {
    NUL(char*)
};


ImageFormatPSColor::ImageFormatPSColor (ImageFormatDialog* dialog) : 
    PostScriptImageFormat("PSColorformat", dialog)
{

}

ImageFormatPSColor::~ImageFormatPSColor()
{
}


void ImageFormatPSColor::initialize()
{
    if (!ImageFormatPSColor::ClassInitialized) {
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    PostScriptImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormatPSColor::DefaultResources);
	ImageFormatPSColor::ClassInitialized = TRUE;
    }
}

boolean ImageFormatPSColor::isA (Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatPSColor);
    if (s == classname)
	return TRUE;
    else
	return PostScriptImageFormat::isA(classname);
}
