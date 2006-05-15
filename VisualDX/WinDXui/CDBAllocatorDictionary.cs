using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    // What a nasty class. What it is supposed to be is a Dictionary, only it needs
    // to return some set value if the lookup fails. Thus I don't believe that
    // Dictionary<> can be used.

    public delegate ConfigurationDialog CDBAllocator(Form f, Node n);

    class CDBAllocatorDictionary : Dictionary<Symbol, CDBAllocator>
    {
        CDBAllocator defaultAlloc;

        public CDBAllocatorDictionary() 
        {
            defaultAlloc = ConfigurationDialog.AllocateConfigurationDialog;
        }

        public static CDBAllocatorDictionary theCDBAllocatorDictionary = null;

        public bool setDefaultAllocator(CDBAllocator nda)
        {
            defaultAlloc = nda;
            return true;
        }

        public ConfigurationDialog allocate(Symbol namesym, Form f, Node n)
        {
            try
            {
                CDBAllocator a = this[namesym];
                return a(f, n);
            }
            catch (KeyNotFoundException)
            {
                return null;
            }
        }

        public CDBAllocator findAllocator(String name)
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
        public CDBAllocator findAllocator(Symbol name)
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
        
    }

}
