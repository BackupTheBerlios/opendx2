/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _ValueListInstance_h
#define _ValueListInstance_h


#include "defines.h"
#include "ValueInstance.h"


class List;
class ValueListNode;
class Node;
class Network;
class ControlPanel;
class InteractorStyle;

//
// Class name definition:
//
#define ClassValueListInstance	"ValueListInstance"


//
// Describes an instance of an interactor in a control Panel.
//
class ValueListInstance : public ValueInstance {

  private:

  protected:

  public:
    ValueListInstance(ValueListNode *n);
	
    ~ValueListInstance(); 

    const char *getClassName() 
	{ return ClassValueListInstance; }
};

#endif // _ValueListInstance_h

