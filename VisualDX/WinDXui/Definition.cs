// Completed 4/24/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    abstract class Definition
    {
        private Symbol key;

        public Definition() { key = new Symbol(0); }
        public Definition(Symbol k) { key = k; }

        public Symbol NameSymbol
        {
            get { return key; }
        }

        public String NameString
        {
            get
            {
                return SymbolManager.theSymbolManager.getSymbolString(key);
            }
        }

        public Symbol setName(String name)
        {
            key = SymbolManager.theSymbolManager.registerSymbol(name);
            return key;
        }


    }
}
