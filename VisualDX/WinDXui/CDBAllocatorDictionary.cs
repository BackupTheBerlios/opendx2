using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    public delegate ConfigurationDialog CDBAllocator(Form f, Node n);

    class CDBAllocatorDictionary
    {
        public CDBAllocatorDictionary() { throw new Exception("Not Yet Implemented");}

        public static CDBAllocatorDictionary theCDBAllocatorDictionary = null;

    }

}
