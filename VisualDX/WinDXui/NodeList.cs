using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    public class NodeList : List<Node>
    {
        private Dictionary<String, List<Node>> nodeDict;

        public NodeList()
        {
            nodeDict = new Dictionary<string, List<Node>>();
        }

        protected List<Node> getSubList(Node node)
        {
            String node_class = node.GetType().ToString();
            List<Node> def;

            if (!nodeDict.TryGetValue(node_class, out def))
            {
                def = new List<Node>();
                nodeDict.Add(node_class, def);
            }
            return def;
        }

        public List<Node> makeClassifiedNodeList(Type classtype)
        {
            Debug.Assert(classtype != null);
            int size = nodeDict.Count;

            foreach(KeyValuePair<String, List<Node>> kvp in nodeDict)
            {
                String cn = kvp.Key;
                if (cn != classtype.ToString())
                    continue;
                return kvp.Value;;
            }

            List<Node> l = null;
            foreach (Node n in this)
            {
                if (n.GetType().ToString() == classtype.ToString())
                {
                    if (l == null) l = new List<Node>();
                    l.Add(n);
                }
            }
            return l;
        }

        public void Add(Node node)
        {
            base.Add(node);

            if (node.needsFastSort())
            {
                List<Node> nl = getSubList(node);
                Debug.Assert(!nl.Contains(node));
                nl.Add(node);
            }
        }

        public void Replace(int index, Node node)
        {
            Node oldNode = this[index];
            this[index] = node;

            if (oldNode.needsFastSort())
            {
                List<Node> nl = getSubList(oldNode);
                Debug.Assert(nl.Contains(oldNode));
                nl.Remove(oldNode);
            }

            if (node.needsFastSort())
            {
                List<Node> nl = getSubList(node);
                Debug.Assert(!nl.Contains(node));
                nl.Add(node);
            }
        }

        public void Clear()
        {
            base.Clear();
            nodeDict.Clear();
        }

        public void RemoveAt(int index)
        {
            Node oldNode = this[index];
            this.RemoveAt(index);

            if (oldNode.needsFastSort())
            {
                List<Node> nl = getSubList(oldNode);
                Debug.Assert(nl.Contains(oldNode));
                nl.Remove(oldNode);
            }
        }

        public void Insert(int index, Node node)
        {
            base.Insert(index, node);

            if (node.needsFastSort())
            {
                List<Node> nl = getSubList(node);
                Debug.Assert(nl.Contains(node));
                nl.Add(node);
            }
        }

    }
}
