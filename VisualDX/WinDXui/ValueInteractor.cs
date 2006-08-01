using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ValueInteractor : Interactor
    {
        public static new Interactor AllocateInteractor(String name, InteractorInstance ii)
        {
            throw new Exception("Not Yet Implemented");
        }

        public ValueInteractor(String name, InteractorInstance ii) :
            base(name, ii)
        {
        }

        public override void handleInteractivePartStateChange(InteractorInstance src_ii, bool major_change)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        public override void updateDisplayedInteractorValue()
        {
            throw new Exception("The method or operation is not implemented.");
        }


    }
}
