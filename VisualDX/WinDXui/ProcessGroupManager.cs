using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ProcessGroupRecord : GroupRecord
    {
        private String host;
        private String newhost;

        public ProcessGroupRecord(Network network, String name)
            : base(network, name)
        {
            host = null;
            newhost = null;
        }

        public virtual bool changesWhere() { return true; }
    }

    class ProcessHostRecord
    {
        private String args;
        private bool dirty;

        public ProcessHostRecord(String args)
        {
            this.args = args;
            dirty = false;
        }
    }

    class ProcessGroupManager : GroupManager
    {
        public const String ProcessGroup = "process";

        /// <summary>
        /// The host-argument dictionary
        /// </summary>
        protected Dictionary<String, ProcessHostRecord> arguments;

        /// <summary>
        /// A dictionary of lists of host assignment.
        /// </summary>
        protected Dictionary<String, List<String>> assignment;

        protected void attachGroup(String host, String group)
        {
            throw new Exception("Not yet implemented");
        }
        protected void detachGroup(String host, String group)
        {
            throw new Exception("Not yet implemented");
        }

        /// <summary>
        /// Update the assignment dictionary.
        /// </summary>
        /// <param name="host"></param>
        /// <param name="group"></param>
        /// <returns>false if given host does not exist</returns>
        protected bool addGroupAssignment(String host, String group)
        {
            throw new Exception("Not yet implemented");
        }
        protected bool removeGroupAssignment(String group)
        {
            throw new Exception("Not yet implemented");
        }

        protected override GroupRecord recordAllocator(Network net, String name)
        {
            return new ProcessGroupRecord(net, name);
        }


        public ProcessGroupManager(Network net)
        {
            throw new Exception("Not yet implemented");
        }

        public static bool SupportsMacros = false;

        public enum Function
        {
            ATTACH,
            DETACH
        };

        public virtual void clear()
        {
            throw new Exception("Not yet implemented");
        }

        /// <summary>
        /// return the host name assigned to a group.
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public String getGroupHost(String name)
        {
            throw new Exception("Not yet implemented");
        }
        public String getGroupHost(int n)
        {
            throw new Exception("Not yet implemented");
        }
        public String getGroupNewHost(String name)
        {
            throw new Exception("Not yet implemented");
        }
        public String getGroupNewHost(int n)
        {
            throw new Exception("Not yet implemented");
        }
        public bool getGroupHostDirty(String name)
        {
            throw new Exception("Not yet implemented");
        }
        public void clearGroupHostDirty(String name)
        {
            throw new Exception("Not yet implemented");
        }

        /// <summary>
        /// Assign a host name to a group
        /// </summary>
        /// <param name="groupname"></param>
        /// <param name="hostname"></param>
        /// <returns>return false if the given group doesn't exist</returns>
        public bool assignHost(String groupname, String hostname)
        {
            throw new Exception("Not yet implemented");
        }
        public bool assignHost(int n, String hostname)
        {
            throw new Exception("Not yet implemented");
        }

        /// <summary>
        /// Really change host names when OK is pressed
        /// </summary>
        public void updateHosts()
        {
            throw new Exception("Not yet implemented");
        }

        /// <summary>
        /// clear the temporary storage of host names
        /// </summary>
        public void clearNewHosts()
        {
            throw new Exception("Not yet implemented");
        }

        /// <summary>
        /// Access the host's arguments
        /// </summary>
        /// <param name="host"></param>
        /// <returns></returns>
        public String getArgument(String host)
        {
            throw new Exception("Not yet implemented");
        }
        public bool getArgumentDirty(String host)
        {
            throw new Exception("Not yet implemented");
        }
        public void clearArgumentDirty(String host)
        {
            throw new Exception("Not yet implemented");
        }
        public void assignArgument(String host, String args)
        {
            throw new Exception("Not yet implemented");
        }
        public void clearArgument()
        {
            throw new Exception("Not yet implemented");
        }

        /// <summary>
        /// Remove modules from the existing group
        /// </summary>
        /// <param name="name"></param>
        /// <param name="net"></param>
        /// <returns></returns>
        public virtual bool removeGroup(String name, Network net)
        {
            throw new Exception("Not yet implemented");
        }

        /// <summary>
        /// Create the assignment dictionary
        /// </summary>
        /// <returns></returns>
        Dictionary<String, List<String>> createAssignment()
        {
            throw new Exception("Not yet implemented");
        }

        /// <summary>
        /// Clear the assignment dictionary
        /// </summary>
        void clearAssignment()
        {
            throw new Exception("Not yet implemented");
        }

        /// <summary>
        /// send commands to the executive
        /// </summary>
        /// <param name="func"></param>
        public void sendAssignment(int func)
        {
            throw new Exception("Not yet implemented");
        }

        public void updateAssignment()
        {
            throw new Exception("Not yet implemented");
        }


        public override bool parseComment(string s, string s2, int c, Network net)
        {
            throw new Exception("Not yet implemented");
            return base.parseComment(s, s2, c, net);
        }

        public override bool printComment(System.IO.Stream s)
        {
            throw new Exception("Not yet implemented");
            return base.printComment(s);
        }

        public override bool printAssignment(System.IO.Stream s)
        {
            throw new Exception("Not yet implemented");
            return base.printAssignment(s);
        }
    }
}
