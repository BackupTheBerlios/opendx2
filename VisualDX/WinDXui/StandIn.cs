using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using System.IO;

namespace WinDX.UI
{
    public class StandIn : Control
    {
        public enum DragDataType
        {
            Modules,
            Interactors,
            Trash
        };

        #region Private Instances
        private static bool ClassInitialized;
        private Control DragIcon;
        private Dictionary<String, TransferStyle> DragTypeDictionary;

        private bool selected;
        private WorkSpace workSpace;

        private List<Tab> inputTabList;
        private List<Tab> outputTabList;



        #endregion

        #region Protected Instances

        protected Node node;

        #endregion

        #region Private Methods

        private void trackArk() { throw new Exception("Not Yet Implemented"); }

        private bool setMinimumWidth(ref int width) { throw new Exception("Not Yet Implemented"); }
        private int VisibleInputCount { get { throw new Exception("Not Yet Implemented"); } }
        private int VisibleOutputCount { get { throw new Exception("Not Yet Implemented"); } }
        private void adjustParameterLocations(int width) { throw new Exception("Not Yet Implemented"); }

        private Tab createInputTab(Control parent, int index, int width)
        {
            throw new Exception("Not Yet Implemented");
        }
        private Tab createOutputTab(Control parent, int index, int width)
        {
            throw new Exception("Not Yet Implemented");
        }

        private void indicateSelection(bool select) { throw new Exception("Not Yet Implemented"); }

        private void setVisibility(int index, bool outputTab) { throw new Exception("Not Yet Implemented"); }
        private String createButtonLabel() { throw new Exception("Not Yet Implemented"); }

        #endregion

        #region Protected Methods

        protected virtual Dictionary<String, TransferStyle> getDragDictionary()
        {
            return DragTypeDictionary;
        }

        protected virtual void initialize() { throw new Exception("Not Yet Implemented"); }

        protected void setButtonLabel() { throw new Exception("Not Yet Implemented"); }
        protected virtual String getButtonLabel() { throw new Exception("Not Yet Implemented"); }
        protected virtual void handleSelectionChange(bool select) { throw new Exception("Not Yet Implemented"); }
        protected virtual String getButtonLabelFont()
        {
            return "canvas";
        }

        // ... drag n drop stuff was here

        protected StandIn(WorkSpace w, Node n) { throw new Exception("Not Yet Implemented"); }
        

        #endregion

        // Not implemented
        public static StandIn AllocateStandIn(WorkSpace w, Node n)
        {
            throw new Exception("Not Yet Implemented");
        }

        ~StandIn() { throw new Exception("Not Yet Implemented"); }

        public void createStandIn() { throw new Exception("Not Yet Implemented"); }
        public void addInput(int index) { throw new Exception("Not Yet Implemented"); }
        public void removeLastInput() { throw new Exception("Not Yet Implemented"); }

        public void addOutput(int index) { throw new Exception("Not Yet Implemented"); }
        public void removeLastOutput() { throw new Exception("Not Yet Implemented"); }

        public virtual void setLabelColor(Color color)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual Color getLabelColor() { throw new Exception("Not Yet Implemented"); }

        public void deleteArk(Ark a) { throw new Exception("Not Yet Implemented"); }
        public void drawArks(Node dst_node)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void drawTab(int paramIndex, bool outputTab)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void ioStatusChange(int index, bool outputTab,
            Node.NodeParameterStatusChange status) { throw new Exception("Not Yet Implemented"); }

        public static void ToggleHotSpots(EditorWindow editor, Node destnode, bool on)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void displayTabLabel(int index, bool outputTab)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void clearTabLabel() { throw new Exception("Not Yet Implemented"); }

        public Tab getInputParameterTab(int i) { throw new Exception("Not Yet Implemented"); }
        public Tab getOutputParameterTab(int i) { throw new Exception("Not Yet Implemented"); }

        public Tab getParameterTab(int i, bool input)
        {
            return (input ? getInputParameterTab(i) :
                getOutputParameterTab(i));
        }

        // .. stuff with ParameterLines

        public int getIOWidth() { throw new Exception("Not Yet Implemented"); }
        public int getIOHeight() { throw new Exception("Not Yet Implemented"); }

        public int getInputParameterTabX(int i) { throw new Exception("Not Yet Implemented"); }
        public int getInputParameterTabY(int i) { throw new Exception("Not Yet Implemented"); }

        public int getOutputParameterTabX(int i) { throw new Exception("Not Yet Implemented"); }
        public int getOutputParameterTabY(int i) { throw new Exception("Not Yet Implemented"); }

        public int getParameterTabY(int i, bool input)
        {
            return (input ? getInputParameterTabY(i) : getOutputParameterTabY(i));
        }
        public int getParameterTabX(int i, bool input)
        {
            return (input ? getInputParameterTabX(i) : getOutputParameterTabX(i));
        }

        public void setSelected(bool s) { throw new Exception("Not Yet Implemented"); }
        public bool IsSelected { get { return selected; } }

        public void addArk(EditorWindow editor, Ark a) { throw new Exception("Not Yet Implemented"); }

        /// <summary>
        /// Print a representation of the stand in on a PostScript device.  We
        /// assume that the device is in the same coordinate space as the parent
        /// of this uicomponent (i.e. we send the current geometry to the 
        /// PostScript output file).  We do not print the ArkStandIns, but do
        /// print the Tabs.
        /// </summary>
        /// <param name="sw"></param>
        /// <param name="label_parameters"></param>
        /// <returns></returns>
        public bool printPostScriptPage(StreamWriter sw, bool label_parameters)
        {
            throw new Exception("Not Yet Implemented");
        }
        public static bool PrintPostScriptSetup(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual String getPostScriptLabelFont()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// This function can be called to notify a standin that its label
        /// has changed.  By default, this standin just calls setButtonLabel() 
        /// to reset the label. 
        /// </summary>
        public virtual void notifyLabelChange()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Now that StandIns can live in any WorkSpace, we need to query this.
        /// </summary>
        /// <returns></returns>
        public WorkSpace getWorkSpace() { return this.workSpace; }

        // replace by Location
        //public virtual void setXYPosition(int x, int y) { throw new Exception("Not Yet Implemented"); }

    }
}
