///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/Node.h,v 1.1 1999/03/31 22:33:20 gda Exp $
 *
 */

//////////////////////////////////////////////////////////////////////////////


#ifndef _Node_h
#define _Node_h

#include <stdio.h> 
#include <Xm/Xm.h> 

#include "UIConfig.h"
#include "defines.h"
#include "enums.h"
#include "Base.h"
#include "List.h"
#include "SymbolManager.h"
#include "DXPacketIF.h"
#include "NodeDefinition.h" 
#include "DXType.h"
#include "SIAllocatorDictionary.h"
#include "CDBAllocatorDictionary.h"
#include "Cacheability.h"
#if WORKSPACE_PAGES
#include "GroupedObject.h"
#endif

//
// Class name definition:
//
#define ClassNode	"Node"

//
// Referenced classes:
//
class Arc;
class List;
class NodeDefinition;
class DXPacketIF;
class DXWindow;
class Parameter;
class Network;
class StandIn;
class ConfigurationDialog;

#if WORKSPACE_PAGES
class GroupRecord;
class GroupManager;
#endif

typedef long NodeStatusChange;		// For the enums below
typedef long NodeParameterStatusChange; // For the enums below

#define FOR_EACH_NODE_INPUT(node, param, iterator) \
for (iterator.setList(node->inputParameters) ; \
     param = (Parameter*)iterator.getNext() ; )

#define FOR_EACH_NODE_OUTPUT(node, param, iterator) \
for (iterator.setList(node->outputParameters) ; \
     param = (Parameter*)iterator.getNext() ; )

//
// Node class definition:
//				
#if WORKSPACE_PAGES
class Node : public Base, public GroupedObject
#else
class Node : public Base 
#endif
{
    //friend StandIn::setNodePosition(Node *n, int x,int y);		
    friend StandIn;	// FIXME: use the above

  private:
    //
    // Private member data:
    //

    //
    // Used only be the Network for sorting, graph analysis, etc.
    // See isMarked(), setMarked() and clearMarked().
    //
    boolean	marked;

    //
    // This dispatches messages to this->execModuleMessageHandler().
    // Messages are not noticed unless this handler is installed
    // (in this->updateModuleMessageProtocol() via this->netPrintNode()).
    //
    static void ExecModuleMessageHandler(void *clientData, int id, void *line);

    // Should the executive cache the module's state. 
    Cacheability	nodeCacheability;

    // The symbol for the node label (contained in theSymbolTable).
    Symbol		labelSymbol;
   
    // The instance number, allocated from the definition. 
    int			instanceNumber;

#if WORKSPACE_PAGES
#else
    // The Group name. 
    Symbol		groupNameSymbol;
#endif
   
    // The network this node belongs to 
    Network *network;

    // Pointer into a table of definitions generated by the MDF file
    NodeDefinition	*definition;

    // Current values and definitions for inputs and outputs
    List		inputParameters;
    List		outputParameters;

    // Pointer to the UI standin for this node.
    StandIn		*standin;

    // Pointer to the UI standin for this node.
    ConfigurationDialog *cdb;	// CD box

    // Upper left-hand corner of standin for this module.
    int			vpe_xpos, vpe_ypos;

    //
    // Let the Configuration dialog box know that the parameter has changed.
    // Assumes that the node currently has a cdb.
    //
    void notifyCDBParameterChanged(Parameter *p, int index);

    //
    // Set the index'th parameter value of the parameter list given by io
    // to the given value  of type t.  if t==DXType::UndefinedType, then
    // be sure it can be assigned to one of the allowed types in the
    // ParameterDefinition.  If 'value' is NULL, then clear the value (and 
    // handle as a successful setting) and return the default type for the 
    // given parameter.
    // We you the Parameter methods to try and help certain values become
    // the given type (i.e. by adding "'s, {}'s, []'s and so on).
    // If send is true (the default), the results will be sent to the server
    // if possible.
    // If notify is TRUE, then call ioParameterStatusChanged() with one of
    // Node::ParameterSetValueChanged and Node::ParameterValueChanged.
    // index is 1 based.
    //
    Type setIOValue(List *io, int index, const char *value, 
					Type t = DXType::UndefinedType,
					boolean send = TRUE,
					boolean notify = TRUE);

    // This is the same as setIOValue, but it sends the value to the
    // executive without causing an executive execution in execute on change.
    Type setIOValueQuietly(List *io, int index, const char *value, 
					Type t = DXType::UndefinedType);
    //
    //  Mark the given parameter as clean.
    //
    void setIODirty(List *io, int index, boolean dirty);

#if WORKSPACE_PAGES
#else
    //
    // Parse the process group info.
    //
    boolean netParsePgrpComment(const char* comment,
                		const char* filename, int lineno);
#endif

    //
    // Determine if the index'th parameter in the give list is connected 
    // (i.e. has an arc) to another parameter. 
    //
    boolean isIOConnected(List *io, int index);

    //
    // Get the default value of the index'th parameter in the given list. 
    //
    const char *getIODefaultValueString(List *io, int index);

    //
    // Set/Get the cacheability of the index'th parameter in the given list. 
    //
    Cacheability getIOCacheability(List *io, int index);
    virtual void setIOCacheability(List *io, int index, Cacheability c);
    boolean isIOCacheabilityWriteable(List *io, int index);

    //
    // Get the currently set value of the index'th parameter in the given 
    // list.  Ignores the defaulting stuff.
    //
    const char *getIOSetValueString(List *io, int index);
    //
    // Get the default value of the index'th parameter in the given list. 
    //
    boolean     isIODefaulting(List *io, int index);
    //
    // Determine if the value of the index'th parameter in the given list
    // has been set, independent of whether it's defaulting or not.
    //
    boolean     isIOSet(List *io, int index);
    //
    // Get the value of the index'th parameter in the given list. 
    //
    const char *getIOValueString(List *io, int index);
    //
    // Get the type of the set value of the index'th parameter in the list. 
    //
    Type getIOSetValueType(List *io, int index);

    //
    // Get the name of the input as specified in the network
    // (i.e. main_Display_1_in_3)
    //
    char *getNetworkIONameString(int index, 
					boolean input, char *buffer);

    //
    // Get the name of the index'th parameter in the given list. 
    // If buf is provided, then the name is placed there, otherwise a
    // new string is created for the return value which must be deleted
    // by the caller.
    //
    char *getIONameString(List *io, int index, char *buf = NULL);
    //
    // Get the description of the index'th parameter in the given list. 
    //
    const char *getIODescription(List *io, int index);

    //
    // Return a readonly list of strings that represent the types for 
    // the given parameter.
    //
    const char* const *getIOTypeStrings(List *io, int index);

    //
    // Return a readonly list of types for the given parameter.
    // The List is readonly and must not be deleted by the caller.
    //
    List *getIOTypes(List *io, int index);

    //
    // Return a readonly list of Arcs for the given parameter. 
    //
    const List *getIOArcs(List *io, int index);

    //
    // Determine if the index'th parameter from the given list has visible tab. 
    //
    boolean	isIOVisible(List *io, int index);

    //
    // Set the index'th parameter from the given list to be visible.
    //
    void	setIOVisibility(List *io, int index, boolean v);

    //
    // Set all unconnected, defaulting params to be either visible or not.
    //
    void	setAllIOVisibility(List *io, boolean v);

    //
    // Determine if the index'th parameter from the given list is viewable 
    //
    boolean	isIOViewable(List *io, int index);

    //
    // Print 'name = value'  for the index'th parameter in the given list.
    //
    char *ioValueString(List *io, int index, const char *prefix); 

    //
    // Determine if the index'th parameter in the given list is required. 
    //
    boolean	isIORequired(List *io, int index);

    //
    // Determine if the given parameter list contains parameters which
    // can be exposed, implying that there are some that are hidden. 
    //
    boolean hasExposableIO(List *io);
    //
    // Determine if the given parameter list contains parameters which
    // can be hidden, implying that there are some that are exposed. 
    //
    boolean hasHideableIO(List *io);

  protected:
    //
    // Protected member data:
    //

    //
    // Used as a unique identifier for this instance of this Node when  
    // installing the Module message handler.
    //
    char	*moduleMessageId;

    void setInstanceNumber(int inst) { instanceNumber = inst; }
    boolean appendInput(Parameter *p) 
		{ return inputParameters.appendElement((const void*)p); }
    boolean appendOutput(Parameter *p) 
		{ return outputParameters.appendElement((const void*)p); }

    //
    // Add an Arc to the index'th parameter of parameter list 'io'.
    //
    virtual boolean addIOArc(List *io, int index, Arc *a); 
    virtual boolean removeIOArc(List *io, int index, Arc *a);

    boolean removeInputArc(int index, Arc *a)
		{ return this->removeIOArc(&this->inputParameters, index, a); }
    boolean removeOutputArc(int index, Arc *a)
		{ return this->removeIOArc(&this->outputParameters, index, a); }


    //
    // Add/remove a set of repeatable input or output parameters to the
    // this node.   An error  ocurrs if the parameter list indicated does
    // not have repeatable parameters.
    //
    virtual boolean addRepeats(boolean input);
    virtual boolean removeRepeats(boolean input);

    Parameter *getInputParameter(int i)
    {
	return (Parameter*)inputParameters.getElement(i);
    }
    Parameter *getOutputParameter(int i)
    {
	return (Parameter*)outputParameters.getElement(i);
    }

    virtual int strcatParameterNameLvalue(char *s,  Parameter *p, 
				const char *prefix, int index);
    int strcatParameterValueString(char *s,  Parameter *p, int index);

    //
    // Parse either on input or an output comment, setting the value of
    // the indicated parameter with the value and type found in the comment.
    // (Made virtual 9/95 in order to peek at comments inside SelectionNode.)
    //
    virtual boolean parseIOComment(boolean input, const char* comment,
                const char* filename, int lineno, boolean valueOnly = FALSE);

    //
    // These are called when a 'node' comment is found in the .net.
    //
    boolean	netParseNodeComment(const char* comment, 
						const char *file, int lineno);
    //
    // These are called to parse any comments after the 'node', 'input',
    // 'output' and 'pgrp'  comments in the .net file.
    //
    virtual boolean	netParseAuxComment(const char* comment, 
						const char *file, int lineno);
    //
    // Create the invocation of the script language Node call. 
    // The string that is returned should be deleted by the caller.
    //
    virtual char        *netNodeString(const char *prefix);

    //
    // Create the invocation of any script language that is
    // to occur at the beginning or end of the containing macro.
    // The string that is returned should be deleted by the caller.
    //
    virtual char        *netBeginningOfMacroNodeString(const char *prefix);
    virtual char        *netEndOfMacroNodeString(const char *prefix);

    //
    //  Put a parameter name/value ('name = value;') pair into a string if
    //  the parameter is a value.  They may return NULL if no strings are
    //  to be printed.
    //  The strings returned should be deleted by the caller.
    //
    virtual char	*inputValueString(int i, const char *prefix)
	{ return ioValueString(&this->inputParameters,i,prefix); }
    virtual char	*outputValueString(int i, const char *prefix)
	{ return ioValueString(&this->outputParameters,i,prefix); }
    virtual char	*valuesString(const char *prefix);

    //
    // Set the index'th i/o parameter to use either the default value 
    // or the assigned valued. if notify is TRUE then call 
    // ioParameterStatusChanged() with Node::ParameterSetValueToDefaulting.
    // If there is a connection to the executive, then send the change.
    //
    void setIODefaultingStatus(int index,
				       boolean input,
				       boolean defaulting,
				       boolean send = TRUE,
				       boolean notify = TRUE);

    //
    // Notify anybody that needs to know that a parameter has changed its
    // value or arcs.
    //
#if 0
    virtual void ioParameterValueChanged(boolean input, int index);
    virtual void ioParameterArcChanged(boolean input, int index,boolean added);

    void	inputParameterValueChanged(int index)
			{ this->ioParameterValueChanged(TRUE, index); }
    void	outputParameterValueChanged(int index)
			{ this->ioParameterValueChanged(FALSE, index); }
    void	inputParameterArcAdded(int index)
			{ this->ioParameterArcChanged(TRUE, index, ); }
    void	inputParameterArcRemoved(int index)
			{ this->ioParameterArcChanged(TRUE, index, FALSE); }
    void	outputParameterArcAdded(int index)
			{ this->ioParameterArcChanged(FALSE, index, TRUE); }
    void	outputParameterArcRemoved(int index)
			{ this->ioParameterArcChanged(FALSE, index, FALSE); }
#endif
    virtual void ioParameterStatusChanged(boolean input, int index, 
				NodeParameterStatusChange status);
    // notifyIo is the same as io sort of.  notifyIo adds a check to see
    // if the network is in the process of going away.  That avoids useless work.
    void notifyIoParameterStatusChanged(boolean input, int index, 
				NodeParameterStatusChange status); 

    //
    // Used by netPrintNode() to print the Names of it's input and output 
    // parameters.  In the case of inputs, if the input is taking output
    // from another source (i.e it has an arc), then we print the name
    // of that output instead.
    //
    virtual char        *inputParameterNamesString(const char *varprefix,
						const char *indent = NULL);
    virtual char        *outputParameterNamesString(const char *prefix);

    //
    // Print the comment section that precedes the Node invocation. 
    //
    boolean     	netPrintCommentHeader(FILE *f);
    virtual boolean     printIOComment(FILE *f, boolean input, int index, 
					const char *indent = NULL,
					boolean valueOnly = FALSE);
    boolean     	netPrintPgrpComment(FILE *f);
    virtual boolean     netPrintAuxComment(FILE *f);


    //
    // Called when a message is received from the executive after
    // this->ExecModuleMessageHandler() is registered in 
    // this->Node::netPrintNode() to receive messages for this node.  
    // The format of the message coming back is defined by the derived class.
    //
    virtual void execModuleMessageHandler(int id, const char *line);

    //
    // Update the state of message handling for a module/UI message.
    // This is called only when we send a Node's module call to the executive
    // and the node has a module messaging protocol as defined by
    // this->hasModuleMessageProtocol().
    //
    virtual void updateModuleMessageProtocol(DXPacketIF *pif);

    //
    // Return TRUE/FALSE, indicating whether or not we support a message 
    // protocol between the executive module that runs for this node and the
    // UI.  By default Nodes do not have message protocols.
    //
    virtual boolean hasModuleMessageProtocol();

    //
    // Return TRUE/FALSE, indicating whether or not we expect to receive
    // a message from the UI when our module executes in the executive.
    // Be default Nodes do not expect messages.
    //
    virtual boolean expectingModuleMessage();

    //
    // Returns a string that is used to register 
    // this->ExecModuleMessageHandler() when this->hasModuleMessageProtocol() 
    // return TRUE.  This version, returns an id that is unique to this 
    // instance of this node.
    //
    // IMPORTANT: this must set this->moduleMessageId so that Node::~Node()
    //		can know the id string. 
    //
    virtual const char *getModuleMessageIdString();

    //
    // Do any work that must be done before sending the macro/network
    // that this node belongs to to the server.
    // Be default, Nodes do not have any work that needs to be done 
    // before sending.
    //
    virtual void prepareToSendNode();

    //
    // Do any work that must be done before sending the given parameter value 
    // to the server. 
    // Be default, Nodes do not have any work that needs to be done 
    // before sending parameter values.
    //
    virtual void prepareToSendValue(int index, Parameter *p);

    //
    // See if the given string is a viable label to be used as an identifier.
    // Also make sure it is not a reserved script language word.
    // Return TRUE if ok, FALSE otherwise and issue and error message.
    //
    boolean verifyRestrictedLabel(const char *label);

    //
    // Print/parse the 'node %s[%d]:' comment.
    // Not all nodes have cfg info, but it is provided for those that do. 
    //
    boolean cfgPrintNodeLeader(FILE *f);
    boolean cfgParseNodeLeader(const char *comment, 
                                const char *file, int lineno);


  public:
    //
    // Constructor:
    // Node that a node should ONLY be allocated by its definition!
    //
    Node(NodeDefinition *nd, Network *net, int inst);

    //
    // Destructor:
    //
    ~Node(); 

     //
     // The following are used to give notification of Node's change in
     // status.  Currently, notification is done through the Node's network. 
     // Node selection notification is handled by the StandIn for the node.
     //
     enum {	// NodeStatusChange
                NodeSelected   = 1,     // Node was just selected.
                NodeDeselected = 2      // Node was just unselected.
     };


     //
     // The following are used to give notification of Node's parameter 
     // change in status and is an argument to ioParameterStatusChanged.  
     //
#define PARAMETER_VALUE_CHANGED		0x100000
#define PARAMETER_VISIBILITY_CHANGED	0x200000
#define PARAMETER_ARC_CHANGED		0x400000
     enum {	// NodeParameterStatusChange
        ParameterValueChanged	      = PARAMETER_VALUE_CHANGED,
        ParameterSetValueChanged      = 0x000001 | PARAMETER_VALUE_CHANGED,
        ParameterSetValueToDefaulting = 0x000002 | PARAMETER_VALUE_CHANGED,
	ParameterVisibilityChanged    = PARAMETER_VISIBILITY_CHANGED,
	ParameterBecomesVisible       = 0x000003 | PARAMETER_VISIBILITY_CHANGED,
	ParameterBecomesInvisible     = 0x000004 | PARAMETER_VISIBILITY_CHANGED,
	ParameterArcChanged	      = PARAMETER_ARC_CHANGED,
	ParameterArcRemoved	      = 0x000008 | PARAMETER_ARC_CHANGED,
	ParameterArcAdded	      = 0x000010 | PARAMETER_ARC_CHANGED
     };


    
    //
    // Generate a new instance number for this node.  We notify the
    // standIn and mark the network and the node dirty.
    // The new instance number is returned.
    //
    virtual int assignNewInstanceNumber();

    //
    // Used by ONLY Network for sorting and graph analysis.
    //
    boolean	isMarked()	{ return this->marked; }
    void	setMarked()	{ this->marked = TRUE; }
    void	clearMarked()	{ this->marked = FALSE; }


    // FIXME: these should not be public. They are called by the newNode
    // function of the NodeDefinition class.
    virtual void setDefinition(NodeDefinition *nd);
    virtual void updateDefinition();
    //
    // Build a Node's input and output parameter lists based on this
    // node definition.
    //
    boolean buildParameterLists();


    //
    // Perform any additional initializations that were not performed
    // in the constrctor.  If this returns TRUE initialization was 
    // successful, otherwise FALSE.  If FALSE, then it is assumed that
    // initialize() will issue the error/warning message. 
    // initialize() is called before the Node is actually added to the
    // Network.
    //
    virtual boolean initialize();

    //
    // initializeAfterNodeMember() is called after initialize() but after the 
    // Node is actually added to the Network.
    //
    virtual void initializeAfterNetworkMember() {}


    // Get the name of this module
    virtual Symbol getNameSymbol() 
		{ return this->definition->getNameSymbol(); } 
    const char *getNameString() 
		//{ return (const char *) this->definition->getNameString(); } 
		{ return theSymbolManager->getSymbolString(
						this->getNameSymbol()); } 
    virtual const char *getExecModuleNameString() 
		{ return this->definition->getExecModuleNameString(); } 
    const char *getDescription()
		{ return this->definition->getDescription(); }
    NodeDefinition *getDefinition() { return this->definition; }


    // Get the label of this module. 
    virtual boolean setLabelString(const char *label);
    virtual const char *getLabelString();

    int     getInputCount() { return inputParameters.getSize(); }
    int     getOutputCount() { return outputParameters.getSize(); }
    void setVpePosition(int x, int y); 


#if WORKSPACE_PAGES
#else
    //
    // Process group calls.
    //
    virtual void setGroupName(const char* name);
    const char *getGroupName();
    void addToGroup(const char *group);
#endif

    //
    // Add/remove a set of input our output parameters to the give model.
    //
    boolean addInputRepeats()    { return addRepeats(TRUE); }
    boolean removeInputRepeats() { return removeRepeats(TRUE); }
    boolean addOutputRepeats()    { return addRepeats(FALSE); }
    boolean removeOutputRepeats() { return removeRepeats(FALSE); }


    boolean hasExposableInput()
		{ return this->hasExposableIO(&this->inputParameters); }
    boolean hasExposableOutput()
		{ return this->hasExposableIO(&this->outputParameters); }
    boolean hasHideableInput()
		{ return this->hasHideableIO(&this->inputParameters); }
    boolean hasHideableOutput()
		{ return this->hasHideableIO(&this->outputParameters); }

    boolean hasRemoveableInput();
    boolean hasRemoveableOutput();
    boolean isInputRepeatable();
    boolean isOutputRepeatable();
    int	    getInputRepeatCount() { return this->definition->getInputRepeatCount(); } 
    int	    getOutputRepeatCount() { return this->definition->getOutputRepeatCount(); } 

    //
    // Get the network this node belongs to. 
    //
    Network *getNetwork() { return network; }


    //
    // Manage inputs. 
    //
    boolean addInputArc(Arc *a, int index)
        { return addIOArc(&inputParameters, index, a); }
    boolean addOutputArc(Arc *a, int index)
        { return addIOArc(&outputParameters, index, a); }

    const List *getInputArcs(int index)
        { return getIOArcs(&inputParameters, index); }
    const List *getOutputArcs(int index)
        { return getIOArcs(&outputParameters, index); }
    
    virtual boolean deleteArc(Arc *a);

    // If these get virtualized, you must replace p->getValue() with 
    // this->getInputValueString(i) in Node.C 
    const char *getInputValueString(int index)
        { return getIOValueString(&inputParameters, index); }
    const char *getOutputValueString(int index)
        { return getIOValueString(&outputParameters, index); }
    Type getInputSetValueType(int index)
        { return getIOSetValueType(&inputParameters, index); }
    Type getOutputSetValueType(int index)
        { return getIOSetValueType(&outputParameters, index); }

    //
    // If buf is provided, then the name is placed there, otherwise a
    // new string is created for the return value which must be deleted
    // by the caller.
    //
    char *getInputNameString(int index, char *buf = NULL)
        { return getIONameString(&inputParameters, index, buf); }
    char *getOutputNameString(int index, char *buf = NULL)
        { return getIONameString(&outputParameters, index, buf); }

    //
    // Get the name of the input as specified in the network
    // (i.e. main_Display_1_in_3)
    // If buf is not provided the returned string must be deleted
    // by the caller.
    //
    char *getNetworkInputNameString(int index, char *buf = NULL)
        { return getNetworkIONameString(index, TRUE, buf); }
    char *getNetworkOutputNameString(int index, char *buf = NULL)
        { return getNetworkIONameString(index, FALSE, buf); }

    const char* const *getInputTypeStrings(int index)
        { return getIOTypeStrings(&inputParameters, index); }
    const char* const *getOutputTypeStrings(int index)
        { return getIOTypeStrings(&outputParameters, index); }

    // The List is readonly and must not be deleted by the caller.
    List* getInputTypes(int index)
        { return getIOTypes(&inputParameters, index); }
    List* getOutputTypes(int index)
        { return getIOTypes(&outputParameters, index); }

    const char *getInputDescription(int index)
        { return getIODescription(&this->inputParameters, index); }
    const char *getOutputDescription(int index)
        { return getIODescription(&this->outputParameters, index); }

    const char *getInputDefaultValueString(int index)
        { return getIODefaultValueString(&inputParameters, index); }

    const char *getInputSetValueString(int index)
        { return getIOSetValueString(&inputParameters, index); }

    boolean isInputRequired(int index)
        { return isIORequired(&inputParameters, index); }
    boolean isOutputRequired(int index)
        { return isIORequired(&outputParameters, index); }

    boolean isInputConnected(int index)
        { return isIOConnected(&inputParameters, index); }
    boolean isOutputConnected(int index)
        { return isIOConnected(&outputParameters, index); }
    boolean isParameterConnected(int index, boolean input)
        { return (input ? isIOConnected(&inputParameters, index) 
                        : isIOConnected(&outputParameters, index)); }

    void setInputVisibility(int index, boolean v)
        { this->setIOVisibility(&inputParameters, index, v); }
    void setOutputVisibility(int index, boolean v)
        { this->setIOVisibility(&outputParameters, index, v); }

    void setAllInputsVisibility(boolean v)
        { this->setAllIOVisibility(&inputParameters, v); }
    void setAllOutputsVisibility(boolean v)
        { this->setAllIOVisibility(&outputParameters, v); }

    void clearInputDirty(int index)
        { this->setIODirty(&inputParameters, index, FALSE); }
    void setInputDirty(int index)
        { this->setIODirty(&inputParameters, index, TRUE); }
    void clearOutputDirty(int index)
        { this->setIODirty(&outputParameters, index, FALSE); }
    void setOutputDirty(int index)
        { this->setIODirty(&outputParameters, index, TRUE); }

    boolean isInputVisible(int index)
        { return isIOVisible(&inputParameters, index); }
    boolean isOutputVisible(int index)
        { return isIOVisible(&outputParameters, index); }
    boolean isParameterVisible(int index, boolean input)
	{ return (input ? isInputVisible(index) : isOutputVisible(index)); }

    boolean isInputViewable(int index)
        { return isIOViewable(&inputParameters, index); }
    boolean isOutputViewable(int index)
        { return isIOViewable(&outputParameters, index); }
    boolean isParameterViewable(int index, boolean input)
	{ return (input ? isInputViewable(index) : isOutputViewable(index)); }

    Cacheability getOutputCacheability(int index)
	{ return this->getIOCacheability(&outputParameters, index); }
    void setOutputCacheability(int index, Cacheability c)
	{ this->setIOCacheability(&outputParameters, index, c); }
    boolean isOutputCacheabilityWriteable(int index)
	{ return this->isIOCacheabilityWriteable(&outputParameters, index); }

    boolean isInputDefaulting(int index)
        { return isIODefaulting(&inputParameters, index); }

    boolean isInputSet(int index)
        { return isIOSet(&inputParameters, index); }

    boolean hasWriteableCacheability()	
		{ return this->definition->hasWriteableCacheability(); }
    Cacheability getNodeCacheability() { return this->nodeCacheability; }
    void setNodeCacheability(Cacheability val);

    boolean isParameterDefaulting(int index, int input)
        { return (input ? isIODefaulting(&inputParameters, index) 
                        : False); }

    //
    // Match output_index of this node to input_index of n.  Returns TRUE
    // if they can connect.
    //
    virtual boolean typeMatchOutputToInput(
	int output_index,
	Node *n,
	int input_index);

    //
    // Set the stored value.
    // If the parameter is not defaulting, this is
    // the same as setValue, but if it is defaulting, then we set the
    // value but leave the parameter clean and defaulting and ignore send.
    //
    virtual Type setInputSetValue(int index, const char *value, 
				 Type type = DXType::UndefinedType,
				 boolean send = TRUE);

    virtual Type setInputValue(int index,
			       const char *value,
			       Type t = DXType::UndefinedType,
			       boolean send = TRUE)
        { return setIOValue(&inputParameters, index, value, t, send); }
    virtual Type setOutputValue(int index,
				const char *value,
				Type t = DXType::UndefinedType,
				boolean send = TRUE)
        { return setIOValue(&outputParameters, index, value, t, send); }

    // These are the same as setInputValue and setOutputValue, but they send
    // the value to the executive without causing an executive execution in 
    // execute on change.
    virtual Type setInputValueQuietly(int index,
			       const char *value,
			       Type t = DXType::UndefinedType)
        { return setIOValueQuietly(&inputParameters, index, value, t); }
    virtual Type setOutputValueQuietly(int index,
				const char *value,
				Type t = DXType::UndefinedType)
        { return setIOValueQuietly(&outputParameters, index, value, t); }

    virtual Type clearOutputValue(int index,
				  boolean send = TRUE)
        { return setIOValue(&outputParameters, 
			    index, 
			    NULL, 
			    DXType::UndefinedType, 
			    send); }

    //
    // Get this node's instance number (allocated from the definition). 
    //
    int getInstanceNumber() { return instanceNumber; }

    //
    // Get the x,y positions for the VPE
    //
    void getVpePosition(int *x, int *y);
    // FIXME: these should be removed as soon as StandIn.C uses getVpePosition()
    int getVpeX() { return this->vpe_xpos; }
    int getVpeY() { return this->vpe_ypos; }

    //
    // Parse routines for a node, called by a Network. 
    // These are called for the comments found in the .net and .cfg files
    // respectively. 
    //
    virtual boolean	netParseComment(const char* comment, 
						const char *file, int lineno);
    virtual boolean	cfgParseComment(const char* comment, 
						const char *file, int lineno);

    //
    // Print the stuff that belong in a .cfg file
    // At this level, there is nothing.
    //
    virtual boolean     cfgPrintNode(FILE *f, PrintType destination); 

    //
    // Print the invocation of the script language Node call. 
    // LETS TALK IF YOU WANT TO MAKE THIS VIRTUAL (can you use netNodeString()).
    //
    boolean     netPrintNode(FILE *f, 
			  PrintType destination, 
			  const char *prefix,
			  PacketIFCallback callback = NUL(PacketIFCallback),
			  void *clientdata = NUL(void*));

    //
    // Print the invocation of any script language that is
    // to occur at the beginning of the containing macro.
    //
    boolean	netPrintBeginningOfMacroNode(FILE *f, 
			  PrintType destination, 
			  const char *prefix,
			  PacketIFCallback callback = NUL(PacketIFCallback),
			  void *clientdata = NUL(void*));

    //
    // Print the invocation of any script language that is
    // to occur at the end of the containing macro.
    //
    boolean	netPrintEndOfMacroNode(FILE *f, 
			  PrintType destination, 
			  const char *prefix,
			  PacketIFCallback callback = NUL(PacketIFCallback),
			  void *clientdata = NUL(void*));

    //
    // Save any other files that relevant to this mode 
    // The name passed in is file name used to save the network (without the
    // .net extension). 
    //
    virtual boolean 	auxPrintNodeFile();
    
    //
    //  Print parameter name/value ('name,name = value,value;') pairs.
    //
    virtual boolean	printValues(FILE *f, const char *prefix);
    //
    // For inputs, outputs or both sets of parameters send the values
    // for of which do not have arcs. 
    //  
    virtual boolean     sendValues(boolean     ignoreDirty = TRUE);

    //
    // Send all dirty input and output values to the executive in the
    // quiet way using the Executive("assign noexecute",...); call.
    //
    void sendValuesQuietly();


    //
    // Manipulate the standin for this node.
    //
    StandIn *newStandIn(WorkSpace *w) 
		{ this->standin = theSIAllocatorDictionary->allocate(
					this->getNameSymbol(),w,this);
		  return this->standin; }
    StandIn *getStandIn() { return this->standin; }

    //
    // Manipulate the configration dialog box for this node.
    //
    ConfigurationDialog *newConfigurationDialog(Widget w) 
		{
		    if (this->cdb == NULL)
			this->cdb = theCDBAllocatorDictionary->allocate(
					    this->getNameSymbol(),
					    w,this);
		    return this->cdb;
		}
    ConfigurationDialog *getConfigurationDialog() { return this->cdb; }

    //
    // Perform the default function that is associated with the 
    // StandIn's default event.
    //
    virtual void openDefaultWindow(Widget parent);

    //
    // Let the caller of openDefaultWindow() know what kind of window she's getting.
    // This is intended for use in EditorWindow so that we can sanity check the number
    // of cdbs were going to open before kicking off the operation and so that we
    // don't question the user before opening large numbers of interactors.
    // A name describing the type of window can be written into window_name in order
    // to enable nicer warning messages.
    //
    virtual boolean defaultWindowIsCDB(char* window_name = NULL)
	{ if (window_name) strcpy (window_name, "Configuration Dialog"); return TRUE; }

    //
    //  Open this node's configuration dialog box.
    //
    virtual void openConfigurationDialog(Widget parent);

    //
    //  Display help for this node in a window. 
    //
    virtual void openHelpWindow(Widget parent);

    //
    // Returns FALSE for most nodes and is overridden by InteractorNode and
    // MacroNode.
    //
    virtual boolean isAllowedInMacro()
    {
	return this->definition->isAllowedInMacro();
    }

    //
    // Manipulate whether the default value or assigned value is used 
    // as the value for i/o parameter i.  Parameters are indexed from 1.
    //
    void 	useDefaultInputValue(int index, boolean send = TRUE) 
			{this->setIODefaultingStatus(index,TRUE,TRUE,send);}
    void 	useAssignedInputValue(int index, boolean send = TRUE) 
			{this->setIODefaultingStatus(index,TRUE,FALSE,send);}
    void 	useDefaultOutputValue(int index, boolean send = TRUE) 
			{this->setIODefaultingStatus(index,FALSE,TRUE,send);}
    void 	useAssignedOutputValue(int index, boolean send = TRUE) 
			{this->setIODefaultingStatus(index,FALSE,FALSE,send);}

    //
    // Determine if this node is a node of the given class
    //
    boolean isA(const char *classname);
    virtual boolean isA(Symbol classname);

    //
    // Reset the node to using the default cfg state (probably before reading
    // in a new cfg file).  In general, the only state that should be reset
    // here is state that is saved in .cfg files.
    //
    virtual void setDefaultCfgState();

    //
    // Return TRUE if this node has state that will be saved in a .cfg file.
    // At this level, nodes do not have cfg state.
    //
    virtual boolean hasCfgState();

    //
    // Disconnect all input and output arcs from this node.
    //
    boolean disconnectArcs();

    //
    // Return TRUE if the node can be switched (pasted/merged/moved) from 
    // the 'from' net to the 'to' net.
    //
    virtual boolean canSwitchNetwork(Network *from, Network *to);

    //
    // Switch the node's net from 'from' to 'to'
    //
    virtual void switchNetwork(Network *from, Network *to);

    //
    // Get the selectable values for the n'th input.
    // This returns a pointer to a constant array of pointers to
    // constant strings which is NOT to be manipulated by the caller.
    // The returned array of pointers is NULL terminated.
    //
    const char * const *getInputValueOptions(int index);
    
    //
    // Return the window associated with this node (if one exists)
    virtual DXWindow *getDXWindow() {return NULL;}

     //
     // get the node title (if the node has a title)
     //
    virtual const char        *getTitle() {return NULL;}

#ifdef DXUI_DEVKIT
    //
    // Routines to print the module as DX C code.
    //
    boolean beginDXCallModule(FILE *f);
    boolean callDXCallModule(FILE *f);
    boolean endDXCallModule(FILE *f);
#endif // DXUI_DEVKIT

    //
    // Provide a mechanism on behalf of StandIn for getting a small piece of text
    // for postscript output.  This text will be associated with the standin.  I
    // chose to stick this into Node rather than virtualizing the postscript
    // print func which would be the normal C++ way to handle this.  It's just that
    // postscript printing is so complicated and so few people want to learn it that
    // the benefit of making it virtual seems small.   I originally put this here
    // on behalf of Compute so that there is a way to print the expression.
    // ComputeNode will supply its expression as extra PS text.
    //
    virtual const char* getExtraPSText() { return NUL(char*); }


    //
    // I changed Network::nodeList from List to NodeList in order to provide
    // a faster lookup.  (Parsing ReceiverNodes is very slow because they
    // scan the entire network for a matching TransmitterNode.)  Some nodes
    // need special handling:  Transmitter,Receiver,Display,Image,UniqueNameNode
    // because they're frequently looked up.
    //
    virtual boolean needsFastSort() { return FALSE; }

    virtual boolean printAsJava(FILE* );
    virtual const char* getJavaNodeName() { return "Node"; }
    virtual boolean hasJavaRepresentation() { return FALSE; }
    virtual boolean printInputAsJava(int input) { return FALSE; }
    virtual const char *getJavaInputValueString(int index)
        { return getInputValueString(index); }


    //
    // Java Beans
    //
    virtual boolean printAsBean(FILE*) { return TRUE; }
    virtual boolean printAsBeanInitCall(FILE*) { return TRUE; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassNode; }
};


#endif // _Node_h
