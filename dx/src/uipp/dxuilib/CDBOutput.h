//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/CDBOutput.h,v 1.1 1999/03/24 15:17:38 gda Exp $
 */


#ifndef _CDBOutput
#define _CDBOutput


#include "defines.h"
#include "Cacheability.h"
#include "CDBParameter.h"


//
// Class name definition:
//
#define ClassCDBOutput	"CDBOutput"

class ConfigurationDialog;

//
// CDBOutput class definition:
//				
class CDBOutput : public CDBParameter 
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //


  public:
    Cacheability initialCache;
    //
    // Constructor:
    //
    CDBOutput()
    {
	this->cacheWidget = NULL;
	this->cachePulldown = NULL;
	this->fullButton = NULL;
	this->lastButton = NULL;
	this->offButton = NULL;
    }

    //
    // Destructor:
    //
    ~CDBOutput()
    {
    }

    Widget  cacheWidget;
    Widget  cachePulldown;
    Widget  fullButton;
    Widget  lastButton;
    Widget  offButton;

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassCDBOutput;
    }
};


#endif // _CDBOutput
