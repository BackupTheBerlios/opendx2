using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class DXValue
    {
        protected DXType type;
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
        public static bool IsValidValue(String str, DXTypeVals type) { throw new Exception("not yet implemented"); }
        public static bool IsValidValue(String str, DXType type)
        {
            Debug.Assert(str != null);
            return IsValidValue(str, type.getType());
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
        { throw new Exception("Not yet implemented."); }

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
        { throw new Exception("Not yet implemented"); }

        /// <summary>
        /// Assigns a string value of the specified type (DXType constant).
        /// Returns TRUE if the new value has been assigned;
        /// returns FALSE otherwise.
        /// </summary>
        /// <param name="str"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        public bool setValue(String str, DXTypeVals type)
        { throw new Exception("Not yet implemented"); }

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
        { throw new Exception("Not yet implemented");}

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


    }
}
