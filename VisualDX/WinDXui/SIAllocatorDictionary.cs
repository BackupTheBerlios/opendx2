using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public delegate StandIn SIAllocator(WorkSpace ws, Node node);

    public class SIAllocatorDictionary
    {

        public SIAllocatorDictionary() { throw new Exception("Not Yet Implemented"); }

        public static SIAllocatorDictionary theSIAllocatorDictionary = null;

    }
}
