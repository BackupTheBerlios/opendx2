/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _PickNode_h
#define _PickNode_h


#include "ProbeNode.h"


//
// Class name definition:
//
#define ClassPickNode	"PickNode"

//
// Referenced Classes
class Parameter;

//
// PickNode class definition:
//				
class PickNode : public ProbeNode
{

  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //
    virtual char *netNodeString(const char *prefix);
    virtual char *valuesString(const char *prefix);

    void incrementIndex();

  public:
    //
    // Constructor:
    //
    PickNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~PickNode();

    virtual bool initialize();
    virtual void initializeAfterNetworkMember();

    virtual bool setLabelString(const char *label);

    virtual void setCursorValue(int cursor, double x, double y, double z = 0.0);
    virtual void resetCursor();

    virtual void pickFrom(Node *n);

    //
    // Determine if this node is a node of the given class
    //
    virtual bool isA(Symbol classname);

    virtual bool hasJavaRepresentation() { return true; }
    virtual const char* getJavaNodeName() { return "PickNode"; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassPickNode;
    }
};


#endif // _PickNode_h
