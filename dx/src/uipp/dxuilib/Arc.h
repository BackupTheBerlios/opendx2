//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/Arc.h,v 1.1 1999/03/24 15:17:38 gda Exp $
 */


#ifndef _Arc_h
#define _Arc_h


#include "defines.h"
#include "Base.h"



//
// Class name definition:
//
#define ClassArc	"Arc"

//
// referenced classes
//
class Node;
class ArcStandIn;

//
// Arc class definition:
//				
class Arc : public Base
{
  private:
    //
    // Private member data:
    //
    Node        *from;
    int          fromParameter;
    Node        *to;
    int          toParameter;
    ArcStandIn  *arcStandIn;

  protected:
    //
    // Protected member data:
    //


  public:
    //
    // Constructor:
    //
    Arc(Node *fromNode, int fp, Node *toNode, int tp);

    //
    // Destructor:
    //
    ~Arc();

    //
    // Access routines.
    //

    Node *getSourceNode(int& param)
    {
	param = this->fromParameter;
	return  this->from;
    }

    Node *getDestinationNode(int& param)
    {
	param = this->toParameter;
	return  this->to;
    }
    void setArcStandIn(ArcStandIn* asi)
    {
        this->arcStandIn = asi;
    }
    ArcStandIn* getArcStandIn()
    {
        return this->arcStandIn;
    }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassArc;
    }
};


#endif // _Arc_h
