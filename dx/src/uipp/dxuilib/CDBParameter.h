/*  Open Visualization Data Explorer Source File */



#ifndef _CDBParameter
#define _CDBParameter


#include "defines.h"
#include "Base.h"


//
// Class name definition:
//
#define ClassCDBParameter	"CDBParameter"

class ConfigurationDialog;

//
// CDBParameter class definition:
//				
class CDBParameter : public Base
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
    Widget  nameWidget;
    Widget  hideWidget;
    Widget  typeWidget;
    Widget  connectedToWidget;

    boolean initialIsHidden;
    boolean lineIsHidden;

#if 0
    Widget  valueWidget;
    boolean valueChanged;
    boolean initialValueIsDefault;
    char   *initialValue;
    int	    cycleState;    
#endif

    //
    // Constructor:
    //
    CDBParameter()
    {
	this->nameWidget = NULL;
	this->hideWidget = NULL;
	this->typeWidget = NULL;
	this->connectedToWidget = NULL;
	this->initialIsHidden = FALSE;
	this->lineIsHidden = FALSE;
    }

    //
    // Destructor:
    //
    ~CDBParameter() {}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassCDBParameter;
    }
};


#endif // _CDBParameter
