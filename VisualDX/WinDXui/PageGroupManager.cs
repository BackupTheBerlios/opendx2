using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.IO;

namespace WinDX.UI
{
    class PageGroupRecord : GroupRecord
    {
        private Form page_window;
        private Form workspace;

        internal int order_in_list;
        internal bool windowed;
        internal bool showing;

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

        public override bool parseComment(string comment, string filename, int lineno, Network net)
        {
            if (!comment.StartsWith(" page assignment:"))
                return false;

            Regex regex = new Regex(@" page assignment:(.*)\s+order=(\d+), windowed=(\d+), showing=(\d+)");
            Match m = regex.Match(comment);
            if (!m.Success)
            {
                WarningDialog wd = new WarningDialog();
                wd.post("Unrecognized page (file {0}, line {1})", filename, lineno);
                return false;
            }
            String name = m.Groups[1].Value.Trim();
            if (!createGroup(name, net))
                return false;

            PageGroupRecord prec = (PageGroupRecord)getGroup(name);
            prec.order_in_list = int.Parse(m.Groups[2].Value);
            prec.windowed = int.Parse(m.Groups[3].Value) > 0;
            prec.showing = int.Parse(m.Groups[4].Value) > 0;

            return true;
        }
        public override bool printComment(StreamWriter s)
        {
            throw new Exception("Not Yet Implemented");
        }
        public override bool survivesMerging() { return true; }


    }
}
