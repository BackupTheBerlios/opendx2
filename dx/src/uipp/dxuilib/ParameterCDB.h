/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _ParameterCDB_h
#define _ParameterCDB_h


#include "defines.h"
#include "ConfigurationDialog.h"
#include "List.h"


//
// Class name definition:
//
#define ClassParameterCDB	"ParameterCDB"

//
// Referenced classes
class Node;
class List;

//
// ParameterCDB class definition:
//				
class ParameterCDB : public ConfigurationDialog
{
  private:
    //
    // Private member data:
    //
    static boolean ClassInitialized;
    static String  DefaultResources[];

  protected:
    //
    // Protected member data:
    //
    // The Parameter's parameters.
    Widget position;
    Widget name;
    Widget type;
    Widget value;
    Widget description;
    Widget required;
    Widget descriptive;
    Widget hidden;

    int     initialPosition;
    char   *initialName;
    char   *initialValue;
    char   *initialDescription;
    boolean initialRequired;
    boolean initialDescriptive;
    boolean initialHidden;

    //
    // Protected functions

    virtual Widget createParam(Widget parent, Widget top);

    // See the ConfigurationDialog's description of these.  createInputs
    // replaces the standard inputs section with one that consists of
    // a text widget for each of the expression's parameters (and a source
    // field), and the expression itself.
    virtual Widget createInputs(Widget parent, Widget top);
    virtual Widget createOutputs(Widget parent, Widget top);
    virtual boolean applyCallback(Dialog *d);
    virtual void restoreCallback(Dialog *d);

    virtual void saveInitialValues();
    virtual void restoreInitialValues();
    virtual boolean applyValues();


    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    virtual void installDefaultResources(Widget baseWidget);

  public:
    static ConfigurationDialog *AllocateConfigurationDialog(Widget parent,
							   Node *node);
    //
    // Constructor:
    //
    ParameterCDB(Widget parent, Node *node);

    //
    // Destructor:
    //
    ~ParameterCDB();

    virtual void changeInput(int i);
    virtual void changeOutput(int i);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassParameterCDB;
    }
};


#endif // _ParameterCDB_h
