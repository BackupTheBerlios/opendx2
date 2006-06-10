using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Diagnostics;

namespace WinDX.UI
{
    public class NodeDefinition : Definition
    {
        protected enum MDFFLAGS : long
        {
            SWITCH = 0x01,
            ERR_CONT = 0x02,
            PIN = 0x04,
            SIDE_EFFECT = 0x08,
            PERSISTENT = 0x10,
            ASYNCHRONOUS = 0x20,
            REROUTABLE = 0x40,
            REACH = 0x80,
            LOOP = 0x100
        }

        // Was this definition only loaded by the ui
        private bool uiLoadedOnly;

        #region protected Instance Variables
        protected List<ParameterDefinition> inputDefs = new List<ParameterDefinition>();
        protected List<ParameterDefinition> outputDefs = new List<ParameterDefinition>();
        protected Symbol category;
        protected long mdf_flags;  // bits representing FLAGS statment in mdf.
        protected String description;  // A short description
        protected int input_repeats;  // the last n inputs are repeatable 
        protected int output_repeats;  // the last n outputs are repeatable
        protected String loadFile;  // Name of the file containing loadable object
        protected String outboardCommand;  // Name of executable file.
        protected String outboardHost;

        protected bool userTool; // true if defined by a user .mdf file and defaults to true.

        protected bool writeableCacheability; // Is the cacheability of this type of node modifyable

        protected Cacheability defaultCacheability; // Is the module cached by default

        /// <summary>
        /// Increment this number to generate numbers for instances
        /// of the type that is being defined.
        /// </summary>
        protected int nodeInstanceNumbers;

        #endregion

        #region protected Methods
        protected virtual bool addIODef(List<ParameterDefinition> l, ParameterDefinition pd)
        {
            if (l == null)
                return false;
            l.Add(pd);
            return true;
        }

        /// <summary>
        /// Returns the StandIn allocator for this node.
        /// </summary>
        /// <returns></returns>
        protected virtual SIAllocator getSIAllocator()
        {
            // Causes the default definition in the SIAllocatorDictionary to be used.
            return null;
        }

        /// <summary>
        /// Returns the Configuration dialog box allocator for this node. 
        /// </summary>
        /// <returns></returns>
        protected virtual CDBAllocator getCDBAllocator()
        {
            // Causes the default definition in the CDBAllocatorDictionary to be used.
            return null;
        }

        /// <summary>
        /// Allocate a new Node of the corresponding type.
        /// </summary>
        /// <param name="net"></param>
        /// <returns></returns>
        protected virtual Node newNode(Network net)
        {
            return newNode(net, -1);
        }
        protected virtual Node newNode(Network net, int instance)
        {
            Node m = new Node(this, net, instance);
            return m;
        }

        /// <summary>
        /// Get the MDF header (stuff before the INPUT/OUTPUT statements) for this
        /// NodeDefinition.
        /// </summary>
        /// <returns></returns>
        protected String getMDFHeaderString()
        {
            String header = "MODULE " + NameString + "\n";
            String host = DefaultOutboardHost;
            if (CategoryString != null)
            {
                header += "CATEGORY " + CategoryString + "\n";
            }
            if (Description != null)
            {
                header += "DESCRIPTION " + Description + "\n";
            }
            if (IsOutboard)
            {
                header += "OUTBOARD \"" + OutboardCommand + "\" ; " + (host == null ? "" : host) + "\n";
            }
            else if (IsDynamicallyLoaded)
            {
                header += "LOADABLE " + DynamicLoadFile + "\n";
            }
            if (mdf_flags > 0)
            {
                header += "FLAGS";
                if (IsMDFFlagERR_CONT)
                    header += " ERR_CONT";
                if (IsMDFFlagSWITCH)
                    header += " SWITCH";
                if (IsMDFFlagPIN)
                    header += " PIN";
                if (IsMDFFlagLOOP)
                    header += " LOOP";
                if (IsMDFFlagSIDE_EFFECT)
                    header += " SIDE_EFFECT";
                if (IsMDFFlagPERSISTENT)
                    header += " PERSISTENT";
                if (IsMDFFlagASYNCHRONOUS)
                    header += " ASYNC";
                if (IsMDFFlagREACH)
                    header += " REACH";
                if (IsMDFFlagREROUTABLE)
                    header += " REROUTABLE";
                header += "\n";
            }
            return header;
        }

        /// <summary>
        /// Get the list of INPUT/OUTPUT lines in the MDF and the REPEAT if any
        /// </summary>
        /// <param name="inputs"></param>
        /// <returns></returns>
        protected String getMDFParameterString(bool inputs)
        {
            String param = "";
            List<ParameterDefinition> defs;
            if (inputs)
                defs = inputDefs;
            else
                defs = outputDefs;

            foreach (ParameterDefinition pd in defs)
            {
                String line = pd.getMDFString();
                param += line;
            }

            if (inputs && IsInputRepeatable)
            {
                param += "REPEAT " + InputRepeatCount.ToString() + "\n";
            }
            else if (!inputs && IsOutputRepeatable)
            {
                param += "REPEAT " + OutputRepeatCount.ToString() + "\n";
            }
            return param;
        }


        /// <summary>
        /// Set/clear one of the this->mdf_flag bits.
        /// </summary>
        /// <param name="val"></param>
        /// <param name="flag"></param>
        protected void setMDFFlag(bool val, MDFFLAGS flag)
        {
            if (val)
                mdf_flags |= (long) flag;
            else
                mdf_flags &= ~((long)flag);
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Reset all the instance numbers in a dictionary of definitions.
        /// </summary>
        /// <param name="d"></param>
        public static void ResetInstanceNumbers(Dictionary<Symbol, NodeDefinition> d)
        {
            foreach (KeyValuePair<Symbol, NodeDefinition> kvm in d)
            {
                kvm.Value.setNextInstance(0);
            }
        }

        /// <summary>
        /// Allocate a new NodeDefinition.
        /// This function is intended to be used as an allocator in
        /// theNDAllocatorDictionary.
        /// </summary>
        /// <returns></returns>
        public static NodeDefinition AllocateDefinition()
        {
            return new NodeDefinition();
        }

        public NodeDefinition()
        {
            nodeInstanceNumbers = 0;
            description = null;
            input_repeats = 0;
            output_repeats = 0;
            writeableCacheability = true;
            defaultCacheability = Cacheability.ModuleFullyCached;
            mdf_flags = 0;
            loadFile = null;
            outboardHost = null;
            outboardCommand = null;
            userTool = true;
            uiLoadedOnly = false;
        }

        ~NodeDefinition()
        {
            NodeDefinition nd;
            if(NodeDefinition.theNodeDefinitionDictionary.TryGetValue(this.NameSymbol, out nd))
                if (nd == this)
                    NodeDefinition.theNodeDefinitionDictionary.Remove(this.NameSymbol); 
        }

        public virtual bool IsDerivedFromMacro()
        {
            throw new Exception("Not Yet Implemented");
        }

        // Instance number manipulations
        public int newInstanceNumber() { return ++nodeInstanceNumbers; }
        public void setNextInstance(int inst) { nodeInstanceNumbers = inst; }
        public int getCurrentInstance() { return nodeInstanceNumbers; }

        /// <summary>
        /// Add an input or output to the list of i/o definitions..
        /// </summary>
        /// <param name="pd"></param>
        /// <returns></returns>
        public bool addInput(ParameterDefinition pd)
        { return addIODef(inputDefs, pd); }
        public bool addOutput(ParameterDefinition pd)
        { return addIODef(outputDefs, pd); }

        /// <summary>
        /// Get the Nth Input or Output ParameterDefinition.
        /// n is indexed from 1.  If n is greater than the number of input/output 
        /// defintions then it is a repeatable parameter, in which case we 
        /// account for this to find the correct definition.
        /// 
        /// For C# we index from 0. There may be a problem here.
        /// </summary>
        /// <param name="n"></param>
        /// <returns></returns>
        public ParameterDefinition getInputDefinition(int n)
        {
            Debug.Assert(n > 0);

            if (n > InputCount)
            {
                Debug.Assert(input_repeats > 0);
                if (input_repeats == 1)
                {
                    n = InputCount;
                }
                else
                {
                    int num = (((n - 1) - InputCount) % input_repeats) + 1;
                    n = InputCount - input_repeats + num;
                    Debug.Assert(n > InputCount - input_repeats);
                    Debug.Assert(n <= InputCount);
                }
            }
            return inputDefs[n-1];
        }
        public ParameterDefinition getOutputDefinition(int n)
        {
            Debug.Assert(n > 0);
            int cnt = OutputCount;

            if (n > cnt)
            {
                Debug.Assert(output_repeats > 0);
                if (output_repeats == 1)
                {
                    n = cnt;
                }
                else
                {
                    int num = (((n - 1) - cnt) % output_repeats) + 1;
                    n = cnt - output_repeats + num;
                    Debug.Assert(n > cnt - output_repeats);
                    Debug.Assert(n <= cnt);
                }
            }
            return outputDefs[n-1];
        }

        public void setWriteableCacheability(bool v)
        {
            writeableCacheability = v;
        }

        //public virtual String getExecModuleNameString()
        //{
        //    throw new Exception("Not Yet Implemented");
        //}

        /// <summary>
        /// Create a new Node (not NodeDefinition) of this type. 
        /// Node initialize() is done here and any other boiler plate as required.
        /// </summary>
        /// <param name="net"></param>
        /// <returns></returns>
        public virtual Node createNewNode(Network net)
        {
            return createNewNode(net, -1);
        }
        public virtual Node createNewNode(Network net, int instance)
        {
            if (!IsAllowedInMacro() && net.IsMacro)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("The {0} node is not allowed in a macro.",
                    NameString);
                return null;
            }
            Node n = this.newNode(net, instance);
            if (n != null)
            {
                if (!n.initialize())
                {
                    n = null;
                }
            }
            return n;
        }

        public virtual void finishDefinition()
        { // No implementation 
        }

        public virtual bool IsAllowedInMacro() { return true; }

        /// <summary>
        /// Get a new parameter for the node n that corresponds to this node 
        /// definition. index is the one based index of the input/output parameter.
        /// </summary>
        /// <param name="pd"></param>
        /// <param name="n"></param>
        /// <param name="index"></param>
        /// <returns></returns>
        public virtual Parameter newParameter(ParameterDefinition pd, Node n, int index)
        {
            return new Parameter(pd);
        }

        public void setMDFFlagERR_CONT() { setMDFFlagERR_CONT(true); }
        public void setMDFFlagERR_CONT(bool val) { setMDFFlag(val, MDFFLAGS.ERR_CONT); }

        public void setMDFFlagSWITCH() { setMDFFlagSWITCH(true); }
        public void setMDFFlagSWITCH(bool val)
        {
            setMDFFlag(val, MDFFLAGS.SWITCH);
        }

        public void setMDFFlagPIN() { setMDFFlagPIN(true); }
        public void setMDFFlagPIN(bool val) { setMDFFlag(val, MDFFLAGS.PIN); }
        public void setMDFFlagSIDE_EFFECT() { setMDFFlagSIDE_EFFECT(true); }
        public void setMDFFlagSIDE_EFFECT(bool val) { setMDFFlag(val, MDFFLAGS.SIDE_EFFECT); }
        public void setMDFFlagASYNCHRONOUS() { setMDFFlagASYNCHRONOUS(true); }
        public void setMDFFlagASYNCHRONOUS(bool val) { setMDFFlag(val, MDFFLAGS.ASYNCHRONOUS); }
        public void setMDFFlagPERSISTENT() { setMDFFlagPERSISTENT(true); }
        public void setMDFFlagPERSISTENT(bool val) { setMDFFlag(val, MDFFLAGS.PERSISTENT); }
        public void setMDFFlagREACH() { setMDFFlagREACH(true); }
        public void setMDFFlagREACH(bool val) { setMDFFlag(val, MDFFLAGS.REACH); }
        public void setMDFFlagREROUTABLE() { setMDFFlagREROUTABLE(true); }
        public void setMDFFlagREROUTABLE(bool val) { setMDFFlag(val, MDFFLAGS.REROUTABLE); }
        public void setMDFFlagLOOP() { setMDFFlagLOOP(true); }
        public void setMDFFlagLOOP(bool val) { setMDFFlag(val, MDFFLAGS.LOOP); }

        public void setUserTool() { userTool = true; }
        public void setUserTool(bool setting) { userTool = setting; }

        /// <summary>
        /// Called after reading in a mdf record for this node definition.
        /// Calls finishDefinition() after installing the CDB and SI allocators
        /// for this node.
        /// </summary>
        public void completeDefinition()
        {
            if (SIAllocatorDictionary.theSIAllocatorDictionary != null)
            {
                SIAllocator sia = getSIAllocator();
                if (sia != null)
                    SIAllocatorDictionary.theSIAllocatorDictionary.Add(NameString, sia);
            }
            if (CDBAllocatorDictionary.theCDBAllocatorDictionary != null)
            {
                CDBAllocator cdba = getCDBAllocator();
                if (cdba != null)
                    CDBAllocatorDictionary.theCDBAllocatorDictionary.Add(NameString, cdba);
            }
            finishDefinition();
        }

        /// <summary>
        /// Add a selectable value for the n'th input.
        /// </summary>
        /// <param name="n"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public bool addInputValueOption(int n, String value)
        {
            throw new Exception("Not Yet Implemented");
        }

        #endregion

        #region Public Instances and Properties

        /// <summary>
        /// Get the number of base (unrepeated) inputs/outputs for this node.
        /// </summary>
        public int InputCount
        {
            get { return inputDefs.Count; }
        }
        public int OutputCount
        {
            get { return outputDefs.Count; }
        }
        public int InputRepeatCount
        {
            get { return input_repeats; }
            set { input_repeats = value; }
        }
        public int OutputRepeatCount
        {
            get { return output_repeats; }
            set { output_repeats = value; }
        }
        public bool IsOutputRepeatable
        {
            get { return output_repeats != 0; }
        }
        public bool IsInputRepeatable
        {
            get { return input_repeats != 0; }
        }

        public bool HasWriteableCacheability
        {
            get { return writeableCacheability; }
        }

        public Cacheability DefaultCacheability
        {
            get { return defaultCacheability; }
            set { defaultCacheability = value; }
        }

        public Symbol Category
        {
            get { return category; }
            set { category = value; }
        }
        public String CategoryString
        {
            get { return SymbolManager.theSymbolManager.getSymbolString(category); }
        }

        public virtual String ExecModuleNameString
        {
            get { return NameString; }
        }

        public String getMDFString()
        {
            String header = getMDFHeaderString();
            String inputs = getMDFParameterString(true);
            String outputs = getMDFParameterString(false);

            Debug.Assert(header != null);

            String mdf = header + (inputs == null ? "" : inputs) + (outputs == null ? "" : outputs);
            return mdf;
        }

        /// <summary>
        /// Description for this node.
        /// </summary>
        public String Description
        {
            get { return (description == null ? "" : description); }
            set { description = value; }
        }

        public bool IsMDFFlagERR_CONT
        {
            get { return (mdf_flags & (long)MDFFLAGS.ERR_CONT)>0 ? true : false; }
        }
        public bool IsMDFFlagSWITCH
        {
            get { return (mdf_flags & (long)MDFFLAGS.SWITCH)>0 ? true : false; }
        }
        public bool IsMDFFlagPIN
        {
            get { return (mdf_flags & (long)MDFFLAGS.PIN)>0 ? true : false; }
        }
        public bool IsMDFFlagSIDE_EFFECT
        {
            get { return (mdf_flags & (long)MDFFLAGS.SIDE_EFFECT)>0 ? true : false; }
        }
        public bool IsMDFFlagASYNCHRONOUS
        {
            get { return (mdf_flags & (long)MDFFLAGS.ASYNCHRONOUS)>0 ? true : false; }
        }
        public bool IsMDFFlagPERSISTENT
        {
            get { return (mdf_flags & (long)MDFFLAGS.PERSISTENT)>0 ? true : false; }
        }
        public bool IsMDFFlagREACH
        {
            get { return (mdf_flags & (long)MDFFLAGS.REACH)>0 ? true : false; }
        }
        public bool IsMDFFlagREROUTABLE
        {
            get { return (mdf_flags & (long)MDFFLAGS.REROUTABLE)>0 ? true : false; }
        }
        public bool IsMDFFlagLOOP
        {
            get { return (mdf_flags & (long)MDFFLAGS.LOOP)>0 ? true : false; }
        }

        public bool IsOutboard
        {
            get { return outboardCommand != null; }
        }

        public String DefaultOutboardHost
        {
            get { return outboardHost; }
            set { outboardHost = value; }
        }

        public String OutboardCommand
        {
            get { return outboardCommand; }
            set { outboardCommand = value; }
        }

        public String DynamicLoadFile
        {
            get { return loadFile; }
            set { loadFile = value; }
        }
        public bool IsDynamicallyLoaded
        {
            get { return loadFile != null; }
        }

        public bool IsUserTool
        {
            get { return userTool; }
        }

        public bool UILoadedOnly
        {
            get { return uiLoadedOnly; }
            set { uiLoadedOnly = value; }
        }

        #endregion

        public static Dictionary<Symbol, NodeDefinition> theNodeDefinitionDictionary =
            new Dictionary<Symbol, NodeDefinition>();
    }
}
