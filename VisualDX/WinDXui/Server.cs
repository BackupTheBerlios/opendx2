using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    /// <summary>
    /// The server contains a list of all the clients. Each client should
    /// register with the current running server so any messages sent
    /// by the server can propogate to the clients.
    /// 
    /// This will be added as a member to other classes instead of subclassed
    /// as it is in IBM's C++ version.
    /// </summary>
    public sealed class Server
    {
        List<IClient> clientList;

        public Server()
        {
            clientList = new List<IClient>();
        }

        /// <summary>
        /// Sends the notification message to all the registered clients.
        /// </summary>
        /// <param name="message"></param>
        public void notifyClients(Symbol message)
        {
            foreach (IClient c in clientList)
            {
                c.notify(message);
            }
        }
        public void notifyClients(Symbol message, Object msgdata)
        {
            foreach (IClient c in clientList)
            {
                c.notify(message, msgdata);
            }
        }
        public void notifyClients(Symbol message, Object msgdata, String msg)
        {
            foreach (IClient c in clientList)
            {
                c.notify(message, msgdata, msg);
            }
        }

        public bool registerClient(IClient client)
        {
            if (clientList.Contains(client))
                return false;

            clientList.Add(client);
            return true;
        }

        public bool unregisterClient(IClient client)
        {
            return clientList.Remove(client);
        }
    }
}
