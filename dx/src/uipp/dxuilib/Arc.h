/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>




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
