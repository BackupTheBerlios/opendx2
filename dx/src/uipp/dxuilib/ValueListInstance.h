//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// ValueList.C -                                                               //
//                                                                          //
// ValueList Class methods and other related functions/procedures.             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ValueListInstance.h,v 1.1 1999/03/24 15:17:48 gda Exp $
 */


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

