## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include -I../base
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
dxbindir = $(DXROOT)/bin
dxlibdir = $(DXROOT)/lib
dxdatadir = $(DXROOT)/data
dxincludedir = $(DXROOT)/include/dx
noinst_LIBRARIES = libDXUI.a

BUILT_SOURCES = sequence.txt 		\
		gifmac.txt 		\
		vrmlmac.txt 		\
		dxmac.txt 		\
		imagemac.txt 		\
		netlex.h		\
		netyacc.c	

libDXUI_a_SOURCES = 			\
	delete.C			\
	new.C				\
	AccessNetworkPanelsCommand.C	\
	AnnotationGroupManager.C	\
	ApplicIF.C			\
	Arc.C				\
	ArcStandIn.C			\
	AttributeParameter.C		\
	AutoAxesDialog.C		\
	BuildIFDict.C			\
	CDBAllocatorDictionary.C	\
	ColormapAddCtlDialog.C		\
        ColormapEditCommand.C           \
        ColormapEditor.C                \
	ColormapFileCommand.C		\
	ColormapDefinition.C		\
	ColormapNBinsDialog.C		\
	ColormapNode.C			\
	ColormapWaveDialog.C		\
	CommentStyle.C			\
	CommentStyleUser.C		\
	ComputeCDB.C			\
	ComputeDefinition.C		\
	ComputeNode.C			\
	ConfigurationDialog.C		\
	ConfirmedExitCommand.C		\
	ConfirmedQuitCommand.C		\
	ControlPanel.C			\
	ControlPanelAccessDialog.C	\
	ControlPanelGroupDialog.C	\
	ControlPanelWorkSpace.C		\
	CreateMacroDialog.C		\
	Decorator.C			\
	DecoratorStyle.C		\
	DXApplication.C			\
	DXChild.C			\
	DXDragSource.C			\
	DXDropSite.C			\
	DXExecCtl.C			\
	DXLinkHandler.C			\
	DXLInputDefinition.C		\
	DXLInputNode.C			\
	DXLOutputNode.C			\
	DXLOutputDefinition.C		\
	DXPacketIF.C			\
	DXWindow.C			\
	DeleteNodeCommand.C		\
	DescrDialog.C			\
	DialInteractor.C		\
	DisconnectFromServerCommand.C	\
	DisplayDefinition.C		\
	DisplayNode.C			\
	DrivenDefinition.C		\
	DrivenNode.C			\
	DXAnchorWindow.C		\
	EchoNode.C			\
	EchoDefinition.C		\
	EditorToolSelector.C		\
	EditorWindow.C			\
	EditorWorkSpace.C		\
	ExecCommandDialog.C		\
	FileSelectorDefinition.C	\
	FileSelectorDialog.C		\
	FileSelectorInstance.C		\
	FileSelectorInteractor.C	\
	FileSelectorNode.C		\
	FindStack.C			\
	FindToolDialog.C		\
	GetSetConversionDialog.C	\
        GlobalLocalNode.C              	\
        GlobalLocalDefinition.C       	\
        GridDialog.C              	\
	GroupedObject.C			\
	GroupManager.C			\
	GroupStyle.C			\
	HelpOnNetworkDialog.C		\
	HelpOnPanelDialog.C		\
	ImageApproxCommand.C		\
	ImageCDB.C			\
	ImageConstraintCommand.C	\
	ImageDefinition.C		\
	ImageFileDialog.C		\
	ImageFormatDialog.C		\
	ImageFormat.C			\
	ImageFormatGIF.C		\
	ImageFormatMIF.C		\
	ImageFormatPSColor.C		\
	ImageFormatPSColorEnc.C		\
	ImageFormatPSGrey.C		\
	ImageFormatPSGreyEnc.C		\
	ImageFormatREX.C		\
	ImageFormatRGB.C		\
	ImageFormatTIF.C		\
	ImageFormatYUV.C		\
	ImageLookCommand.C		\
	ImageNode.C			\
	ImageNodeUtils.C		\
	ImagePerspectiveCommand.C	\
	ImageRedoCommand.C		\
	ImageResetCommand.C		\
	ImageSetModeCommand.C		\
	ImageSetViewCommand.C		\
	ImageFormatCommand.C		\
	ImageHardwareCommand.C		\
	ImageSoftwareCommand.C		\
	ImageUndoCommand.C		\
	ImageWindow.C			\
	InsertNetworkDialog.C		\
	Interactor.C			\
	InteractorDefinition.C		\
	InteractorInstance.C		\
	InteractorNode.C		\
	InteractorStyle.C		\
	InteractorStandIn.C		\
	ItalicLabeledStandIn.C		\
	JavaNet.C			\
	LabeledStandIn.C		\
	LabelDecorator.C		\
	LinkHandler.C			\
	LoadMDFDialog.C			\
	LoadMacroDialog.C		\
	MacroDefinition.C		\
	MacroNode.C			\
	MacroParameterDefinition.C	\
	MacroParameterNode.C		\
	ModuleMessagingNode.C		\
	MoveNodesDialog.C		\
	MsgWin.C			\
	MWClearCmd.C			\
	MWFileDialog.C			\
	NDAllocatorDictionary.C		\
	NewCommand.C			\
	Node.C				\
	NodeDefinition.C		\
	NodeList.C			\
	NondrivenInteractorNode.C	\
	Network.C			\
	NoUndoAnchorCommand.C		\
	NoUndoDXAppCommand.C		\
	NoUndoDXWindowCommand.C		\
	NoUndoJavaNetCommand.C		\
	NoUndoEditorCommand.C		\
	NoUndoImageCommand.C		\
	NoUndoMWCmd.C			\
	NoUndoNetworkCommand.C		\
	NoUndoPanelCommand.C		\
	ResetDefinition.C		\
	ResetNode.C			\
	OpenColormapDialog.C		\
	OpenCommand.C			\
	OpenCFGDialog.C			\
	OpenNetCommentDialog.C		\
	OpenNetworkDialog.C		\
	PacketIF.C			\
	PacketHandler.C			\
	PageGroupManager.C		\
	PageSelector.C			\
	PageTab.C			\
	PanelAccessManager.C		\
	PanelGroupManager.C		\
	Parameter.C			\
	ParameterCDB.C			\
	ParameterDefinition.C		\
	ParseMDF.C			\
	PickDefinition.C		\
	PickNode.C			\
	PixelImageFormat.C		\
	PostScriptImageFormat.C		\
	PrintDefinition.C		\
	PrintImageDialog.C		\
	PrintNode.C			\
	PrintProgramDialog.C		\
	PrintProgramFileDialog.C	\
	ProbeDefinition.C		\
	ProbeNode.C			\
	ProcessGroupCreateDialog.C	\
	ProcessGroupAssignDialog.C	\
	ProcessGroupOptionsDialog.C	\
	ProcessGroupManager.C		\
	ReceiverDefinition.C		\
	ReceiverNode.C			\
	RenderingOptionsDialog.C	\
	SaveAsCCodeDialog.C		\
	SaveAsDialog.C			\
	SaveCFGDialog.C			\
	SaveImageDialog.C		\
	SaveMacroCommand.C		\
	ScalarInstance.C		\
	ScalarInteractor.C		\
	ScalarDefinition.C		\
	ScalarNode.C			\
	ScalarListDefinition.C		\
	ScalarListInstance.C		\
	ScalarListInteractor.C		\
	ScalarListNode.C		\
	SelectionAttrDialog.C		\
	SelectionInstance.C		\
	SelectionNode.C			\
	SelectorDefinition.C		\
	SelectorInstance.C		\
	SelectorInteractor.C		\
	SelectorListDefinition.C	\
	SelectorListNode.C		\
	SelectorListInstance.C		\
	SelectorListInteractor.C	\
	SelectorListToggleInteractor.C	\
	SelectorRadioInteractor.C	\
	SelectorNode.C			\
	SIAllocatorDictionary.C		\
	SeparatorDecorator.C		\
        SequencerDefinition.C           \
        SequencerNode.C                 \
        SequencerWindow.C               \
	SetAnnotatorTextDialog.C	\
	SetAttrDialog.C			\
	SetBGColorDialog.C		\
	SetColormapNameDialog.C		\
	SetDecoratorTextDialog.C	\
	SetImageNameDialog.C		\
	SetInteractorNameDialog.C	\
	SetMacroNameDialog.C		\
	SetNetworkCommentDialog.C	\
	SetPageNameDialog.C		\
	SetPanelCommentDialog.C		\
	SetPanelNameDialog.C		\
	SetScalarAttrDialog.C		\
	SetSeparatorAttrDlg.C		\
	SetVectorAttrDialog.C		\
        ShadowedOutputNode.C            \
        SliderInteractor.C              \
	StandIn.C			\
	StartOptionsDialog.C		\
	StartServerDialog.C		\
	StepperInteractor.C		\
	StreaklineDefinition.C		\
	StreaklineNode.C		\
	Tab.C				\
	ThrottleDialog.C		\
	TickLabelList.C			\
	TickLabel.C			\
	ToolSelector.C			\
	ToolPanelCommand.C		\
	ToggleAttrDialog.C		\
	ToggleDefinition.C		\
	ToggleInteractor.C		\
	ToggleInstance.C		\
	ToggleNode.C			\
	ToggleToggleInteractor.C	\
	TransmitterDefinition.C		\
	TransmitterNode.C		\
	UniqueNameNode.C		\
	ValueDefinition.C		\
	ValueInstance.C			\
	ValueInteractor.C		\
	ValueNode.C			\
	ValueListDefinition.C		\
	ValueListInstance.C		\
	ValueListInteractor.C		\
	ValueListNode.C			\
	VectorDefinition.C		\
	VectorListDefinition.C		\
	ViewControlDialog.C		\
	ViewControlWhichCameraCommand.C	\
	VPEAnnotator.C			\
	VPEPostIt.C			\
	VPEPage.C			\
	VPERoot.C			\
	WorkSpaceComponent.C 		\
	\
	sequence.txt 			\
	gifmac.txt 			\
	vrmlmac.txt 			\
	dxmac.txt 			\
	imagemac.txt			\
	\
	netyacc.c

sequence.txt: sequence.net
	sed -e 's/"/\\"/g' sequence.net | \
		sed -e 's/$$/\\n"/g' | \
		sed -e 's/^/"/g' > sequence.txt

gifmac.txt:
	grep -h -v // ../java/dx/server/gifmac.net | \
		grep -v include | \
		grep -v "= NULL" | \
		sed -e 's/"/\\"/g' | \
		sed -e 's/\\\\"/\\\\\\"/g' | \
		sed -e 's/_out_/_o/g' | \
		sed -e 's/_in_/_i/g' | \
		sed -e 's/    //g' | \
		sed -e 's/^/"/' | \
		sed -e 's/$$/",/' > gifmac.txt

vrmlmac.txt:
	grep -h -v // ../java/dx/server/vrmlmac.net | \
		grep -v include | \
		grep -v "= NULL" | \
		sed -e 's/"/\\"/g' | \
		sed -e 's/\\\\"/\\\\\\"/g' | \
			sed -e 's/_out_/_o/g' | \
		sed -e 's/_in_/_i/g' | \
		sed -e 's/    //g' | \
		sed -e 's/^/"/' | \
		sed -e 's/$$/",/' > vrmlmac.txt

dxmac.txt:
	grep -h -v // ../java/dx/server/dxmac.net | \
		grep -v include | \
		grep -v "= NULL" | \
		sed -e 's/"/\\"/g' | \
		sed -e 's/\\\\"/\\\\\\"/g' | \
		sed -e 's/_out_/_o/g' | \
		sed -e 's/_in_/_i/g' | \
		sed -e 's/    //g' | \
		sed -e 's/^/"/' | \
		sed -e 's/$$/",/' > dxmac.txt
	
imagemac.txt: imagemac.net
	grep -h -v // imagemac.net | \
		grep -v include | \
		grep -v "= NULL" | \
		sed -e 's/"/\\"/g' | \
		sed -e 's/\\\\"/\\\\\\"/g' | \
		sed -e 's/Image_/I/g' | \
		sed -e 's/Receiver_/Rcv/g' | \
		sed -e 's/Input_/Inp/g' | \
		sed -e 's/Inquire_/Inq/g' | \
		sed -e 's/_out_/_o/g' | \
		sed -e 's/_in_/_i/g' | \
		sed -e 's/    //g' | \
		sed -e 's/^/"/' | \
		sed -e 's/$$/",/' > imagemac.txt

netlex.h: net.lex
	$(LEX) net.lex
	mv lex.yy.c netlex.h

netyacc.c: net.yacc netlex.c netyacc.awk
	$(YACC) net.yacc
	awk -f netyacc.awk y.tab.c > netyacc.c
	rm -f y.tab.c


