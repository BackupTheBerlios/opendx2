using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.Diagnostics;

namespace WinDX.UI
{
    /// <summary>
    /// Definition for the InteractorNode class.				 
    ///
    /// The InteractorNode is represented by the StandIn that is visible in the
    /// Editor work space.  Each InteractorNode has a family of 
    /// InteractorInstance/Interactor pairs.  This family is of unlimited size,
    /// and different pairs can reside in different control panels.
    /// The InteractorNode maintains a list of InteractorInstances (which in turn
    /// reference their associated Interactor).
    /// 
    /// We redefine this->openDefaultWindow() to (by default) open the control
    /// panel that the InteractorInstance(s) are contained in.  If you want
    /// a different action for you derived class, redefine this.
    /// 
    /// We also implement this->reflectStateChange()
    /// which calls InteractorInstance::handleInteractorStateChange() on each of
    /// the InteractorInstances in the list of associated instances.  
    /// 
    /// this->newInteractorInstance() and this->addInstance() are used during
    /// .cfg file parsing to allocate a new InteractorInstance for (what is
    /// usually) a derived class and add the instance to this->instanceList.
    /// Redefine newInteractorInstance() if you need other than an
    /// InteractorInstance class instance for your InteractorNode derived
    /// class.
    /// 
    /// Apart from the above we (re)define the standard parsing and printing
    /// methods.  We also define setOutputValues() so that all
    /// InteractorInstances  associated with this InteractorNode have their
    /// displayed value updated by calling
    /// this->setOutputAndOtherInteractorValues().  Typically, an Interactor
    /// will change it's nodes output value which results in all other
    /// Interactors having their displayed value change.
    ///
    /// All InteractorNodes are by default data-driven as defined by 
    /// DrivenNode::isDataDriven().  See the NondrivenInteractorNode sub-class
    /// for interactor nodes that are not data-driven.  A general discussion of
    /// data-driven interactors follows...
    ///
    /// Data-driven interactors are interactors that have inputs and make an 
    /// executive module call and then expect a UImessage from that module 
    /// concerning the state of the Interactor (i.e. mininum, maximum, increment, 
    /// label...).  this->Node::netPrintNode() determines if the InteractorNode is 
    /// data-driven with this->DrivenNode::expectingModuleMessage() via 
    /// this->DrivenNode::isDataDriven() and arranges
    /// for this->execModuleMessageHandler() to be called when a message for
    /// this InteractorNode is found.
    ///
    /// The following inputs are assumed at this level...
    ///      Input 1: Unique Id string identifying the instance of this node.
    ///      Input 2: Field/group input object.
    ///      Input 3: Current output value.
    ///         . . .
    ///      Input N: The label for this interactor (this is the last input).
    ///
    /// Because this class is derived from the ShadowedOutputNode class,
    /// when this->setOutputValue() is called shadowing inputs are updated
    /// to set to the values of any inputs that may be shadowing the given
    /// output.  Input to Output shadowing is defined in the virtual function
    /// this->getShadowingInput().  A one to one mapping of input to output is
    /// assumed in the overall architecture and by default output 1 is shadowed
    /// by input 3 when this->isDataDriven() returns TRUE.
    ///
    /// </summary>
    public abstract class InteractorNode : ShadowedOutputNode
    {
        private String java_variable;

        /// <summary>
        /// Used by getInteractorLabel() so it can return a string.
        /// </summary>
        protected String lastInteractorLabel;

        /// <summary>
        /// numComponents is the value parsed from the .cfg file and may
        /// be interpreted differently depending upon the derived class.
        /// </summary>
        protected int numComponents;

        protected List<InteractorInstance> instanceList = new List<InteractorInstance>();

        protected virtual bool cfgParseInteractorComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgParseInstanceComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgParseLabelComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected virtual bool cfgPrintInteractor(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgPrintInteractorComment(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgPrintInteractorAuxInfo(StreamWriter sw)
        {
            return true;
        }
        protected virtual bool cfgPrintInteractorInstances(StreamWriter sw, PrintType dest)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgPrintInstanceComment(StreamWriter sw, InteractorInstance ii)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgPrintInstanceLabelComment(StreamWriter sw, InteractorInstance ii)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgPrintInstanceAuxInfo(StreamWriter sw, InteractorInstance ii)
        {
            return true;
        }
        
        protected bool appendInstance(InteractorInstance ii)
        {
            instanceList.Add(ii);
            return true;
        }

        /// <summary>
        /// Get a new interactor instance for this class.
        /// Derived classes can override this to allocated subclasses of 
        /// InteractorInstance which may be specific to the derived class.
        /// For example, ScalarNode uses a ScalarInstance instead
        /// of an InteractorInstance which incorporates local modes.
        /// </summary>
        /// <returns></returns>
        protected virtual InteractorInstance newInteractorInstance()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Delete and free an instance from the list of instances.
        /// This may be called by a ControlPanel.
        /// </summary>
        /// <param name="ii"></param>
        /// <returns></returns>
        protected bool deleteInstance(InteractorInstance ii)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Create a new interactor instance (using newInteractorInstance()) 
        /// giving it the given position and style and assigning it to the given 
        /// ContorlPanel, if given.  This includes adding the instance to the 
        /// control panels list of instances.  
        /// Returns the InteractorInstance on success, NULL otherwise.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="intstyle"></param>
        /// <param name="cp"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <returns></returns>

        protected InteractorInstance addInstance(int x, int y, InteractorStyle intstyle)
        { return addInstance(x, y, intstyle, null, 0, 0); }
        protected InteractorInstance addInstance(int x, int y, InteractorStyle intstyle,
            ControlPanel cp) { return addInstance(x, y, intstyle, cp, 0, 0); }
        protected InteractorInstance addInstance(int x, int y, InteractorStyle intstyle,
            ControlPanel cp, int width, int height)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Get the index'th interactor instance for this Interactor.
        /// C++ was indexed starting at 1, this is now 0.
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        protected InteractorInstance getInstance(int index)
        {
            return instanceList[index];
        }

        /// <summary>
        /// Called when a message is received from the executive after
        /// this->ExecModuleMessageHandler() is registered in
        /// this->Node::netPrintNode() to receive messages for this node.
        /// We parse all the common information and then the class specific.
        /// We return the number of items in the message.
        /// </summary>
        /// <param name="line"></param>
        /// <returns></returns>
        protected override int handleNodeMsgInfo(String line)
        {
            int values = 0;

            // Parse the attributes specific to this class
            values += handleInteractorMsgInfo(line);

            // Parse the attributes specific to this class
            values += handleCommonMsgInfo(line);

            return values;
        }

        /// <summary>
        /// Parse the interactor specific info from an executive message.
        /// Returns the number of attributes parsed.
        /// </summary>
        /// <param name="line"></param>
        /// <returns></returns>
        protected abstract int handleInteractorMsgInfo(String line);

        /// <summary>
        /// Parse attributes that are common to all data-driven interactors.
        /// Parses and sets the label from a message string.
        /// Returns the number of recognized message items.
        /// </summary>
        /// <param name="line"></param>
        /// <returns></returns>
        protected int handleCommonMsgInfo(String line)
        {
            int values = 0;

            if (line.Contains("label="))
            {
                Regex regex = new Regex("label=\\s*\"*([^\"]*)\"");
                Match m = regex.Match(line);
                int label_index = getLabelParameterIndex();
                Debug.Assert(label_index > 0);
                saveInteractorLabel(m.Groups[1].Value, true);
                setInputAttributeFromServer(label_index, lastInteractorLabel, DXTypeVals.StringType);
                values++;
            }
            return values;
        }

        /// <summary>
        /// Update all interactor instances that may be based on the state of this
        /// node.   Among other times, this is called after receiving a message
        /// from the executive.
        /// </summary>
        /// <param name="unmanage"></param>
        protected override void reflectStateChange(bool unmanage)
        {
            foreach (InteractorInstance ii in instanceList)
                ii.handleInteractorStateChange(null, unmanage);
        }

        /// <summary>
        /// Define the mapping of inputs that shadow outputs.
        /// By default, all data driven interactors, have a single output that is
        /// shadowed by the third input. 
        /// </summary>
        /// <param name="output_index"></param>
        /// <returns>an input index (greater than 1) or 0 if there is no shadowing input 
        /// for the given output index</returns>
        protected override int getShadowingInput(int output_index)
        {
            int input_index;

            switch (output_index)
            {
                case 1: input_index = 3; break;
                default: input_index = 0; break;
            }
            return input_index;
        }

        /// <summary>
        /// Get the index of the label parameter.
        /// Be default, it is always the last parameter.
        /// </summary>
        /// <returns></returns>
        protected virtual int getLabelParameterIndex()
        {
            return InputCount;
        }

        /// <summary>
        /// Set all shadowing inputs to use the default value.
        /// This is most likely used during initialization after setting the outputs
        /// (which sets the shadowing inputs).
        /// </summary>
        /// <param name="send"></param>
        /// 
        protected void setShadowingInputsDefaulting() { setShadowingInputsDefaulting(false); }
        protected void setShadowingInputsDefaulting(bool send)
        {
            for (int i = 1; i <= OutputCount; i++)
            {
                int input_shadow = getShadowingInput(i);
                if (input_shadow > 0)
                    useDefaultInputValue(input_shadow, send);
            }
        }

        /// <summary>
        /// Notify anybody that needs to know that a parameter has changed its arcs.
        /// At this class level, we just check changes in output arcs that may
        /// change the label associated with the Interactor.  If it may have 
        /// changed the label, then we notify all instances with 
        /// notifyVisualsOfStateChange().
        /// </summary>
        /// <param name="input"></param>
        /// <param name="index"></param>
        /// <param name="status"></param>
        /// 
        protected override void ioParameterStatusChanged(bool input, int index, 
            NodeParameterStatusChange status)
        {
            bool doit = false;

            deferVisualNotification();
            if ((int)(status & NodeParameterStatusChange.ParameterArkChanged) > 0)
            {
                if (input)
                {
                    if (index == getLabelParameterIndex())
                        doit = true;

                    // If we become un data driven, then we must make sure the
                    // outputs get sent on the next execution.

                    if (!IsDataDriven)
                    {
                        for (int i = 1; i <= OutputCount; i++)
                            setOutputDirty(i);
                        // Don't need to send them because the network will get marked
                        // dirty as a result of an arc change.
                    }
                }
                else
                {
                    int narcs = 0;
                    // Count the number of output arcs.
                    for (int i = 1; i <= OutputCount; i++)
                    {
                        List<Ark> arcs = getOutputArks(i);
                        narcs += arcs.Count;
                    }
                    // If the number of arcs has changed in such a way that the label
                    // may have to change then notify the instances to reset their 
                    // labels.
                    // Labels can change if we ADD an arc and change from having...
                    //	a) 0 to having 1 arc
                    //	b) 1 to having 2 arcs 
                    // or we REMOVE an arc and we change from having...
                    //   	a) 1 to having 0 arcs
                    //	b) 2 to having 1 arc 

                    bool added = (status == NodeParameterStatusChange.ParameterArkAdded);
                    if ((narcs <= 1) || (added && narcs == 2))
                        doit = true;
                }
                if (doit)
                    notifyVisualsOfStateChange();
            }
            base.ioParameterStatusChanged(input, index, status);
            undeferVisualNotification();
        }

        /// <summary>
        /// Print the script representation of the call for interactors.
        /// For interactors, there is no executive call, unless we are being
        /// data driven.  The work done here is to determine if we are acting
        /// as a data-driven interactor and then to do the correct action.
        /// If we are not data-driven, return "" since there is no work for
        /// the executive to do for us.
        /// If we are data-driven, then we generate the call to the correct
        /// executive module by calling the superclass' method.
        /// </summary>
        /// <param name="prefix"></param>
        /// <returns></returns>
        protected override string netNodeString(string prefix)
        {
            if (InputCount != 0 && IsDataDriven)
            {
                // Assuming ShadowedOutputNode is the super class for InteractorNode.
                // What we want here is for a call to the node to be made
                // in the executive.
                return base.netNodeString(prefix);
            }
            return "";
        }

        protected bool changeDimensionality(int new_dim)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected virtual bool doDimensionalityChange(int new_dim)
        {
            throw new Exception("Not Yet Implemented");
        }

        public InteractorNode(NodeDefinition nd, Network net, int instnc)
            :
            base(nd, net, instnc)
        {
            numComponents = 1;
            lastInteractorLabel = null;
            java_variable = null;
        }

        /// <summary>
        /// Return a pointer to a string representing the global name that can
        /// be used to label interactors.   This can be superseded by a local label
        /// string maintained in InteractorInstance. 
        /// The algorithm we use is as follows...
        ///  If there are no output arcs  or more than 1 use "Value:" 
        ///	If there is a single output arc, use the name of the destination 
        ///	    node and parameter.
        /// </summary>
        /// <returns></returns>
        public String getOutputDerivedLabel()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual String getInteractorLabel()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Set the global label for all instances of this interactor node.
        /// DrivenInteractors keep their labels in the label parameter.
        /// If strip_quotes is TRUE, then remove leading and trail double quotes
        /// which are expected to be present.
        /// </summary>
        /// <param name="label"></param>
        /// <param name="strip_quotes"></param>
        /// 
        public void saveInteractorLabel(String label) { saveInteractorLabel(label, false); }
        public void saveInteractorLabel(String label, bool strip_quotes)
        {
            if (label == null)
            {
                lastInteractorLabel = null;
                return;
            }

            label = label.Trim();

            if (strip_quotes)
            {
                if (label.StartsWith("\"") && label.EndsWith("\""))
                    label = label.Substring(1, label.Length - 2);
            }
            lastInteractorLabel = label;
        }

        /// <summary>
        /// Get the current type of the given output.
        /// Be default, this is the type of current output value or if no value is
        /// currently set, then the first (and only?) type in the parameters type 
        /// list. If an interactor can have different outputs, that class should
        /// override this.
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        public DXType getTheCurrentOutputType(int index)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override bool netParseComment(string comment, string file, int lineno)
        {
            bool r = base.netParseComment(comment, file, lineno);
            int lindex = getLabelParameterIndex();
            if (r && (lindex > 0))
            {
                String label = getInputSetValueString(lindex);
                if (label == "NULL")
                    saveInteractorLabel(label, true);
            }
            return r;
        }
        public override bool cfgParseComment(string comment, string file, int lineno)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgParseComment(comment, file, lineno);
        }

        public override bool cfgPrintNode(StreamWriter sw, PrintType destination)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgPrintNode(sw, destination);
        }

        public int getInstanceCount() { return instanceList.Count; }
        public int getComponentCount() { return numComponents; }

        /// <summary>
        /// Calls setOutputAndOtherInteractorValues to update all interactor
        /// instances.
        /// </summary>
        /// <param name="index"></param>
        /// <param name="value"></param>
        /// <param name="type"></param>
        /// <param name="send"></param>
        /// <returns></returns>
        public override DXTypeVals setOutputValue(int index, string value, DXTypeVals type, bool send)
        {
            // Set the output value of an interactor.  This is the same as for
            // Node::setOutputValue(), except that it also updates the interactors
            // in this->instanceList with 
            //  InteractorInstance->Interactor->updateDisplayedInteractorValue().

            DXTypeVals dxtype;

            dxtype = base.setOutputValue(index, value, type, send);

            if ((dxtype != DXTypeVals.UndefinedType) &&
                !isVisualNotificationDeferred())
            {
                foreach (InteractorInstance ii in instanceList)
                {
                    Interactor interactor = ii.getInteractor();
                    if (interactor != null)
                        interactor.updateDisplayedInteractorValue();
                }
            }
            return dxtype;
        }

        /// <summary>
        /// Indicates whether this node has outputs that can be remapped by the
        /// server.
        /// </summary>
        /// <returns></returns>
        public virtual bool hasRemappableOutput()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Do what ever is necessary to enable/disable remapping of output values
        /// by the server.
        /// </summary>
        /// <param name="val"></param>
        public virtual void setOutputRemapping(bool val)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// The default action for interactors is to open the control panels
        /// associated with the instances.  This overrides Node::openDefaultWindow()
        /// </summary>
        /// <param name="parent"></param>
        public override void openDefaultWindow(System.Windows.Forms.Form parent)
        {
            throw new Exception("Not Yet Implemented");
            base.openDefaultWindow(parent);
        }

        /// <summary>
        /// Let the caller of openDefaultWindow() know what kind of window she's getting.
        /// This is intended for use in EditorWindow so that we can sanity check the number
        /// of cdbs were going to open before kicking off the operation and so that we
        /// don't question the user before opening large numbers of interactors.
        /// A name describing the type of window can be written into window_name in order
        /// to enable nicer warning messages.
        /// </summary>
        /// <param name="window_name"></param>
        /// <returns></returns>
        public override bool defaultWindowIsCDB(ref string window_name)
        {
            throw new Exception("Not Yet Implemented");
            return base.defaultWindowIsCDB(ref window_name);
        }

        /// <summary>
        /// If the node does not currently have any InteractorInstances, then
        /// add them to the editor's/network's notion of the current control panel.
        /// </summary>
        /// <param name="parent"></param>
        public void openControlPanels(Form parent)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Does this node support dimensionality changes.
        /// By default all interactors do NOT support this.
        /// </summary>
        /// <param name="ignoreDataDriven"></param>
        /// <returns></returns>
        public virtual bool hasDynamicDimensionality() { return hasDynamicDimensionality(false); }
        public virtual bool hasDynamicDimensionality(bool ignoreDataDriven)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override bool isA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
            return base.isA(classname);
        }

        /// <summary>
        /// just like deleteInstance except don't delete ii, just remove it from the list.
        /// </summary>
        /// <param name="ii"></param>
        /// <returns></returns>
        public virtual bool removeInstance(InteractorInstance ii)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns>true if this node has state that will be saved in a .cfg file.</returns>
        public override bool hasCfgState()
        {
            return true;
        }

        public override bool printAsJava(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
            return base.printAsJava(sw);
        }
        public virtual bool printJavaValue(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual String getJavaVaraible()
        {
            throw new Exception("Not Yet Implemented");
        }
        public override String getJavaNodeName() { return "ValueNode"; }

    }
}
