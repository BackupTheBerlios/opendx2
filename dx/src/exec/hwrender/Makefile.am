## Process this file with automake to produce Makefile.in

SUBDIRS = opengl 

INCLUDES = -D$(ARCH) -I$(DXROOT)/include -I../libdx
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
dxincludedir = $(DXROOT)/include/dx
noinst_LIBRARIES = libHW.a

SUFFIXES = .m .y .c .s .h .o .a 

libHW_a_SOURCES = \
	hwClientMessage.c hwClipped.c hwCursorInteractor.c hwDraw.c \
	hwGroupInteractor.c hwInitScreen.c hwInteractor.c hwList.c \
	hwMatrix.c hwMaterials.c hwMemory.c hwNavigateInteractor.c \
	hwObject.c hwObjectHash.c hwPolyline.c hwPortHandle.c \
	hwQmesh.c hwRender.c hwRotateInteractor.c hwScreen.c \
	hwSort.c hwStereo.c hwStereoSys.c hwStereoCams.c  \
	hwTexture.c hwTmesh.c hwWindow.c hwZoomInteractor.c \
	hwGather.c hwPaint.c hwUpdateview.c hwUserInteractor.c \
	hwView.c hwXfield.c

