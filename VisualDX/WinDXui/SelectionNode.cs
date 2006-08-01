using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WinDX.UI
{
    abstract class SelectionNode : InteractorNode
    {
        // This is used during parsing of the .cfg, to delay setting of 
        // the selected option.
        private static int OptionsLeftToSet;

        private int optionCount;
        private bool alwaysEnlistOutputs;

        private static void InstallNewOptions(Object staticdata, Object requestdata)
        {
            throw new Exception("Not Yet Implemented");
        }
        private DeferrableAction deferNewOptionInstallation;

        /// <summary>
        /// Update the output values based on the current selections, then send
        /// the values to the server.
        /// </summary>
        /// <param name="fromServer"></param>
        private void updateOutputs() { updateOutputs(false); }
        private void updateOutputs(bool fromServer)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Update the selected option index, and if requested, update the output
        /// values to match the values indicated by the index.
        /// </summary>
        /// <param name="index"></param>
        /// <param name="set"></param>
        /// <param name="send"></param>
        /// <param name="update_outputs"></param>
        private void changeSelectedOptionIndex(int index, bool set)
        {
            changeSelectedOptionIndex(index, set, true, true);
        }
        private void changeSelectedOptionIndex(int index, bool set,
            bool send, bool update_outputs)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Update the selected option index, and if requested, update the output
        /// values to match the values indicated by the index.
        /// </summary>
        /// <param name="index"></param>
        private void addSelectedOptionIndex(int index)
        {
            addSelectedOptionIndex(index, true, true);
        }
        private void addSelectedOptionIndex(int index, bool send, bool update_outputs)
        {
            throw new Exception("Not Yet Implemented");
        }

        private void clearSelections() { clearSelections(true, true); }
        private void clearSelections(bool send, bool update)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected List<int> selectedOptions = new List<int>();
        protected override bool cfgPrintInteractorAuxInfo(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected bool cfgPrintSelectionsComment(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected bool cfgPrintOptionComments(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected bool cfgParseOptionComment(String comment, String filename,
            int fileno)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected bool cfgParseSelectionsComment(String comment, String filename,
            int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// The messages we parse can contain one or more of the following...
        ///
        ///      'value list={...}' or 'string list={...}'
        ///
        /// If any input or output values are to be changed, don't send them
        /// because the module backing up the interactor will have just executed
        /// and if the UI is in 'execute on change' mode then there will be an
        /// extra execution.
        /// </summary>
        /// <param name="line"></param>
        /// <returns>the number of attributes parsed.</returns>
        protected override int handleInteractorMsgInfo(string line)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        /// <summary>
        /// Define the mapping of inputs that shadow outputs.
        /// By default, all data driven interactors, have a single output that is
        /// shadowed by the third (hidden) input.
        /// Returns an input index (greater than 1) or 0 if there is no shadowing 
        /// input for the given output index.
        /// </summary>
        /// <param name="output_index"></param>
        /// <returns></returns>
        protected override int getShadowingInput(int output_index)
        {
            throw new Exception("Not Yet Implemented");
            return base.getShadowingInput(output_index);
        }

        /// <summary>
        /// If either of the list inputs has changed, we must determine the size
        /// of the smaller of the two lists and reset this->optionCount to that 
        /// value.  
        /// NOTE: If this routine is being called, then one of the values must 
        ///    have a set value (even though both are allowed not too). 
        /// </summary>
        /// <param name="input"></param>
        /// <param name="index"></param>
        /// <param name="status"></param>
        protected override void ioParameterStatusChanged(bool input, int index, NodeParameterStatusChange status)
        {
            throw new Exception("Not Yet Implemented");
            base.ioParameterStatusChanged(input, index, status);
        }

        protected bool setValueOptionsAttribute(String vlist)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected bool setStringOptionsAttribute(String slist)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected bool initValueOptionsAttribute(String vlist)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected bool initStringOptionsAttribute(String slist)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected String getValueOptionsAttribute()
        {
            throw new Exception("Not Yet Implemented");
        }
        protected String getStringOptionsAttribute()
        {
            throw new Exception("Not Yet Implemented");
        }

        protected override InteractorInstance newInteractorInstance()
        {
            throw new Exception("Not Yet Implemented");
        }

        protected abstract String getInitialValueList();
        protected abstract String getInitialStringList();


        public SelectionNode(NodeDefinition nd, Network net, int instnc /* false */)
            :
            base(nd, net, instnc)
        {
            optionCount = 0;
            alwaysEnlistOutputs = false;
            deferNewOptionInstallation = new DeferrableAction(
                SelectionNode.InstallNewOptions, this);
        }
        public SelectionNode(NodeDefinition nd, Network net, int instnc, bool alwaysEnlistOutputs)
            : base(nd, net, instnc)
        {
            optionCount = 0;
            this.alwaysEnlistOutputs = alwaysEnlistOutputs;
            deferNewOptionInstallation = new DeferrableAction(
                SelectionNode.InstallNewOptions, this);
        }

        public int getSelectedOptionCount() { return selectedOptions.Count; }
        public int getOptionCount() { return optionCount; }

        /// <summary>
        /// Get the value of the indicated option.
        /// The returned string must be deleted by the caller.
        /// </summary>
        /// <param name="optind"></param>
        /// <returns></returns>
        public String getOptionValueString(int optind)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Get the name of the indicated option.
        /// The return string is not double quoted unless keep_quotes is TRUE.
        /// Ther returned string must be deleted by the caller.
        /// </summary>
        /// <param name="optind"></param>
        /// <param name="keep_quotes"></param>
        /// <returns></returns>
        public String getOptionNameString(int optind) { return getOptionNameString(optind, false); }
        public String getOptionNameString(int optind, bool keep_quotes)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool appendOptionPair(String val, String label)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Use the value list and string list to set the new list of options.
        /// Also, notify all instances that the state has changed.
        /// </summary>
        /// <param name="vlist"></param>
        /// <param name="slist"></param>
        /// <param name="send"></param>
        public void installNewOptions(String vlist, String slist, bool send)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override bool initialize()
        {
            throw new Exception("Not Yet Implemented");
            return base.initialize();
        }

        /// <summary>
        /// Parse comments found in the .cfg that the InteractorNode knows how to
        /// parse plus ones that it does not.
        /// </summary>
        /// <param name="comment"></param>
        /// <param name="file"></param>
        /// <param name="lineno"></param>
        /// <returns></returns>
        public override bool cfgParseComment(string comment, string file, int lineno)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgParseComment(comment, file, lineno);
        }

        /// <summary>
        /// Return true of the given index'ed option is selected.
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        public bool isOptionSelected(int index)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override bool isA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
            return base.isA(classname);
        }

        /// <summary>
        /// Update the selected option index, and if requested, update the output
        /// values to match the values indicated by the index.
        /// </summary>
        /// <param name="setIndices"></param>
        /// <param name="count"></param>
        public void setSelectedOptions(int setIndices, int count)
        {
            setSelectedOptions(setIndices, count, true, true);
        }
        public void setSelectedOptions(int setIndices, int count,
            bool send, bool update_outputs)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool printJavaType(StreamWriter sw, String filename, String lineno)
        {
            throw new Exception("Not Yet Implemented");
        }
        public override string getJavaNodeName()
        {
            return "SelectionNode";
        }
        public override bool printJavaValue(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
            return base.printJavaValue(sw);
        }
    }
}
