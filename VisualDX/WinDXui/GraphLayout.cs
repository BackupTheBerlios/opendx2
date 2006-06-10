using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class GraphLayout
    {
        private class LayoutGroup { }
        private class LayoutInfo { }

        private const int ABSOLUTE_MINIMUM_HEIGHT_PER_LEVEL = 70;
        private const int MAXIMUM_HEIGHT_PER_LEVEL = 200;
        private const int MINIMUM_HORIZONTAL_GROUP_SPACING = 10;
        private const int MAXIMUM_HORIZONTAL_GROUP_SPACING = 100;
        private const int MINIMUM_DESIRED_HSEP = 5;
        private const int MAXIMUM_DESIRED_HSEP = 100;

        private EditorWindow editor;

        private bool adjustHopCounts(Node[] reflow, int reflow_count, ref int min) { throw new Exception("Not Yet Implemented"); }
        private void adjustAncestorHops(Node parent, int newHopCount, ref int min) { throw new Exception("Not Yet Implemented"); }
        private void adjustDescendantHops(Node parent, int newHopCount) { throw new Exception("Not Yet Implemented"); }
        private int computeRequiredHopsTo(Node n) { throw new Exception("Not Yet Implemented"); }
        private int computeRequiredHopsToSiblingsOf(Node n) { throw new Exception("Not Yet Implemented"); }
        private void fixForTooManyReceivers(Node n, ref int min) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Return TRUE if the node's standin can move to x,y without
        // causing overlap with any other node in the list.
        /// </summary>
        /// <param name="n"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        private bool nodeCanMoveTo(Node n, int x, int y) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// return TRUE if the positioning was accomplished but with collision
        /// </summary>
        /// <param name="arc"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        private bool positionSourceOverDest(Ark arc, ref int x, ref int y) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// return TRUE if the positioning was accomplished but with collision
        /// </summary>
        /// <param name="arc"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        private bool positionDestUnderSource(Ark arc, ref int x, ref int y) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// return TRUE if the positioning was accomplished but with collision
        /// </summary>
        /// <param name="arc"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="prefer_left"></param>
        /// <param name="ususableNodes"></param>
        /// <returns></returns>
        private bool positionDestBesideSibling(Ark arc, ref int x, ref int y, bool prefer_left, List<Node> ususableNodes)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// return TRUE if the positioning was accomplished but with collision
        /// </summary>
        /// <param name="arc"></param>
        /// <param name="x"></param>
        /// <returns></returns>
        private bool positionSource(Ark arc, int x)
        {
            throw new Exception("Not Yet Implemented");
        }

        private void repositionGroups(Node[] reflow, int reflowCount)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected static int HeightPerLevel;
        protected static int GroupSpacing;
        protected static int NodeSpacing;

        protected static String[] ErrorMessages = {
            "-autoLayoutHeight is outside the legal range [80 - 200]. (The default is 90.)\n",
            "-autoLayoutGroupSpacing is outside the legal range [10 - 100]. (The default is 30.)\n",
            "-autoLayoutNodeSpacing is outside the legal range [5 - 100]. (The default is 15.)\n"
        };

        protected static int ArcComparator(object a, object b) { throw new Exception("Not Yet Implemented"); }

        protected void bottomUpTraversal(Node visitKidsOf, int currentDepth, ref int min)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected bool hasConnectedInputs(Node n) { throw new Exception("Not Yet Implemented"); }
        protected bool hasConnectedOutputs(Node n, Node otherThan)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected void unmarkAllNodes(Node[] reflow, int reflowCount) { throw new Exception("Not Yet Implemented"); }

        protected bool computeBoundingBox(List<Node> nodes, ref int minx, ref int miny, ref int maxx, ref int maxy)
        { throw new Exception("Not Yet Implemented"); }
        protected bool computeBoundingBox(Node[] nodes, int count, ref int minx, ref int miny, ref int maxx,
            ref int maxy, List<Decorator> decorators) { throw new Exception("Not Yet Implemented"); }

        protected void respositionDecorators(List<Decorator> decorators, bool sameEventFlag, Node[] reflow,
            int reflowCount) { throw new Exception("Not Yet Implemented"); }

        protected void computeHopCounts(Node[] reflow, int reflowCount) { throw new Exception("Not Yet Implemented"); }

        protected void prepareAnnotationPlacement(List<Decorator> decorators, Node[] reflow, int reflowCount,
            List<Decorator> allDecorators, WorkSpace workSpace, ref int widest, ref int tallest) 
        { throw new Exception("Not Yet Implemented"); }

        List<LayoutGroup> layoutGroups;

        // Count the connected tabs and return the number of the specified
        // tab in the ordering of the visible tabs.  i.e. The 20th input
        // of Image might be the 2nd input tab.
        protected int countConnectedInputs(Node n, int input, ref int nthTab)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected int countConnectedOutputs(Node n, int output, ref int nthTab)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected void respositionNewPlacements(Node n, bool disjoint, List<Node> placed)
        {
            throw new Exception("Not Yet Implemented");
        }

        private static bool CanMoveTo(LayoutInfo info, int x, int y, Node[] reflow,
            int count, List<Decorator> decorators) { throw new Exception("Not Yet Implemented"); }

        protected bool spreadOutSpaghettiFrom(Node n, ref int min)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected int countConnectionsBetween(Node source, Node dest, bool countConsecutive)
        {
            throw new Exception("Not Yet Implemented");
        }

        public GraphLayout(EditorWindow ew)
        {
            editor = ew;
        }

        public static String SetHeightPerLevel(int height)
        {
            if ((height < ABSOLUTE_MINIMUM_HEIGHT_PER_LEVEL) || (height >
                MAXIMUM_HEIGHT_PER_LEVEL))
            {
                return ErrorMessages[0];
            }
            HeightPerLevel = height;
            return null;
        }

        public static String SetGroupSpacing(int spacing)
        {
            if (spacing < MINIMUM_HORIZONTAL_GROUP_SPACING ||
                spacing > MAXIMUM_HORIZONTAL_GROUP_SPACING)
            {
                return ErrorMessages[1];
            }
            GroupSpacing = spacing;
            return null;
        }

        public static String SetNodeSpacing(int spacing)
        {
            if (spacing < MINIMUM_DESIRED_HSEP ||
                spacing > MAXIMUM_DESIRED_HSEP)
            {
                return ErrorMessages[2];
            }
            NodeSpacing = spacing;
            return null;
        }

        public bool entireGraph(WorkSpace workspace, List<Node> nodes, List<Decorator> decorators)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static Ark IsSingleInputNoOutputNode(Node n, ref bool sharesAnOutput, bool positioned)
        {
            throw new Exception("Not Yet Implemented");
        }
        public static bool IsSingleOutputNoInputNode(Node n)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool hasNoCloserDescendant(Node source, Node dest)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// append an ancestor node of root to the list if 
        /// 1) it's not already in the list
        /// 2) The node doesn't have some other descents that it's
        ///    'more closely' related to.
        /// For each node appended to the list append the arc that reaches
        /// that node.
        /// </summary>
        /// <param name="root"></param>
        /// <param name="ancestors"></param>
        /// <param name="arcs"></param>
        /// <param name="lastCall"></param>
        public void getSpecialAncestorsOf(Node root, List<Node> ancestors, List<Ark> arcs, bool lastCall)
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
