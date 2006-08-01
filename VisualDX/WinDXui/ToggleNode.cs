using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WinDX.UI
{
    class ToggleNode : InteractorNode
    {
        /// <summary>
        /// Set the output and send it if requested.
        /// If setit is TRUE, then set the output to the first of the toggle values
        /// otherwise the 2nd of toggle values.
        /// If how is 1, then send the value.
        /// If how is 0,  then don't send the value.
        /// If how is -1, then send the value quietly.
        /// </summary>
        /// <param name="setit"></param>
        /// <param name="how"></param>
        /// <returns></returns>
        private bool setTheToggle(bool setit, int how)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Set the two potential output values.  The 1st corresponds to the
        /// set (toggle down) state and the second to the reset state (toggle up).
        /// If how is 1, then send the values.
        /// If how is 0,  then don't send the values.
        /// If how is -1, then send the values quietly.
        /// </summary>
        /// <param name="set"></param>
        /// <param name="reset"></param>
        /// <param name="how"></param>
        /// <returns></returns>
        private bool changeToggleValues(String set, String reset, int how)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected DXTypeVals outputType;
        protected bool is_set;

        protected override int handleInteractorMsgInfo(string line)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        /// <summary>
        /// Set the output to and send it.
        /// If setit is TRUE, then set the output to the first of the toggle values
        /// otherwise the 2nd of toggle values.
        /// If send is TRUE, then send it.
        /// </summary>
        /// <param name="setit"></param>
        /// <param name="send"></param>
        /// <returns></returns>
        protected bool setToggle(bool setit, bool send)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected bool setToggleQuietly(bool setit)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Get the values that are output for the set and reset states.
        /// The returned string must be freed by the caller.
        /// </summary>
        /// <param name="setval"></param>
        /// <returns></returns>
        protected String getToggleValue(bool setval)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Initialize the two potential output values.  The 1st corresponds to the
        /// set (toggle down) state and the second to the reset state (toggle up).
        /// This (init) is called at creation, where as setToggleValues() is called
        /// after initialization.
        /// </summary>
        /// <param name="set"></param>
        /// <param name="reset"></param>
        /// <returns></returns>
        protected bool initToggleValues(String set, String reset)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected override InteractorInstance newInteractorInstance()
        {
            return base.newInteractorInstance();
        }

        protected bool printToggleComment(StreamWriter sw, String indent, bool includeValues)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected bool parseToggleComment(String comment, String filename, int lineno, bool includeValues)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected override bool netPrintAuxComment(StreamWriter s)
        {
            throw new Exception("Not Yet Implemented");
            return base.netPrintAuxComment(s);
        }
        protected override bool netParseAuxComment(string comment, string filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
            return base.netParseAuxComment(comment, filename, lineno);
        }
        protected override bool cfgPrintInteractorComment(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgPrintInteractorComment(sw);
        }
        protected override bool cfgParseInteractorComment(string comment, string filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgParseInteractorComment(comment, filename, lineno);
        }

        protected override int getShadowingInput(int output_index)
        {
            throw new Exception("Not Yet Implemented");
            return base.getShadowingInput(output_index);
        }

        public ToggleNode(NodeDefinition nd, Network net, int instnc)
            : base(nd, net, instnc)
        {
            outputType = DXTypeVals.UndefinedType;
            is_set = false;
        }

        public override bool initialize()
        {
            throw new Exception("Not Yet Implemented");
            return base.initialize();
        }

        public bool setToggleValues(String set, String reset)
        {
            throw new Exception("Not Yet Implemented");
        }

        // Change the output value of the toggle.
        public bool set() { return setToggle(true, true); }
        public bool set(bool send) { return setToggle(true, send); }
        public bool reset() { return setToggle(false, true); }
        public bool reset(bool send) { return setToggle(false, send); }

        // Get the values that are output for the set and reset states.
        public String getSetValue() { return getToggleValue(true); }
        public String getResetValue() { return getToggleValue(false); }

        // Determine if the toggle is currently set.
        public bool IsSet { get { return is_set; } }

        public bool isSetAttributeVisuallyWriteable() { throw new Exception("Not Yet Implemented"); }
        public bool isResetAttributeVisuallyWriteable() { throw new Exception("Not Yet Implemented"); }

        public override string getJavaNodeName()
        {
            return "ToggleNode";
        }

        public override bool printJavaValue(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
            return base.printJavaValue(sw);
        }
        public virtual bool printJavaType(StreamWriter sw, String indent, String svar)
        {
            throw new Exception("Not Yet Implemented");
        }

    }
}
