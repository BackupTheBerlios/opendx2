/*  Open Visualization Data Explorer Source File */


#ifndef _ProbeNode_h
#define _ProbeNode_h


#include "UIConfig.h"

#include "defines.h"
#include "Node.h"


//
// Class name definition:
//
#define ClassProbeNode	"ProbeNode"

//
// Referenced Classes
class Parameter;

//
// ProbeNode class definition:
//				
class ProbeNode : public Node
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

  public:
    //
    // Constructor:
    //
    ProbeNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~ProbeNode();

    virtual boolean initialize();
    virtual void initializeAfterNetworkMember();
    virtual boolean setLabelString(const char *label);

    Parameter* getOutput();
    virtual void    setCursorValue(int, double, double, double = 0.0);
    virtual void    deleteCursor(int);
    virtual void    resetValueList(int cursor,
			   boolean toDelete = TRUE,
			   double x = 0.0, 
			   double y = 0.0, 
			   double z = 0.0); 

    //
    // Switch the node from one net to another.  
    // Resolve any name space collisions.
    //
    virtual void switchNetwork(Network *from, Network *to);

    //
    // Determine if this node is a node of the given class
    //
    virtual boolean isA(Symbol classname);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassProbeNode;
    }
};


#endif // _ProbeNode_h
