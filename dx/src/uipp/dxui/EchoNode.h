//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// EchoNode.h -							    //
//                                                                          //
// Definition for the EchoNode class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/EchoNode.h,v 1.1 1999/03/31 22:31:33 gda Exp $
 */


#ifndef _EchoNode_h
#define _EchoNode_h


#include "defines.h"
#include "ModuleMessagingNode.h"


//
// Class name definition:
//
#define ClassEchoNode	"EchoNode"

//
// Referenced Classes
//
class NodeDefinition;
class Network;

//
// EchoNode class definition:
//				
class EchoNode : public ModuleMessagingNode
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //

    //
    // Called when a message is received from the executive after
    // this->ExecModuleMessageHandler() is registered in
    // this->Node::netPrintNode() to receive messages for this node.
    // The format of the message coming back is defined by the derived class.
    //
    virtual void execModuleMessageHandler(int id, const char *line);

    //
    // Returns a string that is used to register
    // this->ExecModuleMessageHandler() when this->hasModuleMessageProtocol()
    // return TRUE.  This version, returns an id that is unique to this
    // instance of this node.
    //
    virtual const char *getModuleMessageIdString();


  public:
    //
    // Constructor:
    //
    EchoNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~EchoNode();

    //
    // Determine if this node is a node of the given class
    //
    virtual boolean isA(Symbol classname);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassEchoNode;
    }
};


#endif // _EchoNode_h