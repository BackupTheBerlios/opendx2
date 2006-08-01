using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WinDX.UI
{
    public class InteractorInstance
    {
        protected String localLabel;
        protected Interactor interactor;
        protected ControlPanel controlPanel;
        protected int xpos, ypos;
        protected int width, height;
        protected InteractorStyle style;
        protected InteractorNode node;
        protected bool selected;
        protected bool verticalLayout;

        /// <summary>
        /// Make sure the given output's current value complies with any attributes.
        /// This is called by InteractorInstance::setOutputValue() which is
        /// intern intended to be called by the Interactors.
        /// If verification fails (returns FALSE), then a reason is expected to
        /// placed in reason.
        /// At this level we always return TRUE (assuming that there are no
        /// attributes) and set *reason to NULL.
        /// </summary>
        /// <param name="output"></param>
        /// <param name="val"></param>
        /// <param name="t"></param>
        /// <param name="reason"></param>
        /// <returns></returns>
        protected virtual bool verifyValueAgainstAttributes(int output,
            String val, DXTypeVals t, ref String[] reason)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected virtual bool defaultVertical() { return true; }

        protected static int CountLines(String str)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected static String FetchLine(String str, int line)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected String java_var_name = null;
        protected virtual String javaName() { return "tfld"; }

        public InteractorInstance(InteractorNode n)
        {
            throw new Exception("Not Yet Implemented");
        }

        ~InteractorInstance() { throw new Exception("Not Yet Implemented"); }

        public void setPanel(ControlPanel panel)
        {
            controlPanel = panel;
        }
        public void setLocalLabel(String label)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setXYPosition(int x, int y)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setXYSize(int width, int height)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setStyle(InteractorStyle istyle)
        {
            style = istyle;
        }
        public bool IsSelected { get { return selected; } }
        public void setSelected(bool select)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void setSelected() { setSelected(true); }
        public void clrSelected() { setSelected(false); }
        public virtual void setVerticalLayout() { setVerticalLayout(true); }
        public virtual void setVerticalLayout(bool val)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool IsVerticalLayout { get { return verticalLayout; } }

        // Ask the InteractorStyle to build an Interactor for this instance.
        public void createInteractor()
        {
            throw new Exception("Not Yet Implemented");
        }

        public String getInteractorLabel()
        {
            throw new Exception("Not Yet Implemented");
        }
        public String getLocalLabel()
        {
            return localLabel;
        }
        public void getXYPosition(out int x, out int y)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// If the interactor for this instance exists, then return TRUE
        /// and the width and height in *x and *y respectively.
        /// If the interactor does not exists return FALSE and set *x and *y to 0.
        /// </summary>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <returns></returns>
        public bool getXYSize(out int width, out int height)
        {
            throw new Exception("Not Yet Implemented");
        }

        public InteractorStyle getStyle() { return style; }
        public ControlPanel getControlPanel() { return controlPanel; }
        public Form getParentForm() { throw new Exception("Not Yet Implemented"); }

        public Interactor getInteractor() { return interactor; }
        public Node getNode() { return node; }
        public Network getNetwork()
        {
            throw new Exception("Not Yet Implemented");
        }

        public void changeStyle(InteractorStyle style)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Delete an interactor in such a way that we could create another one
        /// with createInteractor().
        /// </summary>
        public void uncreateInteractor()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Send notification to this->interactor that the attributes may have 
        /// changed and to reflect these changes in the display Interactor. 
        /// Some changes can be ignored if 'this != src_ii'.  This is typically
        /// called by InteractorNode::notifyInstancesOfStateChange().
        /// </summary>
        /// <param name="src_ii"></param>
        /// <param name="unmanage"></param>
        public void handleInteractorStateChange(InteractorInstance src_ii)
        {
            handleInteractorStateChange(src_ii, false);
        }
        public void handleInteractorStateChange(InteractorInstance src_ii,
            bool unmanage)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool IsDataDriven
        {
            get
            {
                InteractorNode n = (InteractorNode)getNode();
                return n.IsDataDriven;
            }
        }

        /// <summary>
        /// Return TRUE/FALSE indicating if this class of interactor instance has
        /// a set attributes dialog (i.e. this->newSetAttrDialog returns non-NULL).
        /// At this level in the class hierarchy, we return FALSE.
        /// </summary>
        /// <returns></returns>
        public virtual bool hasSetAttrDialog()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Open the set attributes dialog for this Interactor.
        /// </summary>
        public void openSetAttrDialog()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Make sure the given value complies with any attributes and if so
        /// set the value in the Node.  This should generally be called from
        /// interactors that can't directly enforce  attributes.  For example,
        /// the Text style versus the Stepper style Vector interactor.  The
        /// Stepper style enforces its attributes itself, but the Text style
        /// accepts any value and then must have the value checked for type
        /// and attribute compliance.
        /// If we fail because attribute verification fails, then *reason contains
        /// the reason (as passed back by verifyValueAgainstAttributes()) for
        /// failure.  
        /// </summary>
        /// <param name="index"></param>
        /// <param name="val"></param>
        /// <param name="type"></param>
        /// <param name="send"></param>
        /// <param name="reason"></param>
        /// <returns></returns>
        public bool setAndVerifyOutput(int index, String val, DXTypeVals type, 
            bool send, ref String reason)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Called from ControlPanel in the process of performing cut/copy + paste
        /// of interactors within the control panels of one executable.  If possible
        /// change the pointers so that this instance no long belongs to a temp net
        /// but to the real network (passwd in in newnet). Return True on success.
        /// </summary>
        /// <param name="newnet"></param>
        /// <returns></returns>
        public bool switchNets(Network newnet)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool printAsJava(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual String getJavaVariable()
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
