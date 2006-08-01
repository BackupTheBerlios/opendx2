using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    public enum SequencerDirection
    {
        Forward = 1,
        Backward = 2,
        Directionless,
        Loop,
        Palindrome,
        Step,
        Count,
        Stop,
        Pause,
        Forward_Step,
        Backard_Step,
        Nothing
    };

    public class SequencerNode : ShadowedOutputNode
    {

        #region Private Instance Variables

        //
        // Private member data:
        //
        int xpos, ypos, width, height;

        SequencerWindow seq_window;
        bool step;           /* step mode?                   */
        bool loop;           /* loop mode?                   */
        bool palindrome;     /* palindrome mode?             */

        bool current_defined;/* current frame defined?       */
        bool stop_requested; /* execution stop requested?    */
        int startValue;	    	// Start frame
        int stopValue;		// Stop frame

        //short           minimum;        /* minimum frame                */
        //short           maximum;        /* maximum frame                */
        //short           start;          /* start frame                  */
        //short           stop;           /* stop frame                   */
        //short           increment;      /* frame increment              */

        short current;        /* current frame                */
        short next;           /* current frame                */
        short previous;       /* previous frame               */

        bool ignoreFirstFrameMsg;
        bool transmitted;    /* frame values transmitted?    */
        public bool Transmitted { get { return transmitted; } set { transmitted = value; } }
        //
        // Indicates if this node has ever been executed
        // (even across different executions of the User Interface).  This is
        // used to tell the Sequencer module in the executive when to ignore
        // the frame input (it ignores it if it has never been executed before).
        //
        bool wasExecuted;    // Has this instance ever been run 

        //
        // Nov, 1996 - added startup flag to print/parse operation so that you
        // could start in image mode without having the vcr appear.  To preserve
        // old behavior, record whether or not you actuall parsed a startup value
        // and treat those sequencers for which there was not value parsed as if
        // the vcr is a startup window.
        //
        bool startup;

        #endregion

        #region Private Methods
        //
        // Handler for 'frame %d %d' messages.
        //
        private static void ProcessFrameInterrupt(Object clientData, int id, Object p)
        { throw new Exception("not implemented yet"); }

        private void setStartup(bool on)
        { this.startup = on; }

        //
        // Disable the Frame control.
        //
        private void disableFrameControl()
        { throw new Exception("not implemented yet"); }
        //
        // Enable the Frame control if the node is not data driven.
        //
        private void enableFrameControl()
        { throw new Exception("not implemented yet"); }
        //
        // Set the buttons that indicate the direction of play.
        //
        public void setPlayDirection(SequencerDirection dir)
        { throw new Exception("not implemented yet"); }
        private void setForwardPlay()
        { throw new Exception("not implemented yet"); }
        private void setBackwardPlay()
        { throw new Exception("not implemented yet"); }
        private void setStepMode(bool step)
        { throw new Exception("not implemented yet"); }
        private void setLoopMode(bool loop)
        { throw new Exception("not implemented yet"); }
        private void setPalindromeMode(bool pal)
        { throw new Exception("not implemented yet"); }

        // 
        //  Print/parse comments that are common to both .nets and .cfgs.
        // 
        private bool printCommonComments(String file, String indent)
        { throw new Exception("not implemented yet"); }
        private bool parseCommonComments(String comment, String file, int lineno)
        { throw new Exception("not implemented yet"); }

        #endregion

        #region Protected Methods

        //
        // Protected member data:
        //
        protected override String netNodeString(String prefix)
        { throw new Exception("not implemented yet"); }
        protected override String valuesString(String prefix)
        { throw new Exception("not implemented yet"); }
        protected virtual bool cfgPrintNode(String f, PrintType dest)
        { throw new Exception("not implemented yet"); }

        protected virtual bool netPrintAuxComment(String f)
        { throw new Exception("not implemented yet"); }
        protected override bool netParseAuxComment(String comment,
                                                    String file, int lineno)
        { throw new Exception("not implemented yet"); }

        //
        // The messages we parse can contain one or more of the following...
        //
        // 'min=%g' 'max=%g' 'start=%d' 'end=%d' 'delta=%g' 
        //
        // If any input or output values are to be changed, don't send them
        // because the module backing up the sequencer will have just executed
        // and if the UI is in 'execute on change' mode then there will be an
        // extra execution.
        //
        // Returns the number of attributes parsed.
        //
        protected override int handleNodeMsgInfo(String line)
        { throw new Exception("not implemented yet"); }

        //
        // Update the Sequencer state that is based on the state of this
        // node.   Among other times, this is called after receiving a message
        // from the executive.
        //
        protected override void reflectStateChange(bool unmanage)
        { throw new Exception("not implemented yet"); }

        //
        // Initialize the attributes with the give string values.
        //
        protected bool initMinimumValue(int val)
        { throw new Exception("not implemented yet"); }
        protected bool setMinimumValue(int val)
        { throw new Exception("not implemented yet"); }

        protected bool initMaximumValue(int val)
        { throw new Exception("not implemented yet"); }
        protected bool setMaximumValue(int val)
        { throw new Exception("not implemented yet"); }

        protected bool initDeltaValue(int val)
        { throw new Exception("not implemented yet"); }
        protected bool setDeltaValue(int val)
        { throw new Exception("not implemented yet"); }

        protected bool initStartValue(int val)
        { throw new Exception("not implemented yet"); }
        protected bool setStartValue(int val)
        { throw new Exception("not implemented yet"); }

        protected bool initStopValue(int val)
        { throw new Exception("not implemented yet"); }
        protected bool setStopValue(int val)
        { throw new Exception("not implemented yet"); }

        //
        // The Sequencer always expects the 'frame %d %d'  message and when
        // data-driven expects 'Sequencer_%d: ...' messages.  We install the
        // handler for the 'frame' message here and then call the super class
        // to install the 'Sequencer_%d:' handler.
        //
        protected virtual bool hasModuleMessagingProtocol() { return true; }
        protected override void updateModuleMessageProtocol(DXPacketIF pif)
        { throw new Exception("not implemented yet"); }

        //
        // If the min or max input has changed, update the attribute parameter
        // (integer list of min and max) and then call the super class method
        // if the input is not the attribute parameter.
        //
        protected override void ioParameterStatusChanged(bool input, int index,
                                    Node.NodeParameterStatusChange status)
        { throw new Exception("not implemented yet"); }


        //
        // Make sure the value of the parameter that holds a list of ui attributes
        // (i.e. min/max/incr) is up to date in the executive.
        // Always send it since the input attribute is cache:0.
        //
        protected void updateAttributes()
        { throw new Exception("not implemented yet"); }
        #endregion

        #region Public Methods
        //
        // Constructor:
        //
        public SequencerNode(NodeDefinition nd, Network net, int instnc) :
            base(nd, net, instnc)
        { throw new Exception("not implemented yet"); }


        public override bool initialize()
        { throw new Exception("not implemented yet"); }
        public override void openDefaultWindow(Form f)
        { throw new Exception("not implemented yet"); }
        public bool isStartup()
        { throw new Exception("not implemented yet"); }

        //
        // Let the caller of openDefaultWindow() know what kind of window she's getting.
        // This is intended for use in EditorWindow so that we can sanity check the number
        // of cdbs were going to open before kicking off the operation and so that we
        // don't question the user before opening large numbers of interactors.
        // A name describing the type of window can be written into window_name in order
        // to enable nicer warning messages.
        //
        public override bool defaultWindowIsCDB(ref String window_name)
        {
            window_name = "Sequencer";
            return false;
        }

        public override bool cfgParseComment(String comment,
                                            String file,
                                            int lineno)
        { throw new Exception("not implemented yet"); }

        public bool isMinimumVisuallyWriteable()
        { throw new Exception("not implemented yet"); }
        public bool isMaximumVisuallyWriteable()
        { throw new Exception("not implemented yet"); }

        public bool isDeltaVisuallyWriteable()
        { throw new Exception("not implemented yet"); }

        public int getMinimumValue()
        { throw new Exception("not implemented yet"); }
        public int getMaximumValue()
        { throw new Exception("not implemented yet"); }
        public int getDeltaValue()
        { throw new Exception("not implemented yet"); }
        public int getStartValue()
        { throw new Exception("not implemented yet"); }
        public int getStopValue()
        { throw new Exception("not implemented yet"); }


        public bool isStepMode() { return this.step; }
        public bool isLoopMode() { return this.loop; }
        public bool isPalindromeMode() { return this.palindrome; }

        //
        // Get a string representing the assignment to the global vcr variables, 
        // @startframe, @frame, @nextframe, @endframe and @deltaframe.
        // The returned string must be deleted by the caller.
        //
        public String getFrameControlString()
        { throw new Exception("not implemented yet"); }

        public Form getVCRForm()
        { throw new Exception("not implemented yet"); }

        //
        // Determine if this node is a node of the given class
        //
        public override bool isA(Symbol classname)
        { throw new Exception("not implemented yet"); }

        public override bool canSwitchNetwork(Network from, Network to)
        { throw new Exception("not implemented yet"); }

        public override DXWindow getDXWindow()
        { return this.seq_window; }

        //
        // Return TRUE if this node has state that will be saved in a .cfg file.
        //
        public override bool hasCfgState()
        { throw new Exception("not implemented yet"); }

        //
        // Most nodes' id parameter is number 1 but a few aren't.  This number is
        // important because whenever you merge 2 nets, you update instance numbers.
        // When you do that, you must also change the id parameter and for that you
        // need its number.
        //
        public override int getMessageIdParamNumber()
        { throw new Exception("not implemented yet"); }

        public override String getJavaNodeName()
        { return "SequencerNode"; }
        public override bool printInputAsJava(int input)
        { throw new Exception("not implemented yet"); }
        public override String getJavaInputValueString(int index)
        { throw new Exception("not implemented yet"); }

        #endregion

    }
}
