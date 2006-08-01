using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    public class MacroParameterNode : UniqueNameNode
    {
        /// <summary>
        /// Based on the node's connectivity, select values for OPTIONS
        /// automatically.  The strategy is
        /// - Try to keep the OPTIONS the node already has.
        /// - look for OPTIONS in the next connected downstream node(s)
        /// - for each value in OPTIONS, see if the value can be coerced
        ///   to our current type(s)
        /// - Prefer to use OPTIONS from the node at the other end of 
        ///   prefer because it's probably the node were adding via ::addIOArk().
        ///
        /// At this point in the code, our new list of types has already been
        /// computed based on our new connectivity.
        /// </summary>
        /// <param name="pref"></param>
        private void setTypeSafeOptions(Ark pref)
        {
            // This method is nonsense in the case of an Output tool.
            Debug.Assert(IsInput);

            // If we have OPTIONS && any item in OPTION is illegal input given
            // our new type, then remove all the OPTIONS.
            ParameterDefinition macroPd = getParameterDefinition();
            String[] options = macroPd.getValueOptions();
            List<DXType> types = macroPd.getTypes();
            bool can_coerce = true;
            if (options != null && options.Length > 0)
            {
                can_coerce = true;
                for (int i = 0; i < options.Length && can_coerce; i++)
                {
                    can_coerce = can_coerce && canCoerceValue(options[i], types);
                }
                if (!can_coerce)
                {
                    macroPd.removeValueOptions();
                    options = null;
                }
            }

            //If our current OPTIONS are safe to keep using...
            if (options != null && options.Length > 0)
                return;

            // If the parameter has no option values, then check each downstream
            // input tab.  If any has option values, then try to use those but
            // only if each of the option values is legal given our new type.
            Node destination;
            NodeDefinition destinationDef;
            ParameterDefinition destinationParamDef;
            int paramIndex;

            // First check the new ark to see if it gave give us
            // option values.  option strings are stored as a null-terminated
            // array of char*.
            String[] dest_option_values = null;
            can_coerce = true;
            if (pref != null)
            {
                destination = pref.getDestinationNode(out paramIndex);
                destinationDef = destination.Definition;
                destinationParamDef = destinationDef.getInputDefinition(paramIndex);
                dest_option_values = destinationParamDef.getValueOptions();

                if (dest_option_values != null && dest_option_values.Length > 0)
                {
                    for (int i = 0; i < dest_option_values.Length && can_coerce; i++)
                    {
                        can_coerce = can_coerce && canCoerceValue(dest_option_values[i], types);
                    }
                }
            }

            if (can_coerce && dest_option_values != null && dest_option_values.Length > 0)
            {
                for (int i = 0; i < dest_option_values.Length; i++)
                {
                    if (!macroPd.addValueOption(dest_option_values[i]))
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Cannot add {0} to Options values", dest_option_values[i]);
                        break;
                    }
                }
            }
            else
            {
                // get all the destination nodes  When we're called as via ::addIOArk(),
                // the new connection has not yet been added to our list
                // of downstream nodes.
                List<Ark> arks = getOutputArks(1);
                foreach (Ark ark in arks)
                {
                    destination = ark.getDestinationNode(out paramIndex);
                    destinationDef = destination.Definition;
                    destinationParamDef = destinationDef.getInputDefinition(paramIndex);

                    // for each option value see, see if it can be coerced.
                    dest_option_values = destinationParamDef.getValueOptions();
                    if (dest_option_values == null || dest_option_values.Length == 0) continue;

                    can_coerce = true;
                    for (int i = 0; i < dest_option_values.Length && can_coerce; i++)
                    {
                        can_coerce = can_coerce && canCoerceValue(dest_option_values[i], types);
                    }
                    if (can_coerce)
                    {
                        for (int i = 0; i < dest_option_values.Length; i++)
                        {
                            if (!macroPd.addValueOption(dest_option_values[i]))
                            {
                                ErrorDialog ed = new ErrorDialog();
                                ed.post("Cannot add {0} to Options values",
                                    dest_option_values[i]);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }

        private bool canCoerceValue(String option, List<DXType> types)
        {
            bool coerced = false;
            foreach (DXType dxtype in types)
            {
                String s = DXValue.CoerceValue(option, dxtype.getType());
                if (s != null)
                {
                    coerced = true;
                    break;
                }
            }
            return coerced;
        }

        protected int index;

        protected override bool netParseAuxComment(string comment, string filename, int lineno)
        {
            if (comment.StartsWith(" parameter: position = "))
            {
                String name, value, description;
                int pos, descriptive, required;
                bool visible;

                Regex regex = new Regex(@" parameter: position = (\d+), name = '([^']*)', value = '([^']*)', descriptive = (\d+), description = '([^']*)', required = (\d+), visible = (\d+)");
                Match m = regex.Match(comment);
                if (m.Success)
                {
                    pos = Int32.Parse(m.Groups[1].Value);
                    name = m.Groups[2].Value;
                    value = m.Groups[3].Value.Trim();
                    descriptive = Int32.Parse(m.Groups[4].Value);
                    description = m.Groups[5].Value;
                    required = Int32.Parse(m.Groups[6].Value);
                    visible = Int32.Parse(m.Groups[7].Value) == 1;
                }
                else
                {
                    regex = new Regex(@" position = (\d+), name = '([^']*)', value = '([^']*)', descriptive = (\d+), description = '([^']*)', required = (\d+)");
                    m = regex.Match(comment);
                    if (!m.Success)
                        return base.netParseAuxComment(comment, filename, lineno);
                    pos = Int32.Parse(m.Groups[1].Value);
                    name = m.Groups[2].Value;
                    value = m.Groups[3].Value.Trim();
                    descriptive = Int32.Parse(m.Groups[4].Value);
                    description = m.Groups[5].Value;
                    required = Int32.Parse(m.Groups[6].Value);
                    visible = true;
                }
                if (!getNetwork().IsMacro)
                    this.getNetwork().makeMacro(true);
                if (IsInput)
                {
                    moveIndex(pos);
                    ParameterDefinition pd = getParameterDefinition();
                    pd.setName(name);
                    pd.setDescription(description);
                    if (required > 0)
                        pd.setRequired();
                    else if (descriptive > 0)
                        pd.setDescriptiveValue(value);
                    else if (value == null || value.Length == 0)
                        pd.setDefaultValue("(no default)");
                    else
                        pd.setDefaultValue(value);
                    pd.setDefaultVisibility(visible);
                }
                else
                {
                    moveIndex(pos);
                    ParameterDefinition pd = getParameterDefinition();
                    pd.setName(name);
                    pd.setDescription(description);
                    pd.setDefaultVisibility(visible);
                }
                return true;
            }
            else
                return base.netParseAuxComment(comment, filename, lineno);
        }

        protected override string netNodeString(string prefix)
        {
            String str;
            ParameterDefinition param = getParameterDefinition();
            Debug.Assert(param != null);

            String name = param.NameString;
            if (IsInput)
            {
                Debug.Assert(OutputCount == 1);
                String outputs = outputParameterNamesString(prefix);
                str = outputs + " = " + name + ";\n";
            }
            else
            {
                Debug.Assert(InputCount == 1);
                String inputs = inputParameterNamesString(prefix);
                str = name + " = " + inputs + ";\n";
            }
            return str;
        }

        protected override bool netPrintAuxComment(System.IO.StreamWriter s)
        {
            throw new Exception("Not Yet Implemented");
            return base.netPrintAuxComment(s);
        }

        protected override bool addIOArk(List<Parameter> io, int index, Ark a)
        {
            List<DXType> newTypesList = null;
            if (IsInput)
            {
                int i;
                Node dest = a.getDestinationNode(out i);
                Parameter pin = dest.getInputParameter(i);
                ParameterDefinition pind = pin.Definition;

                ParameterDefinition macroPd = getParameterDefinition();
                List<DXType> outTypes = macroPd.getTypes();
                newTypesList = DXType.IntersectTypeLists(outTypes, pind.getTypes());
                foreach (DXType t in outTypes.ToArray())
                {
                    macroPd.removeType(t);
                }

                Parameter pout = getOutputParameter(1);
                ParameterDefinition nodePd = pout.Definition;
                outTypes = nodePd.getTypes();

                foreach (DXType t in outTypes.ToArray())
                {
                    nodePd.removeType(t);
                }

                foreach (DXType t in newTypesList.ToArray())
                {
                    DXType newt = t.duplicate();
                    nodePd.addType(newt);
                    macroPd.addType(t);
                }

                setTypeSafeOptions(a);
            }
            else
            {
                int i;
                Node dest = a.getSourceNode(out i);
                Parameter pin = dest.getOutputParameter(i);
                ParameterDefinition pind = pin.Definition;

                ParameterDefinition macroPd = getParameterDefinition();
                List<DXType> outTypes = macroPd.getTypes();
                newTypesList = DXType.IntersectTypeLists(outTypes, pind.getTypes());
                foreach (DXType t in outTypes.ToArray())
                {
                    macroPd.removeType(t);
                }

                Parameter pout = getInputParameter(1);
                ParameterDefinition nodePd = pout.Definition;
                outTypes = nodePd.getTypes();

                foreach (DXType t in outTypes.ToArray())
                {
                    nodePd.removeType(t);
                }

                foreach (DXType t in newTypesList.ToArray())
                {
                    DXType newt = t.duplicate();
                    nodePd.addType(newt);
                    macroPd.addType(t);
                }
            }

            if (getConfigurationDialog() != null)
            {
                getConfigurationDialog().changeInput(1);
                getConfigurationDialog().changeOutput(1);
            }

            return base.addIOArk(io, index, a);
        }

        protected override bool removeIOArk(List<Parameter> io, int index, Ark a)
        {
            throw new Exception("Not Yet Implemented");
            return base.removeIOArk(io, index, a);
        }

        public MacroParameterNode(NodeDefinition nd, Network net, int instnc)
            :
            base(nd, net, instnc)
        {
            index = -1;
        }
        ~MacroParameterNode()
        {
            Network net = getNetwork();
            MacroDefinition md = net.Definition;
            Parameter p;
            ParameterDefinition pd = getParameterDefinition();

            if (IsInput)
            {
                if (pd != null && !net.IsDeleted || net == DXApplication.theDXApplication.network)
                {
                    if (!net.IsDeleted)
                    {
                        if (this.index != net.getInputCount())
                        {
                            int newIndex = net.getInputCount() + 1;
                            moveIndex(newIndex, false);
                        }
                        else
                        {
                            for (int i = index; i > 1; --i)
                                if (!moveIndex(i - 1, false))
                                    break;
                        }
                    }
                    if (md != null) md.removeInput(pd);
                    pd = null;
                }
                p = getOutputParameter(1);
            }
            else
            {
                if (pd != null && !net.IsDeleted || net == DXApplication.theDXApplication.network)
                {
                    if (!net.IsDeleted)
                    {
                        if (index != net.getOutputCount())
                        {
                            int newIndex = net.getOutputCount() + 1;
                            moveIndex(newIndex, false);
                        }
                        else
                        {
                            for (int i = index; i > 1; --i)
                                if (!moveIndex(i - 1, false))
                                    break;
                        }
                    }
                    if (md != null) md.removeOutput(pd);
                    pd = null;
                }
                p = getInputParameter(1);
            }
            p = null;

            if (net == DXApplication.theDXApplication.network)
            {
                if (md != null && md.InputCount == 0 && md.OutputCount == 0)
                    net.makeMacro(false);
            }
        }

        public override bool initialize()
        {
            base.initialize();
            Network net = getNetwork();
            if (!net.IsMacro)
                net.makeMacro(true);
            MacroDefinition md = net.Definition;
            ParameterDefinition param = null;

            bool input = IsInput;
            if (!md.IsReadingNet)
            {
                param = new ParameterDefinition(Symbol.zero);
                param.addType(new DXType(DXTypeVals.ObjectType));
            }

            if (input)
            {
                if (!md.IsReadingNet)
                {
                    int n = md.getFirstAvailableInputPosition();
                    param.markAsInput();
                    if (n <= md.InputCount)
                    {
                        ParameterDefinition dummyPd = md.getInputDefinition(n);
                        Debug.Assert(dummyPd.IsDummy);
                        md.replaceInput(param, dummyPd);
                    }
                    else
                    {
                        md.addInput(param);
                    }
                    setIndex(n);
                    param.setName(String.Format("input_{0}", index));
                    param.setDefaultValue("(no default)");
                }
                // The Parameter  must have its own ParameterDefinition since
                // it may change depending upon what we are connected to.
                // FIXME: ParameterDefinition should have a dup() method.
                Parameter p = getOutputParameter(1);
                ParameterDefinition pd = p.Definition;
                ParameterDefinition newpd = pd.duplicate();
                p.setDefinition(newpd);
            }
            else
            {
                if (!md.IsReadingNet)
                {
                    int n = md.getFirstAvailableOutputPosition();
                    param.markAsOutput();
                    if (n <= md.OutputCount)
                    {
                        ParameterDefinition dummyPd = md.getOutputDefinition(n);
                        Debug.Assert(dummyPd.IsDummy);
                        md.replaceOutput(param, dummyPd);
                    }
                    else
                    {
                        md.addOutput(param);
                    }
                    setIndex(n);
                    param.setName(String.Format("output_{0}", index));
                    param.setDefaultValue("(no default)");
                }
                Parameter p = getInputParameter(1);
                ParameterDefinition pd = p.Definition;
                ParameterDefinition newpd = pd.duplicate();
                p.setDefinition(newpd);
            }
            return true;
        }

        // Match output_index of this node to input_index of n. Returns true
        // if they can connect.
        public override bool typeMatchOutputToInput(int output_index, Node n, int input_index)
        {
            Debug.Assert(output_index >= 1);
            Debug.Assert(input_index >= 1);

            List<DXType> tout = getOutputTypes(output_index);
            List<DXType> tin = n.getInputTypes(input_index);

            Debug.Assert(tout != null && tin != null);

            List<DXType> newTypesList = DXType.IntersectTypeLists(tin, tout);
            return (newTypesList != null && newTypesList.Count > 0);
        }

        public virtual String getParameterNameString()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual ParameterDefinition getParameterDefinition() { return getParameterDefinition(true); }
        public virtual ParameterDefinition getParameterDefinition(bool includeDummies)
        {
            MacroDefinition md = getNetwork().Definition;

            if (md == null)
                return null;

            int idx = getIndex();
            if (idx <= 0)
                return null;

            if (IsInput)
            {
                Debug.Assert(isInputRepeatable() == false);
                if (idx > md.InputCount)
                    return null;
            }
            else
            {
                Debug.Assert(isOutputRepeatable() == false);
                if (idx > md.OutputCount)
                    return null;
            }

            ParameterDefinition pd;
            if (IsInput)
            {
                if (includeDummies)
                    pd = md.getInputDefinition(idx);
                else
                    pd = md.getNonDummyInputDefinition(idx);
            }
            else
            {
                if (includeDummies)
                    pd = md.getOutputDefinition(idx);
                else
                    pd = md.getNonDummyOutputDefinition(idx);
            }
            return pd;
        }

        public virtual void setIndex(int index)
        {
            this.index = index;
        }
        public virtual int getIndex()
        {
            return index;
        }
        public virtual bool moveIndex(int index) { return moveIndex(index, true); }
        public virtual bool moveIndex(int index, bool issue_error)
        {
            if (index == this.index)
                return true;
            if (this.index == -1)
            {
                setIndex(index);
                return true;
            }
            bool result;
            if (IsInput)
                result = getNetwork().moveInputPosition(this, index);
            else
                result = getNetwork().moveOutputPosition(this, index);
            if (result)
                setIndex(index);
            else if (issue_error)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Cannot move {0} {1} to {2}, it would overwrite another {3}.",
                    NameString, this.index, index, NameString);
            }
            if (getConfigurationDialog() != null)
            {
                if (IsInput)
                    getConfigurationDialog().changeInput(1);
                else
                    getConfigurationDialog().changeOutput(1);
            }
            return result;
        }

        // Determine if this node an input or output
        // Should not be called until after initialization.
        public bool IsInput
        {
            get
            {
                return Definition.InputCount == 0;
            }
        }

        public override void switchNetwork(Network from, Network to, bool silently)
        {
            throw new Exception("Not Yet Implemented");
            base.switchNetwork(from, to, silently);
        }
        public override bool canSwitchNetwork(Network from, Network to)
        {
            throw new Exception("Not Yet Implemented");
            return base.canSwitchNetwork(from, to);
        }

        public virtual String getUniqueName()
        {
            throw new Exception("Not Yet Implemented");
        }

        // Determine if this node is a node of the given class
        public override bool isA(Symbol classname)
        {
            return base.isA(classname);
        }
    }
}
