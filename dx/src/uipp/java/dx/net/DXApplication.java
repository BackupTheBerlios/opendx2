//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/DXApplication.java,v 1.1 1999/03/24 15:17:30 gda Exp $
 */

package dx.net;
import dx.client.*;
import java.applet.*;
import java.awt.*;
import java.util.*;

public abstract class DXApplication extends DXClient {

    //
    // Bean Properties
    // Bean Properties
    // Bean Properties
    //
    // Does this class draw ui features or is it left to the subclass?
    private boolean makesGui = true;
    public void setMakesGui(boolean mk) { this.makesGui = mk; }
    public boolean getMakesGui() { return this.makesGui; } 

    // Does this class draw the fake 3d shadows around itself?
    public void setShadows(boolean s) { this.shadows = s; }
    public boolean getShadows() { return this.shadows; }
    private boolean shadows = true;

    // Execute-on-change mode
    private boolean eocMode = false;
    public boolean getEocMode() { return this.eocMode; }
    public void setEocMode (boolean onoroff) {
	if (onoroff) {
	    this.eocMode = true;
	    if (this.exec_on_change != null)
		this.exec_on_change.setState(true);
	    this.DXLExecuteOnce();
	} else {
	    this.eocMode = false;
	    if (this.exec_on_change != null)
		this.exec_on_change.setState(false);
	    if ((this.isExecuting() == false) && (this.execCtrl != null)) {
		Checkbox cb = execCtrl.getTab();
		cb.setForeground(Color.black);
	    }
	}
    }

    private String bwcompat_string;
    private boolean bwcompat_checked;


    // Do we implement image caching?
    protected boolean cachingMode;
    public boolean getCachingMode() { return this.cachingMode; }
    public void setCachingMode (boolean onoroff, boolean clear_cache) {
	this.cachingMode = onoroff;
	if (onoroff) {
	    if (this.cache_size != null) 
		this.cache_size.enable();
	    if (this.cache_options != null)
		this.execCtrl.add(this.cache_options);
	} else {
	    if (this.cache_size != null) 
		this.cache_size.disable();
	    if (this.cache_options != null) 
		this.execCtrl.remove(this.cache_options);
	    if (this.selected_image != null)
		this.selected_image.setInteractionMode(ImageWindow.NO_MODE, 0);
	}

	if (this.imageWindows == null) return ;
	if (clear_cache) {
	    Enumeration enum = this.imageWindows.elements();
	    while (enum.hasMoreElements()) {
		ImageWindow iw = (ImageWindow)enum.nextElement(); 
		iw.clearImageCache();
	    }
	}
    }


    protected Network network;
    protected Button execute_once;
    protected Button end_execution;
    protected Button connect_btn;
    protected Checkbox exec_on_change;
    protected Checkbox set_caching;
    protected TextField cache_size;
    protected Choice cache_options;
    protected Label speed_label;
    private Vector imageWindows;
    private Vector named_image_list;
    private Vector panels;
    private int selected_panel;
    private Panel cardPanel;
    private Panel tabPanel;
    private CheckboxGroup selector;
    private static final int SHADOW = 8;
    private static final int TABHEIGHT = 35;
    private ControlPanel execCtrl;
    private Node sequencer;
    private boolean in_connect_callback;
    private boolean dirty;
    private String macro_name;

    private int modes[];
    private int sequence_mode_choice;

    private final static int CHOOSER_XPOS = 50;
    private final static int CHOOSER_WIDTH = 110;
    private final static int LABEL_XPOS = 3;
    private final static int LABEL_WIDTH = 42;
    private final static int CONTROL_HEIGHT = 35;

    private Choice image_chooser;
    private dx.net.ImageNode selected_image;
    public dx.net.ImageNode getSelectedImageNode() { return this.selected_image; }

    private Choice pick_chooser;
    private PickNode selected_pick;
    public PickNode getSelectedPickNode() { return this.selected_pick; }

    private Choice mode_chooser;
    private Choice view_chooser;
    private int selected_mode;

    public boolean getCachingFeaturesEnabled() { return (this.cache_size != null); }

    protected SequencerNode getSequencerNode() { return (SequencerNode)this.sequencer; }




    protected DXApplication() {
	super();
	this.network = null;
	this.execute_once = null;
	this.end_execution = null;
	this.connect_btn = null;
	this.exec_on_change = null;
	this.eocMode = false;
	this.imageWindows = new Vector(4);
	this.selected_panel = 0;
	this.panels = null;
	this.cardPanel = null;
	this.tabPanel = null;
	this.selector = null;
	this.selected_pick = null;
	this.pick_chooser = null;
	this.mode_chooser = null;
	this.view_chooser = null;
	this.selected_mode = ImageWindow.NO_MODE;
	this.named_image_list = null;
	this.execCtrl = null;
	this.cache_size = null;
	this.cache_options = null;
	this.cachingMode = false;
	this.sequencer = null;
	this.set_caching = null;
	this.modes = new int[10];
	this.sequence_mode_choice = -1;
	this.dirty = false;
	this.macro_name = null;
	this.bwcompat_checked = false;
	this.bwcompat_string = null;
    }

    public String getMacroName() { return this.macro_name; }

    public void setNetwork(Network n) { 
	this.network = n; 
	n.setApplet(this);

	Vector image_list = null;
	Class ic = null;
	try {
	    ic = Class.forName("dx.net.ImageNode");
	} catch (Exception e) {
	    System.out.println ("DXApplication: failed to list ImageNodes");
	}
	if (ic != null)
	    image_list = this.network.makeNodeList(ic, false);

	this.named_image_list = null;
	if ((image_list != null) && (image_list.size() > 0)) {
	    Enumeration enum = image_list.elements();
	    while (enum.hasMoreElements()) {
		ImageNode in = (ImageNode)enum.nextElement();
		String iname = in.getTitle();
		boolean isWired = in.isInteractionModeConnected();
		if (iname != null) {
		    this.selected_image = in;
		    if (isWired == false) {
			if (this.named_image_list == null) 
			    this.named_image_list = new Vector(4);
			this.named_image_list.addElement((Object)in);
		    }
		}
	    }
	}

	Class sc = null;
	try { sc = Class.forName("dx.net.SequencerNode");
	} catch (ClassNotFoundException cnfe) { }
	Vector seq_list = this.network.makeNodeList (sc, false);
	if ((seq_list != null) && (seq_list.size() >= 1))
	    this.sequencer = (Node)seq_list.elementAt(0);

    }

    public void start() {
	super.start();
	if ((this.getMakesGui()) && (this.network != null)) {
	    Dimension d = this.size();
	    int st = (this.shadows?SHADOW:0);
	    int tpw = d.width-(2+st);
	    tabPanel.reshape (2,2,tpw,TABHEIGHT-2);
	    cardPanel.reshape(2,TABHEIGHT+2,tpw,d.height-(2+TABHEIGHT+st));
	}
    }

    public void init() {
	int control_count = 0;

	super.init();
	int sthick = (this.shadows?SHADOW:0);
	if (this.network != null) {
	    if (this.getMakesGui()) {
		Dimension d = this.size();
		int tpw = d.width-(2+sthick);
		tabPanel.reshape (2,2,tpw,TABHEIGHT-2);
		cardPanel.reshape(2,TABHEIGHT+2,tpw,d.height-(2+TABHEIGHT+sthick));
	    }
	    return ;
	}
	//
	// Clumsy api here.  I should pass network into this.readNetwork but
	// I didn't want to force subclasses to change.
	//
	this.network = new Network();
	this.readNetwork();
	this.setNetwork(this.network);

	if (this.getMakesGui() == false)
	    return ;

	Dimension d = this.size();
	int panel_cnt = network.getPanelCount();
	this.selector = new CheckboxGroup();
	cardPanel = new Panel();
	this.add(cardPanel);
	cardPanel.setLayout(new CardLayout());
	panels = new Vector(panel_cnt);
	this.selected_panel = 0;

	tabPanel = new Panel();
	tabPanel.setFont (new Font("Helvetica", Font.BOLD, 12));
	this.add(tabPanel);
	this.setLayout(null);
	int tpw = d.width-(2+sthick);
	tabPanel.reshape (2,2,tpw,TABHEIGHT-2);
	cardPanel.reshape (2,TABHEIGHT+2,tpw,d.height-(2+TABHEIGHT+sthick));
	tabPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 2, 0));

	int i = 0;
	while (i < panel_cnt) {
	    ControlPanel cp = network.getPanel(i);
	    cp.buildPanel();
	    panels.addElement((Object)cp);
	    cardPanel.add (cp.getName(), cp);

	    Checkbox cb = cp.getTab();
	    cb.setBackground(this.getBackground());
	    cb.setCheckboxGroup(this.selector);
	    if (i == 0) cb.setState(true);
	    else cb.setState(false);
	    tabPanel.add(cb);
	    i++;
	}

	//
	// Add execution control
	//
	this.execCtrl = new ControlPanel(this.network, "Execution", 
	    this.network.getPanelCount() + 1);
	this.execCtrl.setFont (new Font("Helvetica", Font.BOLD, 12));
	this.execCtrl.buildPanel();
	panels.addElement((Object)this.execCtrl);
	Dimension crd = cardPanel.size();
	int crd_width = (crd.width > 400? 400: crd.width);
	cardPanel.add (this.execCtrl.getName(), this.execCtrl);
	Checkbox cb = this.execCtrl.getTab();
	cb.setBackground(this.getBackground());
	cb.setCheckboxGroup(this.selector);
	if (i == 0) cb.setState(true);
	else cb.setState(false);
	tabPanel.add(cb);

	//
	// Execute Once
	//
	execute_once = new Button("Execute Once");
	this.execute_once.setBackground(this.getBackground());
	execute_once.reshape(10,crd.height-40, 100,25);
	this.execCtrl.add(execute_once);

	//
	// Execute - On - Change
	//
	String eoc = getParameter("EXECUTE_ON_CHANGE");
	if (eoc != null)
	    this.eocMode = Boolean.valueOf(eoc).booleanValue();
	else this.eocMode = false;
	this.exec_on_change = new Checkbox("Execute On Change");
	this.exec_on_change.setBackground(this.getBackground());
	this.exec_on_change.setState(this.eocMode);
	exec_on_change.reshape(10, crd.height-70, 140, 25);
	this.execCtrl.add(exec_on_change);

	//
	// We'll conditionally allow users to set caching features
	// so that we don't wreck existing web pages by added 
	// unexpected features.  When the version number jumps to
	// 1.1, then we should add caching features by default.
	//
	this.setCachingMode(false, false);
	String enabstr = getParameter("CACHING_FEATURES");
	boolean enable_animation = false;
	if (enabstr != null)
	    enable_animation = Boolean.valueOf(enabstr).booleanValue();

	if (enable_animation) {
	    //
	    // Image caching
	    //
	    this.setCachingMode(true, false);
	    this.set_caching = new Checkbox("Enable Animation");
	    this.set_caching.setState(this.getCachingMode());
	    this.set_caching.setBackground(this.getBackground());
	    this.set_caching.reshape(10, crd.height-100, 140, 25);
	    this.execCtrl.add(this.set_caching);
	}

	if ((enable_animation) || (this.sequencer != null)) {
	    //
	    // Image cache size
	    //
	    this.cache_size = new TextField("0", 4);
	    this.cache_size.setBackground(this.getBackground());
	    this.cache_size.reshape(210,crd.height-98, 40,28);
	    this.execCtrl.add(this.cache_size);
	    this.cache_size.disable();
	    Label lab = new Label("Frames:");
	    lab.setAlignment(Label.RIGHT);
	    lab.reshape(160,crd.height-100, 48,20);
	    this.execCtrl.add(lab);

	    //
	    // Image cache options
	    //
	    this.cache_options = new Choice();
	    this.cache_options.setBackground(this.getBackground());
	    this.cache_options.addItem("Loop");
	    this.cache_options.addItem("Palindrome");
	    this.cache_options.addItem("Faster");
	    this.cache_options.addItem("Slower");
	    this.cache_options.addItem("Reset");
	    this.cache_options.reshape(165, crd.height-140, 90, 30); 
	    if (this.getCachingMode()) 
		this.execCtrl.add(this.cache_options);
	}


	//
	// Connect option
	//
	String cstr = getParameter("CONNECT_OPTION");
	boolean has_connect = false;
	if (cstr != null)
	    has_connect = Boolean.valueOf(cstr).booleanValue();
	if (has_connect) {
	    this.connect_btn = new Button("Connect");
	    this.connect_btn.setBackground(this.getBackground());
	    this.connect_btn.reshape(160,crd.height-70, 100,25);
	    this.execCtrl.add(this.connect_btn);
	}

	//
	// Pick tool chooser
	//
	Vector pick_list = null;
	Class pc = null;
	try {
	    pc = Class.forName("dx.net.PickNode");
	} catch (Exception e) {
	    System.out.println ("DXApplication: failed to list PickNodes");
	}
	if (pc != null)
	    pick_list = this.network.makeNodeList(pc, false);
	pick_chooser = null;
	if ((pick_list != null) && (pick_list.size() == 1)) {
	    this.selected_pick = (PickNode)pick_list.elementAt(0);
	} else if ((pick_list != null) && (pick_list.size() > 1)) {
	    pick_chooser = new Choice();
	    pick_chooser.setBackground(this.getBackground());
	    Enumeration enum = pick_list.elements();
	    while (enum.hasMoreElements()) {
		PickNode pn = (PickNode)enum.nextElement();
		String name = pn.getName() + "_" + pn.getInstanceNumber();
		pick_chooser.addItem(name);
	    }
	    pick_chooser.disable();
	    pick_chooser.select(0);
	    this.selected_pick = (PickNode)pick_list.elementAt(0);
	    int yloc = 4+(control_count*CONTROL_HEIGHT);
	    control_count++;
	    pick_chooser.reshape (CHOOSER_XPOS, yloc, CHOOSER_WIDTH, 30);
	    this.execCtrl.add(pick_chooser);

	    Label lab = new Label("Pick:");
	    lab.setAlignment(Label.RIGHT);
	    lab.reshape (LABEL_XPOS, yloc-4, LABEL_WIDTH, 30);
	    this.execCtrl.add(lab);
	}

	//
	// Image chooser
	//
	if ((this.named_image_list != null)&&(this.named_image_list.size() > 1)) {
	    image_chooser = new Choice();
	    image_chooser.setBackground(this.getBackground());
	    Enumeration enum = this.named_image_list.elements();
	    while (enum.hasMoreElements()) {
		ImageNode in = (ImageNode)enum.nextElement();
		String name = in.getTitle();
		image_chooser.addItem(name);
	    }
	    int yloc = 2+(control_count*CONTROL_HEIGHT);
	    control_count++;
	    image_chooser.reshape (CHOOSER_XPOS, yloc, CHOOSER_WIDTH, 30);
	    this.execCtrl.add(image_chooser);

	    image_chooser.select(0);
	    this.selected_image = (ImageNode)this.named_image_list.elementAt(0);

	    Label lab = new Label("Image:");
	    lab.setAlignment(Label.RIGHT);
	    lab.reshape (LABEL_XPOS, yloc-4, LABEL_WIDTH, 30);
	    this.execCtrl.add(lab);
	}

	//
	// End Execution
	//
	this.end_execution = new Button("End Execution");
	this.end_execution.setBackground(this.getBackground());
	this.end_execution.reshape(160,crd.height-40, 100,25);
	this.execCtrl.add(this.end_execution);


	//
	// Mode chooser
	//
	if ((this.named_image_list != null) && (this.named_image_list.size() > 0)) {
	    int m = 0;
	    mode_chooser = new Choice();
	    mode_chooser.setBackground(this.getBackground());
	    mode_chooser.addItem("(None)");	 this.modes[m++]= ImageWindow.NO_MODE;
	    mode_chooser.addItem("Rotate");	 this.modes[m++]= ImageWindow.ROTATE_MODE;
	    if (this.selected_pick != null) {
		mode_chooser.addItem("Pick");	 this.modes[m++]= ImageWindow.PICK_MODE;
	    }
	    mode_chooser.addItem("Pan");	 this.modes[m++]= ImageWindow.PAN_MODE;
	    mode_chooser.addItem("Zoom");	 this.modes[m++]= ImageWindow.ZOOM_MODE;
	    mode_chooser.addItem("Orbit");	 this.modes[m++]= ImageWindow.ORBIT_MODE;
	    mode_chooser.addItem("Reset Camera");this.modes[m++]= ImageWindow.RESET_CAMERA;
	    if (this.sequencer != null) {
		this.sequence_mode_choice = m;
		mode_chooser.addItem("Sequence");this.modes[m++]= ImageWindow.LOOP_MODE;
	    } else if (enable_animation) {
		mode_chooser.addItem("Review");	 this.modes[m++]= ImageWindow.LOOP_MODE;
	    }
	    int yloc = 2+(control_count*CONTROL_HEIGHT);
	    control_count++;
	    mode_chooser.reshape (CHOOSER_XPOS, yloc, CHOOSER_WIDTH, 30);
	    this.execCtrl.add(mode_chooser);

	    if (this.selected_image != null) {
		this.selected_mode = this.selected_image.getInteractionMode();
		mode_chooser.select(this.selected_mode);
	    } else {
		mode_chooser.select(0);
		this.selected_mode = ImageWindow.NO_MODE;
	    }

	    Label lab = new Label("Mode:");
	    lab.setAlignment(Label.RIGHT);
	    lab.reshape (LABEL_XPOS, yloc-4, LABEL_WIDTH, 30);
	    this.execCtrl.add(lab);

	    this.view_chooser = new Choice();
	    this.view_chooser.setBackground(this.getBackground());
	    this.view_chooser.addItem("Front");
	    this.view_chooser.addItem("Back");
	    this.view_chooser.addItem("Top");
	    this.view_chooser.addItem("Bottom");
	    this.view_chooser.addItem("Right");
	    this.view_chooser.addItem("Left");
	    this.view_chooser.addItem("Diagonal");
	    this.view_chooser.addItem("Off Front");
	    this.view_chooser.addItem("Off Back");
	    this.view_chooser.addItem("Off Top");
	    this.view_chooser.addItem("Off Bottom");
	    this.view_chooser.addItem("Off Right");
	    this.view_chooser.addItem("Off Left");
	    this.view_chooser.addItem("Off Diagonal");

	    yloc = 2+(control_count*CONTROL_HEIGHT);
	    control_count++;
	    this.view_chooser.reshape (CHOOSER_XPOS, yloc, CHOOSER_WIDTH, 30);
	    this.execCtrl.add(this.view_chooser);

	    lab = new Label("View:");
	    lab.setAlignment(Label.RIGHT);
	    lab.reshape (LABEL_XPOS, yloc-4, LABEL_WIDTH, 30);
	    this.execCtrl.add(lab);
	}

	//
	// If this parameter is set to false, then we won't draw shadows
	// The purpose would be to let the user wrap in the applet in html
	// table dressing.
	//
	String nobrd = this.getParameter("SHADOWS");
	if (nobrd != null) 
	    this.shadows = Boolean.valueOf(nobrd).booleanValue();
    }


    public void setJavaId (int jid) {}

    public void setMacroName (String macro) {
	this.macro_name = macro;
	if (isConnected()) {
	    boolean resume_eoc = this.eocMode;
	    this.setEocMode (false);

	    //
	    // Install value handlers for all DrivenNodes
	    //
	    Enumeration enum = this.network.elements();
	    while (enum.hasMoreElements()) {
		dx.net.Node n = (dx.net.Node)enum.nextElement();
		n.enableJava();
	    }

	    //
	    // Set a special DXLInput tool
	    //
	    DXLSend ("_java_control=1;");

	    //
	    // If WebOptions.imgId was tab-down and unconnected in the
	    // original net, then we can associate some ImageWindows with
	    // their ImageNodes early rather than waiting for an execution.
	    //
	    this.locateImageWindows();
	    enum = this.imageWindows.elements();
	    int wid = -1;
	    while (enum.hasMoreElements()) {
		ImageWindow iw = (ImageWindow)enum.nextElement(); wid++;
		String node_name = iw.getInitialNodeName(this.network);
		if (node_name == null) continue;
		Vector v = this.network.makeNodeList(node_name);
		if ((v == null) || (v.size() != 1)) continue;

		ImageNode in = (ImageNode)v.elementAt(0);
		in.associate(iw, wid);
	    }

	    this.setEocMode(resume_eoc);
	}
	this.enable();
    }

    protected void connect() {
	boolean was_connected = this.isConnected();
	if ((this.connect_btn == null) || (this.in_connect_callback)) {
	    this.in_connect_callback = false;
	    super.connect();
	}
	if ((this.connect_btn != null) && (this.isConnected())) {
	    this.connect_btn.setLabel("Disconnect");
	}
	if ((was_connected == false) && (this.isConnected())) {
	    this.disable();
	}
    }

    public void updateCaching(ImageNode in) {
	if (this.cache_size == null) return ;
	Integer Size = new Integer(in.getCacheCount());
	this.cache_size.setText(Size.toString());
    }

    protected void disconnect(Thread t) {
	super.disconnect(t);
	if (this.connect_btn != null) 
	    this.connect_btn.setLabel("Connect");
	if (this.execCtrl != null) {
	    Checkbox cb = this.execCtrl.getTab();
	    if (cb != null) {
		cb.setForeground(Color.black);
		cb.disable();
		cb.enable();
	    }
	}
	if (this.mode_chooser != null) {
	    this.mode_chooser.select(ImageWindow.NO_MODE);
	    this.selected_mode = ImageWindow.NO_MODE;
	    if (this.selected_image != null)
		this.applyInteractionMode (ImageWindow.NO_MODE, 0);
	}
    }

    protected abstract void readNetwork();
    protected abstract boolean isExecuting();

    protected void DXLExecuteOnce() {
	if ((this.isExecuting()) && (this.execCtrl != null)) {
	    Checkbox cb = this.execCtrl.getTab();
	    //cb.setForeground(Color.green);
	    cb.setForeground(new Color((float)0.0, (float)1.0, (float)0.49));
	    Graphics g = cb.getGraphics();
	    cb.paint(g);
	    cb.disable();
	    cb.enable();
	}
	this.dirty = false;
    }

    public boolean handleEvent (Event e, ImageNode in) {
	if ((this.named_image_list != null) && (this.selected_image != in)) {
	    if ((in != null) && (this.named_image_list.contains((Object)in))) {
		int i = this.named_image_list.indexOf((Object)in);
		this.image_chooser.select(i);
		this.selected_image = in;
	    }
	}
	return this.handleEvent(e);
    }

    public boolean handleEvent (Event e) {
	if (e.id == Event.KEY_PRESS) {
	    //System.out.println ("DXApplication.handleEvent: " + e.toString());
	    boolean retval = false;
	    switch (e.key) {
		case Event.END:
		    if ((e.modifiers & Event.CTRL_MASK) != 0) {
			this.setEocMode(false);
			retval = true;
		    }
		    break;
		case 15: /* Ctrl-O */
		    this.DXLExecuteOnce();
		    retval = true;
		    break;
		case 18: /* Ctrl-R */
		    this.setInteractionMode(ImageWindow.ROTATE_MODE, 0);
		    retval = true;
		    break;
		case 6: /* Ctrl-F */
		    if (this.selected_image != null) {
			this.selected_image.resetCamera(true, false);
			this.DXLExecuteOnce();
			this.selected_image.resetCamera(false, false);
			this.setInteractionMode(ImageWindow.NO_MODE, 0);
		    }
		    retval = true;
		    break;
		case 7: /* Ctrl-G */
		    this.setInteractionMode(ImageWindow.PAN_MODE, 0);
		    retval = true;
		    break;
		case 26: /* Ctrl-Z */
		    this.setInteractionMode(ImageWindow.ZOOM_MODE, 0);
		    retval = true;
		    break;
		case 3: /* Ctrl-C */
		    this.setEocMode(true);
		    retval = true;
		    break;
		default:
		    break;
	    }

	    if (retval) return true;
	}
	return super.handleEvent(e);
    }

    public boolean action (Event e, Object o) {
	if (this.panels == null) return false;

	Date now = new Date();
	long event_time = now.getTime();

	//
	// Pick a new panel
	//
	Enumeration enum = this.panels.elements();
	int selp = 0;
	while (enum.hasMoreElements()) {
	    ControlPanel cp = (ControlPanel)enum.nextElement();
	    Checkbox cb = cp.getTab();
	    if (cb == e.target) {
		((CardLayout)cardPanel.getLayout()).show (cardPanel, cp.getName());
		this.selected_panel = selp;
		return true;
	    }
	    selp++;
	}

	//
	// Hit execute once
	//
	if (e.target == this.execute_once) {
	    this.DXLExecuteOnce();
	    return true;
	}

	//
	// Hit End Execution
	//
	if (e.target == this.end_execution) {
	    this.DXLEndExecution();
	    return true;
	}

	//
	// Enter/Leave exec-on-change mode
	//
	if (e.target == this.exec_on_change) {
	    this.setEocMode(exec_on_change.getState());
	    return true;
	}

	//
	// Image caching
	//
	if (e.target == this.set_caching) {
	    this.setCachingMode(this.set_caching.getState(), true);
	    return true;
	}

	//
	// Cache size
	//
	if (e.target == this.cache_size) {
	    String sizestr = this.cache_size.getText();
	    int size;
	    try {
		Integer I = new Integer(sizestr);
		size = I.intValue();
	    } catch (NumberFormatException nfe) {
		return false;
	    }
	    this.setCacheSize(size);
	    return true;
	}

	//
	// Cache speed
	//
	if (e.target == this.cache_options) {
	    int selected = this.cache_options.getSelectedIndex();
	    this.setCacheOption(selected);
	    return true;
	}

	//
	// Choose a pick tool
	//
	if ((this.pick_chooser != null) && (e.target == this.pick_chooser)) {
	    String pick_name = pick_chooser.getSelectedItem();
	    Vector pick_list = this.network.makeNodeList(pick_name);
	    PickNode old_pick = this.selected_pick;
	    if ((pick_list != null) && (pick_list.size() > 0)) {
		int i = this.pick_chooser.getSelectedIndex();
		this.selected_pick = (PickNode)pick_list.elementAt(i);
	    }
	    if (this.selected_image != null) {
		if (this.selected_mode == ImageWindow.PICK_MODE) {
		    PickNode tmp = this.selected_pick;
		    this.selected_pick = old_pick;
		    this.applyInteractionMode (ImageWindow.NO_MODE, event_time);
		    this.selected_pick = tmp;
		    this.applyInteractionMode (ImageWindow.PICK_MODE, event_time);
		} else {
		    this.applyInteractionMode (this.selected_mode, event_time);
		}
	    }
	    return true;
	}

	//
	// Choose an image tool
	//
	if ((this.image_chooser != null) && (e.target == this.image_chooser)) {
	    String image_name = image_chooser.getSelectedItem();
	    if ((this.named_image_list != null) && (this.named_image_list.size() > 0)) {
		if (this.selected_image != null) {
		    this.applyInteractionMode (ImageWindow.NO_MODE, event_time);
		}
		int i = this.image_chooser.getSelectedIndex();
		this.selected_image = (ImageNode)this.named_image_list.elementAt(i);
		this.applyInteractionMode (this.selected_mode, event_time);
		if ((this.mode_chooser != null) && (this.modes != null)){
		    int mode = this.selected_image.getInteractionMode();
		    //
		    // loop over modes in this.modes in order to find
		    // the index to stick into mode_chooser which
		    // corresponds to mode.
		    //
		    int k;
		    int length = this.modes.length;
		    for (k=0; k<length; k++) {
			if (this.modes[k] == mode) {
			    this.mode_chooser.select(k);
			    break;
			}
		    }
		}
	    }
	    this.updateCaching(this.selected_image);
	    return true;
	}

	//
	// Select a view
	//
	if ((this.view_chooser != null) && (e.target == this.view_chooser)) {
	    if (this.selected_image != null) 
		this.selected_image.setView(this.view_chooser.getSelectedIndex(), true);
	}

	//
	// Select an interaction mode
	//
	if ((this.mode_chooser != null) && (e.target == this.mode_chooser)) {
	    int old_mode = this.selected_mode;

	    int ndx = this.mode_chooser.getSelectedIndex();
	    this.selected_mode = this.modes[ndx];
	    
	    if (this.selected_mode == ImageWindow.RESET_CAMERA) {
		if (this.selected_image != null) {
		    this.selected_image.resetCamera(true, false);
		    this.DXLExecuteOnce();
		    this.selected_image.resetCamera(false, false);
		}
		this.mode_chooser.select(0);
		this.selected_mode = ImageWindow.NO_MODE;
	    }

	    if ((this.selected_mode == old_mode) && (old_mode == ImageWindow.LOOP_MODE)) {
		this.applyInteractionMode(ImageWindow.NO_MODE, 0);
		old_mode = ImageWindow.NO_MODE;
	    }

	    if (this.selected_mode == ImageWindow.LOOP_MODE) {
		if (this.set_caching == null) this.setCachingMode(true, false);
	    }

	    if (this.pick_chooser != null) {
		if (this.selected_mode == ImageWindow.PICK_MODE)
		    this.pick_chooser.enable();
		else
		    this.pick_chooser.disable();
	    }

	    if (this.selected_mode == ImageWindow.ORBIT_MODE) {
		if (this.sequencer != null) {
		    SequencerNode sn = (SequencerNode)this.sequencer;
		    sn.reset();
		}
	    }

	    if (this.selected_image != null) {
		if ((this.dirty == true) && (ndx == this.sequence_mode_choice) &&
		    (this.sequencer != null)) {
		    SequencerNode sn = (SequencerNode)this.sequencer;
		    sn.reset();
		    this.setCacheOption(ImageNode.RESET);
		}
		boolean status = this.applyInteractionMode
		    (this.selected_mode, event_time);
		if ((status == false) && (this.selected_mode == ImageWindow.LOOP_MODE)) {
		    if ((ndx == this.sequence_mode_choice) && (this.sequencer != null)) {
			this.applyInteractionMode(ImageWindow.NO_MODE, 0);
			SequencerNode sn = (SequencerNode)this.sequencer;
			sn.reset();
			this.setCacheOption(ImageNode.RESET);
			this.setCacheSize(sn.getSteps());
			//sn.step(this);
			this.DXLExecuteOnce();
			sn.stepQuietly();
			status = true;
		    }
		}
		if (status == false) {
		    this.mode_chooser.select(old_mode);
		    this.selected_mode = old_mode;
		}
	    }
	    return true;
	}

	//
	// Hit Connect
	//
	if (e.target == this.connect_btn) {
	    if (this.isConnected()) {
		this.disconnect(null);
	    } else { this.in_connect_callback = true;
		this.connect();
		this.in_connect_callback = false;
	    }
	    return true;
	}


	return false;
    }

    private void setCacheOption (int mode) {
	if (mode == ImageNode.RESET) 
	    this.cache_options.select(0);
	ImageNode in = this.selected_image;
	String group_name = in.getGroupName();
	if (group_name == null) {
	    in.setCacheOption(mode);
	    return ;
	}
	Vector node_list = null;
	Class ic = null;
	try {
	    ic = Class.forName("dx.net.ImageNode");
	} catch (Exception e) {
	    System.out.println ("DXApplication: failed to list ImageNodes");
	}
	if (ic != null)
	    node_list = this.network.makeNodeList(ic, false);

	if (node_list != null) {
	    Enumeration enum = node_list.elements();
	    while (enum.hasMoreElements()) {
		ImageNode n = (ImageNode)enum.nextElement();
		if (group_name.equals(n.getGroupName()))
		    n.setCacheOption(mode);
	    }
	}
    }

    private void setCacheSize(int size) {
	ImageNode in = this.selected_image;
	String group_name = in.getGroupName();
	if (group_name == null) {
	    in.setCacheSize(size);
	    return ;
	}
	Vector node_list = null;
	Class ic = null;
	try {
	    ic = Class.forName("dx.net.ImageNode");
	} catch (Exception e) {
	    System.out.println ("DXApplication: failed to list ImageNodes");
	}
	if (ic != null)
	    node_list = this.network.makeNodeList(ic, false);

	if (node_list != null) {
	    Enumeration enum = node_list.elements();
	    while (enum.hasMoreElements()) {
		ImageNode n = (ImageNode)enum.nextElement();
		if (group_name.equals(n.getGroupName()))
		    n.setCacheSize(size);
	    }
	}
    }

    public boolean setInteractionMode (int mode, long time) {
	if (this.applyInteractionMode(mode, time) == false) return false;


	//
	// loop over modes in this.modes in order to find
	// the index to stick into mode_chooser which
	// corresponds to mode.
	//
	if (this.mode_chooser != null) {
	    int k;
	    int length = this.modes.length;
	    for (k=0; k<length; k++) {
		if (this.modes[k] == mode) {
		    this.mode_chooser.select(k);
		    break;
		}
	    }
	}
	this.selected_mode = mode;
	return true;
    }

    private boolean applyInteractionMode(int mode, long time) {
	ImageNode in = this.selected_image;
	boolean status = in.setInteractionMode(mode, time);
	if (status == false) return false;
	String group_name = in.getGroupName();
	if (group_name == null) return true;
	if (ImageWindow.IsGroupInteraction(mode)) {
	    Vector node_list = null;
	    Class ic = null;
	    try {
		ic = Class.forName("dx.net.ImageNode");
	    } catch (Exception e) {
		System.out.println ("DXApplication: failed to list ImageNodes");
	    }
	    if (ic != null)
		node_list = this.network.makeNodeList(ic, false);

	    if (node_list != null) {
		Enumeration enum = node_list.elements();
		while (enum.hasMoreElements()) {
		    ImageNode n = (ImageNode)enum.nextElement();
		    if (group_name.equals(n.getGroupName()))
			n.setInteractionMode(mode, time);
		}
	    }
	}
	return true;
    }

    public void paint (Graphics g) {
	super.paint(g);
	if (this.getMakesGui() == false) return ;
	if (this.shadows == false) return ;
	Dimension d = size();
	g.setColor(Color.black);
	g.drawRect (0,TABHEIGHT,d.width-SHADOW,d.height-(SHADOW+TABHEIGHT));
	g.fillRect (SHADOW,d.height-SHADOW,d.width-SHADOW,SHADOW);
	g.fillRect (d.width-SHADOW,TABHEIGHT+SHADOW,SHADOW,d.height-(SHADOW+TABHEIGHT));
    }

    public ImageWindow getImageWindow(int id) {
        ImageWindow iw = null;
        if (this.imageWindows.size() == 0)
            this.locateImageWindows();
        try {
            iw = (ImageWindow)this.imageWindows.elementAt(id);
        } catch (ArrayIndexOutOfBoundsException aiobe) {
        } catch (NullPointerException npe) {
        }
        return iw;
    }

    public void showWorld(String name, String path, int id) { }

    private void locateImageWindows() {
	AppletContext apcxt = this.getAppletContext();
	Enumeration enum = apcxt.getApplets();
	while (enum.hasMoreElements()) {
	    Applet a = (Applet)enum.nextElement();
	    if ((a != null) && (a.isActive()) && (a instanceof ImageWindow)) {
		if (this.imageWindows.contains((Object)a) == false)
		    this.imageWindows.addElement((Object)a);
	    }
	}
    }

    public synchronized void DXLSend (String msg) {
	if (msg.lastIndexOf("assign noexecute") == -1) {
	    this.dirty = true;
	    if (this.eocMode) 
		this.DXLExecuteOnce();
	}
    }


    public void enableModeSelector(boolean active) {
	if (this.mode_chooser == null) return ;
	if (active) this.mode_chooser.enable();
	else this.mode_chooser.disable();
    }

    public synchronized void finishedExecuting() {
	if ((this.isExecuting() == false) && (this.execCtrl != null)) {
	    Checkbox cb = this.execCtrl.getTab();
	    if (this.getEocMode() == true) 
		//cb.setForeground(new Color((float)0.49, (float)0.49, (float)0.7));
		cb.setForeground(new Color((float)0.35, (float)0.2, (float)1.0));
	    else
		cb.setForeground(Color.black);
	    Graphics g = cb.getGraphics();
	    cb.paint(g);
	    cb.disable();
	    cb.enable();

	    //
	    // Do another sequencer step?
	    //
	    if ((this.sequencer != null)&&(this.selected_mode == ImageWindow.LOOP_MODE)) {
		int ndx = this.mode_chooser.getSelectedIndex();
		if ((ndx == this.sequence_mode_choice) && 
		    (this.selected_image.getInteractionMode() != ImageWindow.LOOP_MODE)) {
		    SequencerNode sn = (SequencerNode)this.sequencer;
		    int snsteps = sn.getSteps();
		    int isteps = this.selected_image.getCacheCount();
		    if (snsteps != isteps) 
			this.setCacheSize(sn.getSteps());

		    Date now = new Date();
		    long et = now.getTime();
		    if (sn.hasMoreFrames() == true) {
			//sn.step(this);
			this.DXLExecuteOnce();
			sn.stepQuietly();
		    } else if (this.selected_image != null) {
			this.applyInteractionMode(this.selected_mode, et);
		    }
		}
	    } else if (this.selected_mode == ImageWindow.PICK_MODE) {
		PickNode pn = this.getSelectedPickNode();
		ImageNode in = this.getSelectedImageNode();
		if ((pn != null) && (in != null)) {
		    in.resetPickList();
		}
	    }
	}
    }

    public void DXLEndExecution() {
	if ((this.sequencer != null)&&(this.selected_mode == ImageWindow.LOOP_MODE)) 
	    this.setInteractionMode(ImageWindow.NO_MODE, 0);
    }

    /*
    protected void page(boolean up) { 
	if (this.panels == null) return ;

	int index = this.selected_panel;

	if (up) ((CardLayout)cardPanel.getLayout()).previous (cardPanel); 
	else ((CardLayout)cardPanel.getLayout()).next (cardPanel); 

	if (up) index--;
	else index++;

	// There exist getPanelCount() + 1 panels
	if (index < 0)
	    index = this.network.getPanelCount();
	else if (index > this.network.getPanelCount()) 
	    index = 0;

	ControlPanel cp = (ControlPanel)this.panels.elementAt(index);
	Checkbox cb = cp.getTab();
	this.selected_panel = index;
	cb.setState(true);
    }
    */

    public String getBWCompatString() {
	if (this.bwcompat_checked) return this.bwcompat_string;
	this.bwcompat_string = null;
	this.bwcompat_checked = true;

	try {
	    //
	    // Pare down each one to the rightmost '/'
	    //
	    String docbase = this.getDocumentBase().toString();
	    String codebase = this.getCodeBase().toString();
	    int dind = docbase.lastIndexOf((int)'/');
	    int cind = codebase.lastIndexOf((int)'/');

	    docbase = docbase.substring (0, dind);
	    codebase = codebase.substring (0, cind);

	    if (docbase.equals(codebase)) this.bwcompat_string = "../";
	} catch (Exception e) {
	}

	return this.bwcompat_string;
    }



}; // end DXApplication
