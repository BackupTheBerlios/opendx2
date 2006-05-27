using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public delegate StandIn SIAllocator(WorkSpace ws, Node node);

    public class SIAllocatorDictionary : Dictionary<String, SIAllocator>
    {
        SIAllocator defaultAlloc = null;

        public SIAllocatorDictionary()
        {
            defaultAlloc = StandIn.AllocateStandIn;
        }

        public bool setDefaultAllocator(SIAllocator nda)
        {
            defaultAlloc = nda;
            return true;
        }

        public StandIn allocate(Symbol namesym, WorkSpace w, Node n)
        {
            throw new Exception("Not Yet Implemented");
        }

        public SIAllocator findAllocator(String name)
        {
            Symbol s;
            SymbolManager sm = SymbolManager.theSymbolManager;
            try
            {
                return this[name];
            }
            catch (KeyNotFoundException)
            {
                return defaultAlloc;
            }
        }
        public SIAllocator findAllocator(Symbol name)
        {
            try
            {
                String s = SymbolManager.theSymbolManager.getSymbolString(name);
                return this[s];
            }
            catch (KeyNotFoundException)
            {
                return defaultAlloc;
            }
        }

        public static SIAllocatorDictionary theSIAllocatorDictionary = null;

    }
}
