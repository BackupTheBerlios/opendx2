// Completed

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    /// <summary>
    /// The standard symbol is really just an Int32 at this time.
    /// May need to be changed if the StringTable ever got bigger.
    /// </summary>
    public struct Symbol
    {
        private int val;
        public static readonly Symbol zero = new Symbol(-1);

        public int Val { get { return val; } }

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
        { return this.val; }

        public override bool Equals(object obj)
        {
            if (obj != null && obj is Symbol)
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
    public class SymbolManager
    {
        private Dictionary<int, String> ht;
        private Dictionary<String, int> rt;
        private static int lastCode = 0;

        public SymbolManager()
        {
            ht = new Dictionary<int, String>();
            rt = new Dictionary<String, int>();
        }

        public Symbol registerSymbol(String symbolString)
        {
            if (!ht.ContainsValue(symbolString))
            {
                ht.Add(lastCode, symbolString);
                rt.Add(symbolString, lastCode++);
                return (Symbol)(lastCode - 1);
            }
            return (Symbol) rt[symbolString];
        }

        public Symbol getSymbol(String symbolString)
        {
            int val;
            if (rt.TryGetValue(symbolString, out val) )
            {
                return (Symbol) val;
            }
            return Symbol.zero;
        }

        public String getSymbolString(Symbol symbol)
        {
            String val;
            if (ht.TryGetValue(symbol.Val, out val))
                return val;
            return null;
        }

        public static SymbolManager theSymbolManager = null;
    }
}
