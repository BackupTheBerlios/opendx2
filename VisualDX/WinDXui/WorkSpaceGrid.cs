using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WinDX.UI
{
    class WorkSpaceGrid
    {
        private bool active;
        private short width;
        private short height;
        private Alignment x_alignment;
        private Alignment y_alignment;

        public void setSpacing(int w, int h) { width = (short) w; height = (short) h; }
        public void setAlignment(Alignment x, Alignment y)
        { x_alignment = x; y_alignment = y; }
        protected void parseAlignment(String align)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected String alignmentString()
        {
            throw new Exception("Not Yet Implemented");
        }
        // Use the default grid configuration.
        public void setDefaultConfiguration()
        {
            active = false;
            width = height = 50;
            x_alignment = y_alignment = Alignment.None;
        }

        public WorkSpaceGrid()
        {
            setDefaultConfiguration();
        }

        public bool Active
        {
            get { return active; }
            set { active = value; }
        }

        public void getSpacing(out int w, out int h) { w = width; h = height; }
        public String getCommentString()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool printComments(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool parseComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        public Alignment getXAlignment() { return x_alignment; }
        public Alignment getYAlignment() { return y_alignment; }
    }
}
