using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Drawing;

namespace WinDX.UI
{
    public class WorkSpaceInfo
    {
        private const int MIN_WIDTH = 500;
        private const int MIN_HEIGHT = 400;
        private WorkSpaceGrid grid = new WorkSpaceGrid();
        private int width;
        private int height;
        private WorkSpace workSpace;
        private bool prevent_overlap;

        public int Width
        {
            get { return width; }
            set { width = value; }
        }
        public int Height
        {
            get { return height; }
            set { height = value; }
        }
        protected void setGridActive() { grid.Active = true; }
        protected void setGridActive(bool val) { grid.Active = val; }
        protected void setGridSpacing(int w, int h) { grid.setSpacing(w, h); }
        protected void setGridAlignment(Alignment x, Alignment y) { grid.setAlignment(x, y); }
        protected void setPreventOverlap() { prevent_overlap = true; }
        protected void setPreventOverlap(bool val) { prevent_overlap = val; }
        protected void associateWorkSpace(WorkSpace ws) { workSpace = ws; }
        protected void disassociateWorkSpace() { workSpace = null; }

        public void setDefaultConfiguration()
        {
            width = MIN_WIDTH;
            height = MIN_HEIGHT;
            prevent_overlap = false;
            grid.setDefaultConfiguration();

            if (workSpace != null)
            {
                workSpace.resize();
                workSpace.installInfo(this);
            }
        }

        public WorkSpaceInfo()
        {
            workSpace = null;
            setDefaultConfiguration();
        }

        public bool printComments(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool parseComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool isGridActive() { return grid.Active; }
        public void getGridSpacing(out int w, out int h) { grid.getSpacing(out w, out h); }
        public bool getPreventOverlap() { return prevent_overlap; }

        public Alignment getGridXAlignment() { return grid.getXAlignment(); }
        public Alignment getGridYAlignment() { return grid.getYAlignment(); }

        public void getXYSize(out int w, out int h)
        {
            throw new Exception("Not Yet Implemented");
        }

    }
}
