## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include -I../base
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
dxbindir = $(DXROOT)/bin
dxdatadir = $(DXROOT)/data
dxincludedir = $(DXROOT)/include/dx
dxbin_PROGRAMS = gar

gar_SOURCES =  				\
	Browser.C			\
	BrowserCommand.C		\
	BuildTCDict.C			\
	CDFChoice.C			\
	CommandTextPopup.C		\
	CommentDialog.C			\
	ConfirmedOpenCommand.C		\
	ConfirmedQCommand.C		\
	DataFileDialog.C		\
	DXChoice.C			\
	Field.C				\
	FileContents.C			\
	FilenameSelectDialog.C		\
	GARApplication.C		\
	GARChooserWindow.C		\
	GARCommand.C			\
	GARMainWindow.C			\
	GARNewCommand.C			\
	GridChoice.C			\
	HDFChoice.C			\
	ImageChoice.C			\
	ImportableChoice.C		\
	MsgDialog.C			\
	NetCDFChoice.C			\
	NonimportableChoice.C		\
	NoUndoChoiceCommand.C		\
	NoUndoChooserCommand.C		\
	NoUndoGARAppCommand.C		\
	OpenFileDialog.C		\
	QuitCommand.C			\
	RecordSeparator.C		\
	SADialog.C			\
	SearchDialog.C			\
	SpreadSheetChoice.C		\
	TypeChoice.C			\
	\
	Main.C

gar_LDADD = 				\
	../base/libBASE.a  		\
	../widgets/libWIDGETS.a  	\
	../dxl/libDXL.a		  	\
	-L/usr/X11R6/lib 		\
	-L/usr/local/lib 		\
	-L$(DXROOT)/lib_$(ARCH) 	\
	-lcrypt -lg++ -lXm -lXmu -lXt -lX11 -lXext

dxdata_DATA = 				\
	col_insens.bm			\
	col_sens.bm			\
	grid1.bm			\
	grid2.bm			\
	grid3.bm			\
	grid4.bm			\
	row_insens.bm			\
	row_sens.bm			\
	series1.bm			\
	series1_insens.bm		\
	series2.bm			\
	series2_insens.bm		\
	vector1.bm			\
	vector1_insens.bm		\
	vector2.bm			\
	vector2_insens.bm
