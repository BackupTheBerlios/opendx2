/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#ifndef _DATA_FILE_DIALOG_H
#define _DATA_FILE_DIALOG_H

#include "FileDialog.h"

#define ClassDataFileDialog "DataFileDialog"

class GARChooserWindow;

class DataFileDialog: public FileDialog 
{
  private:
    GARChooserWindow* gcw;

  protected:

    static String DefaultResources[];
    static boolean ClassInitialized;

    virtual void okFileWork(const char *string);

    virtual void installDefaultResources (Widget );

  public:

    DataFileDialog (Widget parent, GARChooserWindow *gcw);
    ~DataFileDialog();

    const char *getClassName() { return ClassDataFileDialog; }
};

#endif //_DATA_FILE_DIALOG_H
