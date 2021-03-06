// Completed 4/24/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    //
    // dxui and dxexec have a dining philosophers problem.  Each writes (thru
    // a socket) to the other.  When the sockets' buffers are full, then the
    // next fwrite or fputs blocks and never returns.  So we wind up with both
    // processes having filled their buffers and neither able to read from the
    // other.
    //
    // PacketIF has been changed so that it always checks for socket input
    // before writing.  If input is available then PacketIF instances one
    // of the objects in this file.  Each is really just a struct that
    // holds the output until we find time to ship it to dxexec.  Many places
    // within dxuilib and dxui directories used to access the socket directly,
    // but now they always go thru PacketIF.
    //
    // These 3 classes will be instanced and stuck into a fifo queue in PacketIF.
    // They differ in the way they cause their buffered information to be sent
    // to dxexec.
    //

    //
    // Store raw data.  These bytes will be sent unformatted.
    //
    public class QueuedBytes
    {
        internal String data;

        public QueuedBytes(String data)
        {
            this.data = data;
        }

        public virtual void send(PacketIF pif)
        {
            pif._sendBytes(data);
        }
    }

    public class QueuedPacket : QueuedBytes
    {
        internal PacketIF.PacketType type;
        internal int packetId;

        public QueuedPacket(PacketIF.PacketType type, int packetId, String data) : base (data)
        {
            this.type = type;
            this.packetId = packetId;
        }

        public override void send(PacketIF pif)
        {
            pif._sendPacket(type, packetId, data);
        }
    }

    public class QueuedImmediate : QueuedBytes
    {
        public QueuedImmediate(String data) : base(data)
        { }
        public override void send(PacketIF pif)
        {
            pif._sendImmediate(data);
        }
    }
}
