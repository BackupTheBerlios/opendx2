using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    class FileSelectorNode : ValueNode
    {
        protected override InteractorInstance newInteractorInstance()
        {
            FileSelectorInstance ii;
            ii = new FileSelectorInstance(this);
            return ii;
        }

        protected override bool cfgPrintInstanceAuxInfo(System.IO.StreamWriter sw, InteractorInstance ii)
        {
            FileSelectorInstance fsi = (FileSelectorInstance)ii;
            String filter = fsi.FileFilter;

            if (!base.cfgPrintInstanceAuxInfo(sw, ii))
                return false;

            if (filter != null)
            {
                sw.WriteLine("// filter = {0}", filter); 
            }
            return true;
        }

        public override bool cfgParseComment(string comment, string file, int lineno)
        {
            if (!comment.StartsWith(" filter = "))
            {
                return base.cfgParseComment(comment, file, lineno);
            }

            int instance = getInstanceCount();
            FileSelectorInstance fsi = (FileSelectorInstance)getInstance(instance);

            if (fsi == null)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("'filter' comment out of order (file {0}, line {1})",
                    file, lineno);
            }
            else
            {
                fsi.FileFilter = comment.Substring(10);
            }
            return true;
        }

        public FileSelectorNode(NodeDefinition nd, Network net, int instnc)
            :
            base(nd, net, instnc)
        { }

        /// <summary>
        /// // We implement this for FileSelector node so that we can keep the
        /// 2nd output (the basename of the full file name) up to date.
        /// One should never use this method to set the 2nd output, only the 1st.
        /// Well, this is used when we parse a .net file.
        /// </summary>
        /// <param name="index"></param>
        /// <param name="value"></param>
        /// <param name="t"></param>
        /// <param name="send"></param>
        /// <returns></returns>
        public override DXTypeVals setOutputValue(int index, String value, DXTypeVals t, bool send)
        {
            Regex regex = new Regex(@"\\");
            String localValue = regex.Replace(value, "/");

            if (index == 2)
                return base.setOutputValue(2, localValue, t, send);

            DXTypeVals type = base.setOutputValue(1, localValue, t, false);
            if (type != DXTypeVals.UndefinedType)
            {
                String basename = getOutputValueString(1);
                basename = regex.Replace(basename, "/");

                if (!basename.Contains("/"))
                    type = base.setOutputValue(2, value, type, send);
                else
                {
                    // Not quite sure what the code is trying to do here.
                    throw new Exception("Not Yet Implemented");
                }
            }
            return type;
        }
    }
}
