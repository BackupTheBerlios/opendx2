using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public abstract class ModuleMessagingNode : Node
    {
        /// <summary>
        /// Return TRUE/FALSE, indicating whether or not we support a message
        /// protocol between the executive module that runs for this node and the
        /// UI.  
        /// </summary>
        /// <returns></returns>
        protected virtual bool hasModuleMessageProtocol() { return true; }

        /// <summary>
        /// Return TRUE/FALSE, indicating whether or not we expect to receive
        /// a message from the UI when our module executes in the executive.
        /// </summary>
        /// <returns></returns>
        protected virtual bool expectingModuleMessage() { return true; }

        /// <summary>
        /// Called when a message is received from the executive after
        /// this->ExecModuleMessageHandler() is registered in
        /// this->Node::netPrintNode() to receive messages for this node.
        /// The format of the message coming back is defined by the derived class.
        /// </summary>
        /// <param name="id"></param>
        /// <param name="line"></param>
        protected abstract void execModuleMessageHandler(int id, String line);

        public ModuleMessagingNode(NodeDefinition nd, Network net, int instnc)
            :
            base(nd, net, instnc) { }

        public virtual bool isA(Symbol classname)
        {
            Symbol s = SymbolManager.theSymbolManager.registerSymbol("ModuleMessagingNode");
            if (s == classname)
                return true;
            else
                return base.isA(classname);
        }
    }
}
