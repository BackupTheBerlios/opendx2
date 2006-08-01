using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    class ScalarListNode : ScalarNode
    {
        protected override bool adjustOutputDimensions(int old_dim, int new_dim)
        {
            throw new Exception("Not Yet Implemented");
            return base.adjustOutputDimensions(old_dim, new_dim);
        }

        protected override InteractorInstance newInteractorInstance()
        {
            throw new Exception("Not Yet Implemented");
            return base.newInteractorInstance();
        }

        protected override int handleInteractorMsgInfo(string line)
        {
            int values = base.handleInteractorMsgInfo(line);

            if (IsVectorType)
                values += handleVectorListMsgInfo(line);
            else
                values += handleScalarListMsgInfo(line);

            return values;
        }

        /// <summary>
        /// Handle
        ///
        ///              'list={%g, %g...}'
        /// </summary>
        /// <param name="line"></param>
        /// <returns>the number of tokens handled</returns>
        protected int handleScalarListMsgInfo(String line)
        {
            int values = 0;
            Regex regex = new Regex(@"list=\{([^\}]*)\}");
            Match m = regex.Match(line);

            if (m.Success)
            {
                values++;
                setShadowedOutputSentFromServer(1, m.Groups[1].Value, DXTypeVals.UndefinedType);
            }
            else if (line.Contains("list="))
            {
                values++;
                setShadowedOutputSentFromServer(1, "NULL", DXTypeVals.UndefinedType);
            }
            return values;
        }

        /// <summary>
        /// Handle the vector list message
        ///
        ///              'list={ [ %g %g ... ], ...}'
        /// </summary>
        /// <param name="line"></param>
        /// <returns>the number of tokens handled.</returns>
        protected int handleVectorListMsgInfo(String line)
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
        protected override void doRangeCheckComponentValue(int component, double min, double max)
        {
            throw new Exception("Not Yet Implemented");
            base.doRangeCheckComponentValue(component, min, max);
        }

        public ScalarListNode(NodeDefinition nd, Network net, int instnc,
            bool isvector, int dimensions)
            : base(nd, net, instnc, isvector, dimensions)
        { }

        public override bool initialize()
        {
            if (!verifyInputCount())
                return false;

            String value = null;
            switch (numComponents)
            {
                case 1: if (IsVectorType)
                        value = "{ [ 0 ] }";
                    else
                        value = "{ 0 }";
                    break;
                case 2: value = "{ [ 0 0 ] }"; break;
                case 3: value = "{ [ 0 0 0 ] }"; break;
                default: Debug.Assert(false); break;
            }
            if ((setOutputValue(1, value, DXTypeVals.UndefinedType, false) ==
                DXTypeVals.UndefinedType) ||
                !setDefaultAttributes())
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Error setting default attributes for {0} interactor, check ui.mdf",
                    NameString);
                return false;
            }

            // Make the shadows defaulting (even though we have a current output)
            // so that the executive module can tell when it is executing a just
            // placed module and one that is read in from a .net or .cfg file.
            // When read in, the output will be set again which should make the
            // corresponding shadowing input be non-defaulting.
            setShadowingInputsDefaulting();
            return true;
        }

        public override bool isA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
            return base.isA(classname);
        }
    }
}
