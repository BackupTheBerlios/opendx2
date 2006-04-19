using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace WinDX
{
    namespace UI
    {
        /// <summary>
        /// The standard symbol is really just an Int32 at this time.
        /// May need to be changed if the StringTable ever got bigger.
        /// </summary>
        public struct Symbol
        {
            private int val;
            public static readonly Symbol zero = new Symbol(-1);

            public Symbol(int initialVal)
            {
                val = initialVal;
            }

            public static explicit operator Symbol(Int32 initialVal)
            {
                Symbol s = new Symbol(initialVal);
                return s;
            }

            public override int GetHashCode()
            { return this.ToString().GetHashCode(); }

            public override bool Equals(object obj)
            {
                if (obj is Symbol)
                {
                    if (((Symbol)obj).val == this.val)
                        return true;
                }
                return false;
            }

            public static bool operator ==(Symbol s1, Symbol s2)
            {
                return s1.Equals(s2);
            }

            public static bool operator !=(Symbol s1, Symbol s2)
            {
                return !s1.Equals(s2);
            }

        }

        /// <summary>
        /// The Symbol Manager is a HashTable of Strings/Unique Id. Since the string
        /// class already implements a unique GetHashCode, this should be pretty
        /// straight forward.
        /// </summary>
        class SymbolManager
        {
            private Hashtable ht;

            public SymbolManager()
            {
                ht = new Hashtable();
            }

            public Symbol registerSymbol(String symbolString)
            {
                if (!ht.ContainsValue(symbolString))
                {
                    ht.Add(symbolString.GetHashCode(), symbolString);
                }
                return (Symbol)symbolString.GetHashCode();
            }

            public String getSymbolString(Symbol symbol)
            {
                if (ht.ContainsKey(symbol))
                {
                    return (String)ht[symbol];
                }
                return null;
            }
        }
    }
}
