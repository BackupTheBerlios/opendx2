/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#include "ImageFormatPSGrey.h"
#include "Application.h"

boolean ImageFormatPSGrey::ClassInitialized = FALSE;

String ImageFormatPSGrey::DefaultResources[] = {
    NUL(char*)
};


ImageFormatPSGrey::ImageFormatPSGrey (ImageFormatDialog* dialog) : 
    PostScriptImageFormat("PSGreyformat", dialog)
{

}

ImageFormatPSGrey::~ImageFormatPSGrey()
{
}


void ImageFormatPSGrey::initialize()
{
    if (!ImageFormatPSGrey::ClassInitialized) {
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    PostScriptImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormatPSGrey::DefaultResources);
	ImageFormatPSGrey::ClassInitialized = TRUE;
    }
}

boolean ImageFormatPSGrey::isA (Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatPSGrey);
    if (s == classname)
        return TRUE;
    else
        return PostScriptImageFormat::isA(classname);
}

