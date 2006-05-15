using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class BinaryParameter : Parameter
    {
        private Parameter secondValue;

        public BinaryParameter(ParameterDefinition pd)
            : base(pd)
        {
            secondValue = new Parameter(pd);
        }

        public DXTypeVals set2ndValue(String v)
        {
            return this.secondValue.setValue(v);
        }

        // Manipulate the Value and definition
        public bool set2ndValue(String v, DXTypeVals t)
        {
            return set2ndValue(v, t, true);
        }
        public bool set2ndValue(String v, DXTypeVals t, bool coerce)
        {
            return this.secondValue.setValue(v, t, coerce);
        }

        /// <summary>
        /// Set the stored value. IF the parameter is not defaulting, this is
        /// the same as setValue, but if it is defaulting, then we set the
        /// value but leave the parameter clean and defaulting.
        /// </summary>
        /// <param name="v"></param>
        /// <param name="t"></param>
        /// <returns></returns>
        public bool set2ndSetValue(String v, DXTypeVals t)
        {
            return this.secondValue.setSetValue(v, t);
        }

        public bool Has2ndValue
        {
            get { return this.secondValue.HasValue; }
        }

        public DXTypeVals get2ndValueType()
        {
            return this.secondValue.ValueType;
        }

        public String get2ndSetValueString()
        {
            return this.secondValue.getSetValueString();
        }

        public String get2ndValueString()
        {
            return this.secondValue.getValueString();
        }

        public String get2ndValueOrDefaultString()
        {
            return this.secondValue.getValueOrDefaultString();
        }

        /// <summary>
        /// Get the i'th component of a vector value.
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        public double get2ndVectorComponentValue(int index)
        {
            return this.secondValue.getVectorComponentValue(index);
        }

        /// <summary>
        /// Get the floating point value of a scalar
        /// </summary>
        /// <returns></returns>
        public double get2ndScalarValue()
        {
            return this.secondValue.getScalarValue();
        }

        /// <summary>
        /// Get the value of an integer... 
        /// </summary>
        /// <returns></returns>
        public int get2ndIntegerValue()
        { 
            return this.secondValue.getIntegerValue(); 
        }

        //
        // These methods are somewhat of a hack, but at least they belong here and
        // not in ScalarNode.C which is what uses them (for now anyway).
        //
        // G/Set the n'th component of a vector, scalar or integer.  For scalars
        // and integers, the component number must be 1.
        // Components are indexed from 1.
        //
        public double get2ndComponentValue(int component)
        { 
            return this.secondValue.getComponentValue(component); 
        }
        public bool set2ndComponentValue(int component, double val)
        { 
            return this.secondValue.setComponentValue(component, val); 
        }
        public int get2ndComponentCount()
        { 
            return this.secondValue.getComponentCount(); 
        }

        
    }
}
