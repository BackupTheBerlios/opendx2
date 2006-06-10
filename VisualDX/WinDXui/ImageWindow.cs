using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    public partial class ImageWindow : DXWindow
    {
        public ImageWindow(bool isAnchor, Network network)
            : base("imageWindow", isAnchor, DXApplication.theDXApplication.appAllowsImageMenus())
        {
            InitializeComponent();
        }

        public override bool IsAnchor { get { return false; } }
        protected override Control createWorkArea(Form parent)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        // Not implemented below this line
        public void resetWindowTitle() { }
        public bool IsAssociatedWithNode { get { return false; } }
        public void changeDepth(int depth) { }
        public void setGeometry(int x, int y, int w, int h) { }
        public String getDisplayString() { return null; }
        public void deleteProbe(ProbeNode pn) { }
        public void addProbe(ProbeNode pn) { }
        public void changeProbe(ProbeNode pn) { }
        public void deletePick(PickNode pn) { }
        public void addPick(PickNode pn) { }
        public void changePick(PickNode pn) { }
        public void allowDirectInteraction(bool b) { }
        public void sensitizeThrottleDialog(bool flag) { }
        public void updateThrottleDialog(double val) { }
        public void sensitizePrintImageDialog(bool flag) { }
        public void sensitizeSaveImageDialog(bool flag) { }
        public void sensitizeBackgroundColorDialog(bool flag) { }
        public void updateBGColorDialog(String color) { }

        public void setAutoAxesDialogTicks(){}
        public void setAutoAxesDialogFrame(){}
        public void setAutoAxesDialogGrid(){}
        public void setAutoAxesDialogAdjust(){}
        public void setAutoAxesDialogLabels(){}
        public void setAutoAxesDialogLabelScale(){}
        public void setAutoAxesDialogFont(){}
        public void setAutoAxesDialogAnnotationColors(){}
        public void setAutoAxesDialogCorners(){}
        public void setAutoAxesDialogCursor(){}
        public void setAutoAxesDialogEnable(){}
        public void setAutoAxesDialogXTickLocs(){}
        public void setAutoAxesDialogYTickLocs(){}
        public void setAutoAxesDialogZTickLocs(){}
        public void setAutoAxesDialogXTickLabels(){}
        public void setAutoAxesDialogYTickLabels(){}
        public void setAutoAxesDialogZTickLabels(){}

        public void sensitizeViewControl(bool flag){}
        public void sensitizeChangeImageName(bool flag){}
        public void sensitizeRenderMode(bool flag){}
        public void sensitizeButtonUpApprox(bool flag){}
        public void sensitizeButtonDownApprox(bool flag){}
        public void sensitizeButtonUpDensity(bool flag){}
        public void sensitizeButtonDownDensity(bool flag){}

        // Update the autoaxes dialog with whatever the current
        // values in the ImageNode are data-driven
        public void updateAutoAxesDialog() { }
        public void updateRenderingOptionsDialog() { }

        // Update any displayed information from the new cfg state found in
        // the associated ImageNode. 
        //
        public void updateFromNewCfgState() { }


    }
}