//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// ShadowedOutputNode.h -						    //
//                                                                          //
// Definition for the ShadowedOutputNode class.				    //
//
// These are DrivenNodes that have inputs that are shadow (are kept in
// sync with one or more of their outputs).  We define a virtual method,
// this->getShadowingInput() that defines the mapping of output to input
// indices.   We redefined setOutputValue() to update a shadowing input
// when necessary.
// 
// The setShadowedOutputSentFromServer() is used to update both the output
// and its shadowing input internally, and send the value of the shadowing
// input back to the executive.  
//
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ShadowedOutputNode.h,v 1.1 1999/03/31 22:35:05 gda Exp $
 */


#ifndef _ShadowedOutputNode_h
#define _ShadowedOutputNode_h


#include "defines.h"
#include "DrivenNode.h"


//
// Class name definition:
//
#define ClassShadowedOutputNode	"ShadowedOutputNode"


//
// ShadowedOutputNode class definition:
//				
class ShadowedOutputNode : public DrivenNode
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
    // Define the mapping of inputs that shadow outputs.
    // By default, all data driven interactors, have a single output that is
    // shadowed by the third input.
    // Returns an input index (greater than 1) or 0 if there is no shadowing
    // input for the given output index.
    //
    virtual int getShadowingInput(int output_index);


    //
    // A node that has its first parameter set or its last parameter unset
    // must mark the network dirty so that is resent with/without the module
    // in the network.  
    // FIXME: this really belongs in an OptionalExecuteNode class between
    //	DrivenNode and this class.
    //
    virtual void ioParameterStatusChanged(boolean input, int index,
				NodeParameterStatusChange status);

    //
    // Update any inputs that are being updated by the server (i.e. the
    // module that is doing the data-driven operations).
    // We update the values internally, and send the shadowing input
    // value back to the executive with an Executive() call.
    // We use the Executive call instead of a direct assignment, because if
    // we are currently in execute-on-change  mode, the assignment would cause
    // extra executions.  
    // The Executive() call (a dictionary update) avoids that.
    //
    Type setShadowedOutputSentFromServer(
			    int output_index, const char *val, Type t);


  public:
    //
    // Constructor:
    //
    ShadowedOutputNode(NodeDefinition *nd, Network *net, int instnc):
			DrivenNode(nd,net,instnc) {}

    //
    // Destructor:
    //
    ~ShadowedOutputNode(){}


    //
    // Set the output value of ShadowedOutputNode.  This is the same as for
    // the super class methodd, except that it updates the shadowing inputs 
    //
    Type setOutputValue(int index, const char *value,
				    Type t = DXType::UndefinedType,
				    boolean send = TRUE);
    //
    // Determine if this node is a node of the given class
    //
    virtual boolean isA(Symbol classname);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassShadowedOutputNode;
    }
};


#endif // _ShadowedOutputNode_h

