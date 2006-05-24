using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public class WorkSpace 
    {
        // No code yet.

        // I believe this is going to have to be a subclass of a ScrollableControl or Panel

        public virtual void resize() { throw new Exception("Not Yet Implemented"); }
        public virtual void installInfo(WorkSpaceInfo wsi)
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
