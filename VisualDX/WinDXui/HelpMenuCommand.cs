using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
        class HelpMenuCommand : NoUndoCommand
        {
            protected HelpType commandType;

            public override bool doIt(CommandInterface ci)
            {
                bool ret = false;

                switch (commandType)
                {
                    case HelpType.GenericHelp:
                        Debug.Assert(ci != null);
                        ci.componentHelp();
                        ret = true;
                        break;
                    case HelpType.HelpTutorial:
                        ret = MainProgram.theApplication.startTutorial();
                        break;
                    case HelpType.AboutApp:
                        InfoDialog id = new InfoDialog();
                        id.post(MainProgram.theApplication.getAboutAppString());
                        ret = true;
                        break;
                    case HelpType.TechSupport:
                        String url = "file://" + MainProgram.theApplication.getUIRoot() +
                            "/html/pages/qikgu033.htm";

                        Process p = Process.Start("iexplore.exe", url);
                        if (p == null)
                        {
                            InfoDialog infoDialog = new InfoDialog();
                            infoDialog.post(MainProgram.theApplication.getTechSupportString());
                        }
                        ret = true;
                        break;
                    default:
                        Debug.Assert(false);
                        break;
                }
                return ret;
            }

            public enum HelpType { GenericHelp, HelpTutorial, TechSupport, AboutApp }

            public HelpMenuCommand(String name, CommandScope scope, bool active, HelpType comType)
                : base (name, scope, active)
            {
                commandType = comType;
            }
        }
}
