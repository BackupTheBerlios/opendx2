using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WinDX.UI
{
    public class GroupRecord
    {
        private Network network;
        private bool dirty;
        private String name;

        protected GroupRecord(Network network, String name)
        {
            this.network = network;
            this.dirty = false;
            this.name = name;
        }

        public bool IsDirty
        {
            get { return dirty; }
        }
        public void setDirty()
        {
            dirty = true;
        }
        public void setDirty(bool dirty)
        {
            this.dirty = dirty;
        }
        Network getNetwork() { return network; }
        public virtual bool changesWhere() { return false; }

        public String Name
        {
            get { return name; }
        }
    }

    public abstract class GroupManager
    {
        protected bool dirty;
        protected Dictionary<String, GroupRecord> groups = new Dictionary<string,GroupRecord>();
        protected DXApplication app;
        protected Network network;
        protected Symbol groupID;

        protected GroupManager(Network network, Symbol groupID)
        {
            app = DXApplication.theDXApplication;
            this.network = network;
            setDirty();
            this.groupID = groupID;
        }

        ~GroupManager()
        {
            clear();
        }

        protected abstract GroupRecord recordAllocator(Network net, String name);

        /// <summary>
        /// Remove all nodes from all groups and all groups from this manager.
        /// </summary>
        public virtual void clear()
        {
            groups.Clear();
        }

        /// <summary>
        /// Return the number of groups.
        /// </summary>
        public int GroupCount
        {
            get
            { return groups.Count; }
        }

        /// <summary>
        /// Check if the given group exists
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public bool hasGroup(String name)
        {
            return groups.ContainsKey(name);
        }

        /// <summary>
        /// Return the group record
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public GroupRecord getGroup(String name)
        {
            return groups[name];
        }

        /// <summary>
        /// Create a new group of nodes with the given name.
        /// If name is already active, then return FALSE.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="net"></param>
        /// <returns></returns>
        public bool createGroup(String name, Network net)
        {
            throw new Exception("Not yet implemented.");
        }

        /// <summary>
        /// Add more modules to the existing group.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="net"></param>
        /// <returns></returns>
        public bool addGroupMember(String name, Network net)
        {
            throw new Exception("Not yet implemented.");
        }

        /// <summary>
        /// Remove modules from the existing group.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="net"></param>
        /// <returns></returns>
        public virtual bool removeGroupMember(String name, Network net)
        {
            throw new Exception("Not yet implemented.");
        }

        /// <summary>
        /// Called when reading a network.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="net"></param>
        /// <returns></returns>
        public bool registerGroup(String name, Network net)
        {
            throw new Exception("Not yet implemented.");
        }

        /// <summary>
        /// Removes the nodes from the named group.
        /// Return false if the group does not exist.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="net"></param>
        /// <returns></returns>
        public virtual bool removeGroup(String name, Network net)
        {
            throw new Exception("Not yet implemented.");
        }

        /// <summary>
        /// return the network a group resides
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public Network getGroupNetwork(String name)
        {
            throw new Exception("Not yet implemented.");
        }

        /// <summary>
        /// Select nodes in the group
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public bool selectGroupNodes(String name)
        {
            throw new Exception("Not yet implemented.");
        }

        public bool IsDirty
        {
            get { return dirty; }
        }

        public void setDirty()
        {
            dirty = true;
        }
        public void setDirty(bool set)
        {
            dirty = set;
        }

        public virtual bool parseComment(String s, String s2, int c, Network net)
        {
            return true;
        }

        public virtual bool printComment(StreamWriter s) { return true; }
        public virtual bool printAssignment(StreamWriter s) { return true; }

        public String getManagerName()
        {
            return SymbolManager.theSymbolManager.getSymbolString(this.groupID); 
        }
        public Symbol getManagerSymbol() { return groupID; }
        public virtual bool survivesMerging() { return false; }


        public static Dictionary<String, GroupManager> BuildTheGroupManagerDictionary(Network net)
        {
            GroupManager gmgr;
            Dictionary<String, GroupManager> groupManagers = new Dictionary<string, GroupManager>();
            bool isMacro = net.IsMacro;
            if (!isMacro || ProcessGroupManager.SupportsMacros)
            {
                gmgr = new ProcessGroupManager(net);
                groupManagers.Add(gmgr.getManagerName(), gmgr);
            }
            if (!isMacro || PageGroupManager.SupportsMacros)
            {
                gmgr = new PageGroupManager(net);
                groupManagers.Add(gmgr.getManagerName(), gmgr);
            }
            if (!isMacro || AnnotationGroupManager.SupportsMacros)
            {
                gmgr = new AnnotationGroupManager(net);
                groupManagers.Add(gmgr.getManagerName(), gmgr);
            }
            return groupManagers;
        }
    }
}
