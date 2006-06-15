// Completed 5/1/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class InteractorStyle
    {
        public enum Style
        {
            UnknownStyle = 0,
            DefaultStyle = 1,
            StepperStyle = 2,
            SliderStyle = 3,
            DialStyle = 4,
            VectorStyle = 5,
            TextStyle = 6,	// These three should have the same value
            ValueStyle = 6,    // These three should have the same value
            StringStyle = 6,    // These three should have the same value
            SelectorOptionMenuStyle = 7,

            IntegerListEditorStyle = 8,
            ScalarListEditorStyle = 9,
            VectorListEditorStyle = 10,
            TextListEditorStyle = 11, // These three should have the same value
            ValueListEditorStyle = 11, // These three should have the same value
            StringListEditorStyle = 11, // These three should have the same value

            FileSelectorStyle = 12,

            SelectorToggleStyle = 13,	// Toggle button for Selector
            SelectorRadioStyle = 15,	// Radio buttons 

            ToggleToggleStyle = 16,		// Toggle button
            SelectorListToggleStyle = 17,	// Toggle button

            SelectorPulldownStyle = 18,	//  scrollable menu
            SelectorListStyle = 19,		// scrolled list 

            UserStyle = 1000 
        };

        public delegate Interactor InteractorAllocator(String name, InteractorInstance ii);

        public static Dictionary<String, Dictionary<String, InteractorStyle>> 
            theInteractorStyleDictionary = null;

        public static void BuildtheInteractorStyleDictionary()
        {
            theInteractorStyleDictionary = new Dictionary<string, Dictionary<string, InteractorStyle>>();
            AddSupportedStyle("Integer", Style.StepperStyle, "Stepper", "StepperInteractor",
                StepperInteractor.AllocateInteractor);

            AddSupportedStyle("Integer", Style.DialStyle, "Dial",
                             DialInteractor.AllocateInteractor);
            AddSupportedStyle("Integer", Style.SliderStyle, "Slider",
                                         SliderInteractor.AllocateInteractor);
            AddSupportedStyle("Integer", Style.TextStyle, "Text", "ScalarInteractor",
                                         ValueInteractor.AllocateInteractor);

            AddSupportedStyle("Scalar", Style.StepperStyle, "Stepper",
                            "StepperInteractor",
                         StepperInteractor.AllocateInteractor);
            AddSupportedStyle("Scalar", Style.DialStyle, "Dial",
                                         DialInteractor.AllocateInteractor);
            AddSupportedStyle("Scalar", Style.SliderStyle, "Slider",
                                         SliderInteractor.AllocateInteractor);
            AddSupportedStyle("Scalar", Style.TextStyle, "Text", "ScalarInteractor",
                                         ValueInteractor.AllocateInteractor);

            AddSupportedStyle("Vector", Style.StepperStyle, "Stepper",
                         "StepperInteractor",
                         StepperInteractor.AllocateInteractor);
            AddSupportedStyle("Vector", Style.TextStyle, "Text", "Interactor",
                         ValueInteractor.AllocateInteractor);


            //
            // Supported styles for list interactors.
            //
            AddSupportedStyle("ScalarList",
                     Style.ScalarListEditorStyle, "List Editor",
                     ScalarListInteractor.AllocateInteractor);
            AddSupportedStyle("ScalarList",
                     Style.TextStyle, "Text", "Interactor",
                     ValueInteractor.AllocateInteractor);

            AddSupportedStyle("IntegerList",
                     Style.IntegerListEditorStyle, "List Editor",
                     ScalarListInteractor.AllocateInteractor);
            AddSupportedStyle("IntegerList",
                     Style.TextStyle, "Text", "Interactor",
                     ValueInteractor.AllocateInteractor);

            AddSupportedStyle("VectorList",
                     Style.VectorListEditorStyle, "List Editor",
                     ScalarListInteractor.AllocateInteractor);
            AddSupportedStyle("VectorList",
                     Style.TextStyle, "Text", "Interactor",
                     ValueInteractor.AllocateInteractor);

            AddSupportedStyle("Value",
                     Style.TextStyle, "Text", "Interactor",
                     ValueInteractor.AllocateInteractor);
            AddSupportedStyle("String",
                     Style.TextStyle, "Text", "StringInteractor",
                     ValueInteractor.AllocateInteractor);

            AddSupportedStyle("ValueList",
                     Style.TextListEditorStyle, "List Editor",
                     ValueListInteractor.AllocateInteractor);
            AddSupportedStyle("ValueList",
                     Style.TextStyle, "Text", "Interactor",
                     ValueInteractor.AllocateInteractor);

            AddSupportedStyle("StringList",
                     Style.TextListEditorStyle, "List Editor",
                     ValueListInteractor.AllocateInteractor);
            AddSupportedStyle("StringList",
                     Style.TextStyle, "Text", "Interactor",
                     ValueInteractor.AllocateInteractor);


            //
            // Supported styles for Selector interactors 
            //
            AddSupportedStyle("Selector",
                     Style.SelectorOptionMenuStyle, "Option Menu", "Selector",
                     SelectorInteractor.AllocateInteractor);
            AddSupportedStyle("Selector",
                     Style.SelectorRadioStyle, "Radio Button", "RadioGroup",
                     SelectorRadioInteractor.AllocateInteractor);
            // This interactor solves a problem that users have with data-driven
            // Option Menu selectors.  That is that the menu can become too big
            // very easily.  Nonetheless, I'm not adding support for this new
            // interactor because this problem can be solved by switching from
            // Option Menu to Scrolled List. I'm just not happy with having so
            // much overlap in functionality. 
            //   AddSupportedStyle("Selector", 
            //			Style.SelectorPulldownStyle,  "Pulldown Menu",
            //			SelectorPulldownInteractor.AllocateInteractor);
            AddSupportedStyle("Selector",
                     Style.SelectorListStyle, "Scrolled List", "ListSelector",
                     SelectorListInteractor.AllocateInteractor);

            //
            // Supported styles for other interactors 
            //
            AddSupportedStyle("FileSelector", Style.FileSelectorStyle,
                     "FileSelector",
                     FileSelectorInteractor.AllocateInteractor);
            AddSupportedStyle("Toggle", Style.ToggleToggleStyle,
                     "Toggle", "Toggle",
                     ToggleToggleInteractor.AllocateInteractor);
            AddSupportedStyle("Reset", Style.ToggleToggleStyle,
                     "Toggle", "Toggle",
                     ToggleToggleInteractor.AllocateInteractor);
            AddSupportedStyle("SelectorList", Style.SelectorListToggleStyle,
                     "Button List", "ToggleGroup",
                     SelectorListToggleInteractor.AllocateInteractor);
            AddSupportedStyle("SelectorList", Style.SelectorListStyle,
                     "Scrolled List", "ListSelector",
                     SelectorListInteractor.AllocateInteractor);

            //
            // AT LAST, set the Default Style for each interactor.
            //
            SetDefaultStyle("Integer", Style.StepperStyle);
            SetDefaultStyle("Scalar", Style.StepperStyle);
            SetDefaultStyle("Vector", Style.StepperStyle);
            SetDefaultStyle("IntegerList", Style.TextListEditorStyle);
            SetDefaultStyle("ScalarList", Style.TextListEditorStyle);
            SetDefaultStyle("VectorList", Style.TextListEditorStyle);
            SetDefaultStyle("ValueList", Style.TextListEditorStyle);
            SetDefaultStyle("StringList", Style.TextListEditorStyle);
            SetDefaultStyle("Selector", Style.SelectorOptionMenuStyle);
            SetDefaultStyle("FileSelector", Style.FileSelectorStyle);

        }

        private Style style;
        private Symbol name;
        private String interactorName;
        private InteractorAllocator allocateInteractor;
        private bool isDefault;
        private String javaStyle;

        //
        // Added supported style/name/interactorbuild group to the list
        // of supported styles for the given named interactor (node name).
        //
        public static bool AddSupportedStyle(String interactor, Style style,
            String stylename, InteractorAllocator ia)
        {
            return AddSupportedStyle(interactor, style, stylename, null, ia);
        }
        public static bool AddSupportedStyle(String interactor, Style style,
            String stylename, String javaStyle, InteractorAllocator ia)
        {
            Dictionary<String, InteractorStyle> styledict;
            styledict = GetInteractorStyleDictionary(interactor);
            if (styledict == null)
                styledict = new Dictionary<string, InteractorStyle>();
            theInteractorStyleDictionary[interactor] = styledict;

            InteractorStyle istyle = new InteractorStyle(style, stylename, javaStyle, ia);
            styledict.Add(stylename, istyle);
            return true;
        }

        //
        // Get the InteractorStyle entry associated with the give interactor
        // (node name) and the give style or style name.
        //
        public static InteractorStyle GetInteractorStyle(String interactor,
            Style style)
        {
            Dictionary<String, InteractorStyle> styledict;
            InteractorStyle firstIs = null;

            styledict = GetInteractorStyleDictionary(interactor);
            if (styledict == null)
                return null;

            foreach (InteractorStyle istyle in styledict.Values)
            {
                if (firstIs == null)
                    firstIs = istyle;
                if ((istyle.style == style) ||
                    (style == Style.DefaultStyle && istyle.isDefault))
                    return istyle;
            }

            if (style == Style.DefaultStyle)
                return firstIs;

            return null;
        }

        public static InteractorStyle GetInteractorStyle(String interactor,
            String stylename)
        {
            Dictionary<String, InteractorStyle> styledict;
            styledict = GetInteractorStyleDictionary(interactor);
            if (styledict == null)
                return null;

            return styledict[stylename];
        }
        public static void SetDefaultStyle(String interactor,
            Style style)
        {
            Dictionary<String, InteractorStyle> styledict;

            styledict = GetInteractorStyleDictionary(interactor);
            if(styledict == null)
                return;

            foreach (InteractorStyle istyle in styledict.Values)
            {
                istyle.isDefault = (istyle.style == style);
            }
        }

        //
        // Return the list of InteractorStyles for the give interactor (node name).
        //
        public static Dictionary<String, InteractorStyle>
            GetInteractorStyleDictionary(String interactor)
        {
            Debug.Assert(theInteractorStyleDictionary != null);
            Dictionary<String, InteractorStyle> intstyle;
            if(theInteractorStyleDictionary.TryGetValue(interactor, out intstyle))
            {
                return intstyle;
            }
            else
            {
                return null;
            }
        }

        public InteractorStyle(Style s, String n, String javaStyle, InteractorAllocator ia)
        {
            style = s;
            name = SymbolManager.theSymbolManager.registerSymbol(n);
            allocateInteractor = ia;
            isDefault = false;
            interactorName = null;
            this.javaStyle = javaStyle;
        }

        public Interactor createInteractor(InteractorInstance ii)
        {
            Debug.Assert(allocateInteractor != null);
            if (interactorName != null)
            {
                String styleName = SymbolManager.theSymbolManager.getSymbolString(name);
                styleName = styleName.Trim();
                styleName = styleName.ToLower();
                interactorName = styleName + "Interactor";
            }
            Interactor interactor = allocateInteractor(interactorName, ii);
            interactor.initialize();
            interactor.createInteractor();
            return interactor;
        }

        public String getJavaStyle() { return javaStyle; }

        public bool HasJavaStyle
        {
            get { return (this.javaStyle != null); }
        }
        public String getNameString()
        {
            return SymbolManager.theSymbolManager.getSymbolString(name);
        }
        public Style getStyle() { return style; }

    }
}
