//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// TextFileFileDialog.C -							    //
//                                                                          //
// TextFileFileDialog Class methods and other related functions/procedures.	    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/TextFileFileDialog.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */



#include "defines.h"
#include "Strings.h"
#include "Application.h"
#include "TextFileFileDialog.h"
#include "TextFile.h"

#include <sys/stat.h>

boolean TextFileFileDialog::ClassInitialized = FALSE;

String TextFileFileDialog::DefaultResources[] =
{
        "*dialogTitle:     Save Macro As File...",
        "*dirMask:         *.net",
        NULL
};


void TextFileFileDialog::okFileWork(const char *filename)
{
    this->textFile->fileSelectCallback(filename);	
}

//
// Constructor for derived classes 
//
TextFileFileDialog::TextFileFileDialog(const char *name, TextFile *tf ) :
			   FileDialog(name, tf->getRootWidget())
{
    this->textFile = tf;
}
//
// Constructor for instances of THIS class
//
TextFileFileDialog::TextFileFileDialog( TextFile *tf ) :
			   FileDialog("textFileFileDialog", 
			    tf->getRootWidget())
{
    this->textFile = tf;
    if (NOT TextFileFileDialog::ClassInitialized)
    {
        TextFileFileDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}

void TextFileFileDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget, TextFileFileDialog::DefaultResources);
    this->FileDialog::installDefaultResources( baseWidget);
}







