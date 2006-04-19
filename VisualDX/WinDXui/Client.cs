using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    /// <summary>
    /// Adds requirement by all Clients to handle notifications 
    /// from the server.
    /// </summary>
    public interface IClient
    {
        void notify(Symbol message);
        void notify(Symbol message, Object data);
        void notify(Symbol message, Object data, String msg);
    }
}
