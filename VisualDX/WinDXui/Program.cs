using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace WinDX.UI
{
    static class MainProgram
    {
        /// <summary>
        /// Global instances that must be declared in order to run.
        /// </summary>
        private static BaseApplication globalApp;
        private static XmlPreferences globalPrefs;

        public static BaseApplication theApplication
        {
            get { return globalApp; }
        }

        public static XmlPreferences theXmlPreferences
        {
            get { return globalPrefs; }
        }
	
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.SetCompatibleTextRenderingDefault(false);
            Application.EnableVisualStyles();

            globalSymbols = new SymbolManager();
            globalApp = new DXApplication("dx");
            globalPrefs = new XmlPreferences();

            InfoDialog wd = new InfoDialog();
            wd.modalPost(theApplication.getAboutAppString());

            String test = "{\"{a, b}\"}";
            String resulting = Utils.FindDelimitedString(test, '{', '}', "\"");

            MessageBox.Show(resulting);
            //MessageBox.Show("see what happens");
            //Application.Run(new Form1());
        }
    }
}