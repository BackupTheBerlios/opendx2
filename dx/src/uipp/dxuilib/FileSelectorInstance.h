/*  Open Visualization Data Explorer Source File */



#ifndef _FileSelectorInstance_h
#define _FileSelectorInstance_h


#include "defines.h"
#include "ValueInstance.h"

class FileSelectorNode;
class FileSelectorDialog;

//
// Class name definition:
//
#define ClassFileSelectorInstance	"FileSelectorInstance"


//
// Describes an instance of an interactor in a control Panel.
//
class FileSelectorInstance : public ValueInstance {

      friend FileSelectorNode;
      friend FileSelectorDialog;

  private:
    char 	*fileFilter;

  protected:
    void	setFileFilter(const char *filter);

  public:
    FileSelectorInstance(FileSelectorNode *n);
	
    ~FileSelectorInstance(); 

    const char *getFileFilter() { return this->fileFilter; }

    const char *getClassName() 
	{ return ClassFileSelectorInstance; }
};

#endif // _FileSelectorInstance_h

