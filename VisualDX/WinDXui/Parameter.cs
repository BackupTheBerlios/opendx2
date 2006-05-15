using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    public class Parameter
    {
        private ParameterDefinition definition;
        private DXValue value;
        private List<Ark> arcs;                     // List of parameters that where connected too
        private bool defaultingWhenUnconnected;     // Should we use the default value.
        private bool viewable;                      // Is this parameter's tab exposable.
        private bool visible;                       // Is this paramater's tab visible.
        private bool dirty;                         // Has parameter changed.

        // Valid for Outputs only. Indicates how the exec should cache an output.
        protected Cacheability cacheability;

        /// <summary>
        /// For the given type, try and augment the given string value with
        /// syntactic sugar to coerce the given value to the given type.
        /// The types we can coerce are StringType, ListType, VectorType and 
        /// TensorType.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="type"></param>
        /// <returns>t/f indicating whether the value was successfully set</returns>
        protected bool coerceAndSetValue(String value, DXTypeVals type)
        {
            throw new Exception("Not Yet Implemented");
        }

        public Parameter(ParameterDefinition pd)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool addArk(Ark a)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool removeArk(Ark a) { return arcs.Remove(a); }
        public Ark getArk(int i) { return arcs[i]; }
        public bool IsConnected { get { return arcs.Count > 0; } }

        // Manipulate the exposability and visibility
        public void setVisibility(bool v) { visible = (IsViewable && v); }
        public void setVisible() { visible = true; }
        public bool IsVisible { get { return visible; } }
        public bool IsVisibleByDefault
        {
            get
            {
                Debug.Assert(definition != null);
                return definition.DefaultVisibility;
            }
        }
        public void clearVisible() { visible = false; }
        bool IsViewable
        {
            get
            {
                Debug.Assert(definition != null);
                return definition.IsViewable;
            }
        }

        // Manipulate the Value and definition
        public void setDirty() { dirty = true; }
        public bool IsDirty { get { return dirty; } }
        public void clearDirty() { dirty = false; }
        public bool IsNeededValue() { return IsNeededValue(true); }
        public bool IsNeededValue(bool ignoreDirty)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool IsRequired { get { return definition.IsRequired; } }

        public bool IsInput { get { return definition.IsInput; } }
        public bool IsDefaulting { get { throw new Exception("Not Yet Implemented"); } }
        public void setUnconnectedDefaultingStatus() { setUnconnectedDefaultingStatus(true); }
        public void setUnconnectedDefaultingStatus(bool defaulting)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Set the value of this parameter to the value represented by v which 
        /// must match the given type.  If coerce is TRUE, then try and add
        /// syntactic sugar to make the value match the type.
        /// </summary>
        /// <param name="v"></param>
        /// <param name="t"></param>
        /// <param name="coerce"></param>
        /// <returns></returns>
        public bool setValue(String v, DXTypeVals t) { return setValue(v, t, true); }
        public bool setValue(String v, DXTypeVals t, bool coerce)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Use setValue(v,t,c) to try and set the value to one of the types.
        /// </summary>
        /// <param name="v"></param>
        /// <returns></returns>
        public DXTypeVals setValue(String v)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Uset setValue(v,t,c) to set the stored value.
        /// If the parameter is not defaulting, this is
        /// the same as setValue, but if it is defaulting, then we set the
        /// value but leave the parameter clean and defaulting.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        public bool setSetValue(String value, DXTypeVals type)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool HasValue
        {
            get
            {
                return (value != null && value.getType() != DXTypeVals.UndefinedType);
            }
        }
        public DXTypeVals ValueType
        {
            get
            {
                Debug.Assert(value != null);
                return value.getType();
            }
        }
        public void setDefinition(ParameterDefinition pd) { definition = pd; }
        public ParameterDefinition Definition { get { return this.definition; } }
        public String Description { get { return definition.Description; } }

        public String getSetValueString()
        {
            String s = "NULL";
            if (HasValue)
                s = value.getValueString();
            return s;
        }
        public String getValueString()
        {
            String s = "NULL";
            if (!IsDefaulting && value != null)
                s = value.getValueString();
            return s;
        }
        public String getValueOrDefaultString()
        {
            String s;
            if (!IsDefaulting && value != null)
                s = value.getValueString();
            else
                s = definition.DefaultValue;
            return s;
        }

        /// <summary>
        /// Get the default type of this parameter.  When a parameter has more
        /// than 1 type, always return the first type on the type list.
        /// </summary>
        /// <returns></returns>
        public DXTypeVals getDefaultType() { return definition.getDefaultType(); }

        /// <summary>
        /// Get the i'th component of a vector value.
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        public double getVectorComponentValue(int index)
        {
            Debug.Assert(value != null);
            return value.getVectorComponentValue(index);
        }

        /// <summary>
        /// Get the floating point value of a scalar
        /// </summary>
        /// <returns></returns>
        public double getScalarValue()
        {
            Debug.Assert(value != null);
            return value.getScalar();
        }

        /// <summary>
        /// Get the value of an integer
        /// </summary>
        /// <returns></returns>
        public int getIntegerValue()
        {
            Debug.Assert(value != null);
            return value.getInteger();
        }

        /// <summary>
        ///These methods are somewhat of a hack, but at least they belong here and
        /// not in ScalarNode.C which is what uses them (for now anyway).
        ///
        /// G/Set the n'th component of a vector, scalar or integer.  For scalars
        /// and integers, the component number must be 1.
        /// Components are indexed from 1. 
        /// </summary>
        /// <returns></returns>
        public int getComponentCount()
        {
            throw new Exception("Not Yet Implemented");
        }
        public double getComponentValue(int component)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool setComponentValue(int component, double val)
        {
            throw new Exception("Not Yet Implemented");
        }

        public String NameString { get { return definition.NameString; } }

        /// <summary>
        /// Get the list of allowed types for this parameter.
        /// </summary>
        /// <returns></returns>
        public String[] getTypeStrings() { return definition.getTypeStrings(); }

        /// <summary>
        /// Determine if this (input) and another parameter (output) are type 
        /// compatible. 
        /// </summary>
        /// <param name="src"></param>
        /// <returns></returns>
        public bool typeMatch(Parameter src)
        {
            return DXType.MatchTypeLists(src.definition.DXTypes, this.definition.DXTypes);
        }

        /// <summary>
        /// Inquire and change the cacheability of a parameter.  This (today) is
        /// only available for outputs.
        /// </summary>
        /// <returns></returns>
        public Cacheability getCacheability()
        {
            return cacheability;
        }

        public bool IsFullyCached { get { return cacheability == Cacheability.OutputFullyCached; } }
        public void setCacheability(Cacheability c)
        {
            Debug.Assert(IsInput);
            if (cacheability != c)
            {
                cacheability = c;
                setDirty();
            }
        }
        public bool HasWriteableCacheability { get { return definition.HasWriteableCacheability; } }
        public Cacheability DefaultCacheability { get { return definition.DefaultCacheability; } }

        public bool IsA(String classname)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool IsA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Remove all the Arks connected to this parameter.
        /// </summary>
        public void disconnectArks()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Get the selectable values for this parameter.
        /// </summary>
        /// <returns></returns>
        public String[] getValueOptions()
        {
            throw new Exception("Not Yet Implemented");
        }


    }
}
