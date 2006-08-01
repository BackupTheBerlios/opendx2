using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class FileSelectorInteractor : ValueInteractor
    {
        public static Interactor AllocateInteractor(String name, InteractorInstance ii)
        {
            FileSelectorInteractor i = new FileSelectorInteractor(name, ii);
            return i;
        }

        public FileSelectorInteractor(String name, InteractorInstance ii)
            :
            base(name, ii) { }
    }
}
