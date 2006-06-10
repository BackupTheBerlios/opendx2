using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;

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
            if (align == null || align.Length == 0)
            {
                y_alignment = Alignment.Center;
                x_alignment = Alignment.Center;
                return;
            }

            switch (align.ToCharArray()[0])
            {
                case 'U':
                    y_alignment = Alignment.Beginning;
                    break;
                case 'C':
                    y_alignment = Alignment.Center;
                    break;
                case 'L':
                    y_alignment = Alignment.End;
                    break;
                case 'N':
                    y_alignment = Alignment.None;
                    break;
                default:
                    y_alignment = Alignment.Center;
                    x_alignment = Alignment.Center;
                    return;
                    break;
            }

            if (align.Length == 1)
            {
                x_alignment = Alignment.Center;
                return;
            }

            switch (align.ToCharArray()[1])
            {
                case 'L':
                    x_alignment = Alignment.Beginning;
                    break;
                case 'C':
                    x_alignment = Alignment.Center;
                    break;
                case 'R':
                    x_alignment = Alignment.End;
                    break;
                case 'N':
                    x_alignment = Alignment.None;
                    break;
            }
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
            if (!comment.StartsWith(" layout"))
                return false;

            Regex regex = new Regex(@" layout: snap = (\d+), width = (\d+), height = (\d+), align = (.*)");
            Match m = regex.Match(comment);
            if (!m.Success)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Bad 'layout' panel comment (file {0}, line {1})", filename, lineno);
                return true;
            }
            int snap = Int32.Parse(m.Groups[1].ToString());
            int width = Int32.Parse(m.Groups[2].ToString());
            int height = Int32.Parse(m.Groups[3].ToString());
            String align = m.Groups[4].ToString();

            Active = (snap > 0);
            setSpacing(width, height);
            parseAlignment(align);

            return true;
        }

        public Alignment getXAlignment() { return x_alignment; }
        public Alignment getYAlignment() { return y_alignment; }
    }
}
