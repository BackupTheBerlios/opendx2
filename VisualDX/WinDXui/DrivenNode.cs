using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using System.Diagnostics;

namespace WinDX.UI
{
    public abstract class DrivenNode : ModuleMessagingNode
    {
        private int visualNotificationDeferrals;
        private bool visualsNeedNotification;

        private void setInteractorLable(String label)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// This is set when the execModuleMessageHandler() starts accepting
        /// a long message.
        /// </summary>
        protected bool handlingLongMessage;

        /// <summary>
        /// Called when a message is received from the executive after
        /// this->ExecModuleMessageHandler() is registered in
        /// this->Node::netPrintNode() to receive messages for this node.
        /// We parse all the common information and then the class specific.
        /// If any relevant info was found then we call this->reflectStateChange(). 
        ///
        /// If any input or output values are to be changed, don't send them 
        /// because the module backing up the node will have just executed 
        /// and if the UI is in 'execute on change' mode then there will be an 
        /// extra execution.
        /// </summary>
        /// <param name="id"></param>
        /// <param name="line"></param>
        protected override void execModuleMessageHandler(int id, string line)
        {
            bool do_notify = true;
            deferVisualNotification();
            Regex regex = new Regex(@".*:.*:(.*)");
            Match m = regex.Match(line);
            String substr = "";

            if (m.Success)
                substr = m.Groups[1].Value;

            if (!handlingLongMessage && substr.StartsWith("  begin"))
            {
                // Begin handling a long message.
                handlingLongMessage = true;
                //Don't notify visuals during a long message.
                do_notify = false;
            }
            else if (substr.StartsWith("  end"))
            {
                // End of long message encountered.
                handlingLongMessage = false;
                // Always notify visuals after a long message.
                do_notify = true;
            }
            else
            {
                // Handle both long and short messages.
                // Only do notification on short messages.
                int values = handleNodeMsgInfo(line);
                do_notify = (!handlingLongMessage && values > 0);
            }

            if (do_notify)
                notifyVisualsOfStateChange();

            undeferVisualNotification(true);
        }

        /// <summary>
        /// Parse the node specific info from an executive message. 
        /// </summary>
        /// <param name="line"></param>
        /// <returns>Returns the number of attributes parsed.</returns>
        protected abstract int handleNodeMsgInfo(String line);


        /// <summary>
        /// Update any UI visuals that may be based on the state of this
        /// node.   Among other times, this is called after receiving a message
        /// from the executive.
        /// </summary>
        /// <param name="unmanage"></param>
        protected abstract void reflectStateChange(bool unmanage);


        /// <summary>
        /// Return TRUE/FALSE, indicating whether or not we expect to receive
        /// a message from the UI when our module executes in the executive.
        /// By default, a module only executes in the executive for data-driven
        /// nodes and so we don't expect messages unless the node 
        /// is data-driven.
        /// </summary>
        /// <returns></returns>
        protected override bool expectingModuleMessage()
        {
            return IsDataDriven;
        }


        /// <summary>
        /// Set the message id parameter for a data-driven node.  
        /// We assume that the id parameter is always parameter the value
        /// returned by getMessageIdParamNumber().
        /// Returns TRUE/FALSE.  If FALSE, an error message is given.
        /// </summary>
        /// <returns></returns>
        public bool setMessageIdParameter() { return setMessageIdParameter(0); }
        public bool setMessageIdParameter(int id_index)
        {
            String id = getModuleMessageIdString();

            if (id_index == 0)
            {
                id_index = getMessageIdParamNumber();
                if (id_index == 0)
                    return true;
            }

            if (setInputValue(id_index, id, DXTypeVals.StringType, false) ==
                DXTypeVals.UndefinedType)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Error setting message id string for node {0}, check ui.mdf",
                    NameString);
            }
            return true;
        }

        /// <summary>
        /// Get the index of the parameter that has a message id token.
        /// Returns 0, if there is not message id parameter for the node.
        /// </summary>
        /// <returns></returns>
        public virtual int getMessageIdParamNumber() { return 1; }

        /// <summary>
        /// Notify anybody that needs to know that a parameter has changed its 
        /// arcs or values.
        /// </summary>
        /// <param name="input"></param>
        /// <param name="index"></param>
        /// <param name="status"></param>
        protected override void ioParameterStatusChanged(bool input, int index, Node.NodeParameterStatusChange status)
        {
            if (input && (long)(status & NodeParameterStatusChange.ParameterArkChanged) > 0)
            {
                bool driven = IsDataDriven;
                if (driven)
                {
                    for (int i = 1; i <= OutputCount; i++)
                        setOutputDirty(i);
                    // Don't need to send them because the network will get marked
                    // dirty as a result of an arc change.
                }
            }

            base.ioParameterStatusChanged(input, index, status);

            // Update the UI visuals for this node when ever any of our viewable
            // input arcs or values change, which may lead to a sensitivity change 
            //  on one of the UI visuals for this node. 
            if (input && ((long)(status & NodeParameterStatusChange.ParameterVisibilityChanged) == 0) &&
                isInputViewable(index))
                notifyVisualsOfStateChange();
        }


        /// <summary>
        /// Update any inputs that are being updated by the server (i.e. the
        /// module that is doing the data-driven operations).  These inputs
        /// are updated in a special way since we don't want to change the
        /// defaulting/set status of the parameter, we don't want it sent back
        /// to the server, and we don't want to mark it as dirty.
        /// </summary>
        /// <param name="index"></param>
        /// <param name="val"></param>
        /// <returns></returns>
        protected DXTypeVals setInputAttributeFromServer(int index, String val)
        { return setInputAttributeFromServer(index, val, DXTypeVals.UndefinedType); }
        protected DXTypeVals setInputAttributeFromServer(int index, String val, DXTypeVals t)
        {
            Parameter p = getInputParameter(index);
            Debug.Assert(p is AttributeParameter);

            bool was_dirty = p.IsDirty;

            bool r = setInputAttributeParameter(index, val);

            if (!was_dirty)
                clearInputDirty(index);
            Debug.Assert(r);
            if (t == DXTypeVals.UndefinedType)
            {
                AttributeParameter ap = (AttributeParameter)p;
                t = ap.getAttributeValueType();
            }
            return t;
        }

        /// <summary>
        /// Initialize/set the value of an attribute parameter.
        /// If forceSync is TRUE (default = FALSE), then force the primary
        /// parameters of the AttributeParameter to be updated regardless of
        /// whether or not the types match.
        /// </summary>
        /// <param name="index"></param>
        /// <param name="val"></param>
        /// <returns></returns>
        protected bool setInputAttributeParameter(int index, String val)
        { return setInputAttributeParameter(index, val, false); }
        protected bool setInputAttributeParameter(int index, String val, bool forceSync)
        {
            AttributeParameter p = (AttributeParameter)getInputParameter(index);
            return p.setAttributeValue(val, forceSync);
        }

        protected bool initInputAttributeParameter(int index, String val)
        {
            AttributeParameter p = (AttributeParameter)getInputParameter(index);
            return p.initAttributeValue(val);
        }
        protected String getInputAttributeParameterValue(int index)
        {
            AttributeParameter p = (AttributeParameter)getInputParameter(index);
            return p.getAttributeValueString();
        }

        /// <summary>
        /// Determine if the give attribute/paramater is visually writeable (i.e.
        /// settable from something other than the CDB, like the SetAttrDialog).
        /// It may be ok to make this public, but erring on the side of caution
        /// for now.
        /// </summary>
        /// <param name="input_index"></param>
        /// <returns></returns>
        protected virtual bool isAttributeVisuallyWriteable(int input_index)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Sync all the attribute values with the actual parameter values.
        /// </summary>
        protected void syncAttributeParameters()
        {
            throw new Exception("Not Yet Implemented");
        }


        public DrivenNode(NodeDefinition nd, Network net, int instnc) :
            base(nd, net, instnc)
        {
            visualNotificationDeferrals = 0;
            visualsNeedNotification = false;
            handlingLongMessage = false;
        }

        /// <summary>
        /// Check all input parameters to see if any are connected.
        /// If connected, then we consider the ModuleMessagingNode to be data-driven
        /// (at this level of the the class hierarchy) and return TRUE,
        /// otherwise FALSE.
        /// </summary>
        /// <returns></returns>
        public virtual bool IsDataDriven
        {
            get
            {
                bool driven = false;
                for (int i = 1; !driven && i <= InputCount; i++)
                {
                    if (isInputViewable(i))
                        driven = !isInputDefaulting(i);
                }
                return driven;
            }
        }


        /// <summary>
        /// Notify all UI visuals that the attributes have changed.
        /// If 'unmanage' is TRUE, then it is recommended that the visual
        /// be unmanage making the changes.  This calls this->reflectStateChange()
        /// when undefered.
        /// </summary>
        public void notifyVisualsOfStateChange() { notifyVisualsOfStateChange(false); }
        public void notifyVisualsOfStateChange(bool unmanage)
        {
            if (!isVisualNotificationDeferred())
            {
                visualsNeedNotification = false;
                reflectStateChange(unmanage);
            }
            else
                visualsNeedNotification = true;
        }


        /// <summary>
        /// In addition to superclass' work, change the node name parameter.
        /// </summary>
        /// <returns></returns>
        public override int assignNewInstanceNumber()
        {
            throw new Exception("Not Yet Implemented");
        }


        public bool isVisualNotificationDeferred()
        { return visualNotificationDeferrals != 0; }
        public void deferVisualNotification() { visualNotificationDeferrals++; }
        public void undeferVisualNotification() { undeferVisualNotification(false); }
        public void undeferVisualNotification(bool unmanage)
        {
            Debug.Assert(visualNotificationDeferrals > 0);
            if ((--visualNotificationDeferrals == 0) &&
                visualsNeedNotification)
                notifyVisualsOfStateChange(unmanage);
        }

        public override bool isA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override bool hasJavaRepresentation() { return true; }
        public override string getJavaNodeName() { return "DrivenNode"; }
    }
}
