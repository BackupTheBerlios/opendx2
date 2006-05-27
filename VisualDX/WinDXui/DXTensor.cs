using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    class DXTensor
    {
        // [ 
        //   [ 
        //     [ 1 2 3 4 5 ] [ 1 2 3 4 5 ] [ 1 2 3 4 5 ] [ 1 2 3 4 5 ]
        //   ]
        //   [
        //     [ 1 2 3 4 5 ] [ 1 2 3 4 5 ] [ 1 2 3 4 5 ] [ 1 2 3 4 5 ]
        //   ]
        // ]
        // This yeilds: 
        //  dimensions = 3
        //  dim_sizes = 2, 4, 5
        // 
        // with 2 subtensors of:
        //  [ [ 1 2 3 4 5 ] [ 1 2 3 4 5 ] [ 1 2 3 4 5 ] [ 1 2 3 4 5 ] ]
        //  dimensions = 2
        //  dim_size = 4, 5
        // 
        // with 4 subtensors of:
        //  [ 1 2 3 4 5 ]
        //  dimensions = 1
        //  dim_size = 5

        private double [] scalars;              // List of scalar values
        private List<DXTensor> tensors;         // List of tensors
        private int dimensions;                 // Number of dimensions (depth) in the vector
        private int [] dim_sizes;               // Size of each dimension

        public DXTensor()
        {
            scalars = null;
            tensors = null;
            dimensions = 0;
            dim_sizes = null;
        }

        public DXTensor(List<double> scalarList) 
        {
            int i = 0;
            scalars = new double[scalarList.Count];
            foreach (double d in scalarList)
            {
                scalars[i++] = d;
            }
            dimensions = 1;
            dim_sizes = new int[1];
            dim_sizes[0] = scalarList.Count;
        }

        /// <summary>
        /// Set the vector value from a null terminated string.
        /// </summary>
        public void printValue()
        {
            Console.Write("Dimensions ({0}) Dim Sizes (", dimensions);
            for (int i = 0; i < dimensions; i++)
            {
                Console.Write("{0} ", dim_sizes[i]);
            }
            Console.WriteLine(")");
            Console.WriteLine("Value : {0}", getValueString());
        }

        /// <summary>
        /// Set the vector value from a null terminated string. 
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public bool setValue(String str)
        {
            bool sawValue = false;
            //Stack<char> stack = new Stack<char>();
            Stack<DXTensor> stack = new Stack<DXTensor>();
            int newDim = 0;
            List<DXTensor> tensorList;

            // Need to use Regex to push space around all [ and ]
            String s = @"\[";
            Regex rgx = new Regex(s);
            String newStr = rgx.Replace(str, @" [ ");
            s = @"\]";
            rgx = new Regex(s);
            String fnlStr = rgx.Replace(newStr, @" ] ");
            fnlStr = fnlStr.Trim();

            // Use split to split over space and get array of strings
            String[] vals = fnlStr.Split();

            List<double> scalarList = new List<double>();
            foreach (String ind in vals)
            {
                if (ind == "[")
                {
                    if (scalarList.Count > 0)
                        return false;

                    stack.Push(new DXTensor());
                    newDim++;
                }
                else if (ind == "]")
                {
                    if (sawValue == false)
                        return false;

                    if (stack.Count == 0)
                        return false;

                    // Need to add a vector.
                    if (scalarList.Count > 0)
                    {
                        DXTensor top = stack.Pop(); // Pop off top DXTensor.
                        if (top.scalars != null || top.tensors != null)
                            return false;

                        if (stack.Count > 0)
                        {
                            top = new DXTensor(scalarList);
                            DXTensor ptop = stack.Peek();
                            ptop.tensors.Add(top);
                            ptop.dimensions = top.dimensions + 1;
                            if (ptop.dim_sizes == null)
                            {
                                ptop.dim_sizes = new int[2];
                                ptop.dim_sizes[0] = 1;
                                ptop.dim_sizes[1] = scalarList.Count;
                            }
                            else
                            {
                                // Must match previous scalar list for shape.
                                if (ptop.dim_sizes[1] != scalarList.Count)
                                    return false;
                                ptop.dim_sizes[0] += ptop.dim_sizes[0];
                            }
                        }
                        else
                        {
                            // Just a single vector tensor.
                            int i = 0;
                            scalars = new double[scalarList.Count];
                            foreach (double d in scalarList)
                            {
                                scalars[i++] = d;
                            }
                            dimensions = 1;
                            dim_sizes = new int[1];
                            dim_sizes[0] = scalarList.Count;
                        }
                        scalarList.Clear();
                    }
                    else
                    {
                        // Pop off a ] after a ]

                        DXTensor top = stack.Pop();
                        if (stack.Count == 0)
                        {
                            if (dimensions > 0 && dimensions != top.dimensions + 1)
                                return false;
                            if (dimensions == 0)
                                dimensions = top.dimensions + 1;

                            if (dim_sizes == null)
                                dim_sizes = new int[dimensions + 1];

                            for (int j = 1; j < dimensions; j++)
                            {
                                if (dim_sizes[j] != 0 && dim_sizes[j] != top.dim_sizes[j - 1])
                                    return false;

                                dim_sizes[j] = top.dim_sizes[j - 1];
                            }

                            dim_sizes[0]++;
                        }
                        else
                        {
                            DXTensor ptop = stack.Peek();
                            if (ptop.dimensions > 0 && ptop.dimensions != top.dimensions + 1)
                                return false;

                            if (ptop.dimensions == 0)
                                ptop.dimensions = top.dimensions + 1;

                            if (ptop.dim_sizes == null)
                                ptop.dim_sizes = new int[ptop.dimensions];

                            for (int j = 1; j < ptop.dimensions; j++)
                            {
                                if (ptop.dim_sizes[j] != 0 && ptop.dim_sizes[j] != top.dim_sizes[j - 1])
                                    return false;

                                ptop.dim_sizes[j] = top.dim_sizes[j - 1];
                            }

                            ptop.dim_sizes[0]++;
                        }

                    }

                }
                else if (ind == ",")
                {
                    if (!sawValue)
                        return false;
                    sawValue = false;
                }
                else
                {
                    sawValue = true;
                    // Add to vector
                    try
                    {
                        double val = double.Parse(ind);
                        scalarList.Add(val);
                    }
                    catch (FormatException)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        /// <summary>
        /// Put the vector value in a null terminated string.
        /// </summary>
        /// <returns></returns>
        public String getValueString()
        {
            String fmtStr = "";
            if (tensors != null)
            {
                fmtStr += " [ ";
                for (int i = 0; i < tensors.Count; i++)
                {
                    fmtStr += tensors[i].getValueString();
                }
                fmtStr += " ] ";
            }
            else if (scalars != null)
            {
                fmtStr += " [ ";
                for (int i = 0; i < scalars.Length; i++)
                {
                    fmtStr += scalars[i];
                    fmtStr += " ";
                }
                fmtStr += "] ";
            }
            return fmtStr;
        }

        /// <summary>
        /// Return the number of dimensions in this tensor.
        /// </summary>
        /// <returns></returns>
        public int getDimensions()
        {
            return dimensions;
        }

        /// <summary>
        /// Get the number of items in the given dimension.
        /// Dimensions are indexed from 1.
        /// </summary>
        /// <param name="dim"></param>
        /// <returns></returns>
        public int getDimensionSize(int dim)
        {
            Debug.Assert(dim > 0);
            Debug.Assert(dim <= dimensions);
            Debug.Assert(dim_sizes != null);

            return dim_sizes[dim - 1];
        }

        /// <summary>
        /// Return the value of the i'th component of a vector. 
        /// indexing is one based.
        /// </summary>
        /// <param name="component"></param>
        /// <returns></returns>
        public double getVectorComponentValue(int component)
        {
            Debug.Assert(getDimensions() == 1);
            Debug.Assert(dim_sizes[0] >= component);
            return scalars[component - 1];
        }
        public int getVectorComponentCount()
        {
            return getDimensionSize(1);
        }

        /// <summary>
        /// Set the value of the i'th component of a vector. 
        /// indexing is one based.
        /// </summary>
        /// <param name="component"></param>
        /// <param name="val"></param>
        /// <returns></returns>
        public bool setVectorComponentValue(int component, double val)
        {
            Debug.Assert(dimensions == 1);
            Debug.Assert(dim_sizes[0] >= component);
            scalars[component - 1] = val;
            return true;
        }

        public static bool IsTensor(String s)
        {
            DXTensor t = new DXTensor();
            return (t.setValue(s));
        }

        public static bool IsVector(String s, ref int tuple)
        {
            DXTensor t = new DXTensor();
            if (t.setValue(s) && (t.getDimensions() == 1))
            {
                tuple = t.getDimensionSize(1);
                return true;
            }
            return false;
        }
    }
}
