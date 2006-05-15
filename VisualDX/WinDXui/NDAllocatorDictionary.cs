using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public delegate NodeDefinition NDAllocator();

    class NDAllocatorDictionary : Dictionary<Symbol, NDAllocator>
    {
        public static Symbol GetNodeNameSymbol = Symbol.zero;
        public static Symbol SetNodeNameSymbol = Symbol.zero;

        private NDAllocator defaultAlloc;

        public NDAllocatorDictionary()
        {
            defaultAlloc = NodeDefinition.AllocateDefinition;
            this.Add("Display", DisplayDefinition.AllocateDefinition);

        }

        public bool setDefaultAllocator(NDAllocator nda)
        {
            defaultAlloc = nda;
            return true;
        }

        public void Add(String name, NDAllocator nda)
        {
            SymbolManager sm = SymbolManager.theSymbolManager;
            int pos = 0;

            Symbol temp = new Symbol(name.GetHashCode());
            if (this.ContainsKey(temp))
                return;

            Symbol s = sm.registerSymbol(name);
            this.Add(s, nda);
        }

        public NodeDefinition allocate(String name)
        {
            NodeDefinition i = null;
            NDAllocator a = findAllocator(name);
            if (a != null) i = a();
            return i;
        }

        public NDAllocator findAllocator(String name)
        {
            SymbolManager sm = SymbolManager.theSymbolManager;
            try
            {
                Symbol s = sm.getSymbol(name);
                return findAllocator(s);
            }
            catch (KeyNotFoundException)
            {
                return defaultAlloc;
            }
        }
        public NDAllocator findAllocator(Symbol name)
        {
            try
            {
                return this[name];
            }
            catch (KeyNotFoundException)
            {
                return defaultAlloc;
            }
        }

        public static NDAllocatorDictionary theNDAllocatorDictionary = null;

    }
}
