using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    class ImageNode : DisplayNode
    {
        private class ParamConst
        {
            public const int IMAGETAG = 1;
            public const int OBJECT = 2;
            public const int WHERE = 3;
            public const int USEVECTOR = 4;
            public const int TO = 5;
            public const int FROM = 6;
            public const int WIDTH = 7;
            public const int RESOLUTION = 8;
            public const int ASPECT = 9;
            public const int UP = 10;
            public const int VIEWANGLE = 11;
            public const int PROJECTION = 12;
            public const int OPTIONS = 13;
            public const int BUTTON_STATE = 14;
            public const int BUTTON_UP_APPROX = 15;
            public const int BUTTON_DOWN_APPROX = 16;
            public const int BUTTON_UP_DENSITY = 17;
            public const int BUTTON_DOWN_DENSITY = 18;
            public const int RENDER_MODE = 19;
            public const int DEFAULT_CAMERA = 20;
            public const int RESET_CAMERA = 21;
            public const int BACKGROUND = 22;
            public const int THROTTLE = 23;
            public const int RECENABLE = 24;
            public const int RECFILE = 25;
            public const int RECFORMAT = 26;
            public const int RECRESOLUTION = 27;
            public const int RECASPECT = 28;
            public const int AAENABLE = 29;
            public const int AALABELS = 30;
            public const int AATICKS = 31;
            public const int AACORNERS = 32;
            public const int AAFRAME = 33;
            public const int AAADJUST = 34;
            public const int AACURSOR = 35;
            public const int AAGRID = 36;
            public const int AACOLORS = 37;
            public const int AAANNOTATION = 38;
            public const int AALABELSCALE = 39;
            public const int AAFONT = 40;
            public const int INTERACTIONMODE = 41;
            public const int IMAGENAME = 42;

            //
            // new AutoAxes parameters
            //
            public const int AA_XTICK_LOCS = 43;
            public const int AA_YTICK_LOCS = 44;
            public const int AA_ZTICK_LOCS = 45;
            public const int AA_XTICK_LABELS = 46;
            public const int AA_YTICK_LABELS = 47;
            public const int AA_ZTICK_LABELS = 48;

            //
            // On behalf of Java Explorer
            //
            public const int JAVA_OPTIONS = 49;

            public static int[] translateInputs = {
                0,
                USEVECTOR,
                OBJECT,
                WHERE,
                TO,
                FROM,
                WIDTH,
                RESOLUTION,
                ASPECT,
                UP,
                OPTIONS,
                AAENABLE,
                AALABELS,
                AATICKS,
                AACORNERS,
                AAFRAME,
                AAADJUST,
                AACURSOR,
                RECENABLE,
                RECFILE,
                THROTTLE,
                RECFORMAT,
                PROJECTION,
                VIEWANGLE,
                BUTTON_STATE,
                BUTTON_UP_APPROX,
                BUTTON_DOWN_APPROX,
                BUTTON_UP_DENSITY,
                BUTTON_DOWN_DENSITY,
                RENDER_MODE,
                BACKGROUND,
                AAGRID,
                AACOLORS,
                AAANNOTATION,
                AALABELSCALE,
                AAFONT
            };
        }

        private bool printCommonComments(StreamWriter sw, String indent)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected bool parseCommonComments(String comment, String file, int lineno)
        {
            Regex regex = new Regex(@" interaction mode = (.*)");
            Match m = regex.Match(comment);
            if (m.Success)
            {
                setInteractionMode(m.Groups[1].Value);

                // Now since this is the last comment, ask the ImageWindow 
                // to refresh its state from our new cfg state. 
                if (image != null)
                    image.updateFromNewCfgState();
                return true;
            }
            else if (comment.StartsWith(" internal caching:"))
            {
                regex = new Regex(@" internal caching: (\d+)");
                m = regex.Match(comment);
                if (m.Success)
                {
                    int cacheval = Int32.Parse(m.Groups[1].Value);
                    switch (cacheval)
                    {
                        case 0:
                            InternalCacheability = Cacheability.InternalsNotCached;
                            break;
                        case 1:
                            InternalCacheability = Cacheability.InternalsFullyCached;
                            break;
                        case 2:
                            InternalCacheability = Cacheability.InternalsCacheOnce;
                            break;
                        default:
                            return false;
                            break;
                    }
                    return true;
                }
            }
            return false;
        }

        // The mode that was saved in the .net/.cfg file (when not data-driven). 
        private DirectInteractionMode saveInteractionMode;

        // cache value for the nodes internal to the image macro.
        private Cacheability internalCache;

        // FIXME!: this should really be being done through ImageWindow via
        // ImageNode::reflectStateChange().  ImageNode has no business setting
        // senstivities of another object.  That is ImageWindow's decision.
        //
        private void updateWindowSensitivities()
        { }

        private Node getWebOptionsNode()
        {
            throw new Exception("Not Yet Implemented");
        }

        private static bool SendString(Object o, PacketIF.PacketIFCallback pif, 
            StreamWriter sw, String str, bool a)
        {
            throw new Exception("Not Yet Implemented");
        }
        private static void FormatMacro(StreamWriter sw, PacketIF.PacketIFCallback pif, Object o,
            String[] s, bool a)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected static String[] GifMacroTxt;
        protected static String[] VrmlMacroTxt;
        protected static String[] ImageMacroTxt;
        protected static String[] DXMacroTxt;

        // The height which isn't stored in the parameter list.
        protected int height;

        // A boolean which says whether we're translating old values
        // into new ones.
        protected bool translating;

        // Fields and members to control the image macro.  When a parameter
        // that affects the image macro changes, macroDirty should be set
        // indicating that when ready, the system should update the macro.
        protected bool macroDirty;
        protected virtual bool sendMacro(DXPacketIF pif)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool printMacro(StreamWriter sw, PacketIF.PacketIFCallback pif,
            Object callbackData, bool viasocket) { throw new Exception("Not Yet Implemented"); }

        // Fields for handling and storing parts of the image messages
        // sent from the executive.
        protected override void handleImageMessage(int id, string line)
        {
            throw new Exception("Not Yet Implemented");
            base.handleImageMessage(id, line);
        }

        public override void openDefaultWindow(System.Windows.Forms.Form parent)
        {
            throw new Exception("Not Yet Implemented");
            base.openDefaultWindow(parent);
        }

        // Let the caller of openDefaultWindow() know what kind of window she's getting.
        // This is intended for use in EditorWindow so that we can sanity check the number
        // of cdbs were going to open before kicking off the operation and so that we
        // don't question the user before opening large numbers of interactors.
        // A name describing the type of window can be written into window_name in order
        // to enable nicer warning messages.
        protected virtual bool defaultWindowIsCDB(String window_name)
        {
            if (window_name != null)
                window_name = "Image Window";
            return false;
        }

        protected double[,] boundingBox = new double[4,3];

        // Overrides of Node members to ensure that the correct stuff
        // gets printed and sent to the server.  The image node prevents
        // "RECENABLE", whether to record frames or not, from being saved.
        protected override string inputValueString(int i, string prefix)
        {
            throw new Exception("Not Yet Implemented");
            return base.inputValueString(i, prefix);
        }
        protected override bool printIOComment(StreamWriter s, bool input, int index, string indent, bool valueOnly)
        {
            throw new Exception("Not Yet Implemented");
            return base.printIOComment(s, input, index, indent, valueOnly);
        }

        protected virtual void notifyProjectionChange(bool newPersp)
        {
            int parameter;
            if (newPersp)
                parameter = ParamConst.WIDTH;
            else
                parameter = ParamConst.VIEWANGLE;
            useDefaultInputValue(parameter, false);
            if (newPersp)
                parameter = ParamConst.VIEWANGLE;
            else
                parameter = ParamConst.WIDTH;
            useAssignedInputValue(parameter, false);
        }
        protected virtual void notifyUseVectorChange(bool newUse)
        {
            if (newUse == UseVector)
                return;

            DXPacketIF pif = DXApplication.theDXApplication.getPacketIF();
            if (pif != null)
            {
                if (newUse)
                {
                    useAssignedInputValue(ParamConst.TO, false);
                    useAssignedInputValue(ParamConst.FROM, false);
                    useAssignedInputValue(ParamConst.WIDTH, false);
                    useAssignedInputValue(ParamConst.UP, false);
                    useAssignedInputValue(ParamConst.VIEWANGLE, false);
                    useAssignedInputValue(ParamConst.PROJECTION, false);
                    setInputDirty(ParamConst.TO);
                    setInputDirty(ParamConst.FROM);
                    setInputDirty(ParamConst.WIDTH);
                    setInputDirty(ParamConst.UP);
                    setInputDirty(ParamConst.VIEWANGLE);
                    setInputDirty(ParamConst.PROJECTION);
                }
                else
                {
                    useDefaultInputValue(ParamConst.TO, false);
                    useDefaultInputValue(ParamConst.FROM, false);
                    useDefaultInputValue(ParamConst.WIDTH, false);
                    useDefaultInputValue(ParamConst.UP, false);
                    useDefaultInputValue(ParamConst.VIEWANGLE, false);
                }
            }
        }

        protected override string netEndOfMacroNodeString(string prefix)
        {
            String buf = "";
            String gpn = getGroupName(SymbolManager.theSymbolManager.getSymbol(ProcessGroupManager.ProcessGroup));
            if (gpn != null)
                buf = String.Format("CacheScene({0}Image_{1}_in_{2}, {3}Image_{4}_out_1, {5}Image_{6}_out_2)[group: \"{7}\"];\n",
                    prefix, InstanceNumber, ParamConst.IMAGETAG,
                    prefix, InstanceNumber, prefix, InstanceNumber, gpn);
            else
                buf = String.Format("CacheScene({0}Image_{1}_in_{2}, {3}Image_{4}_out_1, {5}Image_{6}_out_2);\n",
                    prefix, InstanceNumber, ParamConst.IMAGETAG,
                    prefix, InstanceNumber, prefix, InstanceNumber);

            return buf;
        }

        public override bool netParseComment(string comment, string file, int lineno)
        {
            int major, minor, micro;
            String buf;

            if (getNetwork().getDXMajorVersion() < 3)
            {
                if (comment.Contains("input["))
                {
                    Regex regex = new Regex(@"(.*input\[)(\d)+(\].*)");
                    Match m = regex.Match(comment);

                    if (m.Success)
                    {
                        int input = Int32.Parse(m.Groups[2].Value);
                        String newcom = m.Groups[1].Value + ParamConst.translateInputs[input].ToString() +
                            m.Groups[3].Value;
                        comment = newcom;
                    }
                }
            }
            getNetwork().getVersion(out major, out minor, out micro);

            if (major == 2 && minor >= 0 && micro >= 1)
                translating = true;
            bool res = base.netParseComment(comment, file, lineno);
            translating = false;

            return res;
        }

        protected override bool netPrintAuxComment(StreamWriter s)
        {
            throw new Exception("Not Yet Implemented");
            return base.netPrintAuxComment(s);
        }
        protected override bool netParseAuxComment(string comment, string filename, int lineno)
        {
            return base.netParseAuxComment(comment, filename, lineno) ||
                parseCommonComments(comment, filename, lineno);
        }

        protected override int handleNodeMsgInfo(string line)
        {
            throw new Exception("Not Yet Implemented");
            return base.handleNodeMsgInfo(line);
        }
        protected override void reflectStateChange(bool unmanage)
        { // Intentionally left blank
        }
        protected override void ioParameterStatusChanged(bool input, int index, NodeParameterStatusChange status)
        {
            switch (index)
            {
                case ParamConst.THROTTLE:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded ||
                            status == NodeParameterStatusChange.ParameterArkRemoved)
                        {
                            bool st = isInputDefaulting(ParamConst.THROTTLE);
                            image.sensitizeThrottleDialog(st);
                        }
                        else if (status == NodeParameterStatusChange.ParameterValueChanged ||
                            status == NodeParameterStatusChange.PatemeterSetValueChanged)
                        {
                            double t;

                            getThrottle(out t);
                            image.updateThrottleDialog(t);
                        }
                    }
                    break;

                case ParamConst.RECENABLE:
                case ParamConst.RECFILE:
                case ParamConst.RECFORMAT:
                case ParamConst.RECRESOLUTION:
                case ParamConst.RECASPECT:
                    if (image != null)
                    {
                        // This used to say isRecFileInputSet() instead of TRUE
                        // but it always worked because isRecFileInputSet always returns
                        // the wrong value.  Nowdays, we only want to revisit the sensitivity
                        // of the dialogs, not the sensitivity of the command anyway.
                        image.sensitizePrintImageDialog(true);
                        image.sensitizeSaveImageDialog(true);
                    }
                    break;

                case ParamConst.BACKGROUND:
                    if (image != null)
                    {
                        if ((long)(status & NodeParameterStatusChange.ParameterArkAdded) > 0 ||
                            (long)(status & NodeParameterStatusChange.ParameterArkRemoved) > 0)
                        {
                            image.sensitizeBackgroundColorDialog(!IsBGColorConnected);
                        }
                        else if ((long)(status & NodeParameterStatusChange.ParameterValueChanged) > 0 ||
                            (long)(status & NodeParameterStatusChange.PatemeterSetValueChanged) > 0)
                        {
                            String color;
                            getBackgroundColor(out color);
                            image.updateBGColorDialog(color);
                        }
                    }
                    break;

                case ParamConst.AAENABLE:
                    if (image != null)
                        image.setAutoAxesDialogEnable();
                    break;

                case ParamConst.AALABELS:
                    if (image != null)
                        image.setAutoAxesDialogLabels();
                    break;

                case ParamConst.AATICKS:
                    if (image != null)
                        image.setAutoAxesDialogTicks();
                    break;

                case ParamConst.AA_XTICK_LOCS:
                    if (image != null)
                        image.setAutoAxesDialogXTickLocs();
                    break;

                case ParamConst.AA_YTICK_LOCS:
                    if (image != null)
                        image.setAutoAxesDialogYTickLocs();
                    break;

                case ParamConst.AA_ZTICK_LOCS:
                    if (image != null)
                        image.setAutoAxesDialogZTickLocs();
                    break;

                case ParamConst.AA_XTICK_LABELS:
                    if (image != null)
                        image.setAutoAxesDialogXTickLabels();
                    break;

                case ParamConst.AA_YTICK_LABELS:
                    if (image != null)
                        image.setAutoAxesDialogYTickLabels();
                    break;

                case ParamConst.AA_ZTICK_LABELS:
                    if (image != null)
                        image.setAutoAxesDialogZTickLabels();
                    break;

                case ParamConst.AACORNERS:
                    if (image != null)
                        image.setAutoAxesDialogCorners();
                    break;

                case ParamConst.AAFRAME:
                    if (image != null)
                        image.setAutoAxesDialogFrame();
                    break;

                case ParamConst.AAADJUST:
                    if (image != null)
                        image.setAutoAxesDialogAdjust();
                    break;

                case ParamConst.AACURSOR:
                    if (image != null)
                        image.setAutoAxesDialogCursor();
                    break;

                case ParamConst.AAGRID:
                    if (image != null)
                        image.setAutoAxesDialogGrid();
                    break;

                case ParamConst.AACOLORS:
                    if (image != null)
                        image.setAutoAxesDialogAnnotationColors();
                    break;

                case ParamConst.AAANNOTATION:
                    if (image != null)
                        image.setAutoAxesDialogAnnotationColors();
                    break;

                case ParamConst.AALABELSCALE:
                    if (image != null)
                        image.setAutoAxesDialogLabelScale();
                    break;

                case ParamConst.AAFONT:
                    if(image != null)
                        image.setAutoAxesDialogFont();
                    break;

                case ParamConst.INTERACTIONMODE:
                    if (image != null)
                    {
                        bool stat = IsInteractionModeConnected;
                        image.sensitizeViewControl(!stat);
                    }
                    break;

                case ParamConst.IMAGENAME:
                    if (image != null)
                    {
                        bool stat = isInputConnected(ParamConst.IMAGENAME);
                        if ((!stat) && (isInputDefaulting(ParamConst.IMAGENAME)))
                            setTitle(null);
                        else
                            setTitle(getInputValueString(ParamConst.IMAGENAME));
                        image.sensitizeChangeImageName(!stat);
                    }
                    break;

                case ParamConst.RENDER_MODE:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded)
                            image.sensitizeRenderMode(false);
                        else if (status == NodeParameterStatusChange.ParameterArkRemoved)
                            image.sensitizeRenderMode(true);
                        else if ((long)(status & (NodeParameterStatusChange.ParameterValueChanged |
                       NodeParameterStatusChange.PatemeterSetValueChanged)) > 0)
                            image.updateRenderingOptionsDialog();
                    }
                    break;

                case ParamConst.BUTTON_UP_APPROX:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded)
                            image.sensitizeButtonUpApprox(false);
                        else if (status == NodeParameterStatusChange.ParameterArkRemoved)
                            image.sensitizeButtonUpApprox(true);
                        else if ((long)(status & (NodeParameterStatusChange.ParameterValueChanged |
                            NodeParameterStatusChange.PatemeterSetValueChanged)) > 0)
                            image.updateRenderingOptionsDialog();
                    }
                    break;

                case ParamConst.BUTTON_DOWN_APPROX:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded)
                            image.sensitizeButtonDownApprox(false);
                        else if (status == NodeParameterStatusChange.ParameterArkRemoved)
                            image.sensitizeButtonDownApprox(true);
                        else if ((long)(status & (NodeParameterStatusChange.ParameterValueChanged |
                            NodeParameterStatusChange.PatemeterSetValueChanged)) > 0)
                            image.updateRenderingOptionsDialog();
                    }
                    break;

                case ParamConst.BUTTON_UP_DENSITY:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded)
                            image.sensitizeButtonUpDensity(false);
                        else if (status == NodeParameterStatusChange.ParameterArkRemoved)
                            image.sensitizeButtonUpDensity(true);
                        else if ((long)(status & (NodeParameterStatusChange.ParameterValueChanged |
                            NodeParameterStatusChange.PatemeterSetValueChanged)) > 0)
                            image.updateRenderingOptionsDialog();
                    }
                    break;

                case ParamConst.BUTTON_DOWN_DENSITY:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded)
                            image.sensitizeButtonDownDensity(false);
                        else if (status == NodeParameterStatusChange.ParameterArkRemoved)
                            image.sensitizeButtonDownDensity(true);
                        else if ((long)(status & (NodeParameterStatusChange.ParameterValueChanged |
                            NodeParameterStatusChange.PatemeterSetValueChanged)) > 0)
                            image.updateRenderingOptionsDialog();
                    }
                    break;
                default:
                    break;
            }
            base.ioParameterStatusChanged(input, index, status);
        }


        protected void setAutoAxesTickLocs(int param, ref double t, int size, bool send)
        {
            throw new Exception("Not Yet Implemented");
        }

        public ImageNode(NodeDefinition nd, Network net, int instnc)
            : base(nd, net, instnc)
        {
            ImageDefinition imnd = (ImageDefinition)nd;
            macroDirty = true;
            translating = false;

            // Anything below here also belongs in this->setDefaultCfgState().
            saveInteractionMode = DirectInteractionMode.NONE;
            internalCache = imnd.DefaultInternalCacheability;
        }

        ~ImageNode()
        { }

        public override bool initialize()
        {
            DXApplication.theDXApplication.setBusyCursor(true);
            base.initialize();
            if (!setMessageIdParameter(ParamConst.IMAGETAG))
                return false;

            enableVector(false, false);
            if (image != null)
                image.allowDirectInteraction(false);

            height = -1;

            enableSoftwareRendering(true, false);
            setButtonUp(true, false);

            DXApplication.theDXApplication.setBusyCursor(false);

            return true;
        }

        public override void setTitle(string title, bool fromServer)
        {
            if (!isInputConnected(ParamConst.IMAGENAME))
            {
                if (title == null || title.Length == 0)
                    useDefaultInputValue(ParamConst.IMAGENAME, false);
                else
                {
                    if (fromServer && isInputDefaulting(ParamConst.IMAGENAME))
                        setInputAttributeFromServer(ParamConst.IMAGENAME, title, DXTypeVals.StringType);
                    else
                    {
                        String v = getInputValueString(ParamConst.IMAGENAME);
                        if (v != title)
                            setInputValue(ParamConst.IMAGENAME, title, DXTypeVals.StringType, false);
                    }
                }
            }
            if (title != null && title.StartsWith("\""))
            {
                String tmp = title.Substring(1).Trim();
                if (tmp.EndsWith("\""))
                    tmp = tmp.Substring(0, tmp.Length - 1);
                base.setTitle(tmp);
            }
            else
                base.setTitle(title, fromServer);
        }

        // FIXME: I am confused.  (At last a genuine FIXME comment.)
        // If the param is defaulting, then rely on the superclass.  If the param isn't
        // defaulting then fetch the value from the node.  If the node has a null value,
        // then rely on the superclass.  Should there ever be a difference between
        // what the superclass thinks and what this thinks?  I don't think so.
        // Wierdness: this and the the superclass support {set,get}Title,
        // but the superclass versions use an ioComment whereas this uses an input
        // parameter.
        public override string getTitle()
        {
            // Using the node's value if the input is defaulting would prevent us
            // from using "nodename: filename".
            if (isInputDefaulting(ParamConst.IMAGENAME))
                return base.getTitle();

            // Make sure the value is a valid string and strip off the quotes
            // and use it, if it is.
            if (getInputSetValueType(ParamConst.IMAGENAME) == DXTypeVals.StringType)
            {
                String v = getInputValueString(ParamConst.IMAGENAME);
                if (v != null || v.Length != 0 || v == "NULL")
                    return base.getTitle();

                // Match quoted string
                Regex regex = new Regex(@"""([^""]+)""");
                Match m = regex.Match(v);
                if(!m.Success)
                    return base.getTitle();

                String t = m.Groups[1].Value;

                title = t;
                return title;
            }

            return base.getTitle();
        }

        public override DXTypeVals setInputValue(int index, string value, 
            DXTypeVals type, bool send)
        {
            DXTypeVals result;

            bool trans = translating;
            translating = false;

            switch (index)
            {
                case ParamConst.USEVECTOR:
                    if (trans)
                    {
                        if (value.StartsWith("1"))
                            value = "0";
                        else if (value.StartsWith("2"))
                            value = "1";
                    }
                    if (value == "NULL")
                        value = "0";
                    notifyUseVectorChange(!value.StartsWith("0"));
                    break;

                case ParamConst.AAENABLE:
                    if (trans)
                    {
                        if (value.StartsWith("1"))
                            value = "0";
                        else if (value.StartsWith("2"))
                            value = "1";
                    }
                    break;

                case ParamConst.RECENABLE:
                    if (trans)
                    {
                        if (value.StartsWith("1"))
                            value = "0";
                        else if (value.StartsWith("2"))
                            value = "1";
                    }
                    break;

                case ParamConst.PROJECTION:
                    notifyProjectionChange(!value.StartsWith("0"));
                    break;

                case ParamConst.RENDER_MODE:
                    if (value == "\"hardware\"" ||
                    value == "hardware")
                        value = "1";
                    else if (value == "\"software\"" ||
                        value == "software")
                        value = "0";
                    else if (trans)
                    {
                        if (value.StartsWith("1"))
                            value = "0";
                        else if (value.StartsWith("2"))
                            value = "1";
                    }
                    if (type == DXTypeVals.StringType)
                        type = DXTypeVals.FlagType;
                    break;
                case ParamConst.BUTTON_UP_APPROX:
                case ParamConst.BUTTON_DOWN_APPROX:
                    if (value == "\"flat\"")
                        value = "\"none\"";
                    break;
            }

            result = base.setInputValue(index, value, type, send);
            translating = trans;
            return result;
        }

        public bool sendValues() { return sendValues(true); }
        public bool sendValues(bool ignoreDirty)
        {
            throw new Exception("Not Yet Implemented");
        }

        public override bool printValues(StreamWriter sw, string prefix, PrintType dest)
        {
            throw new Exception("Not Yet Implemented");
            return base.printValues(sw, prefix, dest);
        }
        public override bool associateImage(ImageWindow w)
        {
            throw new Exception("Not Yet Implemented");
            return base.associateImage(w);
        }

        Cacheability InternalCacheability
        {
            get { return internalCache; }
            set { internalCache = value; }
        }

        public bool UseVector
        {
            get
            {
                Parameter p = getInputParameter(ParamConst.USEVECTOR);
                String s = p.getValueOrDefaultString();
                return s != "0";
            }
        }
        public void enableVector(bool use, bool send)
        {
            if (use == UseVector)
                return;

            setInputValue(ParamConst.USEVECTOR, use ? "1" : "0", DXTypeVals.IntegerType, send);
            Parameter p = getInputParameter(ParamConst.USEVECTOR);
            p.setDirty();
        }
        public void setTo(double to, bool send)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setFrom(double from, bool send)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setResolution(int x, int y, bool send)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setWidth(double w, bool send)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setAspect(double a, bool send)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setThrottle(double a, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setUp(ref double up, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setBox(double[,] box, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setProjection(bool persp, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setViewAngle(double angle, bool send) { throw new Exception("Not Yet Implemented"); }
        
        public void setButtonUp(bool up, bool send) {
            String s = (up ? "1" : "2");
            setInputValue(ParamConst.BUTTON_STATE, s, DXTypeVals.IntegerType, send);
        }

        public void setApprox(bool up, String approx, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setDensity(bool up, int density, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setBackgroundColor(String color, bool send) { throw new Exception("Not Yet Implemented"); }

        public void getTo(out double to) { throw new Exception("Not Yet Implemented"); }
        public void getFrom(out double from) { throw new Exception("Not Yet Implemented"); }
        public void getResolution(out int x, out int y) { throw new Exception("Not Yet Implemented"); }
        public void getWidth(out double w) { throw new Exception("Not Yet Implemented"); }
        public void getAspect(out double a) { throw new Exception("Not Yet Implemented"); }
        public void getThrottle(out double v) { throw new Exception("Not Yet Implemented"); }
        public void getUp(out double up) { throw new Exception("Not Yet Implemented"); }
        public void getBox(out double[,] box) { throw new Exception("Not Yet Implemented"); }
        public void getProjection(out bool persp) { throw new Exception("Not Yet Implemented"); }
        public void getViewAngle(out double angle) { throw new Exception("Not Yet Implemented"); }
        public bool IsButtonUp { get { throw new Exception("Not Yet Implemented"); } }
        public void getApprox(bool up, out String approx) { throw new Exception("Not Yet Implemented"); }
        public void getDensity(bool up, out int density) { throw new Exception("Not Yet Implemented"); }
        public void getBackgroundColor(out String color) { throw new Exception("Not Yet Implemented"); }
        public void getRecordEnable(out int x) { throw new Exception("Not Yet Implemented"); }
        public void getRecordResolution(out int x, out int y) { throw new Exception("Not Yet Implemented"); }
        public void getRecordAspect(out double aspect) { throw new Exception("Not Yet Implemented"); }

        public bool useAutoAxes() { throw new Exception("Not Yet Implemented"); }

        public void setRecordEnable(int use, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setRecordResolution(int x, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setRecordAspect(double aspect, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setRecordFile(String file, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setRecordFormat(String format, bool send) { throw new Exception("Not Yet Implemented"); }
        public void getRecordFile(out String file) { throw new Exception("Not Yet Implemented"); }
        public void getRecordFormat(out String format) { throw new Exception("Not Yet Implemented"); }

        public void enableSoftwareRendering(bool use, bool send)
        {
            String s = use ? "0" : "1";

            if (use)
            {
                if (!isInputDefaulting(ParamConst.BUTTON_UP_DENSITY))
                    useDefaultInputValue(ParamConst.BUTTON_UP_DENSITY, false);
                if (!isInputDefaulting(ParamConst.BUTTON_DOWN_DENSITY))
                    useDefaultInputValue(ParamConst.BUTTON_DOWN_DENSITY, false);
            }
            else
            {
                if (isInputSet(ParamConst.BUTTON_UP_DENSITY) &&
                    isInputDefaulting(ParamConst.BUTTON_UP_DENSITY))
                    useAssignedInputValue(ParamConst.BUTTON_UP_DENSITY, false);
                if (isInputSet(ParamConst.BUTTON_DOWN_DENSITY) &&
                    isInputDefaulting(ParamConst.BUTTON_DOWN_DENSITY))
                    useAssignedInputValue(ParamConst.BUTTON_DOWN_DENSITY, false);
            }
            setInputValue(ParamConst.RENDER_MODE, s, DXTypeVals.StringType, send);
        }

        //
        public void getAutoAxesCorners(out double[] dval) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesCursor(out double x, out double y, out double z) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesStringList(int index, out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesLabels(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesAnnotation(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesColors(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesXTickLabels(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesYTickLabels(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesZTickLabels(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesString(int index, out String sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesFont(out String sval) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesTicks(out int t1, out int t2, out int t3) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesTicks(out int t) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesXTickLocs(out double[] t) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesYTickLocs(out double[] t) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesZTickLocs(out double[] t) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesInteger(int index) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesEnable() { throw new Exception("Not Yet Implemented"); }
        public double getAutoAxesDouble(int index) { throw new Exception("Not Yet Implemented"); }
        public double getAutoAxesLabelScale() { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesTicksCount() { throw new Exception("Not Yet Implemented"); }


        public void setAutoAxesCorners(double[] dval, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesCursor(double x, double y, double z, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesFlag(int index, bool state, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesFrame(bool state, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesGrid(bool state, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesAdjust(bool state, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesInteger(int index, int d, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesEnable(int d, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesDouble(int index, double d, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesLabelScale(double d, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesStringList(int index, String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesLabels(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesAnnotation(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesColors(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesXTickLocs(double[] t, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesYTickLocs(double[] t, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesZTickLocs(double[] t, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesXTickLabels(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesYTickLabels(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesZTickLabels(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesString(int index, String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesFont(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesTicks(int t1, int t2, int t3, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesTicks(int t, bool send) { throw new Exception("Not Yet Implemented"); }

        public void disableAutoAxesCorners(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesCorners(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesCursor(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesTicks(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesXTickLocs(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesYTickLocs(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesZTickLocs(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesStringList(int index, bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesAnnotation(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesLabels(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesColors(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesXTickLabels(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesYTickLabels(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesZTickLabels(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesString(int index, bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesFont(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesEnable(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesFrame(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesGrid(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesAdjust(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesLabelScale(bool send) { throw new Exception("Not Yet Implemented"); }

        public void unsetRecordResolution(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetRecordAspect(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetRecordFile(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetRecordFormat(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetRecordEnable(bool send) { throw new Exception("Not Yet Implemented"); }

        public bool isAutoAxesCornersSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesCursorSet() { throw new Exception("Not Yet Implemented"); }
        public bool isSetAutoAxesFlag(int index) { throw new Exception("Not Yet Implemented"); }
        public bool isSetAutoAxesFrame() { throw new Exception("Not Yet Implemented"); }
        public bool isSetAutoAxesGrid() { throw new Exception("Not Yet Implemented"); }
        public bool isSetAutoAxesAdjust() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesStringListSet(int index) { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesAnnotationSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesLabelsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesColorsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesStringSet(int index) { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesFontSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesTicksSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesXTickLocsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesYTickLocsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesZTickLocsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesXTickLabelsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesYTickLabelsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesZTickLabelsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesDoubleSet(int index) { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesLabelScaleSet() { throw new Exception("Not Yet Implemented"); }

        public bool useSoftwareRendering() { throw new Exception("Not Yet Implemented"); }

        public virtual String getPickIdentifier() { throw new Exception("Not Yet Implemented"); }

        // Save and retrieve image window state (camera, approx, render mode...)
        // to and from the .cfg file.
        public override bool cfgParseComment(string comment, string file, int lineno)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgParseComment(comment, file, lineno);
        }
        public override bool cfgPrintNode(StreamWriter sw, PrintType destination)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgPrintNode(sw, destination);
        }

        public override void setDefaultCfgState()
        {
            throw new Exception("Not Yet Implemented");
            base.setDefaultCfgState();
        }

        public override DXTypeVals setInputSetValue(int index, string value)
        {
            throw new Exception("Not Yet Implemented");
            return base.setInputSetValue(index, value);
        }

        public bool IsAutoAxesEnableConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesCornersConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesCursorConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesFrameConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesGridConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesAdjustConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesAnnotationConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesLabelsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesColorsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesFontConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesTicksConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesXTickLocsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesYTickLocsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesZTickLocsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesXTickLabelsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesYTickLabelsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesZTickLabelsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesLabelScaleConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsBGColorConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsThrottleConnected { get { throw new Exception("Not Yet Implemented"); } }

        public bool IsViewControlInputSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsImageNameInputSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordEnableSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordFileSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordFormatSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordResolutionSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordAspectSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecFileInputSet { get { throw new Exception("Not Yet Implemented"); } }

        public bool IsRecordEnableConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordFileConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordFormatConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordResolutionConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordAspectConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsInteractionModeConnected { get { throw new Exception("Not Yet Implemented"); } }

        public bool IsRenderModeSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonUpApproxSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonDownApproxSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonUpDensitySet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonDownDensitySet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRenderModeConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonUpApproxConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonDownApproxConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonUpDensityConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonDownDensityConnected { get { throw new Exception("Not Yet Implemented"); } }

        public bool IsDataDriven { get { throw new Exception("Not Yet Implemented"); } }

        public bool setInteractionMode(String mode) { throw new Exception("Not Yet Implemented"); }
        public void setInteractionModeParameter(DirectInteractionMode mode) { throw new Exception("Not Yet Implemented"); }
        public override void openImageWindow(bool manage)
        {
            base.openImageWindow(manage);
        }

        // Most nodes' id parameter is number 1 but a few aren't.  This number is
        // important because whenever you merge 2 nets, you update instance numbers.
        // When you do that, you must also change the id parameter and for that you
        // need its number.
        public override int getMessageIdParamNumber()
        {
            return ParamConst.IMAGETAG;
        }

        // On behalf of ImageFormatDialog (Save/Print Image dialogs) which needs to
        // know what strategy to use for saving the current image.
        public bool hardwareMode() { throw new Exception("Not Yet Implemented"); }

        // Determine if this node is a node of the given class
        public override bool isA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
            return base.isA(classname);
        }

        public virtual void enableJava(String base_name, bool send) { throw new Exception("Not Yet Implemented"); }
        public virtual void disableJava(bool send) { throw new Exception("Not Yet Implemented"); }
        public virtual bool isJavified() { throw new Exception("Not Yet Implemented"); }
        public virtual bool isJavified(Node webOptions) { throw new Exception("Not Yet Implemented"); }
        public virtual void javifyNode(Node webOptions, Node w2) { throw new Exception("Not Yet Implemented"); }
        public virtual void unjavifyNode() { throw new Exception("Not Yet Implemented"); }
        public virtual String getJavaNodeName() { return "ImageNode"; }
        public virtual bool printInputAsJava(int input) { throw new Exception("Not Yet Implemented"); }
        public String getWebOptionsFormat() { throw new Exception("Not Yet Implemented"); }
        public bool isWebOptionsOrbit() { throw new Exception("Not Yet Implemented"); }
        public override bool printAsJava(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
            return base.printAsJava(sw);
        }
        public bool isWebOptionsImgIdConnected()
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
