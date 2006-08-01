using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public delegate Decorator DecoratorAllocator(bool developerStyle);

    public class DecoratorStyle
    {
        private static Dictionary<String, Dictionary<String, DecoratorStyle>> theDecoratorStyleDictionary = null;

        public enum DecoratorType
        {
            Unknown = 0,
            Default = 1,
            Label = 2,
            Separator = 3,
            PostIt = 4
        };

        private Symbol name;
        private DecoratorAllocator allocateDecorator;
        private bool isDefault;
        private String key;
        private bool useInVPE;

        protected DecoratorType style;

        /// <summary>
        /// Added supported style/name/decoratorbuild group to the list
        /// of supported styles for the given named decorator (node name).
        /// </summary>
        /// <param name="decorator"></param>
        /// <param name="style"></param>
        /// <param name="stylename"></param>
        /// <param name="useInVPE"></param>
        /// <param name="ia"></param>
        /// <returns></returns>
        public static bool AddSupportedStyle(String decorator,
            DecoratorType style, String stylename, bool useInVPE, DecoratorAllocator ia)
        {
            throw new Exception("Not Yet Implemented");
        }

        private static void BuildDictionary()
        {
            theDecoratorStyleDictionary = new Dictionary<string, Dictionary<string, DecoratorStyle>>();
            // AddSupportedStyle("Label", DecoratorType.Label, "Label", false, LabelDecorator.AllocateDecorator);
            //throw new Exception("Not completed yet.");
        }

        // Get the DecoratorStyle entry associated with the give decorator
        // (node name) and the give style or style name.
        public static DecoratorStyle GetDecoratorStyle(String decorator, DecoratorType style)
        {
            throw new Exception("Not Yet Implemented");
        }
        public static DecoratorStyle GetDecoratorStyle(String decorator, String stylename)
        {
            throw new Exception("Not Yet Implemented");
        }
        public static void SetDefaultStyle(String decorator, DecoratorType style)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static Dictionary<String, DecoratorStyle> GetDecoratorStyleDictionary(String decorator)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static Dictionary<String, Dictionary<String, DecoratorStyle>> GetDecoratorStyleDictionary()
        {
            throw new Exception("Not Yet Implemented");
        }

        public DecoratorStyle(DecoratorType style, String n, bool useInVPE,
            DecoratorAllocator ia, String key)
        {
            throw new Exception("Not Yet Implemented");
        }

        public Decorator createDecorator(bool developerStyle)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool allowedInVPE { get { return useInVPE; } }

        public String KeyString { get { return key; } }

        public String NameString { get { return SymbolManager.theSymbolManager.getSymbolString(name); } }

        public DecoratorType StyleType { get { return style; } }


        public static void BuildtheDecoratorStyleDictionary() { BuildDictionary(); }

    }
}
