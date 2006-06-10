using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WinDX.UI
{
    public class ControlPanel : DXWindow
    {
        private enum StyleEnum
        {
            NeverSet,
            Developer,
            User
        };

        private static bool ClassInitialized;
        private bool developerStyle;
        private StyleEnum displayedStyle;
        private bool allowOverlap;
        private int xpos, ypos;
        private String comment;
        private List<InteractorInstance> instanceList = new List<InteractorInstance>();
        private List<Node> addingNodes = null;
        private List<Control> styleList = new List<Control>();
        private List<Control> dimensionalityList = new List<Control>();
        private List<Decorator> componentList = new List<Decorator>();
        private List<Decorator> addingDecoratorList = new List<Decorator>();

        private int instanceNumber;
        //private GridDialog gridDialog;
        //private SetInteractorNameDialog setLabelDialog;
        PanelAccessManager panelAccessManager = null;
        //Dimension develModeDiagWidth;
        // Dimension develModeDiagHeight;
        private bool develModeGridding;
        private bool hit_detection;

        // Parsing state:
        //
        // remember what object was most recently parsed so that resource comments
        // which follow can be associated with that object.
        //private WorkSpaceComponent lastObjectParsed;

        // Do we allow the user to toggle between developer and dialog style
        private bool allowDeveloperStyleChange() { throw new Exception("Not Yet Implemented"); }
        private String java_variable;

        protected Network network;
        protected Command closeCmd;
        protected Command addSelectedInteractorsCmd;
        protected Command showSelectedInteractorsCmd;
        protected Command showSelectedStandInsCmd;
        protected Command deleteSelectedInteractorsCmd;
        protected Command setSelectedInteractorAttributesCmd;
        protected Command setSelectedInteractorLabelCmd;
        protected Command setPanelCommentCmd;
        protected Command setPanelNameCmd;
        protected Command setPanelAccessCmd;
        protected Command setPanelGridCmd;
        protected Command togglePanelStyleCmd;
        protected Command verticalLayoutCmd;
        protected Command horizontalLayoutCmd;
        protected Command helpOnPanelCmd;
        protected Command hitDetectionCmd;

        // Control panel components:
        //
        //Widget scrolledWindow;
        //Widget scrolledWindowFrame;
        //WorkSpaceInfo workSpaceInfo;
        //ControlPanelWorkSpace* workSpace;

        // collection of pushbuttons
        //Widget commandArea;

        // Menus & pulldowns:
        //
        //Widget fileMenu;
        //Widget editMenu;
        //Widget panelsMenu;
        //Widget optionsMenu;

        //Widget fileMenuPulldown;
        //Widget editMenuPulldown;
        //Widget panelsMenuPulldown;
        //Widget optionsMenuPulldown;

        // File menu options:
        //
        protected CommandInterface closeOption;
        protected CommandInterface closeAllOption;

        // Edit menu options:
        //
        //Widget setStyleButton;
        //Widget stylePulldown;
        //Widget setDimensionalityButton;
        //Widget setLayoutButton;
        //Widget addButton;
        //Widget addPulldown;
        protected CommandInterface verticalLayoutOption;
        protected CommandInterface horizontalLayoutOption;
        protected CommandInterface setAttributesOption;
        protected CommandInterface setInteractorLabelOption;
        protected CommandInterface deleteOption;
        protected CommandInterface addSelectedInteractorsOption;
        protected CommandInterface showSelectedInteractorsOption;
        protected CommandInterface showSelectedStandInsOption;
        protected CommandInterface commentOption;

        //
        // Panels menu options:
        //
        protected CommandInterface openAllControlPanelsOption;
        //CascadeMenu* openControlPanelByNameMenu;

        //
        // Options menu options:
        //
        protected CommandInterface changeControlPanelNameOption;
        protected CommandInterface setAccessOption;
        protected CommandInterface gridOption;
        protected CommandInterface styleOption;
        protected CommandInterface hitDetectionOption;

        //
        // Help menu options:
        //
        protected CommandInterface onControlPanelOption;
        protected CommandInterface onVisualProgramOption;
        protected CommandInterface userHelpOption;

        //
        // Various dialogs. 
        //
        //SetPanelNameDialog* setNameDialog;
        //SetPanelCommentDialog* setCommentDialog;
        //HelpOnPanelDialog* helpOnPanelDialog;


        #region Private Methods

        private static void ToDevStyle(Form f)
        {
            throw new Exception("Not Yet Implemented");
        }
        private static void SetOwner(Form f)
        {
            throw new Exception("Not Yet Implemented");
        }
        private static void DeleteSelections(object o)
        {
            throw new Exception("Not Yet Implemented");
        }

        private void setDimensionsCallback()
        {
            throw new Exception("Not Yet Implemented");
        }

        #endregion

        #region Protected Methods

        protected override Control createWorkArea(Form parent)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        protected override Control createCommandArea(Form parent)
        {
            return base.createCommandArea(parent);
        }

        protected override void createMenus(MenuStrip menu)
        {
            base.createMenus(menu);
        }

        protected virtual void createFileMenu(MenuStrip menu)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void createEditMenu(MenuStrip menu)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void createPanelsMenu(MenuStrip menu)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void createOptionsMenu(MenuStrip menu)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected override void createHelpMenu(MenuStrip menu)
        {
            throw new Exception("Not Yet Implemented");
            base.createHelpMenu(menu);
        }

        protected virtual bool cfgParsePanelComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgPrintPanelComment(StreamWriter sr, PrintType dest)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgParseDecoratorComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgPrintDecoratorComment(StreamWriter sr, PrintType dest)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected virtual bool cfgParseCommentComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgPrintCommentComment(StreamWriter sw, PrintType dest)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected virtual bool cfgParseTitleComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual bool cfgPrintTitleComment(StreamWriter sw, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Find THE selected InteractorInstance.
        /// Return TRUE if a single interactor is selected 
        /// Return FALSE if none or more than one selected interactor were found 
        /// Always set *selected to the first selected InteractorInstance that was
        /// found.  If FALSE is return *selected may be set to NULL if no selected
        /// InteractorInstances were found.
        /// </summary>
        /// <param name="selected"></param>
        /// <returns></returns>
        protected bool findTheSelectedInteractorInstance(out InteractorInstance selected)
        {
            throw new Exception("Not Yet Implemented");
        }

        
        //protected bool findTheSelectedComponent(out WorkSpaceComponent selected)
        //{
        //    throw new Exception("Not Yet Implemented");
        //}

        protected int InteractorSelectionCount { get { throw new Exception("Not Yet Implemented"); } }
        protected int ComponentSelectionCount { get { throw new Exception("Not Yet Implemented"); } }

        // Add all the editor's selected InteractorNodes to the control panel
        protected void addSelectedInteractorNodes()
        {
            throw new Exception("Not Yet Implemented");
        }

        //protected InteractorInstance createAndPlaceInteractor(InteractorNode innode,
        //    int x, int y)
        //{
        //    throw new Exception("Not Yet Implemented");
        //}

        protected Decorator createAndPlaceDecorator(String type, int x, int y)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected String PanelName
        {
            get { throw new Exception("Not Yet Implemented"); }
            set { throw new Exception("Not Yet Implemented"); }
        }

        protected override void beginCommandExecuting()
        {
            // Virtual function called at the beginning of Command::execute().
            // Before command in the system is executed we disable (the active
            // current) interactor placement.

            throw new Exception("Not Yet Implemented");
            base.beginCommandExecuting();
        }

        protected virtual void getGeometryAlternateNames(ref String s, ref int a, int b)
        {
            throw new Exception("Not Yet Implemented");
        }

        #endregion

        #region Public Methods

        public ControlPanel(Network net)
            : base("controlPanel", false, true)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void setActivationOfEditingCommands()
        {
            throw new Exception("Not Yet Implemented");
        }

        ~ControlPanel() { throw new Exception("Not Yet Implemented"); }

        public void clearInstance()
        {
            throw new Exception("Not Yet Implemented");
        }

        public override void initialize()
        {
            throw new Exception("Not Yet Implemented");
            base.initialize();
        }

        //Widget getWorkSpaceWidget();

        //ControlPanelWorkSpace* getWorkSpace()
        //{
        //    return this->workSpace;
        //}

        //void manage();
        //void unmanage();

        // Add/Remove an instance of an interactor.
        public bool addInteractorInstance(InteractorInstance ii)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool removeInteractorInstance(InteractorInstance ii)
        {
            throw new Exception("Not Yet Implemented");
        }

        // Parse the comments in the .cfg file
        public virtual bool cfgParseComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool cfgPrintPanel(StreamWriter sw, PrintType dest)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Take the first item on this->selectedNodes list and place
        /// it in the ContolPanel data structures and workspace.
        /// We get this callback even when the list is empty, so be sure we
        /// do the right thing when it is empty.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public virtual void placeSelectedInteractorCallback(Object sender, EventArgs e)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Highlight each InteractorInstance that is in this control panel
        ///  and have their corresponding Node selected.
        ///  Called when this->showSelectedInteractorsCmd is used.
        /// </summary>
        public void showSelectedInteractors()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Deselect all nodes in the VPE, and then highlight each 
        ///  InteractorNode that has a selected InteractorInstance in this 
        ///  control panel.
        ///  Called when this->showSelectedStandInsCmd is used.
        /// </summary>
        public void showSelectedStandIns()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Delete all selected InteractorInstances from the control panel. 
        /// </summary>
        public void deleteSelectedInteractors()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Open the set attributes dialog box for THE selected interactor. 
        /// If there is more than one interactor selected then we pop up an 
        /// error message. With this version we could change this behavior.
        /// </summary>
        public void openSlectedSetAttrDialog()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Set the label of THE selected interactor. 
        /// If there is more than one interactor selected then we pop up an 
        /// error message.
        /// </summary>
        public void setSelectedInteractorLabel()
        {
            throw new Exception("Not Yet Implemented");
        }

        public String InteractorLabel
        {
            get { throw new Exception("Not Yet Implemented"); }
            set { throw new Exception("Not Yet Implemented"); }
        }

        // Edit/get/view the comment for this panel.
        public void editPanelComment()
        {
            throw new Exception("Not Yet Implemented");
        }
        public String PanelComment
        {
            get { throw new Exception("Not Yet Implemented"); }
            set { throw new Exception("Not Yet Implemented"); }
        }
        public void postHelpOnPanel() { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Edit the name of this panel
        /// </summary>
        public void editPanelName() { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Change the work space grid setup
        /// </summary>
        public void setPanelGrid() { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// User/Developer styles
        /// </summary>
        /// <param name="developerStyle"></param>
        public void setPanelStyle(bool developerStyle) { throw new Exception("Not Yet Implemented"); }
        public bool IsDeveloperStyle { get { return developerStyle; } }

        /// <summary>
        /// Decorators only no interactors in this list.
        /// </summary>
        /// <returns></returns>
        public List<Decorator> getComponents() { return componentList; }
        public void addComponentToList(Decorator d) { componentList.Add(d); }

        /// <summary>
        /// This is called by the ControlPanelWorkSpace class to handle
        /// double clicks in the workspace.
        /// </summary>
        public virtual void doDefaultWorkSpaceAction() { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Initialize for selected interactor node placement.  Should be called
        /// when the 'Add Selected Interactors' command is issued.
        /// Returns the number of selected interactor nodes that will be allowed 
        /// to be placed.
        /// </summary>
        public void initiateInteractorPlacement() { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Normal termination of interactor placement.
        /// There should be no more items in this->selectedNodes.
        /// We reset the work space cursor and then deactivate the 
        /// 'Add Selected Interactors' pulldown command.
        /// </summary>
        public void concludeInteractorPlacement() { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Change the layout of all selected interactors.
        /// </summary>
        /// <param name="vertical"></param>
        public void setVerticalLayout(bool vertical) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Do any work that is required when a Node's state has changed.
        /// This work may include enable or disabling certain commands.
        /// </summary>
        /// <param name="node"></param>
        /// <param name="status"></param>
        public void handleNodeStatusChange(Node node, Node.NodeStatusChange status)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void handleInteractorInstanceStatusChange(InteractorInstance ii,
            Interactor.Status status)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Get/Set the instance number of this control panel.
        /// </summary>
        /// <returns></returns>
        public int InstanceNumber
        {
            get { return instanceNumber; }
            set { instanceNumber = value; }
        }

        public Network getNetwork()
        {
            return network;
        }

        /// <summary>
        /// Used in mergeAndDeleteNet
        /// </summary>
        /// <param name="from"></param>
        /// <param name="to"></param>
        public void switchNetwork(Network from, Network to) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// The number of interactor instances/decorators in this control panel.
        /// </summary>
        public int InstanceCount { get { return instanceList.Count; } }
        public int DecoratorCount { get { return componentList.Count; } }
        public int ComponentCount { get { return instanceList.Count + componentList.Count; } }

        public String PanelNameString { get { return this.Text; } }
        public String AppletClass { get { throw new Exception("Not Yet Implemented"); } }

        // Same as the super class, but also sets the icon name.
        public void setWindowTitle(String name, bool checkGeometry) { throw new Exception("Not Yet Implemented"); }

        public bool changeInteractorDimensionality(int newDim) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Select/Deselect all instances in the control panel.
        /// </summary>
        /// <param name="select"></param>
        public void selectAllInstances(bool select) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Get the next x,y position of an interactor being placed during a
        /// series of placements into an initially empty control panel and
        /// that use this method to get x,y positions of all placed interactors.
        /// This needs to be public so InteractorNode can call it.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public void getNextInteractorPosition(ref int x, ref int y)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// True if n is pointed to by some InteractorInstance in this->instanceList 
        /// && that interactor is selected.  Used by Network::cfgPrintSelection 
        /// because he wants to visit only certain nodes.
        /// </summary>
        /// <param name="node"></param>
        /// <returns></returns>
        public bool nodeIsInInstanceList(Node node)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Supply the Position of the the NW most interactor.
        /// ...used by Interactor::decideToDrag so that it can compute offsets.
        /// </summary>
        /// <param name="minx"></param>
        /// <param name="miny"></param>
        public void getMinSelectedXY(ref int minx, ref int miny)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void mergePanels(ControlPanel cp, int x, int y) { throw new Exception("Not Yet Implemented"); }

        public bool printAsJava(StreamWriter sw) { throw new Exception("Not Yet Implemented"); }
        public String getJavaVariableName() { throw new Exception("Not Yet Implemented"); }
        public void getWorkSpaceSize(ref int w, ref int h) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Change a resource in the Workspace widget that lets the user know
        /// if things will overlap - during the course of moving
        /// </summary>
        /// <returns></returns>
        public bool toggleHitDetection() { throw new Exception("Not Yet Implemented"); }


        #endregion

    }
}
