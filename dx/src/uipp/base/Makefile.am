## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include -I../widgets
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
dxincludedir = $(DXROOT)/include/dx
noinst_LIBRARIES = libBASE.a

libBASE_a_SOURCES =  \
	Application.C			\
	ApplyFileDialog.C		\
	ButtonInterface.C		\
	CascadeMenu.C			\
	CloseWindowCommand.C		\
	CmdEntry.C			\
	Command.C			\
	CommandInterface.C		\
	ConfirmedCommand.C		\
	DeferrableAction.C		\
	Dialog.C			\
	DialogManager.C			\
	Dictionary.C			\
	DragSource.C			\
	DropSite.C			\
	DXTensor.C			\
	DXType.C			\
	DXValue.C			\
	DynamicResource.C		\
	ErrorDialogManager.C		\
	FileDialog.C			\
	HelpMenuCommand.C		\
	HelpOnContextCommand.C		\
	HelpWin.C			\
	IBMApplication.C		\
	IBMMainWindow.C			\
	InfoDialogManager.C		\
	License.C			\
	Link.C				\
	List.C				\
	ListEditor.C			\
	ListIterator.C			\
	MainWindow.C			\
	NoOpCommand.C			\
	NoUndoCommand.C			\
	NoUndoHelpCmd.C			\
	OptionalPreActionCommand.C	\
	PreActionCommand.C		\
	QuestionDialogManager.C		\
	QuitCommand.C			\
	RepeatingToggle.C		\
	SaveFileDialog.C		\
	Server.C			\
	SetNameDialog.C			\
	Stack.C				\
	Strings.C			\
	StringTable.C			\
	SymbolManager.C			\
	TemporaryLicense.C		\
	TextEditDialog.C		\
	TextFile.C			\
	TextFileFileDialog.C		\
	TextPopup.C			\
	TextSelector.C			\
	TimedDialog.C			\
	TimedMessage.C			\
	ToggleButtonInterface.C		\
	TransferStyle.C			\
	UIComponent.C			\
	UIComponentHelpCommand.C	\
	UndoCommand.C			\
	WarningDialogManager.C		\
	WizardDialog.C			\
	WorkSpace.C			\
	WorkSpaceGrid.C			\
	WorkSpaceInfo.C			\
	WorkSpaceRoot.C			\
	XHandler.C			\
	XmUtility.C			\
	lex.C				\
	util.C				\
	helpcallbacks.c			\
	help.c				\
	helplist.c			\
	helpstack.c			\
	history.c			\
	parse.c

