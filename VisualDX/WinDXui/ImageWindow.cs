using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace WinDX.UI
{
    public partial class ImageWindow : DXWindow
    {
        [StructLayout(LayoutKind.Sequential, Pack=1)]
        protected struct WindowsPixels
        {
            public int width;
            public int height;
            public IntPtr pixels;
        }

        [DllImport("user32.dll", SetLastError=true, CharSet=CharSet.Auto)]
        public static extern int RegisterWindowMessage(
        [MarshalAs(UnmanagedType.LPTStr)]
            String lpString);       // Point to a null-terminated string that
                                    // specifies the message to be registered.

        private Node node;
        protected System.Windows.Forms.PictureBox pictureBox;
        protected int DX_DISPLAYREADY = RegisterWindowMessage("DX_DISPLAY_READY");
        private IntPtr storedBmap = IntPtr.Zero;

        public ImageWindow(bool isAnchor, Network network)
            : base("imageWindow", isAnchor, DXApplication.theDXApplication.appAllowsImageMenus())
        {
            InitializeComponent();
            //this.Show();
        }

        public override bool IsAnchor { get { return false; } }
        protected override Control createWorkArea(Form parent)
        {
            return pictureBox;
        }

        protected override void createMenus(MenuStrip menu)
        {
            //base.createMenus(menu);
        }

        protected override void WndProc(ref Message m)
        {
            if (m.Msg == DX_DISPLAYREADY)
            {
                WindowsPixels wp = new WindowsPixels();
                IntPtr pPointerTowp = Marshal.AllocHGlobal(Marshal.SizeOf(wp));
                wp = (WindowsPixels)Marshal.PtrToStructure(m.WParam, typeof(WindowsPixels));
                this.DrawPicture(wp, true);
            }
            base.WndProc(ref m);
        }

        protected void DrawPicture(WindowsPixels wp, bool force)
        {
            if (storedBmap != null && (force || storedBmap != wp.pixels || 
                pictureBox.Width != wp.width || pictureBox.Height != wp.height))
            {
                storedBmap = wp.pixels;
                this.ClientSize = new Size(wp.width, wp.height);
                //pictureBox.Width = wp.width;
                //pictureBox.Height = wp.height;
                Image img;
                // bitmap is upside down--can it be fixed easily?
                img = new Bitmap(pictureBox.Width, pictureBox.Height,
                    pictureBox.Width * 3, System.Drawing.Imaging.PixelFormat.Format24bppRgb, storedBmap);
                img.RotateFlip(RotateFlipType.Rotate180FlipX);
                this.pictureBox.Image = img;
                pictureBox.Update();
                Show();
                BringToFront();
            }
        }


        // Not implemented below this line
        public void resetWindowTitle() { }
        public void changeDepth(int depth) { }
        public void setGeometry(int x, int y, int w, int h) { }
        public String getDisplayString()
        {
            bool frame_buffer;
            int x;
            int y;

            String display;
            String host;
            String unit;
            String str;

            //if (hasPendingWindowPlacement())
            //{
            //    throw new Exception("Not Yet Implemented");
            //}

            // Lots of code needs reworked here.

            DisplayNode imgn = (DisplayNode) node;

            host = DXApplication.theDXApplication.ServerName;

            display = host + ":0";

            str = String.Format("W,{0},##{1}", display, this.Handle.ToInt32().ToString());

            return str;
        }
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

        // Associates an Image or Display style node with an ImageWindow.
        // Returns TRUE if there wasn't another node already associated, FALSE
        // if there was.
        public bool associateNode(Node n) { node = n; return true; }
        public Node getAssociatedNode() { return this.node; }
        public bool IsAssociatedWithNode { get { return (node != null); } }

        public void newCamera(int image_width, int image_height) { }

        public void newCamera(double[,] box, double[,] aamat, double[] from, double[] to,
            double[] up, int image_width, int image_height, double width,
            bool perspective, double viewAngle) { }

        public bool setInteractionMode(DirectInteractionMode mode) { return true; }
        public DirectInteractionMode getInteractionMode() { return DirectInteractionMode.NONE; }

        public bool IsCameraInitialized { get { return true; } }

        public virtual void clearFrameBufferOverlay() { }
    }
}