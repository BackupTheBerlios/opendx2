## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include -I../widgets
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
dxincludedir = $(DXROOT)/include/dx
dxdatadir = $(DXROOT)/data
noinst_LIBRARIES = libWIDGETS.a

libWIDGETS_a_SOURCES =  		\
	ColorBar.c			\
	ColorRGB.c			\
	ColorMapEditor.c		\
	ControlColor.c			\
	ControlField.c			\
	ControlLine.c			\
	ControlPoint.c			\
	ControlValue.c			\
	Dial.c				\
        Dither.c                        \
        Grid.c                          \
	FFloat.c			\
	FrameControl.c			\
	Image.c				\
	Number.c			\
	NumberOutput.c			\
        NumericList.c			\
	MultiText.c			\
	Picture.c			\
	Slider.c			\
	SlideBar.c			\
	Stepper.c			\
	findcolor.c			\
	gamma.c				\
	VCRControl.c			\
	WorkspaceW.c			\
	WorkspaceCallback.c		\
	Findroute.c			

dxdata_DATA =				\
	backward.bm			\
	forward.bm			\
	frame.bm			\
	loop.bm				\
	palim.bm			\
	pause.bm			\
	step.bm				\
	stepb.bm			\
	stepf.bm			\
	stop.bm
