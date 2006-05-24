using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Diagnostics;

namespace WinDX.UI
{
    public class PanelAccessManager
    {
        // This is a list of panels that can NOT be opened. 
        // We make it private, because it does not get notification when
        // panels are deleted.  Instead we implement the access methods
        // which make sure the panels being operated on are still in the
        // network.
        private List<int> inaccessiblePanels = new List<int>();
        private List<String> inaccessibleGroups = new List<string>();

        protected Network network;
        ControlPanel cp;
        bool isActive;

        protected void activate()
        {
            isActive = true;
        }
        protected void deactivate()
        {
            isActive = false;
        }

        public PanelAccessManager(Network net)
        {
            network = net;
            this.cp = null;
            isActive = false;
        }
        public PanelAccessManager(Network net, ControlPanel cp)
        {
            network = net;
            this.cp = cp;
            isActive = false;
        }

        ~PanelAccessManager()
        {
            clear();
        }

        public Network getNetwork() { return this.network; }
        public ControlPanel getControlPanel() { return cp; }

        public bool cfgParseInaccessibleComment(String comment,
            String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool cfgPrintInaccessibleComment(StreamWriter stream)
        {
            throw new Exception("Not Yet Implemented");
        }
        // Return TRUE if cfgPrintInaccessibleComment needs to be called.
        public bool hasCfgComment()
        {
            return IsActivated;
        }

        // Add a panel (specified by instance number) to the list of inaccessible
        // panels.
        public void addInaccessiblePanel(int instance)
        {
            if (!inaccessiblePanels.Contains(instance))
            {
                inaccessiblePanels.Add(instance);
                network.setFileDirty();
            }
            activate();
        }
        public void addInaccessibleGroup(String name)
        {
            if (isAccessibleGroup(name))
            {
                inaccessibleGroups.Add(name);
                network.setFileDirty();
            }
            activate();
        }

        // Allow access to all panels.
        public void allowAllPanelAccess()
        {
            if (inaccessiblePanels.Count != 0)
            {
                inaccessiblePanels.Clear();
                network.setFileDirty();
            }
            activate();
        }
        public void allowAllGroupAccess()
        {
            if (inaccessibleGroups.Count != 0)
            {
                inaccessibleGroups.Clear();
                network.setFileDirty();
            }
            activate();
        }

        // Free memory allow all panels/groups acess and deactivate().
        public void clear()
        {
            allowAllPanelAccess();
            allowAllGroupAccess();
            deactivate();
        }

        // Get the index'th (1 based) inaccessible panel.
        public ControlPanel getInaccessiblePanel(int index)
        {
            Debug.Assert(index >= 0 && index < inaccessiblePanels.Count);
            int instance = inaccessiblePanels[index];
            ControlPanel p = network.getPanelByInstance(instance);
            if (p == null)
            {
                // cp was deleted from teh netowkr so save it and remove it later.
                inaccessiblePanels.RemoveAt(index);
            }
            return p;
        }
        public String getInaccessibleGroup(int index)
        {
            PanelGroupManager pgm = network.getPanelGroupManager();
            Debug.Assert(index >= 0 && index < inaccessibleGroups.Count);

            String name = inaccessibleGroups[index];
            List<int> lcp = null;
            if (!pgm.getPanelGroup(name, ref lcp))
            {
                inaccessibleGroups.RemoveAt(index);
                name = null;
            }
            return name;
        }

        public bool isAccessiblePanel(int instanceNumber)
        {
            return !IsActivated || !inaccessiblePanels.Contains(instanceNumber);
        }
        public bool isAccessibleGroup(String name)
        {
            if (!IsActivated)
                return true;

            if (inaccessibleGroups.Contains(name))
                return false;

            return true;
        }

        public bool IsActivated { get { return isActive; } }
    }
}
