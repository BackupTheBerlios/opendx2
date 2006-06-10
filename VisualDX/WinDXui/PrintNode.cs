using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class PrintNode : ModuleMessagingNode
    {
        private const String message_token = "PRINT";

        // Called when a message is received from the executive after
        // this->ExecModuleMessageHandler() is registered in
        // this->Node::netPrintNode() to receive messages for this node.
        // The format of the message coming back is defined by the derived class.
        protected override void execModuleMessageHandler(int id, string line)
        {
            if (line.Contains(message_token))
            {
                MsgWin mw = DXApplication.theDXApplication.MessageWindow;
                if (DXApplication.theDXApplication.doesInfoOpenMessage(true))
                    mw.infoOpen();
            }
        }

        // Returns a string that is used to register
        // this->ExecModuleMessageHandler() when this->hasModuleMessageProtocol()
        // return TRUE.  This version, returns an id that is unique to this
        // instance of this node.
        protected override string getModuleMessageIdString()
        {
            if (moduleMessageId == null)
                moduleMessageId = message_token;
            return moduleMessageId;
        }

        public PrintNode(NodeDefinition nd, Network net, int instnc)
            :
            base(nd, net, instnc)
        { }

        public override bool isA(Symbol classname)
        {
            Symbol s = SymbolManager.theSymbolManager.registerSymbol("PrintNode");
            if (s == classname)
                return true;
            else
                return base.isA(classname);
        }
    }
}
