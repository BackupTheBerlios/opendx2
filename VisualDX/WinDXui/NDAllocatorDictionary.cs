using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public delegate NodeDefinition NDAllocator();

    class NDAllocatorDictionary : Dictionary<Symbol, NDAllocator>
    {
        public static Symbol GetNodeNameSymbol = Symbol.zero;
        public static Symbol SetNodeNameSymbol = Symbol.zero;

        private NDAllocator defaultAlloc;

        public NDAllocatorDictionary()
        {
            defaultAlloc = NodeDefinition.AllocateDefinition;
            this.Add("Display", DisplayDefinition.AllocateDefinition);
            this.Add("Image", ImageDefinition.AllocateDefinition);

            this.Add("Colormap", ColormapDefinition.AllocateDefinition);
            this.Add("Sequencer", SequencerDefinition.AllocateDefinition);

            this.Add("Compute", ComputeDefinition.AllocateDefinition);
            this.Add("Echo", EchoDefinition.AllocateDefinition);
            this.Add("Print", PrintDefinition.AllocateDefinition);

            this.Add("Probe", ProbeDefinition.AllocateDefinition);
            this.Add("ProbeList", ProbeDefinition.AllocateDefinition);
            this.Add("Pick", PickDefinition.AllocateDefinition);
            this.Add("Streakline", StreaklineDefinition.AllocateDefinition);

            // Special interactor definitions.
            this.Add("Selector", SelectorDefinition.AllocateDefinition);
            this.Add("Scalar", ScalarDefinition.AllocateDefinition);
            this.Add("ScalarList", ScalarListDefinition.AllocateDefinition);
            this.Add("Integer", ScalarDefinition.AllocateDefinition);
            this.Add("IntegerList", ScalarListDefinition.AllocateDefinition);
            this.Add("Vector", VectorDefinition.AllocateDefinition);
            this.Add("VectorList", VectorListDefinition.AllocateDefinition);
            this.Add("Value", ValueDefinition.AllocateDefinition);
            this.Add("ValueList", ValueListDefinition.AllocateDefinition);
            this.Add("String", ValueDefinition.AllocateDefinition);
            this.Add("StringList", ValueListDefinition.AllocateDefinition);
            this.Add("FileSelector", FileSelectorDefinition.AllocateDefinition);
            this.Add("Toggle", ToggleDefinition.AllocateDefinition);
            this.Add("Reset", ResetDefinition.AllocateDefinition);

            // Misc. supporting nodes.
            this.Add("Transmitter", TransmitterDefinition.AllocateDefinition);
            this.Add("Receiver", ReceiverDefinition.AllocateDefinition);
            this.Add("Input", MacroParameterDefinition.AllocateDefinition);
            this.Add("Output", MacroParameterDefinition.AllocateDefinition);
            //this.Add("DXLInput", DXLInputDefinition.AllocateDefinition);
            // ...

            // These were added to change Get into GetLocal and GetGlobal and
            // Set into SetGlobal and SetLocal
            //this.Add("Get", GlobalLocalDefinition.AllocateDefinition);
            // ...
            NDAllocatorDictionary.GetNodeNameSymbol = SymbolManager.theSymbolManager.registerSymbol("Get");
            NDAllocatorDictionary.SetNodeNameSymbol = SymbolManager.theSymbolManager.registerSymbol("Set");
        }

        public bool setDefaultAllocator(NDAllocator nda)
        {
            defaultAlloc = nda;
            return true;
        }

        public void Add(String name, NDAllocator nda)
        {
            SymbolManager sm = SymbolManager.theSymbolManager;
            int pos = 0;

            Symbol temp = new Symbol(name.GetHashCode());
            if (this.ContainsKey(temp))
                return;

            Symbol s = sm.registerSymbol(name);
            this.Add(s, nda);
        }

        public NodeDefinition allocate(String name)
        {
            NodeDefinition i = null;
            NDAllocator a = findAllocator(name);
            if (a != null) i = a();
            return i;
        }

        public NDAllocator findAllocator(String name)
        {
            SymbolManager sm = SymbolManager.theSymbolManager;
            try
            {
                Symbol s = sm.getSymbol(name);
                return findAllocator(s);
            }
            catch (KeyNotFoundException)
            {
                return defaultAlloc;
            }
        }
        public NDAllocator findAllocator(Symbol name)
        {
            NDAllocator ndout;
            if(this.TryGetValue(name, out ndout))
            {
                return ndout;
            }
            else
            {
                return defaultAlloc;
            }
        }

        public static NDAllocatorDictionary theNDAllocatorDictionary = null;

    }
}
