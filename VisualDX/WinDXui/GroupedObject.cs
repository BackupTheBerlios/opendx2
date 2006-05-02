using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WinDX.UI
{
    public interface IGroupedObject
    {
        void addToGroup(String group, Symbol groupID);
        String getGroupName(Symbol groupID);
        Network getNetwork();
        bool parseGroupComment(String comment, String filename, int lineno);
        bool printGroupComment(Stream s);
        void setGroupName(GroupRecord gr, Symbol groupID);

        //protected Dictionary<Symbol, GroupRecord> group;
    }
}
