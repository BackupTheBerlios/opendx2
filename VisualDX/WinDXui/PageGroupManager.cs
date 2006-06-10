using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WinDX.UI
{
    class PageGroupRecord : GroupRecord
    {
        private Form page_window;
        private Form workspace;

        private int order_in_list;
        private bool windowed;
        private bool showing;

        internal PageGroupRecord(Network net, String name)
            : base(net, name)
        {
            page_window = null;
            workspace = null;
            order_in_list = 0;
            windowed = false;
            showing = false;
        }
        public void setComponents(Form page_window, Form page)
        {
            this.page_window = page_window;
            this.workspace = page;
        }
    }
    class PageGroupManager : GroupManager
    {
        public const String PageGroup = "page";

        protected override GroupRecord recordAllocator(Network net, String name)
        {
            return new PageGroupRecord(net, name);
        }

        public PageGroupManager(Network net)
            :
            base(net, SymbolManager.theSymbolManager.registerSymbol("page"))
        { }

        public static bool SupportsMacros { get { return true; } }

        public override bool parseComment(string s, string s2, int c, Network net)
        {
            throw new Exception("Not Yet Implemented");
        }
        public override bool printComment(StreamWriter s)
        {
            throw new Exception("Not Yet Implemented");
        }
        public override bool survivesMerging() { return true; }


    }
}
