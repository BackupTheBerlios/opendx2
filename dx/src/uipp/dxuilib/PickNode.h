//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// PickNode.h -							    //
//                                                                          //
// Definition for the PickNode class.					    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/PickNode.h,v 1.1 1999/03/24 15:17:44 gda Exp $
 *
 */

#ifndef _PickNode_h
#define _PickNode_h


#include "defines.h"
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

    virtual boolean initialize();
    virtual void initializeAfterNetworkMember();

    virtual boolean setLabelString(const char *label);

    virtual void setCursorValue(int cursor, double x, double y, double z = 0.0);
    virtual void resetCursor();

    virtual void pickFrom(Node *n);

    //
    // Determine if this node is a node of the given class
    //
    virtual boolean isA(Symbol classname);

    virtual boolean hasJavaRepresentation() { return TRUE; }
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
