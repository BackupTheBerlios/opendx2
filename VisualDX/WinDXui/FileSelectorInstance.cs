// Completed 7/27/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WinDX.UI
{
    class FileSelectorInstance : ValueInstance
    {

        private String fileFilter;

        public String FileFilter
        {
            get
            {
                return fileFilter;
            }
            set
            {
                fileFilter = value;
            }
        }

        public FileSelectorInstance(FileSelectorNode n) : 
            base(n)
        {
            fileFilter = null;
        }

        public bool printAsJava(StreamWriter sw)
        {
            int x, y, w, h;
            getXYPosition(out x, out y);
            getXYSize(out w, out h);

            ControlPanel cpan = getControlPanel();
            bool devstyle = cpan.IsDeveloperStyle;

            InteractorNode ino = (InteractorNode)node;
            String node_var_name = ino.getJavaVaraible();

            // Count up the lines in the label and split it up since java doesn't
            // know how to do this for us.
            String ilab = getInteractorLabel();
            int line_count = CountLines(ilab);

            String java_style = "Interactor";
            if (style.HasJavaStyle)
                java_style = style.getJavaStyle();
            String var_name = getJavaVariable();

            sw.WriteLine("        {0} {1} = new {2}();", java_style, var_name, java_style);
            sw.WriteLine("        {0}.addInteractor({1});", node_var_name, var_name);
            sw.WriteLine("        {0}.setUseQuotes(true);", var_name);
            sw.WriteLine("        {0}.setStyle({1});", var_name, devstyle ? 1 : 0);

            sw.WriteLine("        {0}.setLabelLines({1});", var_name, line_count);
            for (int i = 1; i <= line_count; i++)
            {
                String cp = FetchLine(ilab, i);
                sw.WriteLine("        {0}.setLabel(\"{1}\");", var_name, cp);
            }

            if (IsVerticalLayout)
                sw.WriteLine("        {0}.setVertical();", var_name);
            else
                sw.WriteLine("        {0}.setHorizontal();", var_name);

            if (style.HasJavaStyle)
                sw.WriteLine("        {0}.setBounds ({1}, {2},{3},{4},{5});",
                    node_var_name, var_name, x, y, w, h);
            else
                sw.WriteLine("        {0}.setBounds ({1}, {2},{3},{4},{5});",
                    node_var_name, var_name, x, y, w, 65);

            sw.WriteLine("        {0}.addInteractor({1});", cpan.getJavaVariableName(), var_name);

            return true;
        }

    }
}
