using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    /// <summary>
    /// Definition for the Interactor class.					 
    /// 
    /// The Interactor represents the 'standin' that sits in the ControlPanel
    /// work space.  Each Interactor is tied to an InteractorNode (a stand in
    /// in the Editor workspace) through an InteractorInstance.  The
    /// InteractorInstance stores information local to the Interactor and does
    /// not make any assumptions about the windowing environment.  Each
    /// InteractorNode can have an unlimited number of
    /// Interactor/InteractorInstance pairs.
    /// 
    /// There are 3 main sets of methods associated with an Interactor.  The
    /// first has to do with constructing what is displayed in the control
    /// panel work space. All Interactors and derived classes have a basic
    /// layout  and must implement this->createInteractivePart(), which should
    /// build the part that takes input from the user.  This is then placed in
    /// the default layout using this->layoutInteractor().  Before
    /// layoutInteractor() returns this->completeInteractivePart() is called to
    /// finish any thing having to do with the interactor part.  Typically,
    /// this is just calling this->passEvents() so that most events get passed
    /// through interactor part.  The first two of the routines discussed so
    /// far are virtual and so can be redefined for derived classes.
    /// 
    /// The second set of methods (just 1 method here) is what to do when
    /// the Interactor in the control panel receives indication that the
    /// default action is to be taken.  this->openDefaultWindow implements
    /// this action.  It is a virtual function and can be redefined, but
    /// at this level is defined to open the set attributes dialog box.
    /// 
    ///
    ///
    ///  This is the widget layout of an Interactor.  These widgets are
    ///  created in Interactor.C.  Subclasses create children inside
    ///  this->customPart.  The Workspace widget handles installing translations
    ///  on form (this->root).  Interactor::createInteractor handles translations
    ///  for label and customPart.  passEvents() handles whatever extra widgets are
    ///  created by a subclass.
    ///
    /// --------f-o-r-m-------------------
    /// -                                -
    /// -                                -
    /// -   ----l-a-b-e-l------------    -
    /// -   -                       -    -
    /// -   -                       -    -
    /// -   -------------------------    -
    /// -                                -
    /// -   ---c-u-s-t-o-m-P-a-r-t---    -
    /// -   -                       -    -
    /// -   -                       -    -
    /// -   -                       -    -
    /// -   -                       -    -
    /// -   -                       -    -
    /// -   -                       -    -
    /// -   -------------------------    -
    /// -                                -
    /// -                                -
    /// ----------------------------------
    ///
    /// Functions for selecting and resizing are no longer here.  They live
    /// in WorkSpaceComponent instead.
    /// </summary>
    public abstract partial class Interactor : UserControl
    {
        public enum Status {
            InteractorSelected = 1,
            InteractorDeselected = 2
        };

        private static bool InteractorClassInitialized;

        private int drag_drop_wpid;

        protected InteractorInstance interactorInstance;
        protected virtual void passEvents(Form f, bool dnd)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Build the complete interactor.  Make a form and a label and
        /// invoke the subclasses ::createInteractivePart method.
        /// </summary>
        public void createInteractor()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Layout/size the root, label and interactivePart.
        /// </summary>
        protected void layoutInteractor()
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void layoutInteractorHorizontally()
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void layoutInteractorVertically()
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void layoutInteractorWithNoLabel()
        {
            throw new Exception("Not Yet Implemented");
        }

        protected virtual String getComponentHelpTopic()
        {
            throw new Exception("Not Yet Implemented");
        }

        //Drag-n-drop stuff needed.


        protected Interactor(String name, InteractorInstance ii)
        {
            InitializeComponent();
        }

        /// <summary>
        /// Set the displayed label of the interactor and do a layout if
        /// indicated to handle a significant change in label width.
        /// </summary>
        /// <param name="labelString"></param>
        public virtual void setLabel(String labelString)
        {
            setLabel(labelString, true);
        }
        public virtual void setLabel(String labelString, bool re_layout)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual void setSelected(bool state)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Open the window for the default action (a double click) of 
        /// this interactor;
        /// </summary>
        public virtual void openDefaultWindow()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Reset the resources of the widget based on a presumably new set 
        /// of attributes.  The src_ii is the InteractorInstance that has
        /// initialiated the attribute change.  Some attributes (local or
        /// per interactor ones) may be ignored if the attribute change is 
        /// initiated by a src_ii such that this->instance != src_ii. 
        /// This should also include updating the displayed value.
        /// If major_change is TRUE, then the subclass may choose to unmanage
        /// itself while changes (presumably major) are made to it.
        /// handleInteractorStateChange() remanages the interactor root widget
        /// if it was unmanaged by handleInteractivePartStateChange().
        /// </summary>
        /// <param name="src_ii"></param>
        /// <param name="major_change"></param>
        public virtual void handleInteractorStateChange(InteractorInstance src_ii,
            bool major_change)
        {
            throw new Exception("Not Yet Implemented");
        }
        public abstract void handleInteractivePartStateChange(InteractorInstance src_ii,
            bool major_change);

        /// <summary>
        /// Update the display values for an interactor; 
        /// Called when an InteractorNode does a this->setOutputValue().
        /// </summary>
        public abstract void updateDisplayedInteractorValue();

        public void setVerticalLayout() { setVerticalLayout(true); }
        public void setVerticalLayout(bool vertical)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setBlankLabelLayout() { setBlankLabelLayout(true); }
        public void setBlankLabelLayout(bool blank_label)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool acceptsLayoutChanges()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Indicate that the interactor is selected.  Generally, this means 
        /// highlighting.  This really only needs to be called when the
        /// control panel is first opened up, after that the workspace takes
        /// care of highlighting.  This can be called if the root widget
        /// has not yet been created, but the selection may not be reflected.
        /// </summary>
        /// <param name="selected"></param>
        public void indicateSelect(bool selected)
        {
            throw new Exception("Not Yet Implemented");
        }

        public Network getNetwork()
        {
            throw new Exception("Not Yet Implemented");
        }
        public Node getNode()
        {
            throw new Exception("Not Yet Implemented");
        }
        public ControlPanel getControlPanel()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual void initialize()
        {
            throw new Exception("Not Yet Implemented");
        }

    }
}
