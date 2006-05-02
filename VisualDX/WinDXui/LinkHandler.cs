// Completed 4/24/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public class LinkHandler
    {
        private CmdEntry commandEntry;
        private PacketIF packetIF;

        public void sendPacket(PacketIF.PacketType packetType, int packetId)
        {
            sendPacket(packetType, packetId, null);
        }
        public void sendPacket(PacketIF.PacketType packetType, int packetId,
            String data)
        {
            packetIF.sendPacket(packetType, packetId, data);
        }

        public LinkHandler(PacketIF pif)
        {
            this.packetIF = pif;
            Dictionary<String, CmdEntry> dict = new Dictionary<String, CmdEntry>();
            commandEntry = new CmdEntry(dict, this);
        }

        public void addCommand(String command, CmdEntry.CmdEntryFunction func)
        {
            CmdEntry cmd;
            Dictionary<String, CmdEntry> dict = commandEntry.getDictionary();

            if (func == null)
            {
                Dictionary<String, CmdEntry> d = new Dictionary<String, CmdEntry>();
                cmd = new CmdEntry(d, this);
            }
            else
            {
                cmd = new CmdEntry(func, this);
            }
            dict.Add(command, cmd);
        }

        public void addCommand(String command, Command func)
        {
            CmdEntry cmd;
            Dictionary<String, CmdEntry> dict = this.commandEntry.getDictionary();

            if (func == null)
            {
                Dictionary<String, CmdEntry> d = new Dictionary<String, CmdEntry>();
                cmd = new CmdEntry(d, this);
            }
            else
            {
                cmd = new CmdEntry(func);
            }

            dict.Add(command, cmd);
        }

        public void addSubCommand(String command, String subcommand, CmdEntry.CmdEntryFunction func)
        {
            Dictionary<String, CmdEntry> dict = this.commandEntry.getDictionary();
            Dictionary<String, CmdEntry> subdict;
            CmdEntry oe = dict[command];
            CmdEntry ne;
            if (oe == null)
            {
                Console.WriteLine("adding subcommand ({0}) to nonexistent command ({1})",
                    subcommand, command);
            }
            subdict = oe.getDictionary();
            if (subdict == null)
            {
                Console.WriteLine("adding subcommand({0}) to bad command ({1})",
                    subcommand, command);
            }

            ne = new CmdEntry(func, this);
            subdict.Add(subcommand, ne);
        }

        public void addSubCommand(String command, String subcommand, Command func)
        {
            Dictionary<String, CmdEntry> dict = this.commandEntry.getDictionary();
            Dictionary<String, CmdEntry> subdict;
            CmdEntry oe = dict[command];
            CmdEntry ne;

            if (oe == null)
            {
                Console.WriteLine("adding subcommand ({0}) to nonexistent command ({1})",
		subcommand, command);
            }

            subdict = oe.getDictionary();
            if (subdict == null)
            {
                Console.WriteLine("adding subcommand ({0}) to bad command ({1})",
        subcommand, command);
            }

            ne = new CmdEntry(func);
            subdict.Add(subcommand, ne);
        }

        public bool executeLinkCommand(String commandString, int id)
        {
            return this.commandEntry.parse(commandString, id);
        }

        public PacketIF getPacketIF() { return this.packetIF; }

    }
}
