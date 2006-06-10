using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public class PacketHandler
    {
        private bool linger;
        private PacketIF.PacketType type;
        private int number;
        private String matchString;

        public bool Linger
        {
            get { return linger; }
        }
        public PacketIF.PacketType Type
        {
            get { return type; }
        }
        public int Number
        {
            get { return number; }
        }
        public String MatchString
        {
            get { return matchString; }
        }

        private PacketIF.PacketHandlerCallback callback;
        private Object clientData;

        public PacketHandler(bool plinger,
            PacketIF.PacketType ptype,
            int pnumber)
        {
            linger = plinger;
            type = ptype;
            number = pnumber;
            callback = null;
            clientData = null;
            matchString = null;
        }
        public PacketHandler(bool plinger,
            PacketIF.PacketType ptype,
            int pnumber,
           PacketIF.PacketHandlerCallback pcallback)
        {
            linger = plinger;
            type = ptype;
            number = pnumber;
            callback = pcallback;
            clientData = null;
            matchString = null;
        }
        public PacketHandler(bool plinger,
            PacketIF.PacketType ptype,
            int pnumber,
            PacketIF.PacketHandlerCallback pcallback,
            Object pclientData)
        {
            linger = plinger;
            type = ptype;
            number = pnumber;
            callback = pcallback;
            clientData = pclientData;
            matchString = null;
        }
        public PacketHandler(bool plinger,
            PacketIF.PacketType ptype,
            int pnumber,
            PacketIF.PacketHandlerCallback pcallback,
            Object pclientData,
            String pmatchString)
        {
            linger = plinger;
            type = ptype;
            number = pnumber;
            callback = pcallback;
            clientData = pclientData;
            matchString = pmatchString;
        }

        public void callCallback(int id, String token)
        {
            callback(clientData, id, token);
        }

        public bool match(String s)
        {
            if (s == null)
                return (matchString == null);
            if (matchString == null)
                return false;
            return (matchString == s);
        }

        public bool matchFirst(String s)
        {
            if (matchString == null)
                return true;
            if (s == null)
                return false;
            return (s.Contains(matchString));
        }


    }
}
