using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    public class DisplayNode : DrivenNode
    {
        public const int WHERE = 3;

        private static void HandleImageMessage(Object clientData, int id, String line)
        {
            DisplayNode n = (DisplayNode)clientData;
            n.handleImageMessage(id, line);
        }

        private PanelAccessManager panelAccessManager;
        private bool printCommonComments(StreamWriter sw) { return printCommonComments(sw, null); }
        private bool printCommonComments(StreamWriter sw, String indent)
        {
            throw new Exception("Not Yet Implemented");
        }

        private bool parseCommonComments(String comment, String file, int lineno)
        {
            // Display title comment is of the form
            // title: value = somestring
            if (comment.StartsWith(" title:"))
            {
                int skipl = " title: value = ".Length;
                setTitle(comment.Substring(skipl));
                return true;
            }
            else if (comment.StartsWith(" depth:"))
            {
                // If we have an image window, then changing its depth will put the 
                // proper value into our WHERE param.  If we don't then  we'll set it
                // directly.
                int depth;
                Regex regex = new Regex(@" depth: value = (\d+)");
                Match m = regex.Match(comment);
                if (m.Success)
                {
                    depth = Int32.Parse(m.Groups[1].ToString());
                    if (image != null)
                        image.changeDepth(depth);
                    else
                        setDepth(depth);
                }
                return true;
            }
            else if (Utils.ParseGeometryComment(comment, file, lineno,
           ref this.xpos, ref this.ypos, ref this.width, ref this.height, null))
            {
                ImageWindow w = image;
                if (w != null && (this.xpos != Utils.UnspecifiedPosition) &&
                    DXApplication.theDXApplication.applyWindowPlacements())
                {
                    // The comments, if they exist may cause a resize, but we don't
                    // want to cause an execution that normally results from  a resize. 
                    //
                    w.setGeometry(this.xpos, this.ypos, this.width, this.height);
                }
                return true;
            }
            return false;
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
            Regex regex = new Regex(@"\d+:  IMAGE:  ##\d+: (\d+)x(\d+)");
            Match m = regex.Match(line);
            int x = Int32.Parse(m.Groups[1].Value);
            int y = Int32.Parse(m.Groups[2].Value);

            image.newCamera(x, y);
            if (!image.Visible)
            {
                image.sensitizeChangeImageName(true);
                image.Show();
            }
        }
       
        protected override void prepareToSendValue(int index, Parameter p)
        {
            if (!userSpecifiedWhere)
            {
                // Create a new ImageWindow if necessary.
                if (image == null)
                {
                    openImageWindow(false);
                }
                if (p.IsInput && index == 3)
                {
                    String s = image.getDisplayString();
                    base.setInputValue(index, s, DXTypeVals.WhereType, false);
                    Regex regex = new Regex(@".*##(\d+)");
                    Match m = regex.Match(s);
                    int newWindowId = Int32.Parse(m.Groups[1].Value);
                    if (this.windowId != newWindowId)
                    {
                        String message = String.Format("IMAGE:  ##{0}", windowId);
                        DXPacketIF pif = DXApplication.theDXApplication.getPacketIF();
                        pif.setHandler(PacketIF.PacketType.INFORMATION, null, this, message);
                        windowId = newWindowId;
                        message = String.Format("IMAGE:  ##{0}", windowId);
                        pif.setHandler(PacketIF.PacketType.INFORMATION, DisplayNode.HandleImageMessage,
                            this, message);
                    }
                }
            }
        }

        protected override void prepareToSendNode()
        {
            if (!userSpecifiedWhere)
            {
                if (image == null)
                    openImageWindow(false);

                if (!isInputSet(3))
                    notifyWhereChange(false);
            }
        }

        protected override bool netPrintAuxComment(StreamWriter s)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected override bool netParseAuxComment(string comment, string filename, int lineno)
        {
            return base.netParseAuxComment(comment, filename, lineno) ||
                parseCommonComments(comment, filename, lineno);
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
            List<ImageWindow> imageList = this.getNetwork().getImageList();
            ImageWindow w = null;
            DXWindow anchor = DXApplication.theDXApplication.getAnchor();

            // If this can be the anchor window, then try and get it first.
            if (canBeAnchor && anchor is ImageWindow && imageList.Contains((ImageWindow)anchor))
            {
                ImageWindow image_anchor = (ImageWindow)anchor;
                Debug.Assert(image_anchor.IsAnchor);
                if (!image_anchor.IsAssociatedWithNode)
                    w = image_anchor;
            }

            // If the anchor window wasn't available, try for any other window.
            if (w == null)
            {
                foreach (ImageWindow iw in imageList)
                {
                    if (!iw.IsAssociatedWithNode && (canBeAnchor || !iw.IsAnchor))
                    {
                        w = iw;
                        break;
                    }
                }
            }

            if (alloc_one && (w == null))
            {
                w = DXApplication.theDXApplication.newImageWindow(this.getNetwork());
                w.initialize();
            }
            return w;
        }


        /// <summary>
        /// Update any UI visuals that may be based on the state of this
        /// node.   Among other times, this is called after receiving a message
        /// from the executive.
        /// </summary>
        /// <param name="unmanage"></param>
        protected override void reflectStateChange(bool unmanage)
        {
           // Nothing to do
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
            // If Where is wired up, then treat it the way we treat a user supplied window.
            // This handles wiring, unwiring, and unsetting.  The case of setting (thru
            // the cdb) is handled in this->setInputValue().  DisplayNodes still cling
            // tenaciously to their ImageWindows.  If you run the net and dxui provides
            // an ImageWindow for the DisplayNode, you won't be able to flip the Where
            // param tab up and so dxui will always provide the ImageWindow and the only
            // way to get around that is to delete the DisplayNode and place a new one.
            if ((input) && (index == WHERE))
            {
                if (status == NodeParameterStatusChange.ParameterArkAdded)
                {
                    this.userSpecifiedWhere = true;
                    if (this.image != null)
                    {
                        ImageWindow iw = this.image;
                        this.image = null;
                        if (iw.IsAnchor == false)
                            iw = null;
                    }
                }
                // Flipping the param tab up, might be considered a way to indicate
                // that userSpecifiedWhere should be reset to FALSE.  This was not
                // the behavior in 3.1.2.
                // Set network dirty because changing userSpecifiedWhere requires 
                // a call to DisplayNode::prepareToSend. 
                //
                else if (status == NodeParameterStatusChange.ParameterArkRemoved)
                {
                    this.userSpecifiedWhere = false;
                }
                else if (status == NodeParameterStatusChange.ParameterSetValueToDefaulting)
                {
                    this.userSpecifiedWhere = false;
                    this.getNetwork().setDirty();
                }
            }
            base.ioParameterStatusChanged(input, index, status);
        }

        public DisplayNode(NodeDefinition nd, Network net, int instnc) :
            base(nd, net, instnc)
        {
            xpos = ypos = Utils.UnspecifiedPosition;
            width = height = Utils.UnspecifiedDimension;
            image = null;

            // It's makes no sense to even think about creating an image window
            // for a Display node in a macro.

            userSpecifiedWhere = net.IsMacro;
            title = null;
            panelAccessManager = null;
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
            base.initialize();
            depth = 24;
            windowId = 0;
            lastImage = true;

            panelAccessManager = new PanelAccessManager(getNetwork());

            // Try to find an extant image window that isn't being used.
            ImageWindow w = getUnassociatedImageWindow(false);
            if (w != null)
                associateImage(w);

            Parameter p = getInputParameter(3);
            p.setDirty();
            return true;
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
            if (depth != this.depth)
            {
                this.depth = depth;
                if (this.image != null)
                    setInputValue(WHERE, this.image.getDisplayString(), DXTypeVals.WhereType, true);
            }
        }
        public int Depth { get { return depth; } }

        public override DXTypeVals setInputValue(int index, string value, 
            DXTypeVals type, bool send)
        {
            if (index == 3)
            {
                if (image == null)
                {
                    userSpecifiedWhere = true;
                    DXTypeVals tmp = base.setInputValue(index, value, type, send);
                    userSpecifiedWhere = (tmp != DXTypeVals.UndefinedType);
                    return tmp;
                }
                else
                {
                    String cp = getInputValueString(index);
                    DXTypeVals retVal = base.setInputValue(index, cp, type, send); 
                    return retVal;
                }
            }
            else
                return base.setInputValue(index, value, type, send);
        }

        public virtual bool associateImage(ImageWindow w)
        {
            if (w == null)
            {
                if (image == null)
                    return true;
                w = image;
                if (!w.associateNode(null))
                    return false;
                image = null;
            }
            else
            {
                if (image != null)
                    return false;

                if (!w.associateNode(this))
                    return false;

                image = w;
            }

            if (title != null && image != null)
                image.Text = title;
            return true;
        }

        public void notifyWhereChange(bool send)
        {
            setInputValue(3, "", DXTypeVals.WhereType, send);
            windowId = 0;
        }

        public virtual void openImageWindow() { openImageWindow(true); }
        public virtual void openImageWindow(bool manage)
        {
            ImageWindow w = this.image;
            if (w == null)
            {
                if (userSpecifiedWhere)
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("The user interface can not open the Image window for the {0} " +
                        "tool because it has the input parameter '{1}' set and " +
                        "therefore does not own the window.", NameString, getInputNameString(3));
                    return;
                }
                else
                {
                    w = getUnassociatedImageWindow();
                    Debug.Assert(w != null);
                    associateImage(w);
                    userSpecifiedWhere = false;
                    notifyWhereChange(manage);
                }

                if (xpos != Utils.UnspecifiedPosition &&
                    DXApplication.theDXApplication.applyWindowPlacements())
                {
                    w.setGeometry(xpos, ypos, width, height);
                }
            }
            image.sensitizeChangeImageName(true);
            if (manage)
                w.Show();
        }

        public override void setGroupName(GroupRecord gr, Symbol groupID)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void setLastImage(bool last)
        {
            if (this.lastImage != last)
            {
                lastImage = last;
                if (this.image != null)
                    notifyWhereChange(true);
            }
        }
        public bool isLastImage()
        {
            return lastImage;
        }
    }
}
