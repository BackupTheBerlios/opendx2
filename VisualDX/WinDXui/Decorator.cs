using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WinDX.UI
{
    public class Decorator : Control
    {
        public enum DecoratorStyle
        {
            Unknown,
            Default,
            Label,
            Separator,
            Marker
        };

        protected static int HiLites;

        protected virtual void createDecorator() { throw new Exception("Not Yet Implemented"); }
        protected DecoratorStyle style;
        protected String name;
        protected bool selected;

        protected Decorator(Form parent, String name, bool developerStyle)
        {
            throw new Exception("Not Yet Implemented");
        }

        // When decorators are in the vpe we always want them to get a new size when
        // something changes, but in panels, it seems better to maintain dimensions.
        // Inside panels, users try to line things up and make widths of several things
        // be equal, so I don't want to keep changing widths for them.  That's never
        // the case in the vpe.
        protected virtual bool resizeOnUpdate() { return false; }

        // this is for java support. It chops strings up into their individual
        // lines.  It's used in LabelDecorator and it's a copy of code from
        // InteractorInstance.  
        // FIXME: It needs to be pushed up the heirarchy.
        public static int CountLines(String line) { throw new Exception("Not Yet Implemented"); }
        public static String FetchLine(String line, int lineno) { throw new Exception("Not Yet Implemented"); }

        public virtual void openDefaultWindow() { throw new Exception("Not Yet Implemented"); }
        public virtual Dialog getDialog() { return null; }
        public virtual void setAppearance(bool developerStyle) { throw new Exception("Not Yet Implemented"); }
        public DecoratorStyle Style
        {
            get { return style; }
            set { style = value; }
        }
        public virtual bool HasDefaultWindow { get { return false; } }
        public virtual void uncreateDecorator() { throw new Exception("Not Yet Implemented"); }

        public virtual bool printComment(StreamWriter sw)
        {
            String s = "    //\n    // decorator " + name +
                String.Format("\tpos=({0},{1}) size={2}x{3} style({4})", this.Location.X, this.Location.Y,
                this.Size.Width, this.Size.Height);

            if (style == DecoratorStyle.Label || style == DecoratorStyle.Marker)
            {
                // Need to add the code from LabelDecorator
                throw new Exception("Not Yet Implemented");
            }
            else
                // Need to add the code from SeparatorDecorator
                throw new Exception("Not Yet Implemented");

            return true;
        }
        public virtual bool parseComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual Network getNetwork() { throw new Exception("Not Yet Implemented"); }
        public bool createNetFiles(Network net, StreamWriter sw, String line)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool printAsJava(StreamWriter sw, String line, int i) { return true; }
        public virtual bool printJavaResources(StreamWriter sw, String line, String line2)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool isA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
        }


        // Below this could be WorkSpaceComponent
        public bool IsSelected { get { return selected; } }
        public void setSelected(bool state) { throw new Exception("Not Yet Implemented"); }
    }
}
