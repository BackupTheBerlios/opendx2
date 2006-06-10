//Completed 4/24/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    public class ParameterDefinition : Definition
    {
        private List<DXType> types = new List<DXType>();
        private String[] typeStrings; // If !null, contains type names
        private String description;
        private String default_value;
        private bool viewable;
        private bool required;
        private bool default_visibility;
        private bool descriptive_default;
        private bool is_input; // Does this define an input or output
        private bool dummy; // Is this a dummy parameter
        private String[] valueOptions;

        public List<DXType> DXTypes { get { return types; } }

        private readonly String DUMMY_DESCRIPTION_STRING =
            "<<< Dummy parameter (do not edit) >>>";

        //
        // The following is only valid for inputs and when the value is >= 0.
        // It indicates the output to which this input is rerouted when the
        // executive decides not to schedule the module owning the input.
        // Currenlty, we only keep track of it so we can send it to the 
        // executive if the input belongs to an OUTBOARD module.
        //
        private int rerouteOutput;

        //
        // Cacheability status of parameter.  
        // Initially used for outputs only.
        //
        private Cacheability defaultCacheability;
        private bool writeableCacheability;

        private void buildTypeStrings()
        {
            Debug.Assert(types.Count > 0);
            Debug.Assert(typeStrings == null);

            typeStrings = new String[types.Count + 1];
            for (int i = 0; i < types.Count; i++)
            {
                typeStrings[i] = types[i].getName();
                Debug.Assert(typeStrings[i] != null);
            }
            typeStrings[types.Count] = null;
        }


        public ParameterDefinition(Symbol key)
            : base(key)
        {
            description = null;
            typeStrings = null;
            descriptive_default = false;
            default_value = null;
            is_input = false;
            required = false;
            default_visibility = true;
            viewable = true;
            Debug.Assert(Cacheability.OutputFullyCached == Cacheability.InputDerivesOutputCacheTag);
            defaultCacheability = Cacheability.OutputFullyCached;
            writeableCacheability = true;
            rerouteOutput = -1;
            dummy = false;
            valueOptions = null;
        }

        /// <summary>
        /// Append the given type t to the list of acceptable types for this
        /// parameter definition.  The given type is then owned by the 
        /// ParameterDefinition and will be deleted when it is deleted.
        /// </summary>
        /// <param name="t"></param>
        /// <returns></returns>
        public bool addType(DXType t)
        {
            if (typeStrings != null)
                typeStrings = null;

            if (types == null)
                return false;

            types.Add(t);
            return true;
        }

        /// <summary>
        /// Remove (and free) the type in the list that matches t
        /// </summary>
        /// <param name="t"></param>
        /// <returns></returns>
        public bool removeType(DXType t)
        {
            if (typeStrings != null)
                typeStrings = null;

            foreach (DXType dxtype in types)
            {
                if (dxtype.getType() == t.getType())
                {
                    bool r = this.types.Remove(dxtype);
                    Debug.Assert(r);
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// Manipulate the default visibility of the tab for this parameter
        /// </summary>
        /// <returns></returns>
        public void setDefaultVisibility()
        {
            setDefaultVisibility(true);
        }
        public void setDefaultVisibility(bool v)
        {
            default_visibility = v;
        }

        public bool DefaultVisibility
        {
            get { return default_visibility; }
        }

        /// <summary>
        /// S/Get the 1 based index of the output to which this input can be
        /// be rerouted.
        /// </summary>
        /// <param name="val"></param>
        public void setRerouteOutput(int val)
        {
            Debug.Assert(val > 0 && IsInput);
            rerouteOutput = val;
        }
        public int RerouteOutput
        {
            get { Debug.Assert(IsInput); return rerouteOutput; }
        }

        /// <summary>
        /// Manipulate the viewability of the tab for this parameter
        /// </summary>
        /// <param name="v"></param>
        public void setViewability(bool v)
        {
            viewable = v;
            if (!v)
                default_visibility = false;
        }

        public bool IsViewable
        {
            get { return viewable; }
        }

        /// <summary>
        /// Retrieves an array of strings.
        /// Each string contains the name of a type that this parameter 
        /// can accept.  
        /// </summary>
        /// <returns></returns>
        public String[] getTypeStrings()
        {
            if (typeStrings == null)
                buildTypeStrings();
            Debug.Assert(typeStrings != null);
            return typeStrings;
        }

        public List<DXType> getTypes() { return types; }

        // Manipulate the type of I/O this paramenter definition represents.
        public void markAsInput() { is_input = true; }
        public void markAsOutput() { is_input = false; }
        public bool IsInput
        {
            get { return is_input; }
        }
        public bool IsOutput
        {
            get { return !is_input; }
        }

        // Change the Description of the this parameter
        public void setDescription(String d)
        {
            description = d;
        }
        public String Description
        {
            get
            {
                if (dummy)
                    return DUMMY_DESCRIPTION_STRING;
                else
                    return description;
            }
        }

        // Change need for this parameter
        public bool IsRequired
        {
            get { return required; }
        }
        public void setRequired()
        {
            required = true;
        }
        public void setNotRequired()
        {
            required = false;
        }

        // Set/Get the default value, which must be of a type found in the type list.
        public bool IsDefaultValue
        {
            get { return descriptive_default == false; }
        }
        public bool setDefaultValue(String value)
        {
            List<DXType.DXTypeName> typelist = new List<DXType.DXTypeName>();
            if (value != null && DXType.ValueToType(value, ref typelist) == false)
                return false;

            descriptive_default = false;
            default_value = value;
            return true;
        }
        public String DefaultValue
        {
            get { return default_value; }
        }

        /// <summary>
        /// Get the default type of this parameter.  When a parameter has more
        /// than 1 type, always return the first type on the type list.
        /// </summary>
        /// <returns></returns>
        public DXTypeVals getDefaultType()
        {
            DXType dxtype;
            DXTypeVals type;

            dxtype = this.types[0];
            type = dxtype.getType();
            return type;
        }

        // Set the default value, which must be of a type found in the type list.
        public bool DefaultDescriptive
        {
            get { return descriptive_default; }
        }
        public void setDescriptiveValue(String d)
        {
            default_value = d;
            descriptive_default = true;
        }
        public void setWriteableCacheability(bool v)
        {
            writeableCacheability = v;
        }
        public bool HasWriteableCacheability
        {
            get { return writeableCacheability; }
        }
        public void setDefaultCacheability(Cacheability c)
        {
            defaultCacheability = c;
        }
        public Cacheability DefaultCacheability
        {
            get { return defaultCacheability; }
        }

        // Get the INPUT/OUTPUT entry in the MDF for this parameter.
        public String getMDFString()
        {
            int i, typecnt = getTypes().Count;
            String[] typeNames = getTypeStrings();
            String types = "";

            for (i = 0; i < typecnt; i++)
            {
                if (i + 1 == typecnt)
                    types += typeNames[i];
                else
                    types += typeNames[i] + " or ";
            }

            String name = NameString;
            String dflt = DefaultValue;
            String desc = Description;

            String attributes = "[";
            if (IsViewable)
            {
                attributes += "visible:2 ";
            }
            else if (DefaultVisibility == false)
            {
                attributes += "visible:0 ";
            }
            if (IsInput)
            {
                if (DefaultCacheability != Cacheability.InputDerivesOutputCacheTag)
                {
                    attributes += String.Format("cache:{0} ", (int)DefaultCacheability);
                }
                if (RerouteOutput > 0)
                {
                    attributes += String.Format("reroute:{0} ", RerouteOutput - 1);
                }
            }
            else if (DefaultCacheability != Cacheability.OutputFullyCached)
            {
                attributes += String.Format("cache:{0} ", (int)DefaultCacheability);
            }

            if (attributes.Length > 1)
                attributes += "]";
            else
                attributes = "";

            String mdf = "";
            if (IsInput)
                mdf = String.Format("INPUT {0} {1} ; {2} ; {3} ; {4}\n",
                    name,
                    attributes,
                    types,
                    (dflt != null && dflt != "NULL" ? dflt : ""),
                    (desc != null ? desc : ""));
            else
                mdf = String.Format("OUTPUT {0} {1} ; {2} ; {3}\n",
                    name,
                    attributes,
                    types,
                    (desc != null ? desc : ""));

            return mdf;
        }

        // Manage the dummy status of this parameter (typically a macro parameter)
        public void setDummy(bool b)
        {
            dummy = b;
        }
        public bool IsDummy
        {
            get { return dummy; }
        }

        // Make a brand new copy of this and return it.
        // If newpd is null, then the new ParamterDefinition is allocated.
        public ParameterDefinition duplicate()
        {
            return duplicate(null);
        }
        public ParameterDefinition duplicate(ParameterDefinition newpd)
        {
            if (newpd == null)
                newpd = new ParameterDefinition(NameSymbol);

            newpd.description = null;
            newpd.typeStrings = null;

            newpd.default_value = null;
            newpd.is_input = this.is_input;
            newpd.required = this.required;
            newpd.default_visibility = this.default_visibility;
            newpd.viewable = this.viewable;
            newpd.defaultCacheability = this.defaultCacheability;
            newpd.writeableCacheability = this.writeableCacheability;
            newpd.rerouteOutput = this.rerouteOutput;
            newpd.dummy = this.dummy;

            // Now reset everything that is owned by this parameter defn.
            newpd.setDescription(this.Description);
            if (IsDefaultValue)
                newpd.setDefaultValue(this.DefaultValue);
            else
                newpd.setDescriptiveValue(this.DefaultValue);

            foreach (DXType t in this.types)
            {
                DXType newt = t.duplicate();
                newpd.addType(newt);
            }
            return newpd;
        }

        /// <summary>
        /// Add the given value to the list of suggested values for this parameter
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public bool addValueOption(String value)
        {
            int position;

            if (valueOptions == null)
            {
                valueOptions = new String[1];
                valueOptions[0] = value;
            }
            else
            {
                position = valueOptions.Length;
                Array.Resize(ref valueOptions, position + 1);
                valueOptions[position] = value;
            }

            return true;
        }

        /// <summary>
        /// Get the selectable values for this parameter.
        /// </summary>
        /// <returns></returns>
        public String[] getValueOptions()
        {
            return valueOptions;
        }

        /// <summary>
        /// On behalf of MacroParameterNodes which ought to be able to
        /// take on new types during the running of dxui, permit the
        /// user to create new value options.
        /// </summary>
        public void removeValueOptions()
        {
            if (valueOptions != null)
            {
                for (int i = 0; i < valueOptions.Length; i++)
                    valueOptions[i] = null;
            }
            valueOptions = null;
        }


    }
}
