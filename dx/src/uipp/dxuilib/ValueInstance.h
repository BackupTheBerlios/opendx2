//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// Value.C -                                                               //
//                                                                          //
// Value Class methods and other related functions/procedures.             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ValueInstance.h,v 1.1 1999/03/24 15:17:48 gda Exp $
 */


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

