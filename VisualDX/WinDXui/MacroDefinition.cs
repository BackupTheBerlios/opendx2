using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class MacroDefinition : NodeDefinition
    {
        #region Private Instance Variables
        private SaveMacroCommand saveCmd;
        #endregion

        #region Protected Instance Variables
        #endregion

        #region Public Instance Variables
        public Network body;
        public String fileName;
        #endregion

        #region Public Methods
        public SaveMacroCommand getSaveCmd() { return saveCmd; }

        #endregion
    }
}
