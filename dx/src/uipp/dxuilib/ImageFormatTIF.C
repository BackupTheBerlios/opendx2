/*  Open Visualization Data Explorer Source File */


#include "ImageFormatTIF.h"
#include "Application.h"

boolean ImageFormatTIF::ClassInitialized = FALSE;

String ImageFormatTIF::DefaultResources[] = {
    NUL(char*)
};


ImageFormatTIF::ImageFormatTIF (ImageFormatDialog* dialog) : 
    PixelImageFormat("TIFFformat", dialog)
{

}

ImageFormatTIF::~ImageFormatTIF()
{
}


void ImageFormatTIF::initialize()
{
    if (!ImageFormatTIF::ClassInitialized) {
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    PixelImageFormat::DefaultResources);
	this->setDefaultResources (theApplication->getRootWidget(),
	    ImageFormatTIF::DefaultResources);
	ImageFormatTIF::ClassInitialized = TRUE;
    }
}

boolean ImageFormatTIF::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatTIF);
    if (s == classname)
	return TRUE;
    else
	return this->ImageFormat::isA(classname);
}

