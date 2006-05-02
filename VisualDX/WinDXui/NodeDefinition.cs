using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

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
        protected List<ParameterDefinition> inputDefs;
        protected List<ParameterDefinition> outputDefs;
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
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Returns the Configuration dialog box allocator for this node. 
        /// </summary>
        /// <returns></returns>
        protected virtual CDBAllocator getCDBAllocator()
        {
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Get the MDF header (stuff before the INPUT/OUTPUT statements) for this
        /// NodeDefinition.
        /// </summary>
        /// <returns></returns>
        protected String getMDFHeaderString()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Get the list of INPUT/OUTPUT lines in the MDF and the REPEAT if any
        /// </summary>
        /// <param name="inputs"></param>
        /// <returns></returns>
        protected String getMDFParameterString(bool inputs)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// Set/clear one of the this->mdf_flag bits.
        /// </summary>
        /// <param name="val"></param>
        /// <param name="flag"></param>
        protected void setMDFFlag(bool val, MDFFLAGS flag)
        {
            throw new Exception("Not Yet Implemented");
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Reset all the instance numbers in a dictionary of definitions.
        /// </summary>
        /// <param name="d"></param>
        public static void ResetInstanceNumbers(Dictionary<Symbol, NodeDefinition> d)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Allocate a new NodeDefinition.
        /// This function is intended to be used as an allocator in
        /// theNDAllocatorDictionary.
        /// </summary>
        /// <returns></returns>
        public static NodeDefinition AllocateDefinition()
        {
            throw new Exception("Not Yet Implemented");
        }

        public NodeDefinition()
        {
            throw new Exception("Not Yet Implemented");
        }

        ~NodeDefinition()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool IsDerivedFromMacro()
        {
            throw new Exception("Not Yet Implemented");
        }

        // Instance number manipulations
        public int newInstanceNumber() { return ++nodeInstanceNumbers; }
        public void setNextInstance(int inst) { nodeInstanceNumbers = inst - 1; }
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
        /// </summary>
        /// <param name="n"></param>
        /// <returns></returns>
        public ParameterDefinition getInputDefinition(int n)
        {
            throw new Exception("Not Yet Implemented");
        }
        public ParameterDefinition getOutputDefinition(int n)
        {
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
        }

        public virtual void finishDefinition()
        { // No implementation 
        }

        public virtual bool isAllowedInMacro() { return true; }

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
            throw new Exception("Not Yet Implemented");
        }

        public void setMDFFlagSWITCH() { setMDFFlagSWITCH(true); }
        public void setMDFFlagSWITCH(bool val)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void setMDFFlagPIN() { setMDFFlagPIN(true); }
        public void setMDFFlagPIN(bool val) { throw new Exception("Not Yet Implemented"); }
        public void setMDFFlagSIDE_EFFECT() { setMDFFlagSIDE_EFFECT(true); }
        public void setMDFFlagSIDE_EFFECT(bool val) { throw new Exception("Not Yet Implemented"); }
        public void setMDFFlagASYNCHRONOUS() { setMDFFlagASYNCHRONOUS(true); }
        public void setMDFFlagASYNCHRONOUS(bool val) { throw new Exception("Not Yet Implemented"); }
        public void setMDFFlagPERSISTENT() { setMDFFlagPERSISTENT(true); }
        public void setMDFFlagPERSISTENT(bool val) { throw new Exception("Not Yet Implemented"); }
        public void setMDFFlagREACH() { setMDFFlagREACH(true); }
        public void setMDFFlagREACH(bool val) { throw new Exception("Not Yet Implemented"); }
        public void setMDFFlagREROUTABLE() { setMDFFlagREROUTABLE(true); }
        public void setMDFFlagREROUTABLE(bool val) { throw new Exception("Not Yet Implemented"); }
        public void setMDFFlagLOOP() { setMDFFlagLOOP(true); }
        public void setMDFFlagLOOP(bool val) { throw new Exception("Not Yet Implemented"); }

        public void setUserTool() { userTool = true; }
        public void setUserTool(bool setting) { userTool = setting; }

        /// <summary>
        /// Called after reading in a mdf record for this node definition.
        /// Calls finishDefinition() after installing the CDB and SI allocators
        /// for this node.
        /// </summary>
        public void completeDefinition()
        {
            throw new Exception("Not Yet Implemented");
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
            get { throw new Exception("Not Yet Implemented"); }
        }

        public String getMDFString()
        {
            throw new Exception("Not Yet Implemented");
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
            get { throw new Exception("Not Yet Implemented"); }
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
            get { throw new Exception("Not Yet Implemented"); }
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
