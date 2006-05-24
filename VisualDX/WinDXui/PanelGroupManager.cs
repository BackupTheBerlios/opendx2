using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Diagnostics;

namespace WinDX.UI
{
    public class PanelGroupManager
    {
        protected Dictionary<String, List<int>> panelGroups = new Dictionary<string,List<int>>();
        protected Network network;


        // Make a list of ControlPanels instance numbers from a list of ControlPanel
        // instance numbers making sure that each panel is still in the network.
        protected void buildPanelList(ref List<int> src, ref List<int> dest)
        {
            throw new Exception("Not Yet Implemented");
        }

        public PanelGroupManager(Network n)
        {
            network = n;
        }

        ~PanelGroupManager()
        {
            clear();
        }

        /// <summary>
        /// Remove all panels from all groups and all groups from this panel manager.
        /// </summary>
        public void clear()
        {
            panelGroups.Clear();
        }

        /// <summary>
        /// Create an empty group of control panels with the given name.
        /// If name is already active, then return FALSE.
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public bool createPanelGroup(String name)
        {
            List<int> l = null;

            if (name == null || name.Length == 0)
                return false;

            if (getPanelGroup(name, ref l))
                return false; // named group already exists.

            l = new List<int>();

            try
            {
                panelGroups.Add(name, l);
            }
            catch (Exception)
            {
                return false;
            }

            network.setFileDirty();
            return true;
        }

        /// <summary>
        /// Add the panel indicated by panelInstance to the given named panel group.
        /// The group must already exist, and the panelInstance must not be present
        /// in the group. The panelInstance, should be a member of the network 
        /// with which this PanelGroupManager is associated.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="panelInstance"></param>
        /// <returns></returns>
        public bool addGroupMember(String name, int panelInstance)
        {
            List<int> l;

            Debug.Assert(panelInstance > 0);
            if (panelGroups.TryGetValue(name, out l))
            {
                Debug.Assert(l.Contains(panelInstance));
                try
                {
                    l.Add(panelInstance);
                }
                catch (Exception)
                {
                    return false;
                }
            }
            else
                return false;

            network.setFileDirty();
            return true;
        }

        /// <summary>
        /// Removes the given panelInstance from the named panel group.
        /// Return FALSE if either the group does not exist or the instance
        /// is not a member of the given group.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="panelInstance"></param>
        /// <returns></returns>
        public bool removeGroupMember(String name, int panelInstance)
        {
            List<int> l;

            Debug.Assert(panelInstance > 0);
            try
            {
                l = panelGroups[name];
                l.Remove(panelInstance);
            }
            catch (Exception) { return false; }

            network.setFileDirty();
            return true;
        }

        /// <summary>
        /// Removes the named panel group from this managers list of named groups.
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public bool removePanelGroup(String name)
        {
            try
            {
                panelGroups.Remove(name);
            }
            catch (Exception) { return false; }

            network.setFileDirty();
            return true;
        }

        /// <summary>
        /// Get a panel group by name.  If l is not NULL, then return in a l, a
        /// list of ControlPanel instance numbers each of which is a member of the 
        /// group.
        /// Returns FALSE if the named group does not exist in this panel manager.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="l"></param>
        /// <returns></returns>
        public bool getPanelGroup(String name, ref List<int> panels)
        {
            List<int> l;
            if (panelGroups.TryGetValue(name, out l))
            {
                if (panels == null)
                    return false;

                buildPanelList(ref l, ref panels);
            }
            else
                return false;

            return true;
        }

        /// <summary>
        /// Get a panel group by 1 based index.  If l is not NULL, then return in 
        /// a l, a list of ControlPanel instance numbers, each of which is a 
        /// member of the group.
        /// Returns NULL if the group does not exist in this panel manager, 
        /// otherwise the name of the group is returned.
        /// </summary>
        /// <param name="gindex"></param>
        /// <param name="l"></param>
        /// <returns></returns>
        public bool getPanelGroup(int gindex, ref List<int> l)
        {
            throw new Exception("Not Yet Implemented");
        }


        public bool cfgParseComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool cfgPrintComment(StreamWriter stream)
        {
            throw new Exception("Not Yet Implemented");
        }

        public Network getNetwork() { return network; }

        //public int getGroupCount() { return panelGroups.Count(); }

    }
}
