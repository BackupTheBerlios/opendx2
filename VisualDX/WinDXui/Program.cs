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
        private static SymbolManager globalSymbols;

        public static BaseApplication theApplication
        {
            get { return globalApp; }
        }

        public static XmlPreferences theXmlPreferences
        {
            get { return globalPrefs; }
        }

        public static SymbolManager theSymbolManager
        {
            get { return globalSymbols; }
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

            String[] quotes = { "\"", "[]" };
            List<String> test = Utils.StringTokenizer("[[test]], \"me\", 1.345", " ,", quotes );
            String resulting = "";
            foreach (String t in test)
            {
                resulting += t + ", ";
            }
            MessageBox.Show(resulting);
            //MessageBox.Show("see what happens");
            //Application.Run(new Form1());
        }
    }
}