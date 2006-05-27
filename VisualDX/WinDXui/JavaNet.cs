using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WinDX.UI
{
    class JavaNet : Network
    {
        public JavaNet()
        {
            saveWebPageCmd = new NoUndoJavaNetCommand("saveWebPageCommand", commandScope,
                false, this, NoUndoJavaNetCommand.JavaNetCommandType.SaveWebPage);

            saveAppletCmd = new NoUndoJavaNetCommand("saveAppletCommand", commandScope,
                false, this, NoUndoJavaNetCommand.JavaNetCommandType.SaveApplet);

            saveBeanCmd = new NoUndoJavaNetCommand("saveBeanCommand", commandScope,
                true, this, NoUndoJavaNetCommand.JavaNetCommandType.SaveBean);
        }

        ~JavaNet()
        {
            if (html_f != null) html_f.Close();
            if (make_f != null) make_f.Close();
            if (applet_f != null) applet_f.Close();
        }

        protected static String[] UnsupportedTools;

        protected static List<Node> MakeUnsupportedToolList(JavaNet net)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected String base_name;
        protected String html_file;
        protected String make_file;
        protected String apple_file;
        protected String bean_file;

        protected FileStream html_f;
        protected FileStream make_f;
        protected FileStream applet_f;
        protected FileStream bean_f;

        protected bool setOutputName(String name)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected bool netToApplet()
        {
            throw new Exception("Not Yet Implemented");
        }

        protected Command saveWebPageCmd;
        protected Command saveAppletCmd;
        protected Command saveBeanCmd;

        protected virtual bool printMacroReferences(Stream s, bool inline_define,
            PacketIF.PacketIFCallback echoCallback, Object echoClientData)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected bool requires(String format)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool saveWebPage()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool saveApplet()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool saveBean()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual Command getSaveWebPageCommand()
        {
            return saveWebPageCmd;
        }
        public virtual Command getSaveAppletCommand()
        {
            return saveAppletCmd;
        }
        public virtual Command getSaveBeanCommand()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool IsJavified
        {
            get { throw new Exception("Not Yet Implemented"); }
        }

        public virtual bool saveNetwork(String name)
        {
            return saveNetwork(name, false);
        }
        public virtual bool saveNetwork(String name, bool force)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual void changeExistanceWork(Node n, bool adding)
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
