/*  Open Visualization Data Explorer Source File */


#include "ImageFormatGIF.h"
#include "Application.h"

boolean ImageFormatGIF::ClassInitialized = FALSE;

String ImageFormatGIF::DefaultResources[] = {
    NUL(char*)
};


ImageFormatGIF::ImageFormatGIF (ImageFormatDialog* dialog) : 
    PixelImageFormat("GIFformat", dialog)
{

}

ImageFormatGIF::~ImageFormatGIF()
{
}


void ImageFormatGIF::initialize()
{
    if (!ImageFormatGIF::ClassInitialized) {
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    PixelImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormatGIF::DefaultResources);
	ImageFormatGIF::ClassInitialized = TRUE;
    }
}

boolean ImageFormatGIF::isA (Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatGIF);
    if (s == classname)
	return TRUE;
    else
	return this->ImageFormat::isA(classname);
}
