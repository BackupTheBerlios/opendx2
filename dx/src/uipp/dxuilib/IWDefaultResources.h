/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#ifndef _IWDefaultResources_h
#define _IWDefaultResources_h

#if !defined(DX_NEW_KEYLAYOUT)

String ImageWindow::DefaultResources[] =
{
    ".title:                                       Image",
    ".iconName:                                    Image",
    ".width:                                        654",
    ".height:                                       525",
    "*allowResize:                                  True",

    // This blackens panelAccessDialog's scrolled window
    //"*XmDrawingArea.background:                     Black",

    "*fileMenu.labelString:                         File",
    "*fileMenu.mnemonic:                            F",
    "*imageOpenOption.labelString:                       Open...",
    "*imageOpenOption.mnemonic:                          O",
    "*imageSaveOption.labelString:                       Save Program",
    "*imageSaveOption.mnemonic:                          S",
    "*imageSaveOption.accelerator:                       Ctrl<Key>S",
    "*imageSaveOption.acceleratorText:                   Ctrl+S",
    "*imageSaveAsOption.labelString:                     Save Program As...",
    "*imageSaveAsOption.mnemonic:                        a",
    "*imageSettingsCascade.labelString:             Program Settings",
    "*imageSettingsCascade.mnemonic:                r",
    "*imageSaveCfgOption.labelString:               	Save As...",
    "*imageSaveCfgOption.mnemonic:               	S",
    "*imageOpenCfgOption.labelString:               	Load...",
    "*imageOpenCfgOption.mnemonic:               	L",


    "*fileMenuPulldown.tearOffModel:                 	 XmTEAR_OFF_DISABLED",
    "*windowsMenuPulldown.tearOffModel:                	 XmTEAR_OFF_DISABLED",

#if 0
    "*imageCloseOption.labelString:                      Close",
    "*imageCloseOption.mnemonic:                         C",
    "*imageCloseOption.accelerator:                      Ctrl<Key>Q",
    "*imageCloseOption.acceleratorText:                  Ctrl+Q",
#endif
    "*imageLoadMacroOption.labelString:                  Load Macro...",
    "*imageLoadMacroOption.mnemonic:                     L",
    "*imageLoadMDFOption.labelString:                    Load Module Description(s)...",
    "*imageLoadMDFOption.mnemonic:                       M",
    "*imageSaveImageOption.labelString:               Save Image...",
    "*imageSaveImageOption.mnemonic:                  v", 
    "*imagePrintImageOption.labelString:              Print Image...",
    "*imagePrintImageOption.mnemonic:                 P",

    "*windowsMenu.labelString:                      Windows",
    "*windowsMenu.mnemonic:                         W",
    "*imageOpenVisualProgramEditorOption.labelString:    Open Visual Program Editor",
    "*imageOpenVisualProgramEditorOption.mnemonic:       V",
    "*imageOpenAllControlPanelsOption.labelString:       Open All Control Panels",
    "*imageOpenAllControlPanelsOption.mnemonic:          A",
    "*imageOpenAllControlPanelsOption.accelerator:       Ctrl<Key>P",
    "*imageOpenAllControlPanelsOption.acceleratorText:   Ctrl+P",
    "*imageOpenControlPanelByNameOption.labelString:     Open Control Panel by Name",
    "*imageOpenControlPanelByNameOption.mnemonic:        N",
    "*imageOpenAllColormapEditorsOption.labelString:     Open All Colormap Editors",
    "*imageOpenAllColormapEditorsOption.mnemonic:        E",
    "*imageOpenAllColormapEditorsOption.accelerator:     Ctrl<Key>E",
    "*imageOpenAllColormapEditorsOption.acceleratorText: Ctrl+E",
    "*imageMessageWindowOption.labelString:     	    Open Message Window",
    "*imageMessageWindowOption.mnemonic:        	    M",

    "*optionsMenu.labelString:                      Options",
    "*optionsMenu.mnemonic:                         O",
    "*imageRenderingOptionsOption.labelString:           Rendering Options...",
    "*imageRenderingOptionsOption.mnemonic:              R",
    "*imageAutoAxesOption.labelString:                   AutoAxes...",
    "*imageAutoAxesOption.mnemonic:                      A",
    "*imageSetImageDepthOption.labelString:              Image Depth",
    "*imageSetImageDepthOption.mnemonic:                 D",
    "*imageThrottleOption.labelString:                   Throttle...",
    "*imageThrottleOption.mnemonic:                      T",
    "*imageViewControlOption.labelString:                View Control...",
    "*imageViewControlOption.mnemonic:                   V",
    "*imageViewControlOption.accelerator:                Ctrl<Key>V",
    "*imageViewControlOption.acceleratorText:            Ctrl+V",
    "*imageUndoOption.labelString:                       Undo",
    "*imageUndoOption.mnemonic:                          U",
    "*imageUndoOption.accelerator:                       Ctrl<Key>U",
    "*imageUndoOption.acceleratorText:                   Ctrl+U",
    "*imageRedoOption.labelString:                       Redo",
    "*imageRedoOption.mnemonic:                          e",
    "*imageRedoOption.accelerator:                       Ctrl<Key>D",
    "*imageRedoOption.acceleratorText:                   Ctrl+D",
    "*imageResetOption.labelString:                      Reset",
    "*imageResetOption.mnemonic:                         s",
    "*imageResetOption.accelerator:                      Ctrl<Key>F",
    "*imageResetOption.acceleratorText:                  Ctrl+F",
    "*imageChangeImageNameOption.labelString:            Change Image Name...",
    "*imageChangeImageNameOption.mnemonic:               N",
    "*imageBackgroundColorOption.labelString:            Set Background Color...",
    "*imageBackgroundColorOption.mnemonic:               B",
    "*imageDisplayRotationGlobeOption.labelString:       Display Rotation Globe",
    "*imageDisplayRotationGlobeOption.mnemonic:          G",
    "*imageSetPanelAccessOption.labelString:       	 Control Panel Access...",
    "*imageSetPanelAccessOption.mnemonic:          	 P",

    // FIXME: this should be in DXWindow.C
    "*imageOnVisualProgramOption.labelString:            Application Comment...",
    "*imageOnVisualProgramOption.mnemonic:               A",

    "*imageCanvas.background:			    Black",
    "*imageCanvas.boxGrey:			    #7e7e7e7e7e7e",
    "*imageCanvas.translateSpeed:            	    11",
    "*imageCanvas.rotateSpeed:               	    21",
    "*imageCanvas.unselectedInCursorColor:   	    Black",
    "*imageCanvas.unselectedOutCursorColor:  	    White",
    "*imageCanvas.selectedInCursorColor:     	    Black",
    "*imageCanvas.selectedOutCursorColor:    	    #0000ffff7e7e",
    "*imageCanvas.traversalOn:			    False",

    "*imageSetImageDepthOptionSubmenu*8.labelString: 8",
    "*imageSetImageDepthOptionSubmenu*12.labelString: 12",
    "*imageSetImageDepthOptionSubmenu*15.labelString: 15",
    "*imageSetImageDepthOptionSubmenu*16.labelString: 16",
    "*imageSetImageDepthOptionSubmenu*24.labelString: 24",
    "*imageSetImageDepthOptionSubmenu*32.labelString: 32",
    "*imageSetImageDepthOptionSubmenu*XmToggleButton.indicatorType:ONE_OF_MANY",

    NULL
};


#else /* defined(DX_NEW_KEYLAYOUT) */

String ImageWindow::DefaultResources[] =
{
    ".title:                                       	Image",
    ".iconName:                                    	Image",
    ".width:                                        	654",
    ".height:                                       	525",
    "*allowResize:                                  	True",

    // This blackens panelAccessDialog's scrolled window
    //"*XmDrawingArea.background:                     Black",

    "*fileMenu.labelString:                         	File",
    "*fileMenu.mnemonic:                            	F",
    "*imageOpenOption.labelString:                      Open...",
    "*imageOpenOption.mnemonic:                         O",
    "*imageOpenOption.accelerator:			Ctrl <Key>O",
    "*imageSaveOption.labelString:                      Save Program",
    "*imageSaveOption.mnemonic:                         S",
    "*imageSaveOption.accelerator:                      Ctrl<Key>S",
    "*imageSaveOption.acceleratorText:                  Ctrl+S",
    "*imageSaveAsOption.labelString:                    Save Program As...",
    "*imageSaveAsOption.mnemonic:                       A",
    "*imageSaveAsOption.accelerator:			Ctrl Shift <Key>S",
    "*imageSaveAsOption.acceleratorText:		Ctrl+Shift+S",
    "*imageSettingsCascade.labelString:             	Program Settings",
    "*imageSettingsCascade.mnemonic:                	r",

/* Are the following 4 used? */
    "*imageSaveCfgOption.labelString:               	Save As...",
    "*imageSaveCfgOption.mnemonic:               	S",
    "*imageOpenCfgOption.labelString:               	Load...",
    "*imageOpenCfgOption.mnemonic:               	L",

    "*fileMenuPulldown.tearOffModel:                 	XmTEAR_OFF_DISABLED",
    "*windowsMenuPulldown.tearOffModel:                	XmTEAR_OFF_DISABLED",

#if 0
    "*imageCloseOption.labelString:                     Close",
    "*imageCloseOption.mnemonic:                        C",
    "*imageCloseOption.accelerator:                     Ctrl<Key>Q",
    "*imageCloseOption.acceleratorText:                 Ctrl+Q",
#endif

    "*imageLoadMacroOption.labelString:                 Load Macro...",
    "*imageLoadMacroOption.mnemonic:                    L",
    "*imageLoadMDFOption.labelString:                   Load Module Description(s)...",
    "*imageLoadMDFOption.mnemonic:                      M",
    
    "*imageSaveImageOption.labelString:               	Save Image...",
    "*imageSaveImageOption.mnemonic:                  	v",
    "*imageSaveImageOption.accelerator:			Alt Ctrl <Key>S",
    "*imageSaveImageOption.acceleratorText:		Ctrl+Alt+S",
    "*imagePrintImageOption.labelString:              	Print Image...",
    "*imagePrintImageOption.mnemonic:                 	P",
    "*imagePrintImageOption.accelerator:		Ctrl <Key>P",
    "*imagePrintImageOption.acceleratorText:		Ctrl+P",

    "*windowsMenu.labelString:                      	Windows",
    "*windowsMenu.mnemonic:                         	W",
    "*imageOpenVisualProgramEditorOption.labelString:   Open Visual Program Editor",
    "*imageOpenVisualProgramEditorOption.mnemonic:      V",
    "*imageOpenAllControlPanelsOption.labelString:      Open All Control Panels",
    "*imageOpenAllControlPanelsOption.mnemonic:         A",
    "*imageOpenAllControlPanelsOption.accelerator:      Ctrl Shift <Key>P",
    "*imageOpenAllControlPanelsOption.acceleratorText:  Ctrl+Shift+P",
    "*imageOpenControlPanelByNameOption.labelString:    Open Control Panel by Name",
    "*imageOpenControlPanelByNameOption.mnemonic:       N",
    "*imageOpenAllColormapEditorsOption.labelString:    Open All Colormap Editors",
    "*imageOpenAllColormapEditorsOption.mnemonic:       C",
    "*imageOpenAllColormapEditorsOption.accelerator:    Ctrl Shift <Key>E",
    "*imageOpenAllColormapEditorsOption.acceleratorText: Ctrl+Shift+E",
    "*imageMessageWindowOption.labelString:     	Open Message Window",
    "*imageMessageWindowOption.mnemonic:        	E",
    "*imageMessageWindowOption.accelerator:		Ctrl <Key>M",
    "*imageMessageWindowOption.acceleratorText:		Ctrl+M",

    "*optionsMenu.labelString:                      	Options",
    "*optionsMenu.mnemonic:                         	O",

    "*imageRenderingOptionsOption.labelString:		Rendering Options...",
    "*imageRenderingOptionsOption.mnemonic:		R",
    "*imageAutoAxesOption.labelString:			AutoAxes...",
    "*imageAutoAxesOption.mnemonic:			A",
    "*imageSetImageDepthOption.labelString:		Image Depth",
    "*imageSetImageDepthOption.mnemonic:		D",
    "*imageThrottleOption.labelString:			Throttle...",
    "*imageThrottleOption.mnemonic:			T",
    "*imageViewControlOption.labelString:		View Control...",
    "*imageViewControlOption.mnemonic:			V",
    "*imageViewControlOption.accelerator:		Ctrl<Key>V",
    "*imageViewControlOption.acceleratorText:		Ctrl+V",
    "*imageUndoOption.labelString:			Undo",
    "*imageUndoOption.mnemonic:				U",
    "*imageUndoOption.accelerator:			Ctrl<Key>Z",
    "*imageUndoOption.acceleratorText:			Ctrl+Z",
    "*imageRedoOption.labelString:			Redo",
    "*imageRedoOption.mnemonic:				e",
    "*imageRedoOption.accelerator:			Ctrl <Key>Y",
    "*imageRedoOption.acceleratorText:			Ctrl+Y",
    "*imageResetOption.labelString:			Reset",
    "*imageResetOption.mnemonic:			s",
    "*imageResetOption.accelerator:			Ctrl<Key>F",
    "*imageResetOption.acceleratorText:			Ctrl+F",
    "*imageChangeImageNameOption.labelString:		Change Image Name...",
    "*imageChangeImageNameOption.mnemonic:		N",
    "*imageBackgroundColorOption.labelString:		Set Background Color...",
    "*imageBackgroundColorOption.mnemonic:		B",
    "*imageDisplayRotationGlobeOption.labelString:	Display Rotation Globe",
    "*imageDisplayRotationGlobeOption.mnemonic:		G",
    "*imageSetPanelAccessOption.labelString:		Control Panel Access...",
    "*imageSetPanelAccessOption.mnemonic:		P",

    // FIXME: this should be in DXWindow.C
    "*imageOnVisualProgramOption.labelString:           Application Comment...",
    "*imageOnVisualProgramOption.mnemonic:              A",

    "*imageCanvas.background:			    	Black",
    "*imageCanvas.boxGrey:			    	#7e7e7e7e7e7e",
    "*imageCanvas.translateSpeed:            	    	11",
    "*imageCanvas.rotateSpeed:               	    	21",
    "*imageCanvas.unselectedInCursorColor:   	    	Black",
    "*imageCanvas.unselectedOutCursorColor:  	    	White",
    "*imageCanvas.selectedInCursorColor:     	    	Black",
    "*imageCanvas.selectedOutCursorColor:    	    	#0000ffff7e7e",
    "*imageCanvas.traversalOn:			    	False",

    "*imageSetImageDepthOptionSubmenu*8.labelString: 	8",
    "*imageSetImageDepthOptionSubmenu*12.labelString: 	12",
    "*imageSetImageDepthOptionSubmenu*15.labelString: 	15",
    "*imageSetImageDepthOptionSubmenu*16.labelString: 	16",
    "*imageSetImageDepthOptionSubmenu*24.labelString: 	24",
    "*imageSetImageDepthOptionSubmenu*32.labelString: 	32",
    "*imageSetImageDepthOptionSubmenu*XmToggleButton.indicatorType:ONE_OF_MANY",

    NULL
};

#endif

#endif // _IWDefaultResources_h