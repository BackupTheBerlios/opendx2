using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Diagnostics;

namespace WinDX.UI
{
    public class XmlPreferences
    {
        public enum PrefType { TypeString, TypeInt, TypeBool, TypeFloat };

        private XmlDocument prefs;
        private bool fileExisted = false;
        private XmlNode root = null;
        private const int MaxStoredList = 10;

        public XmlPreferences()
        {
            prefs = new XmlDocument();
        }

        public bool ReadPrefs(String filename)
        {
            XmlTextReader reader = new XmlTextReader(filename);

            if (reader == null)
            {
                return false;
            }
            try
            {
                prefs.Load(reader);
                fileExisted = true;
            }
            catch (XmlException)
            {
                Console.WriteLine("Corrupted prefs file--try deleting");
            }

            reader.Close();
            root = prefs.SelectSingleNode("PREFS");
            if (root == null)
            {
                XmlElement elem = prefs.CreateElement("PREFS");
                prefs.AppendChild(elem);
                root = elem;
            }
            return fileExisted;
        }

        public bool CreatePrefs()
        {
            Debug.Assert(prefs != null);
            try
            {
                XmlElement elem = prefs.CreateElement("PREFS");
                prefs.AppendChild(elem);
                root = elem;
            }
            catch (Exception)
            {
                return false;
            }
            return true;
        }

        public bool WritePrefs(String filename)
        {
            fileExisted = false;

            // Find only Persistent nodes and write them out to the prefs
            // file. This is done by creating a new XmlDocument, importing
            // appropriate nodes and adding them before writing.

            try
            {
                String lookup = "DXUIPREF[@Persistent='true']";
                XmlNodeList nl = root.SelectNodes(lookup);

                if (nl.Count > 0)
                {
                    XmlDocument doc = new XmlDocument();
                    XmlElement elem = doc.CreateElement("PREFS");
                    doc.AppendChild(elem);
                    for (int i = 0; i < nl.Count; i++)
                        elem.AppendChild(doc.ImportNode(nl.Item(i), true));

                    doc.Save(filename);
                    fileExisted = true;
                }
            }
            catch (XmlException)
            {
                Console.WriteLine("Couldn't write file--check permissions.");
            }
            return fileExisted;
        }

        public bool GetPref(String prefName, out String value)
        {
            if (root == null)
            {
                value = null;
                return false;
            }

            value = "";
            if (prefs == null)
                return false;

            // Xml is in the form.
            //<PREF Name='UIRoot' Persistent="true"><TYPE>string</TYPE><VALUE>/usr/local/dx</VALUE></PREF>
            //<PREF Name='wizard' Persistent="false"><TYPE>bool</TYPE><VALUE>false</VALUE></PREF>

            String lookup = "DXUIPREF[@Name='";
            lookup += prefName;
            lookup += "']";

            String val = null;

            try
            {
                XmlNode n = root.SelectSingleNode(lookup);

                if (n == null)
                    return false;

                XmlNode n2 = n.SelectSingleNode("VALUE");
                val = n2.InnerText;
            }
            catch (XmlException)
            {
                Console.WriteLine("Corrupted prefs file--try deleting it");
            }

            if (val.Length == 0)
            {
                value = null;
                return true;
            }
            value = val;
            return true;
        }

        public bool GetPref(String prefName, out bool value)
        {
            if (root == null)
            {
                value = false;
                return false;
            }

            value = false;
            if (prefs == null)
                return false;

            // Xml is in the form.
            //<PREF Name='UIRoot' Persistent="true"><TYPE>string</TYPE><VALUE>/usr/local/dx</VALUE></PREF>
            //<PREF Name='wizard' Persistent="false"><TYPE>bool</TYPE><VALUE>false</VALUE></PREF>

            String lookup = "DXUIPREF[@Name='";
            lookup += prefName;
            lookup += "']";

            String val = null;

            try
            {
                XmlNode n = root.SelectSingleNode(lookup);

                if (n == null)
                    return false;

                XmlNode n2 = n.SelectSingleNode("VALUE");
                val = n2.InnerText;
            }
            catch (XmlException)
            {
                Console.WriteLine("Corrupted prefs file--try deleting it");
            }

            if (val.CompareTo("true") == 0)
                value = true;
            else
                value = false;

            return true;
        }

        public bool GetPref(String prefName, out int value)
        {
            value = 0;

            if (prefs == null)
                return false;

            // Xml is in the form.
            //<PREF Name='UIRoot' Persistent="true"><TYPE>string</TYPE><VALUE>/usr/local/dx</VALUE></PREF>
            //<PREF Name='wizard' Persistent="false"><TYPE>bool</TYPE><VALUE>false</VALUE></PREF>

            String lookup = "DXUIPREF[@Name='";
            lookup += prefName;
            lookup += "']";

            String val = null;

            try
            {
                XmlNode n = root.SelectSingleNode(lookup);

                if (n == null)
                    return false;

                XmlNode n2 = n.SelectSingleNode("VALUE");
                val = n2.InnerText;
            }
            catch (XmlException)
            {
                Console.WriteLine("Corrupted prefs file--try deleting it");
            }

            value = Int32.Parse(val);

            return true;
        }

        public bool GetPref(String prefName, out PrefType type, out String value)
        {
            type = PrefType.TypeString;
            value = "";
            if (prefs == null)
                return false;

            // Xml is in the form.
            //<PREF Name='UIRoot' Persistent="true"><TYPE>string</TYPE><VALUE>/usr/local/dx</VALUE></PREF>
            //<PREF Name='wizard' Persistent="false"><TYPE>bool</TYPE><VALUE>false</VALUE></PREF>

            String lookup = "DXUIPREF[@Name='";
            lookup += prefName;
            lookup += "']";

            String val = null, typeS = null;

            try
            {
                XmlNode n = root.SelectSingleNode(lookup);

                if (n == null)
                    return false;

                XmlNode n2 = n.SelectSingleNode("VALUE");
                val = n2.InnerText;

                n2 = n.SelectSingleNode("TYPE");
                typeS = n2.InnerText;
            }
            catch (XmlException)
            {
                Console.WriteLine("Corrupted prefs file--try deleting it");
            }

            if (val.Length == 0)
            {
                value = null;
                return true;
            }

            value = val;
            if (typeS.CompareTo("bool") == 0)
                type = PrefType.TypeBool;
            else if (typeS.CompareTo("int") == 0)
                type = PrefType.TypeInt;
            else if (typeS.CompareTo("float") == 0)
                type = PrefType.TypeFloat;
            else
                type = PrefType.TypeString;

            return true;
        }

        /// <summary>
        /// Get a value for a specific preference name.
        /// </summary>
        /// <param name="prefName">the param name to query</param>
        /// <param name="value">sets value to a list of strings for the pref</param>
        /// <returns>true if pref found, false if not found</returns>
        public bool GetPref(String prefName, out List<String> value)
        {
            String val;
            bool gotPref = GetPref(prefName, out val);
            if (!gotPref)
            {
                value = null;
                return false;
            }
            //Now break the string into a list
            value = Utils.StringTokenizer(val, "|", null);
            return true;
        }

        /// <summary>
        /// Add a preference value to the list of values all ready existing.
        /// </summary>
        /// <param name="prefName"></param>
        /// <param name="value"></param>
        /// <param name="persist"></param>
        /// <returns></returns>
        public bool AddListPref(String prefName, String value) { return AddListPref(prefName, value, true); }
        public bool AddListPref(String prefName, String value, bool persist)
        {
            String curPrefVal;
            if (GetPref(prefName, out curPrefVal))
            {
                List<String> valueL = Utils.StringTokenizer(curPrefVal, "|", null);
                valueL.Add(value);
                String newval = "";
                for (int i = 0; i < valueL.Count - 1; i++)
                    newval += valueL[i] + "|";
                newval += valueL[valueL.Count - 1];
                return SetPref(prefName, newval, persist);
            }
            else
                return SetPref(prefName, value, persist);
        }

        public bool SetPref(String prefName, String value, bool persist)
        {
            if (prefs == null)
            {
                return false;
            }

            String lookup = "DXUIPREF[@Name='" + prefName + "']";

            try
            {
                XmlNode n = root.SelectSingleNode(lookup);
                if (n != null)
                {
                    try
                    {
                        XmlElement elem = prefs.CreateElement("DXUIPREF");
                        elem.SetAttribute("Name", prefName);
                        if (persist)
                            elem.SetAttribute("Persistent", "true");
                        else
                            elem.SetAttribute("Persistent", "false");
                        XmlElement val = prefs.CreateElement("VALUE");
                        val.InnerText = value;
                        elem.AppendChild(val);
                        root.ReplaceChild(elem, n);
                    }
                    catch (XmlException)
                    {
                        return false;
                    }
                }
                else
                    try
                    {
                        XmlElement elem = prefs.CreateElement("DXUIPREF");
                        elem.SetAttribute("Name", prefName);
                        if (persist)
                            elem.SetAttribute("Persistent", "true");
                        else
                            elem.SetAttribute("Persistent", "false");
                        XmlElement val = prefs.CreateElement("VALUE");
                        val.InnerText = value;
                        elem.AppendChild(val);
                        root.AppendChild(elem);
                    }
                    catch (XmlException)
                    {
                        return false;
                    }
            }
            catch (XmlException)
            {
                return false;
            }

            return true;
        }

        public bool SetPref(String prefName, PrefType type, String value, bool persist)
        {
            if (prefs == null)
                return false;

            String lookup = "DXUIPREF[@Name='" + prefName + "']";

            String typeS = null;
            switch (type)
            {
                case PrefType.TypeString:
                    typeS = "string";
                    break;
                case PrefType.TypeInt:
                    typeS = "int";
                    break;
                case PrefType.TypeBool:
                    typeS = "bool";
                    break;
                case PrefType.TypeFloat:
                    typeS = "float";
                    break;
            }

            try
            {
                XmlNode n = root.SelectSingleNode(lookup);
                if (n != null)
                {
                    try
                    {
                        XmlElement elem = prefs.CreateElement("DXUIPREF");
                        elem.SetAttribute("Name", prefName);
                        if (persist)
                            elem.SetAttribute("Persistent", "true");
                        else
                            elem.SetAttribute("Persistent", "false");
                        XmlElement val = prefs.CreateElement("VALUE");
                        val.InnerText = value;
                        elem.AppendChild(val);
                        XmlElement tp = prefs.CreateElement("TYPE");
                        tp.InnerText = typeS;
                        elem.AppendChild(tp);
                        root.ReplaceChild(elem, n);
                    }
                    catch (XmlException)
                    {
                        return false;
                    }
                }
                else
                    try
                    {
                        XmlElement elem = prefs.CreateElement("DXUIPREF");
                        elem.SetAttribute("Name", prefName);
                        if (persist)
                            elem.SetAttribute("Persistent", "true");
                        else
                            elem.SetAttribute("Persistent", "false");
                        XmlElement val = prefs.CreateElement("VALUE");
                        val.InnerText = value;
                        elem.AppendChild(val);
                        XmlElement tp = prefs.CreateElement("TYPE");
                        tp.InnerText = typeS;
                        elem.AppendChild(tp);
                        root.AppendChild(elem);
                    }
                    catch (XmlException)
                    {
                        return false;
                    }
            }
            catch (XmlException)
            {
                return false;
            }
            return true;
        }

        public bool SetDefault(String prefName, String value)
        {
            if (prefs == null)
                return false;
            String lookup = "DXUIPREF[@Name='" + prefName + "']";

            try
            {
                XmlNode n = root.SelectSingleNode(lookup);
                if (n != null)
                    return true;
                try
                {
                    XmlElement elem = prefs.CreateElement("DXUIPREF");
                    elem.SetAttribute("Name", prefName);
                    elem.SetAttribute("Persistent", "false");
                    XmlElement val = prefs.CreateElement("VALUE");
                    val.InnerText = value;
                    elem.AppendChild(val);
                    root.AppendChild(elem);
                }
                catch (XmlException)
                {
                    return false;
                }
            }
            catch (XmlException)
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// Set a Default for a Pref. If it already exists, just return.
        /// In order to set a pref persistently (saves out to file) use
        /// SetPref.
        /// </summary>
        /// <param name="prefName"></param>
        /// <param name="type"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public bool SetDefault(String prefName, PrefType type, String value)
        {
            return SetDefault(prefName, type, value, false);
        }
        public bool SetDefault(String prefName, PrefType type, String value, bool persistent)
        {
            if (prefs == null)
                return false;
            String lookup = "DXUIPREF[@Name='" + prefName + "']";
            String typeS = null;
            switch (type)
            {
                case PrefType.TypeString:
                    typeS = "string";
                    break;
                case PrefType.TypeInt:
                    typeS = "int";
                    break;
                case PrefType.TypeBool:
                    typeS = "bool";
                    break;
                case PrefType.TypeFloat:
                    typeS = "float";
                    break;
            }

            // First see if it exists. If so just return.
            try
            {
                XmlNode n = root.SelectSingleNode(lookup);
                if (n != null)
                    return true;
                try
                {
                    XmlElement elem = prefs.CreateElement("DXUIPREF");
                    elem.SetAttribute("Name", prefName);
                    if(persistent)
                        elem.SetAttribute("Persistent", "true");
                    else
                        elem.SetAttribute("Persistent", "false");
                    XmlElement val = prefs.CreateElement("VALUE");
                    val.InnerText = value;
                    elem.AppendChild(val);
                    XmlElement tp = prefs.CreateElement("TYPE");
                    tp.InnerText = typeS;
                    elem.AppendChild(tp);
                    root.AppendChild(elem);
                }
                catch (XmlException)
                {
                    return false;
                }
            }
            catch (XmlException)
            {
                return false;
            }
            return true;
        }
        public static XmlPreferences theXmlPreferences = new XmlPreferences();
    }
}