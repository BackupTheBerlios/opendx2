/*  Open Visualization Data Explorer Source File */


#ifndef _ReceiverNode_h
#define _ReceiverNode_h


#include "UIConfig.h"

#include "defines.h"
#include "UniqueNameNode.h"


//
// Class name definition:
//
#define ClassReceiverNode	"ReceiverNode"

//
// Referenced Classes
class TransmitterNode;

//
// ReceiverNode class definition:
//				
class ReceiverNode : public UniqueNameNode
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

    virtual boolean initialize();

  public:
    //
    // Constructor:
    //
    ReceiverNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~ReceiverNode();

    boolean setLabelString(const char *label);

    //
    // Is this receiver connected to a Transmitter.
    //
    boolean isTransmitterConnected();

    //
    // Get the node that is connected to the Transmitter that this Receiver
    // is receiving from.  IF there is no Transmitter for this Receiver, or 
    // the Transmitter is not connected, return NULL, otherwise the Node.
    //
    Node *getUltimateSourceNode(int* param_no = NUL(int*));

    //
    // Switch the node from one net to another.  Look for a tranmitter to
    // connect to.
    //
    void switchNetwork(Network *from, Network *to);

    //
    // Determine if this node is a node of the given class
    //
    virtual boolean isA(Symbol classname);

    //
    // Check for name conflicts.  Usually you disallow 2 nodes with the same
    // labelString, but it certain cases it's desirable.  Capture that logic
    // locally.
    //
    virtual boolean namesConflict (const char* his_label, const char* my_label, 
	const char* his_classname);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassReceiverNode;
    }
};


#endif // _ReceiverNode_h
