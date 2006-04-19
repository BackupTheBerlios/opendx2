using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class DXType
    {
        #region structs and enums
        public struct DXTypeName
        {
            public bool userDefined;
            public String name;
            public DXTypeVals type;

            public DXTypeName(bool userDefined, String name, DXTypeVals type)
            {
                this.userDefined = userDefined;
                this.name = name;
                this.type = type;
            }
        }

        //
        // Ennumeration of base types plus six user-definable types.
        //
        // NOTE: Each type is a bit flag and some times inherit other
        //       types by ORing the bit of the inherited types with
        //       into its bit.
        //
        public enum DXTypeVals : long
        {
            UndefinedType = 0x00000000,	// undefined
            IntegerType = 0x00000001,	// integer
            FlagType = 0x00000003,	// flag   |= integer
            ScalarType = 0x00000005,	// scalar |= integer
            VectorType = 0x00000008,	// vector
            TensorType = 0x00000010,	// tensor
            ValueType = 0x0000001d,	// value = integer|scalar|vector|tensor
            StringType = 0x00000020,	// string
            CameraType = 0x00000040,	// camera
            LightType = 0x00000080,	// light

            UserType1 = 0x00000100,	// user-defined
            UserType2 = 0x00000200,	// user-defined
            WhereType = 0x00000400,	// WHERE parameter

            FieldType = 0x00000800,	// field
            GeometryFieldType = 0x00001800,	// geometry field |= field
            ColorFieldType = 0x00002800,	// color field    |= field
            ScalarFieldType = 0x00004800,	// scalar field   |= field
            VectorFieldType = 0x00008800,	// vector field   |= field
            DataFieldType = 0x00010800,	// data field     |= field
            ImageType = 0x00020800,	// image |= field

            SeriesType = 0x00040800,	// series |= field
            FieldSeriesType = 0x000c0800,	// field series |= field|series

            GroupType = 0x00100800,	// group |= field
            ValueGroupType = 0x00300800,	// value group |= group|field
            ValueListGroupType = 0x00500800,	// value list group |= group|field
            FieldGroupType = 0x00900800,	// field group

            ListType = 0x01000000,	// list
            ListTypeMask = 0x0effffff,	// list mask
            ObjectType = 0x03ffffff,	// object
            DescriptionType = 0x04000000,	// description

            ValueListType = ValueType | ListType,
            ScalarListType = ScalarType | ListType,
            IntegerListType = IntegerType | ListType,
            FlagListType = FlagType | ListType,
            TensorListType = TensorType | ListType,
            VectorListType = VectorType | ListType,
            StringListType = StringType | ListType,

            ReservedType = 0x08000000,	// RESERVED FOR FUTURE

            UserType4 = 0x10000000,	// user-defined
            UserType5 = 0x20000000,	// user-defined
            UserType6 = 0x40000000	// user-defined
        };

        #endregion

        #region static internal constant
        internal static DXTypeName[] _baseType = {
        new DXTypeName( false, "undefined",       DXTypeVals.UndefinedType ),
        new DXTypeName( false, "value",           DXTypeVals.ValueType ),
        new DXTypeName( false, "scalar",          DXTypeVals.ScalarType),
        new DXTypeName( false, "integer",         DXTypeVals.IntegerType ),
        new DXTypeName( false, "flag",            DXTypeVals.FlagType ),
        new DXTypeName( false, "tensor",          DXTypeVals.TensorType ),
        new DXTypeName( false, "matrix",          DXTypeVals.TensorType ),
        new DXTypeName( false, "vector",		    DXTypeVals.VectorType  ),
        new DXTypeName( false, "value list",	    DXTypeVals.ValueType | DXTypeVals.ListType  ),
        new DXTypeName( false, "scalar list",	    DXTypeVals.ScalarType | DXTypeVals.ListType  ),
        new DXTypeName( false, "integer list",    DXTypeVals.IntegerType | DXTypeVals.ListType  ),
        new DXTypeName( false, "flag list",		DXTypeVals.FlagType | DXTypeVals.ListType  ),
        new DXTypeName( false, "tensor list",		DXTypeVals.TensorType | DXTypeVals.ListType  ),
        new DXTypeName( false, "matrix list",		DXTypeVals.TensorType | DXTypeVals.ListType  ),
        new DXTypeName( false, "vector list",		DXTypeVals.VectorType | DXTypeVals.ListType  ),
        new DXTypeName( false, "string",		    DXTypeVals.StringType  ),
        new DXTypeName( false, "string list",		DXTypeVals.StringType | DXTypeVals.ListType  ),
        new DXTypeName( false, "camera",		    DXTypeVals.CameraType  ),
        new DXTypeName( false, "light",			DXTypeVals.LightType  ),
        new DXTypeName( false, "field",			DXTypeVals.FieldType  ),
        new DXTypeName( false, "geometry field",	DXTypeVals.GeometryFieldType  ),
        new DXTypeName( false, "color field",		DXTypeVals.ColorFieldType  ),
        new DXTypeName( false, "scalar field",	DXTypeVals.ScalarFieldType  ),
        new DXTypeName( false, "vector field",	DXTypeVals.VectorFieldType  ),
        new DXTypeName( false, "data field",		DXTypeVals.DataFieldType  ),
        new DXTypeName( false, "series",		    DXTypeVals.SeriesType  ),
        new DXTypeName( false, "field series",	DXTypeVals.FieldSeriesType  ),
        new DXTypeName( false, "image",			DXTypeVals.ImageType  ),
        new DXTypeName( false, "image series",	DXTypeVals.ImageType | DXTypeVals.SeriesType  ),
        new DXTypeName( false, "vector field series",	DXTypeVals.VectorFieldType | DXTypeVals.SeriesType  ),
        new DXTypeName( false, "group",			DXTypeVals.GroupType  ),
        new DXTypeName( false, "value group",		DXTypeVals.ValueGroupType  ),
        new DXTypeName( false, "value list group",	DXTypeVals.ValueListGroupType  ),
        new DXTypeName( false, "field group",		DXTypeVals.FieldGroupType  ),
        new DXTypeName( false, "image group",		DXTypeVals.ImageType | DXTypeVals.GroupType  ),
        new DXTypeName( false, "list",			DXTypeVals.ListType  ),
        new DXTypeName( false, "object",		    DXTypeVals.ObjectType  ),
        new DXTypeName( false, "window",		    DXTypeVals.WhereType )
        };
        #endregion

        #region public constructors and initializers
        public DXType() 
        {
            InitializeClass();

            type = DXTypeVals.UndefinedType;
            name = null;
        }

        public DXType(DXTypeVals type) 
        {
            InitializeClass();

            type = DXTypeVals.UndefinedType;
            name = null;

            setType(type);
        }

        private void InitializeClass()
        {
            if (!DXTypeClassInitialized)
            {
                TypeList = new List<DXTypeName>();
                foreach (DXTypeName tn in _baseType)
                    TypeList.Add(tn);
                DXTypeClassInitialized = true;
            }
        }
        #endregion

        protected static List<DXTypeName> TypeList;
        protected static bool DXTypeClassInitialized;

        protected DXTypeVals type;
        protected String name;

        /// <summary>
        /// Determine the types of the items in a list.
        /// If there are mixed types then the returned type is DXTypeVals.ValueType.
        /// If there are not mixed types than the type of each item is returned.
        /// If an unrecognized list item is found, DXTypeVals.UndefinedType is 
        /// returned.
        /// </summary>
        /// <param name="val"></param>
        /// <returns></returns>
        public static DXTypeVals DetermineListItemType(String val) 
        {
            throw new Exception("Not Yet Implemented");
            bool quitting = false;
            String s1 = null, s2 = null;
            int index = -1;

            if (val == "NULL" || val == "null")
                return DXTypeVals.ValueType;

            // Check to see what the first type is. It can be
            // ValueListType, StringType, IntegerType, ScalarType,
            // VectorType, TensorType, ValueType
            // 
            // Go through the list one item at a time. Set ctype to the
            // type discovered. If found Undefined type, quit and return
            // UndefinedType. If type ever ValueType then return ValueType.
            // If types don't keep matching, then return ValueType.
            //while(!quitting &&
            //    ((s1=DXValue.NextListItem(val, ref index, DXTypeVals.ValueListType, 
        }

        /// <summary>
        /// Adds a user-defined type to the class type list.
        /// Returns TRUE if successful; otherwise, FALSE.
        /// Note: The name string is copied by the function.
        /// </summary>
        /// <param name="type"></param>
        /// <param name="name"></param>
        /// <returns></returns>
        public static bool AddUserType(DXTypeVals type, String name) 
        {
            DXTypeName userType;
            userType = new DXTypeName();
            userType.userDefined = true;
            userType.type = type;
            userType.name = name;

            TypeList.Add(userType);
            return true;
        }

        /// <summary>
        /// Deletes a type (by type) from the class type list.
        /// Returns TRUE if successful; otherwise, FALSE.
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        public static bool DeleteType(DXTypeVals type)
        {
            foreach (DXTypeName knownType in TypeList)
            {
                if (type == knownType.type)
                {
                    TypeList.Remove(knownType);
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// Given a string containing a value, determine its type. 
        /// </summary>
        /// <param name="value"></param>
        /// <param name="typelist"></param>
        /// <returns></returns>
        public static bool ValueToType(String value, List<DXTypeName> typelist) 
        {
            int in_size = typelist.Count;

            foreach (DXTypeName knownType in TypeList)
            {
                if (DXValue.IsValidValue(value, knownType.type))
                    typelist.Add(knownType);
            }
            return (typelist.Count > in_size); 
        }

        /// <summary>
        /// Deletes a type (by name) from the class type list.
        /// Returns TRUE if successful; otherwise, FALSE.
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public static bool DeleteType(String name) 
        {
            foreach (DXTypeName knownType in TypeList)
            {
                if (knownType.name == name)
                {
                    TypeList.Remove(knownType);
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// Returns a name string of the specified type.
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        public static String TypeToString(DXTypeVals type) 
        {
            foreach (DXTypeName knownType in TypeList)
            {
                if (type == knownType.type)
                    return knownType.name;
            }
            return null;
        }


        /// <summary>
        /// Returns the type of the specified name string.
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static DXTypeVals StringToType(String str) 
        {
            foreach (DXTypeName knownType in TypeList)
            {
                if (knownType.name == str)
                    return knownType.type;
            }
            return DXTypeVals.UndefinedType;
        }

        /// <summary>
        /// Convert a version 1.0 (DX/6000 1.2 11/92) type to new type system.
        /// </summary>
        /// <param name="t"></param>
        /// <returns></returns>
        public static DXTypeVals ConvertVersionType(DXTypeVals t)
        {
            throw new Exception("Not implemented function");
        }

        /// <summary>
        /// Find the first type in the list of DXTypes, that matches the value. 
        /// </summary>
        /// <param name="value"></param>
        /// <param name="typelist"></param>
        /// <returns></returns>
        public static DXTypeVals FindTypeMatch(String value, List<DXType> typelist) 
        {
            DXTypeVals t;

            Debug.Assert(typelist.Count > 0);
            foreach (DXType dxtype in typelist)
            {
                t = dxtype.getType();
                if (DXValue.IsValidValue(value, t))
                    return t;

            }
            return DXTypeVals.UndefinedType;
        }

        /// <summary>
        /// Returns true if the source and destination types match; false otherwise.
        /// </summary>
        /// <param name="source"></param>
        /// <param name="destination"></param>
        /// <returns></returns>
        public static bool MatchType(DXType source, DXType destination) 
        {
            return MatchType(source.getType(), destination.getType());
        }

        public static bool MatchType(DXTypeVals source, DXTypeVals destination) 
        {
            DXTypeVals intersection;
            DXTypeVals baseSource;
            DXTypeVals baseDestination;

            //
            // Get the intersection of source and destination types.
            //
            intersection = source & destination;

            //
            // If there is no intersection...
            //
            if (intersection == 0 || intersection == DXTypeVals.ListType)
            {
                return false;
            }

            //
            // If the source/destination type is Object type...
            //
            if (source == DXTypeVals.ObjectType || 
                destination == DXTypeVals.ObjectType)
            {
                return true;
            }

            //
            // If the source type is a list while the destination type
            // is not a list, no match...
            //
            if (((source & DXTypeVals.ListType) == DXTypeVals.ListType) && 
                ((destination & DXTypeVals.ListType) != DXTypeVals.ListType))
            {
                return false;
            }

            //
            // Strip off list attribute from the source and destination
            // types at this point.
            //
            baseSource = source & DXTypeVals.ListTypeMask;
            baseDestination = destination & DXTypeVals.ListTypeMask;

            //
            // Scalar source type cannot match flag/integer destination type.
            //
            if (baseSource == DXTypeVals.ScalarType &&
                (baseDestination == DXTypeVals.FlagType ||
                baseDestination == DXTypeVals.IntegerType))
            {
                return false;
            }

            //
            // Passed all the tests... return successfully.
            //
            return true;
        }

        /// <summary>
        /// Returns TRUE if there exists a matching type in both lists.
        /// Returns FALSE otherwise.  Note that the source list is
        /// semantically different from the destination list.
        /// </summary>
        /// <param name="first"></param>
        /// <param name="second"></param>
        /// <returns></returns>
        public static bool MatchTypeLists(List<DXType> first, List<DXType> second) 
        {
            foreach (DXType sourceType in first)
            {
                foreach (DXType destinationType in second)
                {
                    if (MatchType(sourceType, destinationType))
                        return true;
                }
            }
            return false;
        }

        /// <summary>
        /// Returns an intersection list of the first two type lists
        /// The returned list may be empty, and it must be deleted
        /// by the client.
        /// </summary>
        /// <param name="first"></param>
        /// <param name="second"></param>
        /// <returns></returns>
        public static List<DXType> IntersectTypeLists(List<DXType> first, List<DXType> second) 
        {
            bool found;

            List<DXType> thirdList = new List<DXType>();
            foreach (DXType firstType in first)
            {
                foreach (DXType secondType in second)
                {
                    DXTypeVals intersection = firstType.getType() & secondType.getType();
                    if (intersection != 0 && intersection != DXTypeVals.ListType)
                    {
                        found = false;
                        foreach (DXTypeName typeName in TypeList)
                        {
                            if (intersection == typeName.type)
                            {
                                found = true;
                                break;
                            }
                        }
                        Debug.Assert(found);

                        found = false;
                        foreach (DXType thirdType in thirdList)
                        {
                            if (intersection == thirdType.getType())
                            {
                                found = true;
                                break;
                            }
                        }

                        if (!found)
                            thirdList.Add(new DXType(intersection));
                    }
                }
            }
            return thirdList;
        }

        /// <summary>
        /// Sets the type value IFF the type is a base or user-defined type.
        /// Returns true if successful; false, otherwise.
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        public bool setType(DXTypeVals type) 
        {
            foreach (DXTypeName knownType in TypeList)
            {
                if (knownType.type == type)
                {
                    this.type = type;
                    this.name = knownType.name;
                    return true;
                }
            }
            return false;
        }

        public String getName()
        {
            return name;
        }

        public DXTypeVals getType()
        {
            return type;
        }

        /// <summary>
        /// DXType comparison equality operator.
        /// </summary>
        /// <param name="type1"></param>
        /// <param name="type2"></param>
        /// <returns></returns>
        public static bool operator ==(DXType type1, DXType type2)
        {
            return type1.type == type2.type;
        }

        public static bool operator !=(DXType type1, DXType type2)
        {
            return type1.type != type2.type;
        }

        public override int GetHashCode()
        {
            return this.ToString().GetHashCode();
        }

        public static bool operator &(DXType type1, DXType type2)
        {
            return ((type1.type & type2.type) != 0);
        }

    }
}
