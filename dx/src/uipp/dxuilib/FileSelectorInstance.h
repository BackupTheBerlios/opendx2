//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// FileSelectorInstance.C -                                                 //
//                                                                          //
// FileSelectorInstance  Class methods and other related 	
// functions/procedures.             					//
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/FileSelectorInstance.h,v 1.1 1999/03/24 15:17:40 gda Exp $
 */


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

