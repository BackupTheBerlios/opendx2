//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// CDBInput.h -								    //
//                                                                          //
// Definition for the CDBInput class.					    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/CDBInput.h,v 1.1 1999/03/24 15:17:38 gda Exp $
 */


#ifndef _CDBInput
#define _CDBInput


#include "defines.h"
#include "Strings.h"
#include "CDBParameter.h"
#include "../base/TextPopup.h"


//
// Class name definition:
//
#define ClassCDBInput	"CDBInput"

class ConfigurationDialog;

//
// CDBInput class definition:
//				
class CDBInput : public CDBParameter 
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
#if 11
    TextPopup *valueTextPopup;
#else
    Widget  valueWidget;
#endif
    boolean valueChanged;
    boolean initialValueIsDefault;
    char   *initialValue;
    int	    modified;    

    //
    // Constructor:
    //
    CDBInput() : CDBParameter() 
    {
#if 00 
	this->valueWidget = NULL;
#endif
	this->valueChanged = FALSE;
	this->initialValue = NULL;
	this->initialValueIsDefault = FALSE;
	this->valueTextPopup = new TextPopup();
	this->modified = 0;
    }

    //
    // Destructor:
    //
    ~CDBInput()
    {
	if (this->initialValue != NULL)
	    delete initialValue;
	if (this->valueTextPopup)
	    delete this->valueTextPopup;
    }

    void setInitialValue(const char *s)
    {
	if (this->initialValue)
	    delete this->initialValue;
	if (s)
	    this->initialValue = DuplicateString(s);
	else
	    this->initialValue = NULL;
    }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassCDBInput;
    }
};


#endif // _CDBInput
