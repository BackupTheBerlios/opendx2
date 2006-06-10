using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    class DXValue
    {
        protected DXType type = new DXType();
        protected bool defined;

        String str;
        int integer;
        double scalar;
        DXTensor tensor;

        /// <summary>
        /// Determines whether the specified string is a valid string value
        /// of the specified type (of DXType constant).
        /// </summary>
        /// <param name="str"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        public static bool IsValidValue(String str, DXType type)
        {
            Debug.Assert(str != null);
            return IsValidValue(str, type.getType());
        }
        public static bool IsValidValue(String str, DXTypeVals type)
        {
            bool result = false;
            int tuple = 0;

            if (str == null)
                return false;

            str = str.Trim();
            str = str.ToLower();

            if (str == "" || str == "null")
                result = true;

            else if (type == DXTypeVals.FlagType)
            {
                Regex r = new Regex(@"^(true|false|\d+)$");
                result = r.IsMatch(str);
            }
            else if (type == DXTypeVals.IntegerType)
            {
                Regex r = new Regex(@"^(\+|-)?\d+$");
                result = r.IsMatch(str);
            }
            else if (type == DXTypeVals.ScalarType)
            {
                Regex r = new Regex(@"^(\+|-)?(\d+\.\d*|\.\d+)([eE](\+|)?[0-9]+)?$");
                result = r.IsMatch(str);
            }
            else if (type == DXTypeVals.VectorType)
            {
                result = DXTensor.IsVector(str, ref tuple);
            }
            else if (type == DXTypeVals.TensorType)
            {
                result = DXTensor.IsTensor(str);
            }
            else if (type == DXTypeVals.ValueType)
            {
                DXTypeVals value_type = DXTypeVals.UndefinedType;
                result = IsValue(str, ref value_type);
            }
            else if (type == DXTypeVals.StringType)
            {
                Regex r = new Regex(@"^""[^""]*""$");
                result = r.IsMatch(str);
            }
            else if (type == DXTypeVals.ObjectType)
            {
                result = IsObject(str);
            }

            return result;
        }

        /// <summary>
        /// For the given type, try and augment the given string value with
        /// syntactic sugar to coerce the given value to the given type.
        /// The types we can coerce are StringType, ListType, VectorType and 
        /// TensorType.
        /// If the value is coerceable return a new string that does not need to
        /// be coerced to the given value, otherwise return NULL.
        /// On success, the returned string must be freed by the caller.
        /// </summary>
        /// <param name="val"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        public static String CoerceValue(String val, DXTypeVals type)
        {
            String s;
            bool failed = true;

            if (type == DXTypeVals.ValueType)
            {
                s = DXValue.CoerceValue(val, DXTypeVals.VectorType);
            }
            else
            {
                s = val.Trim();

                if ((type == DXTypeVals.StringType) || (type == DXTypeVals.WhereType))
                {
                    s = "\"" + s + "\"";
                }
                else if (type == DXTypeVals.ListType)
                {
                    s = "{" + s + "}";
                }
                else if (type == DXTypeVals.TensorType || type == DXTypeVals.VectorType)
                {
                    s = "[" + s + "]";
                }

                if (!DXValue.IsValidValue(s, type))
                    failed = true;
                else
                    failed = false;

                // Try and coerce a list with a single element (i.e. coerce both the
                // element and the overall value.
                if (failed && (long)(type & DXTypeVals.ListType) > 0)
                {
                    DXTypeVals basetype = type & DXTypeVals.ListTypeMask;
                    String p = DXValue.CoerceValue(val, basetype);
                    if (p != null)
                    {
                        String p2 = DXValue.CoerceValue(p, type);
                        if (p2 != null)
                        {
                            s = p2;
                            failed = false;
                        }
                    }
                }
                if (failed)
                {
                    s = null;
                }
            }
            return s;
        }

        /// <summary>
        /// Get the next item from a list of the given type.
        /// Currently, only ScalarListType, IntegerListType, VectorListType and
        /// StringListType are supported.
        /// Search for the item is started a s[*index], and upon a successfull,
        /// return *index is updated to point to the character not parsed as a list.
        /// item. If *index is less than zero then we parse the initial list 
        /// delimiter '{'.  If buf is provided (!NULL), then the list item is copied 
        /// into it otherwise a new string is allocated to hold the list item.  In 
        /// either case a pointer to the string holding the list item is returned .
        /// upon success.
        /// </summary>
        /// <param name="s"></param>
        /// <param name="index"></param>
        /// <param name="listtype"></param>
        /// <param name="buf"></param>
        /// <returns></returns>
        public static String NextListItem(String s, ref int index, DXTypeVals listtype,
            ref String buf) { throw new Exception("Not yet implemented"); }
        public static String NextListItem(String s, ref int index, DXTypeVals listtype)
        {
            String tmp = null;
            return NextListItem(s, ref index, listtype, ref tmp);
        }

        /// <summary>
        /// Append a list item to a list value. 
        /// null is returned on failure.
        /// </summary>
        /// <param name="list"></param>
        /// <param name="item"></param>
        /// <returns></returns>
        public static String AppendListItem(String list, String item)
        { throw new Exception("Not yet implemented"); }

        /// <summary>
        /// Replace a list item in a list value.
        /// null is returned on failure.  Positions begin at 1.
        /// This works on the same list types that NextListItem() does.
        /// </summary>
        /// <param name="list"></param>
        /// <param name="item"></param>
        /// <param name="listtype"></param>
        /// <param name="position"></param>
        /// <returns></returns>
        public static String ReplaceListItem(String list, String item,
            DXTypeVals listtype, int position)
        { throw new Exception("Not yet implemented"); }


        /// <summary>
        /// Delete a list item from a list value.
        /// null is returned on failure.  Positions begin at 1, but if position
        /// is less than or equal to 0, then the last item is removed.  This works
        /// on the same list types that NextListItem() does.
        /// </summary>
        /// <param name="list"></param>
        /// <param name="?"></param>
        /// <param name="position"></param>
        /// <returns></returns>
        public static String DeleteListItem(String list, DXTypeVals listtype, int position)
        { throw new Exception("Not yet implemented"); }


        /// <summary>
        /// Get the index'th list item from the given string which
        /// is expected to be a list. 
        /// null is returned if the item was not found or if the listtype is wrong.
        /// </summary>
        /// <param name="list"></param>
        /// <param name="index"></param>
        /// <param name="listtype"></param>
        /// <returns></returns>
        public static String GetListItem(String list, int index, DXTypeVals listtype)
        { throw new Exception("Not yet implemented"); }

        /// <summary>
        /// Get the number of items in the list.
        /// </summary>
        /// <param name="list"></param>
        /// <param name="listtype"></param>
        /// <returns></returns>
        public static int GetListItemCount(String list, DXTypeVals listtype)
        { throw new Exception("Not yet implemented"); }

        /// <summary>
        /// Change the dimensionality of the given vector to the given dimensions.
        /// If added components, use the dflt value.
        /// Returns null on failure.
        /// </summary>
        /// <param name="vec"></param>
        /// <param name="new_dim"></param>
        /// <param name="dflt"></param>
        /// <param name="is_int"></param>
        /// <returns></returns>
        public static String AdjustVectorDimensions(String vec, int new_dim, double dflt,
            bool is_int)
        { throw new Exception("Not yet implemented"); }


        /// <summary>
        /// Make sure all values (Scalar[List], Integer[List] and Vector[List] 
        /// components) are within the given ranges for each component.  
        /// 'val' is the given string value representing the Scalar, Integer or 
        /// Vector and 'valtype' is expected to be its type.  
        /// mins/maxs are arrays of minimum and maximum values for the 
        /// corresponding components (scalar and integer only have a single 
        /// component).  
        /// TRUE is returned if the value needs to be clamped to be within the 
        /// given ranges, FALSE otherwise.  If clampedval is provided, then a 
        /// string is passed back which represents the clamped value. 
        /// </summary>
        /// <param name="val"></param>
        /// <param name="valtype"></param>
        /// <param name="mins"></param>
        /// <param name="maxs"></param>
        /// <param name="clampedval"></param>
        /// <returns></returns>
        public static bool ClampVSIValue(String val, DXTypeVals valtype, ref double mins,
            ref double maxs, ref String clampedval)
        { throw new Exception("Not yet implemented"); }

        /// <summary>
        /// Parse the floating point numbers out of either a ScalarList or a
        /// VectorList.  Numbers are parsed into an array created from within.
        /// The values are placed into the array in the order they are encountered
        /// in the list.  In the case of VectorLists, all vectors in the list must
        /// be of the same dimensionality.
        /// The return value is the number of list items parsed out of the list.  
        /// *data is the allocated array of values.
        /// *tuple is the dimensionality of the VectorList items (1 for ScalarList).
        /// '*tuple * return-val' is the number of items in the *data array.
        /// </summary>
        /// <param name="list"></param>
        /// <param name="listtype"></param>
        /// <param name="data"></param>
        /// <param name="tuple"></param>
        /// <returns></returns>
        public static int GetDoublesFromList(String list, DXTypeVals listtype,
            ref double[] data, ref int tuple)
        { throw new Exception("Not yet implemented"); }


        /// <summary>
        /// Format a double into a string to preserve the double precision.
        /// The values is formatted into buf if provided otherwise into a
        /// newly allocated string.
        /// The value is formatted with a number of decimal places as indicated
        /// by 'decimals'. If decimals is greater than 0, then that number
        /// of decimal places is always printed (upto that number supported by
        /// sprintf()).  If decimals is less than or equal to 0, then we use 8 
        /// decimals, except that we clip any trailing zeros down to ".0". 
        /// Further, if decimals is 0 then we clip off the ".0" too.
        ///
        /// 9/12 - added another defaulting param for telling DXValue to strip
        /// off all trailing 0's including the .0 left behind when decimals==0.
        /// I added this right before shipping 3.1 due to a problem starting in
        /// ScalarInstance:140 related to the vector interactor - c1tignor33?
        /// </summary>
        /// <param name="value"></param>
        /// <param name="buf"></param>
        /// <param name="decimals"></param>
        /// <param name="stripAllZeros"></param>
        /// <returns></returns>
        public static String FormatDouble(double value, ref String buf, int decimals,
            bool stripAllZeros)
        { throw new Exception("Not yet implemented"); }

        public bool isDefined()
        {
            return defined;
        }

        public void clear()
        {
            if (str != null)
                str = null;

            integer = 0;
            scalar = 0.0;

            if (tensor != null)
                tensor = null;

            defined = false;
            this.type.setType(DXTypeVals.UndefinedType);
        }

        /// <summary>
        /// Assigns a string value of the specified type (DXType constant).
        /// Returns TRUE if the new value has been assigned;
        /// returns FALSE otherwise.
        /// </summary>
        /// <param name="str"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        public bool setValue(String strp, DXTypeVals typep)
        {
            bool result = false;

            if (DXValue.IsValidValue(strp, typep))
            {
                this.clear();
                this.type.setType(typep);

                this.str = strp;
                if (String.Compare(str, "NULL", true) == 0)
                {
                    this.type.setType(typep);
                }
                else
                {
                    // Convert the string to internal, native form according to type
                    double d; int v;
                    switch (typep)
                    {
                        case DXTypeVals.FlagType:
                            // The executive dow not recognize 'true' or 'false', so
                            // we convert them to integer values.
                            if (String.Compare(strp, "false", true) == 0)
                            {
                                this.integer = 0; this.scalar = 0;
                                this.str = "0";
                            }
                            else if (String.Compare(strp, "true", true) == 0)
                            {
                                this.integer = 1; this.scalar = 1;
                                this.str = "1";
                            }
                            else
                            {
                                v = int.Parse(strp); this.integer = v;
                                d = double.Parse(strp); this.scalar = d;
                            }
                            break;

                        case DXTypeVals.IntegerType:
                            v = int.Parse(strp); this.integer = v;
                            d = double.Parse(strp); this.scalar = d;
                            break;

                        case DXTypeVals.ScalarType:
                            d = double.Parse(strp); this.scalar = d;
                            if (strp.Contains("."))
                                this.str = this.scalar.ToString();
                            break;

                        case DXTypeVals.VectorType:
                            tensor = new DXTensor();
                            result = tensor.setValue(strp);
                            Debug.Assert(result);
                            break;

                        case DXTypeVals.TensorType:
                        case DXTypeVals.ValueType:
                        case DXTypeVals.StringType:
                        case DXTypeVals.ObjectType:
                        case DXTypeVals.WhereType:
                        case DXTypeVals.DescriptionType:
                            break;

                        default:
                            if ((typep & DXTypeVals.ListType) > 0)
                            {
                                List<String> toks;
                                String buf;
                                switch (typep & DXTypeVals.ListTypeMask)
                                {
                                    case DXTypeVals.ScalarType:
                                        // Convert '{ 1 2.0000 3.3 }' into '{ 1.0 2.0 3.3 }'
                                        // Ignore lists specified with the elipsis '{ 1..2: 3}'
                                        if (this.str.Contains(":") || this.str.Contains(".."))
                                            break;
                                        toks = Utils.StringTokenizer(strp, " ,\t{}", null);
                                        buf = "{ ";
                                        foreach (String tok in toks)
                                        {
                                            buf += double.Parse(tok).ToString() + " ";
                                        }
                                        buf += "}";
                                        this.str = buf;
                                        break;

                                    case DXTypeVals.IntegerType:
                                        // Ignore lists specified with the ellipsis '{ 1..2:3 }'
                                        if (this.str.Contains(":") || this.str.Contains(".."))
                                            break;
                                        toks = Utils.StringTokenizer(strp, " ,\t{}", null);
                                        buf = "{ ";
                                        foreach (String tok in toks)
                                        {
                                            buf += int.Parse(tok).ToString() + " ";
                                        }
                                        buf += "}";
                                        this.str = buf;
                                        break;

                                    case DXTypeVals.StringType:
                                        toks = Utils.StringTokenizer(strp, " ,\t{}", null);
                                        buf = "{ ";
                                        foreach (String tok in toks)
                                        {
                                            buf += tok + " ";
                                        }
                                        buf += "}";
                                        this.str = buf;
                                        break;

                                    case DXTypeVals.FlagType:
                                    case DXTypeVals.VectorType:
                                    case DXTypeVals.TensorType:
                                    case DXTypeVals.ValueType:
                                        break;
                                }
                            }
                            else if ((long)(typep & DXTypeVals.UserType1) > 0 ||
                                (long)(typep & DXTypeVals.UserType2) > 0 ||
                                (long)(typep & DXTypeVals.UserType4) > 0 ||
                                (long)(typep & DXTypeVals.UserType5) > 0 ||
                                (long)(typep & DXTypeVals.UserType6) > 0)
                            { }
                            else
                                Debug.Assert(false);
                            break;
                    }
                }
                return true;
            }
            else
                return false;
        }

        public bool setValue(String str, DXType type)
        {
            Debug.Assert(str != null);
            return setValue(str, type.getType());
        }

        /// <summary>
        /// Assigns a string value.
        /// Returns TRUE if the string is correct; returns FALSE, otherwise.
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public bool setString(String str)
        { throw new Exception("Not yet implemented"); }

        /// <summary>
        /// Assigns an integer value.
        /// Returns TRUE if successful, FALSE otherwise.
        /// </summary>
        /// <param name="integer"></param>
        /// <returns></returns>
        public bool setInteger(int integer)
        { throw new Exception("Not yet implemented"); }

        /// <summary>
        /// Assigns a scalar value.
        /// Returns TRUE if successful, FALSE otherwise.
        /// </summary>
        /// <param name="scalar"></param>
        /// <returns></returns>
        public bool setScalar(double scalar)
        { throw new Exception("Not yet implemented");}

        /// <summary>
        /// Assigns a vector value.
        /// Returns TRUE if successful, FALSE otherwise.
        /// </summary>
        /// <param name="vector"></param>
        /// <returns></returns>
        public bool setVector(DXTensor vector)
        { throw new Exception("Not yet implemented");}

        /// <summary>
        /// Returns the string representation of the current value.
        /// </summary>
        /// <returns></returns>
        public String getValueString()
        { return (this.str != null ? this.str : "NULL"); }

        public DXTypeVals getType() { throw new Exception("Not Yet Implemented"); }
        public String getTypeName() { throw new Exception("Not Yet Implemented"); }
        public int getInteger() { throw new Exception("Not Yet Implemented"); }
        public double getScalar() { throw new Exception("Not Yet Implemented"); }
        public double getVectorComponentValue(int component) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// The number of components in a vector or the 1st vector in a vector list
        /// Must have a value and the type must be Vector or VectorList.
        /// </summary>
        /// <returns></returns>
        public int getVectorComponentCount() { throw new Exception("Not Yet Implemented"); }
        public bool setVectorComponentValue(int component, double val) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Does the given string represent the given type?
        /// </summary>
        /// <param name="str"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        public bool Valid(String str, DXTypeVals type) { throw new Exception("Not Yet Implemented"); }


        public static bool IsValue(String str, ref DXTypeVals type)
        {
            int tuple = 0;

            if (str == null)
                return false;

            Regex r = new Regex(@"^(\+|-)?(\d+\.\d*|\.\d+)([eE](\+|)?[0-9]+)?$");
            switch (type)
            {
                case DXTypeVals.ScalarType:
                    return r.IsMatch(str);
                    break;
                case DXTypeVals.VectorType:
                    return DXTensor.IsVector(str, ref tuple);
                    break;
                case DXTypeVals.TensorType:
                    return DXTensor.IsTensor(str);
                    break;
                default:
                    if (r.IsMatch(str))
                    {
                        type = DXTypeVals.ScalarType;
                        return true;
                    }
                    if (DXTensor.IsVector(str, ref tuple))
                    {
                        type = DXTypeVals.VectorType;
                        return true;
                    }
                    if (DXTensor.IsTensor(str))
                    {
                        type = DXTypeVals.TensorType;
                        return true;
                    }
                    break;
            }
            return false;
        }

        public static bool IsObject(String str)
        {
            if (str == null)
                return false;

            // Match integer
            Regex r = new Regex(@"^(\+|-)?\d+$");
            if (r.IsMatch(str))
                return true;

            // Match Scalar
            r = new Regex(@"^(\+|-)?(\d+\.\d*|\.\d+)([eE](\+|)?[0-9]+)?$");
            if(r.IsMatch(str))
                 return true;
            
            // Match Vector
            int tuple = 0;
            if(DXTensor.IsVector(str, ref tuple))
                return true;
            
            if(DXTensor.IsTensor(str))
                return true;

            DXTypeVals value_type = DXTypeVals.UndefinedType;
            if(IsValue(str, ref value_type))
                return true;

            r = new Regex(@"^""[^""]*""$");
            if(r.IsMatch(str))
                return true;

            if (IsList(str, DXTypeVals.IntegerType))
                return true;

            if (IsList(str, DXTypeVals.ScalarType))
                return true;

            if (IsList(str, DXTypeVals.VectorType))
                return true;

            if (IsList(str, DXTypeVals.TensorType))
                return true;

            if (IsList(str, DXTypeVals.StringType))
                return true;

            return false;
        }

        public static bool IsListExplicit(String str, DXTypeVals type)
        {
            bool lexed;
            int tuple = 0, first_tuple = -1;

            if (str == null)
                return false;

            str = str.Trim();
            if (!str.StartsWith("{") ||
                !str.EndsWith("}"))
                return false;

            str = str.Substring(1);
            str = str.Substring(0, str.Length -1);

            DXTypeVals value_type = DXTypeVals.UndefinedType;

            List<String> toks = Utils.StringTokenizer(str, " ,\t", new String[] { "\"", "[]" });
            Regex r;

            int elements = 0;
            foreach (String tok in toks)
            {
                switch (type)
                {
                    case DXTypeVals.FlagType:
                        r = new Regex(@"^(true|false|\d+)$");
                        lexed = r.IsMatch(tok);
                        break;
                    case DXTypeVals.IntegerType:
                        r = new Regex(@"^(\+|-)?\d+$");
                        lexed = r.IsMatch(tok);
                        break;
                    case DXTypeVals.ScalarType:
                        r = new Regex(@"^(\+|-)?(\d+\.\d*|\.\d+)([eE](\+|)?[0-9]+)?$");
                        lexed = r.IsMatch(tok);
                        break;
                    case DXTypeVals.VectorType:
                        lexed = DXTensor.IsVector(tok, ref tuple);
                        if (elements == 0)
                            first_tuple = tuple;
                        else if (tuple != first_tuple)
                            return false;
                        break;
                    case DXTypeVals.TensorType:
                        lexed = DXTensor.IsTensor(tok);
                        break;
                    case DXTypeVals.ValueType:
                        lexed = IsValue(str, ref value_type);
                        break;
                    case DXTypeVals.StringType:
                        r = new Regex(@"^""[^""]*""$");
                        lexed = r.IsMatch(tok);
                        break;
                    default:
                        return false;
                }
                if (lexed)
                    elements++;
                else
                    return false;
            }
            return true;
        }

        public static bool IsList(String str, DXTypeVals type)
        {
            bool r = IsListExplicit(str, type);
            if (!r && ((type & DXTypeVals.ValueType) > 0))
                r = IsListConstructor(str);
            return r;
        }

        /// <summary>
        /// A scalar list constructor is of the shape:
        /// { 1 .. 5 : 2 }  -> { 1 3 5 }
        /// Find out if the list is acceptable.
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static bool IsListConstructor(String str)
        {
            bool lexed;

            if (str == null)
                return false;

            str = str.Trim();
            if (!str.StartsWith("{") ||
                !str.EndsWith("}"))
                return false;

            str = str.Substring(1);
            str = str.Substring(0, str.Length - 1);

            List<String> toks = Utils.StringTokenizer(str, " \t", new String[] { "\"", "[]" });

            Regex r = new Regex(@"^(\+|-)?(\d+\.\d*|\.\d+)([eE](\+|)?[0-9]+)?$");

            if(toks.Count != 3 || toks.Count != 5)
                return false;

            if (!r.IsMatch(toks[0]))
                return false;

            if (toks[1] != "..")
                return false;

            if (!r.IsMatch(toks[2]))
                return false;

            if (toks.Count == 3)
                return true;

            if (toks[3] != ":")
                return false;

            if (!r.IsMatch(toks[4]))
                return false;

            return true;
        }
    }
}
