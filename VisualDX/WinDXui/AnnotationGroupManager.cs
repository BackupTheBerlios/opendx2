using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WinDX.UI
{
    class AnnotationGroupRecord : GroupRecord
    {
        public AnnotationGroupRecord(Network net, String name)
            :
            base(net, name) { }

    }
    class AnnotationGroupManager : GroupManager
    {
        protected override GroupRecord recordAllocator(Network net, String name)
        {
            return new AnnotationGroupRecord(net, name);
        }

        public static bool SupportsMacros { get { return true; } }

        public AnnotationGroupManager(Network net)
            : base(net, SymbolManager.theSymbolManager.registerSymbol("annotation"))
        {
        }

        public override bool printComment(StreamWriter s)
        {
            throw new Exception("Not Yet Implemented");
        }
        public override bool parseComment(string s, string s2, int c, Network net)
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
