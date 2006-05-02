// Completed 4/04/2006
// Last Edited 4/04/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    public class CmdEntry
    {
        public delegate bool CmdEntryFunction(String str, int id, Object clientData);

        private CmdEntryFunction function;
        private Dictionary<String, CmdEntry> dictionary;
        private Command command;
        private Object clientData;

        public CmdEntry(Dictionary<String, CmdEntry> dict, Object clientData)
        {
            function = null;
            command = null;
            dictionary = dict;
            this.clientData = clientData;
        }

        public CmdEntry(Command command)
        {
            function = null;
            this.command = command;
            dictionary = null;
            clientData = null;
        }

        public CmdEntry(CmdEntryFunction f, Object clientData)
        {
            function = f;
            command = null;
            dictionary = null;
            this.clientData = clientData;
        }

        public bool parse(String str)
        {
            return parse(str, -1);
        }
        public bool parse(String str, int packetId)
        {
            if (function != null)
                return function(str, packetId, this.clientData);
            else if (command != null)
                return command.execute();
            else if (dictionary != null)
            {
                List<String> list;
                list = Utils.StringTokenizer(str, " ", null);
                for(int i = 0; i < list.Count; i++)
                {
                    String s = list[i];
                    String s2 = null;
                    
                    for(int j = i; j < list.Count; j++)
                        s2 += list[j];

                    if (dictionary.ContainsKey(s))
                    {
                        CmdEntry e = dictionary[s];
                        return e.parse(s2, packetId);
                    }
                    else
                        return false;
                }
            }
            else
                Debug.Assert(false);
            return false;
        }

        public Dictionary<String, CmdEntry> getDictionary() { return dictionary; }

    }
}
