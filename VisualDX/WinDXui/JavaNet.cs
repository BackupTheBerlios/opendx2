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
            // In C#, constructors work a little different than C++ with 
            // respect to virtual functions. C# will call a override function
            // if it exists in a subclass even though the contructor of the 
            // subclass may still not have been completed. C++ calls the base
            // classes virtual function instead. We ran into this problem 
            // here due to the fact that changeExistanceWork is called in
            // the Network() constructor, but the following 3 commands have
            // not been initialized yet. So we had to change the function a bit
            // and add the deactivates here in the constructor.

            saveWebPageCmd = new NoUndoJavaNetCommand("saveWebPageCommand", commandScope,
                false, this, NoUndoJavaNetCommand.JavaNetCommandType.SaveWebPage);

            saveAppletCmd = new NoUndoJavaNetCommand("saveAppletCommand", commandScope,
                false, this, NoUndoJavaNetCommand.JavaNetCommandType.SaveApplet);

            saveBeanCmd = new NoUndoJavaNetCommand("saveBeanCommand", commandScope,
                true, this, NoUndoJavaNetCommand.JavaNetCommandType.SaveBean);

            saveWebPageCmd.deactivate();
            saveAppletCmd.deactivate();
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

        public override Command getSaveWebPageCommand()
        {
            return saveWebPageCmd;
        }
        public override Command getSaveAppletCommand()
        {
            return saveAppletCmd;
        }
        public override Command getSaveBeanCommand()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool IsJavified
        {
            get { throw new Exception("Not Yet Implemented"); }
        }

        public override bool saveNetwork(String name)
        {
            return saveNetwork(name, false);
        }
        public override bool saveNetwork(String name, bool force)
        {
            throw new Exception("Not Yet Implemented");
        }
        public override void changeExistanceWork(Node n, bool adding)
        {
            base.changeExistanceWork(n, adding);
            if (saveWebPageCmd != null)
            {
                saveWebPageCmd.deactivate();
                saveAppletCmd.deactivate();
            }
        }
    }
}
