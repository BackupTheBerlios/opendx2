using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WinDX.UI
{
    public class DisplayNode : DrivenNode
    {
        private static void HandleImageMessage(Object clientData, int id, String line)
        {
            throw new Exception("Not Yet Implemented");
        }

        private PanelAccessManager panelAccessManager;
        private bool printCommonComments(StreamWriter sw) { return printCommonComments(sw, null); }
        private bool printCommonComments(StreamWriter sw, String indent)
        {
            throw new Exception("Not Yet Implemented");
        }

        private bool parseCommonComments(String comment, String file, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        private int xpos, ypos, width, height;

        protected bool userSpecifiedWhere;
        protected ImageWindow image;
        protected String title;
        protected int depth;
        protected int windowId;
        protected bool lastImage;

        protected virtual void handleImageMessage(int id, String line)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected void prepareToSendValue(int index, Parameter p)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected void prepareToSendNode()
        {
            throw new Exception("Not Yet Implemented");
        }

        protected override bool netPrintAuxComment(StreamWriter s)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected override bool netParseAuxComment(string comment, string filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected override string inputValueString(int i, string prefix)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected override bool printIOComment(StreamWriter s, bool input, int index, string indent, bool valueOnly)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// Search through the networks list of image windows trying to find one
        /// that is not associated with a (display) node.  If canBeAnchor is TRUE
        /// then any ImageWindow will do and if available we return an anchor
        /// window, otherwise the returned ImageWindow must not by an anchor window.
        /// If one is not found in the current list, then create one if requested.
        /// </summary>
        /// <returns></returns>
        protected ImageWindow getUnassociatedImageWindow()
        { return getUnassociatedImageWindow(true, true); }
        protected ImageWindow getUnassociatedImageWindow(bool alloc_one)
        { return getUnassociatedImageWindow(alloc_one, true); }
        protected ImageWindow getUnassociatedImageWindow(bool alloc_one, bool canBeAnchor)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// Update any UI visuals that may be based on the state of this
        /// node.   Among other times, this is called after receiving a message
        /// from the executive.
        /// </summary>
        /// <param name="unmanage"></param>
        protected override void reflectStateChange(bool unmanage)
        {
            throw new Exception("The method or operation is not implemented.");
        }


        /// <summary>
        /// Parse the node specific info from an executive message.
        /// Returns the number of attributes parsed.
        /// </summary>
        /// <param name="line"></param>
        /// <returns></returns>
        protected override int handleNodeMsgInfo(string line)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        /// <summary>
        /// Monitor the status of the WHERE param.  If the tab is connected, then
        /// treat it as if the user had supplied a value.
        /// </summary>
        /// <param name="input"></param>
        /// <param name="index"></param>
        /// <param name="status"></param>
        protected override void ioParameterStatusChanged(bool input, int index, Node.NodeParameterStatusChange status)
        {
            throw new Exception("Not Yet Implemented");
        }

        public DisplayNode(NodeDefinition nd, Network net, int instnc) :
            base(nd, net, instnc)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override void switchNetwork(Network from, Network to, bool silently)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override int getMessageIdParamNumber()
        {
            throw new Exception("Not Yet Implemented");
        }

        public override bool cfgParseComment(string comment, string file, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override bool cfgPrintNode(StreamWriter sw, PrintType destination)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override bool initialize()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual void setTitle(String title) { setTitle(title, false); }
        public virtual void setTitle(String title, bool fromServer)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override string getTitle()
        {
            throw new Exception("Not Yet Implemented");
        }

        public void setDepth(int depth)
        {
            throw new Exception("Not Yet Implemented");
        }
        public int Depth { get { return depth; } }

        public override DXTypeVals setInputValue(int index, string value, DXTypeVals type, bool send)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool associateImage(ImageWindow w)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void notifyWhereChange(bool send)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual void openImageWindow() { openImageWindow(true); }
        public virtual void openImageWindow(bool manage)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override void setGroupName(GroupRecord gr, Symbol groupID)
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
