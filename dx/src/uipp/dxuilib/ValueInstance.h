/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _ValueInstance_h
#define _ValueInstance_h


#include "defines.h"
#include "InteractorInstance.h"


class List;
class ValueNode;
class Node;
class Network;
class ControlPanel;
class InteractorStyle;

//
// Class name definition:
//
#define ClassValueInstance	"ValueInstance"


//
// Describes an instance of an interactor in a control Panel.
//
class ValueInstance : public InteractorInstance {

  private:

  protected:

  public:
    ValueInstance(ValueNode *n);
	
    ~ValueInstance(); 

    const char *getClassName() 
	{ return ClassValueInstance; }
};

#endif // _ValueInstance_h

