using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Diagnostics;

namespace WinDX
{
    namespace UI
    {
        public class XmlPreferences
        {
            public enum PrefType { TypeString, TypeInt, TypeBool, TypeFloat };

            private XmlDocument prefs;
            private bool fileExisted = false;
            private XmlNode root = null;

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
                catch (XmlException e)
                {
                    Console.WriteLine("Corrupted prefs file--try deleting");
                }

                reader.Close();
                root = prefs.SelectSingleNode("PREFS");
                if (root != null)
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
                catch (Exception e)
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

                    XmlDocument doc = new XmlDocument();
                    XmlElement elem = doc.CreateElement("PREFS");
                    for (int i = 0; i < nl.Count; i++)
                        elem.AppendChild(doc.ImportNode(nl.Item(i), true));

                    doc.Save(filename);
                    fileExisted = true;
                }
                catch (XmlException e)
                {
                    Console.WriteLine("Couldn't write file--check permissions.");
                }
                return fileExisted;
            }

            public bool GetPref(String prefName, out String value)
            {
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
                catch (XmlException e)
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
                catch (XmlException e)
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
                catch (XmlException e)
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
                catch (XmlException e)
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
                        catch (XmlException e)
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
                        catch (XmlException e)
                        {
                            return false;
                        }
                }
                catch (XmlException e)
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
                        catch (XmlException e)
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
                        catch (XmlException e)
                        {
                            return false;
                        }
                }
                catch (XmlException e)
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
                    catch (XmlException e)
                    {
                        return false;
                    }
                }
                catch (XmlException e)
                {
                    return false;
                }
                return true;
            }

            public bool SetDefault(String prefName, PrefType type, String value)
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
                        elem.SetAttribute("Persistent", "false");
                        XmlElement val = prefs.CreateElement("VALUE");
                        val.InnerText = value;
                        elem.AppendChild(val);
                        XmlElement tp = prefs.CreateElement("TYPE");
                        tp.InnerText = typeS;
                        elem.AppendChild(tp);
                        root.AppendChild(elem);
                    }
                    catch (XmlException e)
                    {
                        return false;
                    }
                }
                catch (XmlException e)
                {
                    return false;
                }
                return true;
            }
        }
    }
}
