//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/SaveFileDialog.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */



#include "defines.h"
#include "Strings.h"
#include "Application.h"
#include "SaveFileDialog.h"
#include "QuestionDialogManager.h"


#include <sys/stat.h>

class confirmation_data {
    public:
    confirmation_data() { filename=NULL; }
    ~confirmation_data() { if (this->filename) 
			delete this->filename; 
		    }
    char *filename;
    SaveFileDialog *dialog;
}; 

String SaveFileDialog::DefaultResources[] =
{
        NULL
};

SaveFileDialog::SaveFileDialog(
		const char *name, Widget parent, const char *ext) : 
		FileDialog(name,parent)
{
    if (ext)
	this->forced_extension = DuplicateString(ext);
    else
	this->forced_extension = NULL; 
}

SaveFileDialog::~SaveFileDialog()
{
    if (this->forced_extension)
	delete this->forced_extension;
}
void SaveFileDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget, SaveFileDialog::DefaultResources);
    this->FileDialog::installDefaultResources( baseWidget);
}
void SaveFileDialog::ConfirmationCancel(void *data)
{
    confirmation_data *cd = (confirmation_data *)data;
    delete cd;
}
void SaveFileDialog::ConfirmationOk(void *data)
{
    confirmation_data *cd = (confirmation_data *)data;

    cd->dialog->saveFile(cd->filename);
    delete cd;
}

void SaveFileDialog::okFileWork(const char *filename)
{
#if defined(DXD_WIN) && !defined(OS2)
    struct _stat buffer;
#else
    struct stat buffer;
#endif 

    int len = STRLEN(this->forced_extension);
    char *file = new char[STRLEN(filename) + len + 1];
    strcpy(file, filename);

    // 
    // Build/add the extension
    // 
    if(len > 0)
    {
	const char *ext = strrstr(file, this->forced_extension);
	if (!ext || (strlen(ext) != len))
	    strcat(file,this->forced_extension);
    }
    


#if defined(DXD_WIN) && !defined(OS2)
    if (_stat(file, &buffer) == 0) {
#else
    if (stat(file, &buffer) == 0) {
#endif
	confirmation_data *cd = new confirmation_data;
	cd->dialog = this;
	cd->filename = file;
        theQuestionDialogManager->modalPost(
	    this->parent,
	    "Do you want to overwrite an existing file?",
	    "Overwrite existing file",
	    (void *)cd,
	    SaveFileDialog::ConfirmationOk,
	    SaveFileDialog::ConfirmationCancel,
	    NULL);
    } else {
        this->saveFile(file);
	delete file;
    }

}


