using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class AttributeParameter : BinaryParameter
    {
        protected Node node;
        protected int index;
        protected bool syncOnTypeMatch;

        public AttributeParameter(ParameterDefinition pd, Node n, int index)
            :
            base(pd)
        {
            set2ndValue("NULL");
            node = n;
            this.index = index;
            syncOnTypeMatch = true;
        }

        /// <summary>
        /// Copy the parameter value into the Attribute value.
        /// </summary>
        /// <returns></returns>
        public bool syncAttributeValue()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Make sure that the primary parameter has the same value as the
        /// attribute when appropriate.  Appropriate is defined as the primary
        /// parameter having a value and a type which is the same as the attribute's.
        /// </summary>
        /// <returns></returns>
        public bool syncPrimaryValue() { return syncPrimaryValue(false); }
        public bool syncPrimaryValue(bool force)
        {
            if (force || syncOnTypeMatch)
            {
                DXTypeVals t = get2ndValueType();
                if (force || (HasValue && ValueType == t))
                {
                    Debug.Assert(IsInput);
                    String v = get2ndValueString();
                    return node.setInputSetValue(index, v, t, false) !=
                        DXTypeVals.UndefinedType;
                }
            }
            return true;
        }

        public void setSyncOnTypeMatch() { setSyncOnTypeMatch(true); }
        public void setSyncOnTypeMatch(bool v)
        {
            syncOnTypeMatch = v;
        }

        /// <summary>
        /// Determine if the attribute that shadows this parameter is writeable.
        /// Attributes are writeable if the primary parameter is not connected
        /// and (the primary parameter is defaulting or the value has the same 
        /// type as the attribute value.
        /// </summary>
        /// <returns></returns>
        public bool isAttributeVisuallyWriteable()
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool setAttributeValue(String val) { return setAttributeValue(val, false); }
        public bool setAttributeValue(String val, bool force)
        {
            return set2ndValue(val) != DXTypeVals.UndefinedType &&
                syncPrimaryValue(force);
        }

        public bool initAttributeValue(String val)
        {
            return set2ndValue(val) != DXTypeVals.UndefinedType &&
                syncPrimaryValue(true);
        }

        public String getAttributeValueString()
        {
            Debug.Assert(Has2ndValue);
            return get2ndValueString();
        }

        public DXTypeVals getAttributeValueType()
        {
            Debug.Assert(Has2ndValue);
            return get2ndValueType();
        }

        public bool setAttributeComponentValue(int index, double value)
        {
            return set2ndComponentValue(index, value) && syncPrimaryValue();
        }

        public double getAttributeComponentValue(int index)
        {
            Debug.Assert(Has2ndValue);
            return get2ndComponentValue(index);
        }

        public int getAttributeComponentCount()
        {
            return (Has2ndValue ? get2ndComponentCount() : 0);
        }

        public override bool IsA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
        }

    }
}
