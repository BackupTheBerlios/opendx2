using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    class ScalarNode : InteractorNode
    {
        public enum Params : int { 
            ID = 1,
            DATA,
            CVAL,
            REFRESH,
            MIN,
            MAX,
            INCR,
            INCRMETHOD,
            DECIMALS,
            DFLTVAL,
            LABEL
        }

        public static readonly int EXPECTED_SCALAR_INPUTS = (int) Params.LABEL;
        private bool vectorType;
        private bool needsRangeCheck;
        private int rangeCheckDeferrals;

        /// <summary>
        /// Adjusts the dimensionality of all attribute components for
        /// this->doDimensionalityChange().
        /// </summary>
        /// <param name="old_dim"></param>
        /// <param name="new_dim"></param>
        /// <returns></returns>
        private bool adjustAttributeDimensions(int old_dim, int new_dim)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// If we're parsing input #4 (which is now REFRESH and was at one point REMAP)
        /// and the net version is older than 3.1.0 (which is compiled in by DXVersion.h),
        /// then set the defaulting status = TRUE.  Reason:  the older ui was setting
        /// the defaulting status of this unused param to FALSE.  Now that we want to use
        /// the param again, old nets believe the param is set.
        /// </summary>
        /// <param name="input"></param>
        /// <param name="comment"></param>
        /// <param name="filename"></param>
        /// <param name="lineno"></param>
        /// <param name="valueOnly"></param>
        /// <returns></returns>
        protected override bool parseIOComment(bool input, string comment, string filename, int lineno, bool valueOnly)
        {
            if (base.parseIOComment(input, comment, filename, lineno, valueOnly) == false)
                return false;

            // If the net version is less than 3.1.0 then set param 4 defaulting status
            // to true.  The ui had mistakenly been setting it to false although the param
            // was not in use by the module.  Now we want to use that param but existing
            // nets don't work unless param 4 (REFRESH) starts out defaulting.
            //
            // This code turns into NoOp starting with net version == 3.1.0

            Network net = getNetwork();
            if (net.getNetMajorVersion() > 3) return true;
            if (net.getNetMinorVersion() >= 1) return true;

            Debug.Assert(comment != null);
            bool parse_error = false;
            Params ionum = Params.CVAL;
            int defaulting = 0;

            if (input)
            {
                if (valueOnly)
                {
                    throw new Exception("Not Yet Implemented");
                }
                else
                {
                    throw new Exception("Not Yet Implemented");
                }
            }

            if (!parse_error && input && ionum == Params.REFRESH && defaulting == 0)
            {
                Parameter par = getInputParameter((int)Params.REFRESH);
                par.setUnconnectedDefaultingStatus(true);
            }
            return true;
        }

        /// <summary>
        /// Make sure the number of inputs is the number expected.
        /// </summary>
        /// <returns></returns>
        protected bool verifyInputCount()
        {
            if (InputCount != EXPECTED_SCALAR_INPUTS)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Expected {0} inputs for {1} interactor, please check the mdf file.",
                    EXPECTED_SCALAR_INPUTS,
                    NameString);
                return false;
            }
            return true;
        }

        /// <summary>
        /// Adjusts the dimensionality of all outputs for
        /// this->doDimensionalityChange().
        /// </summary>
        /// <param name="old_dim"></param>
        /// <param name="new_dim"></param>
        /// <returns></returns>
        protected virtual bool adjustOutputDimensions(int old_dim, int new_dim)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// Global flag for all interactor instances indicating whether or not to 
        /// do continuous updates to the exec.
        /// </summary>
        protected bool isContinuousUpdate;

        protected bool cfgParseComponentComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected override bool cfgParseInstanceComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected override bool cfgPrintInteractorComment(System.IO.StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgPrintInteractorComment(sw);
        }
        protected override bool cfgPrintInteractorAuxInfo(System.IO.StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgPrintInteractorAuxInfo(sw);
        }
        protected override bool cfgPrintInstanceAuxInfo(System.IO.StreamWriter sw, InteractorInstance ii)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgPrintInstanceAuxInfo(sw, ii);
        }

        protected override InteractorInstance newInteractorInstance()
        {
            throw new Exception("Not Yet Implemented");
            return base.newInteractorInstance();
        }

        protected bool cfgParseLocalIncrementComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected bool cfgParseLocalContinuousComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// The messages we deal with can contain one or more of the following...
        ///
        /// 'min=%g' 'max=%g' 'delta=%g' 'value=%g' 'decimals=%d'
        ///
        ///  or one or more of the following...
        ///
        /// 'min=[%g %g %g]' 'max=[%g %g %g]' 'delta=[%g %g %g]' 'value=[%g %g %g]'
        /// 'decimals=[%g %g %g]'
        /// </summary>
        /// <param name="line"></param>
        /// <returns>number of attributes parsed</returns>
        protected override int handleInteractorMsgInfo(string line)
        {
            int values;
            if (IsVectorType)
                values = handleVectorMsgInfo(line);
            else
                values = handleScalarMsgInfo(line);

            // Handle the 'method="%s"' part of the message.
            // We only need to look for the message if we don't already have it.
            if (isInputConnected((int)Params.INCRMETHOD))
            {
                if (line.Contains("method="))
                {
                    Regex regex = new Regex("method=\"(.*)\"");
                    Match m = regex.Match(line);
                    if (m.Success)
                    {
                        values++;
                        setInputAttributeFromServer((int)Params.INCRMETHOD, m.Groups[1].Value,
                            DXTypeVals.StringType);
                    }
                }
            }

            // Make sure that the min or max sent back from the executive is 
            // consistent.  If the user has not connected the data tab and has
            // only one of min and max set then it is possible that the value sent
            // back by the module conflicts with the other value stored in the ui. 

            if (!isInputDefaulting((int)Params.DATA))
            {
                bool min_dflting = isInputDefaulting((int)Params.MIN);
                bool max_dflting = isInputDefaulting((int)Params.MAX);
                if ((min_dflting && !max_dflting) || (!min_dflting && max_dflting))
                {
                    int comps = getComponentCount();
                    bool issue_warning = false;
                    for (int i = 1; i <= comps; i++)
                    {
                        double minval = getComponentMinimum(i);
                        double maxval = getComponentMaximum(i);
                        if (minval > maxval)
                        {
                            issue_warning = true;
                            if (min_dflting)
                                setComponentMinimum(i, maxval);
                            else
                                setComponentMaximum(i, minval);
                        }
                    }
                    if (issue_warning)
                    {
                        String set, setattr;
                        if (min_dflting)
                        {
                            set = "maximum";
                            setattr = "minimum";
                        }
                        else
                        {
                            set = "minimum";
                            setattr = "maximum";
                        }
                        WarningDialog wd = new WarningDialog();
                        wd.post("{0} value provided to {1} conflicts with {2} value set with " +
                            "'Set Attributes' dialog ...adjusting {2}.", set, NameString,
                            setattr);
                    }
                }
            }
            return values;
        }

        /// <summary>
        /// Handles...
        /// 'min=%g' 'max=%g' 'delta=%g' 'value=%g' 'decimals=%d'
        /// </summary>
        /// <param name="line"></param>
        /// <returns></returns>
        protected int handleScalarMsgInfo(String line)
        {
            int values = 0;

            // Handle the 'min=%g' part of the message.
            Regex regex = new Regex(@"min=(" + Scanning.Scanner.DoublePattern + ")");
            Match m = regex.Match(line);
            if (m.Success)
            {
                values++;
                setInputAttributeFromServer((int)Params.MIN, m.Groups[1].Value, DXTypeVals.UndefinedType);
            }

            // Handle the 'max=%g' part of the message.
            regex = new Regex(@"max=(" + Scanning.Scanner.DoublePattern + ")");
            m = regex.Match(line);
            if (m.Success)
            {
                values++;
                setInputAttributeFromServer((int)Params.MAX, m.Groups[1].Value, DXTypeVals.UndefinedType);
            }

            // Handle the 'delta=%g' part of the message.
            // Since the attribute and parameter value have the same type, but
            // different meanings we only set the attribute value as received from
            // the exec.
            regex = new Regex(@"decimals=(" + Scanning.Scanner.DoublePattern + ")");
            m = regex.Match(line);
            if (m.Success)
            {
                values++;
                setInputAttributeFromServer((int)Params.DECIMALS, m.Groups[1].Value, DXTypeVals.UndefinedType);
            }

            // Handle the 'value=%g' part of the message.
            regex = new Regex(@"value=(" + Scanning.Scanner.DoublePattern + ")");
            m = regex.Match(line);
            if (m.Success)
            {
                values++;
                setShadowedOutputSentFromServer(1, m.Groups[1].Value, DXTypeVals.UndefinedType);
            }

            return values;
        }

        /// <summary>
        /// Handles...
        /// 'dim=%d'
        /// 'min=[%g %g %g]' 'max=[%g %g %g]' 'delta=[%g %g %g]' 'value=[%g %g %g]'
        /// 'decimals=[%g %g %g]'
        /// </summary>
        /// <param name="line"></param>
        /// <returns></returns>
        protected int handleVectorMsgInfo(String line)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Set the interactor's default attributes (attributes that can
        /// be shared by derived classes).
        /// </summary>
        /// <returns></returns>
        protected virtual bool setDefaultAttributes()
        {
            String min = null, max = null, incr = null, decimals= null;
            switch (numComponents)
            {
                case 1:
                    if (IsVectorType)
                    {
                        min = "[ -1000000 ]";
                        max = "[ 1000000 ]";
                        incr = "[ 1 ]";
                        decimals = (isIntegerTypeComponent() ? "[0]" : "[5]");
                    }
                    else
                    {
                        min = "-1000000";
                        max = "1000000";
                        incr = "1";
                        decimals = (isIntegerTypeComponent() ? "0" : "5");
                    }
                    break;
                case 2:
                    min = "[ -1000000 -1000000 ]";
                    max = "[  1000000  100000 ]";
                    incr = "[ 1 1 ]";
                    decimals = "[ 5 5 ]";
                    break;
                case 3:
                    min = "[ -1000000 -1000000 -1000000 ]";
                    max = "[  1000000  1000000  1000000 ]";
                    incr = "[ 1 1 1 ]";
                    decimals = "[ 5 5 5 ]";
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }

            String id = getModuleMessageIdString();

            if ((setInputValue((int)Params.ID, id, DXTypeVals.UndefinedType, false) ==
                DXTypeVals.UndefinedType) ||
                !initMinimumAttribute(min) ||
                !initMaximumAttribute(max) ||
                !initDeltaAttribute(incr) ||
                !initDecimalsAttribute(decimals))
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// Get and set the USUALLY global component values.  In some cases
        /// (i.e. ScalarListNode), the component values are saved with the 
        /// InteractorInstance.  So we make these protected and only allow
        /// the ScalarInstance class to access them.
        /// </summary>
        /// <param name="component"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        protected bool setComponentValue(int component, double value)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected double getComponentValue(int component)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// Do what ever is necessary when the given component of the output 
        /// value is out of range as indicated by the limits.  Typically, this just 
        /// means resetting the current output value that is associated with the 
        /// node.  ScalarListNodes however, have the current (non-output) value 
        /// associated with the interactor instance. Therefore, ScalarListNodes, 
        /// re-implement this to reset the component values of all their instances.
        /// If 'component' is less than 0, then min/max are ignored and all 
        /// components are checked with the current min/max values.
        /// </summary>
        /// <param name="component"></param>
        /// <param name="min"></param>
        /// <param name="max"></param>
        protected virtual void doRangeCheckComponentValue(int component,
            double min, double max)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Call doRangeCheckComponentValue() if range checking is not deferred.
        /// </summary>
        /// <param name="component"></param>
        /// <param name="min"></param>
        /// <param name="max"></param>
        protected void rangeCheckComponentValue(int component, double min, double max)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Provide methods to delay doRangeCheckComponentValue().
        /// </summary>
        /// <returns></returns>
        protected bool isRangeCheckingDeferred()
        {
            return rangeCheckDeferrals != 0;
        }
        protected void deferRangeChecking() { rangeCheckDeferrals++; }
        protected void undeferRangeChecking()
        {
            Debug.Assert(rangeCheckDeferrals > 0);
            if (--rangeCheckDeferrals == 0 && needsRangeCheck)
                rangeCheckComponentValue(-1, 0.0, 0.0);
        }

        protected bool initMinimumAttribute(String val)
        {
            AttributeParameter p = (AttributeParameter)getInputParameter((int)Params.MIN);
            return p.initAttributeValue(val);
        }
        protected bool setMinimumAttribute(String val)
        {
            AttributeParameter p = (AttributeParameter)getInputParameter((int)Params.MIN);
            return p.setAttributeValue(val);
        }
        protected bool initMaximumAttribute(String val)
        {
            AttributeParameter p = (AttributeParameter)getInputParameter((int)Params.MAX);
            return p.initAttributeValue(val);
        }
        protected bool setMaximumAttribute(String val)
        {
            AttributeParameter p = (AttributeParameter)getInputParameter((int)Params.MAX);
            return p.setAttributeValue(val);
        }
        protected bool initDeltaAttribute(String val)
        {
            AttributeParameter p = (AttributeParameter)getInputParameter((int)Params.INCR);
            return p.initAttributeValue(val);
        }
        protected bool setDeltaAttribute(String val)
        {
            AttributeParameter p = (AttributeParameter)getInputParameter((int)Params.INCR);
            return p.setAttributeValue(val);
        }
        protected bool initDecimalsAttribute(String val)
        {
            AttributeParameter p = (AttributeParameter)getInputParameter((int)Params.DECIMALS);
            return p.initAttributeValue(val);
        }
        protected bool setDecimalsAttribute(String val)
        {
            AttributeParameter p = (AttributeParameter)getInputParameter((int)Params.DECIMALS);
            return p.setAttributeValue(val);
        }

        protected override bool doDimensionalityChange(int new_dim)
        {
            throw new Exception("Not Yet Implemented");
            return base.doDimensionalityChange(new_dim);
        }

        public ScalarNode(NodeDefinition nd, Network net, int instnc /*, false, 1 */)
            : 
            base(nd, net, instnc)
        {
            isContinuousUpdate = false;
            vectorType = false;
            numComponents = 1;
            rangeCheckDeferrals = 0;
            needsRangeCheck = false;

            if (verifyInputCount())
                return;

            AttributeParameter ap = (AttributeParameter) getInputParameter((int)Params.INCR);
            Debug.Assert(ap != null);
            ap.setSyncOnTypeMatch(false);
        }
        public ScalarNode(NodeDefinition nd, Network net, int instnc, bool isVector, int dimensions)
            :
            base(nd, net, instnc)
        {
            Debug.Assert(dimensions > 0);
            isContinuousUpdate = false;
            vectorType = isVector;
            numComponents = dimensions;
            rangeCheckDeferrals = 0;
            needsRangeCheck = false;

            if (verifyInputCount())
                return;

            AttributeParameter ap = (AttributeParameter)getInputParameter((int)Params.INCR);
            Debug.Assert(ap != null);
            ap.setSyncOnTypeMatch(false);
        }

        public bool setAllComponentRanges(double min, double max)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool setComponentMinimum(int component, double min)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool setComponentMaximum(int component, double max)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool setComponentDelta(int component, double delta)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool setComponentDecimals(int component, int decimals)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setContinuous(bool val) { isContinuousUpdate = val; }
        public void setContinuous() { isContinuousUpdate = true; }
        public void clrContinuous() { isContinuousUpdate = false; }


        public double getComponentMinimum(int component) { throw new Exception("Not Yet Implemented"); }
        public double getComponentMaximum(int component) { throw new Exception("Not Yet Implemented"); }
        public double getComponentDelta(int component) { throw new Exception("Not Yet Implemented"); }
        public int getComponentDecimals(int component) { throw new Exception("Not Yet Implemented"); }
        public bool isIntegerTypeComponent()
        {
            if (NameString.Contains("Integer"))
                return true;
            else
                return false;
        }
        public bool IsContinuous { get { return isContinuousUpdate; } }
        public bool IsVectorType { get { return vectorType; } }

        public override bool initialize()
        {
            throw new Exception("Not Yet Implemented");
            return base.initialize();
        }

        public override bool hasRemappableOutput()
        {
            throw new Exception("Not Yet Implemented");
            return base.hasRemappableOutput();
        }

        /// <summary>
        /// Call the super class method, but then catch the output comment 
        /// to determine the number of components.  
        /// We need to do this when we have a 2d vector and no .cfg file to
        /// tell us so.  We then get numComponent==3, but all the parameter
        /// values are 2d, which results in an ASSERTion failure.
        /// </summary>
        /// <param name="comment"></param>
        /// <param name="file"></param>
        /// <param name="lineno"></param>
        /// <returns></returns>
        public override bool netParseComment(string comment, string file, int lineno)
        {
            bool r = base.netParseComment(comment, file, lineno);
            if (r && comment.StartsWith(" output["))
            {
                Parameter p = getOutputParameter(1);
                numComponents = p.getComponentCount();
            }
            return r;
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

        public override bool hasDynamicDimensionality()
        {
            throw new Exception("Not Yet Implemented");
            return base.hasDynamicDimensionality();
        }

        public override bool isA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
            return base.isA(classname);
        }

        public bool isMinimumVisuallyWriteable()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool isMaximumVisuallyWriteable()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool isDecimalsVisuallyWriteable()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool isDeltaVisaullyWriteable()
        {
            throw new Exception("Not Yet Implemented");
        }

        public override bool printAsJava(System.IO.StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
            return base.printAsJava(sw);
        }

        public override string getJavaNodeName()
        {
            return "ScalarNode";
        }

    }
}
