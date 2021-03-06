using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Resources;
using System.Globalization;

namespace WinDX.UI
{
    static class MainProgram
    {
        /// <summary>
        /// Global instances that must be declared in order to run.
        /// </summary>
        private static BaseApplication globalApp;
        private static ResourceManager resources = new ResourceManager("WinDXui.StringsTable",
                System.Reflection.Assembly.GetExecutingAssembly());

        public static ResourceManager theResources
        {
            get { return resources; }
        }

        public static BaseApplication theApplication
        {
            get { return globalApp; }
        }
	
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.SetCompatibleTextRenderingDefault(false);
            Application.EnableVisualStyles();

            //String test = "{ 1 3, 4.5 \"fjd\", 7}";
            //List<String> resulting = Utils.StringTokenizer(test, " \t,{}", null);

            globalApp = new DXApplication("dx");
            String[] args = Environment.GetCommandLineArgs();
            globalApp.initialize(ref args);

            //InfoDialog wd = new InfoDialog();
            //wd.modalPost(theApplication.getAboutAppString());


            //MessageBox.Show(resulting);
            //MessageBox.Show("see what happens");
            //Application.Run(new Form1());

            //DXAnchorWindow daw = new DXAnchorWindow("test", true, true);
            System.Diagnostics.Debug.Assert(globalApp.getAnchorForm() != null);
            Application.Run(globalApp.getAnchorForm());
            //InfoDialog id = new InfoDialog();
            //id.modalPost(theApplication.getAboutAppString());

        }
    }
}