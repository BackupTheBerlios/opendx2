# Microsoft Developer Studio Project File - Name="dxexec" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=dxexec - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dxexec.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dxexec.mak" CFG="dxexec - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dxexec - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "dxexec - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dxexec - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".." /I "../../include" /I "../../../include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "DLL_NETCDF" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib opengl32.lib glu32.lib netcdf.lib dllcdf.lib hd414m.lib hm414m.lib CORE_RL_magick_.lib binmode.obj /nologo /subsystem:console /machine:I386 /libpath:"../../../lib"

!ELSEIF  "$(CFG)" == "dxexec - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /I "../../include" /I "../../../include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "DLL_NETCDF" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib opengl32.lib glu32.lib netcdf.lib dllcdf.lib hd414m.lib hm414m.lib CORE_RL_magick_.lib binmode.obj /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"../Debug/libs_intelnt" /libpath:"../../../lib"

!ENDIF 

# Begin Target

# Name "dxexec - Win32 Release"
# Name "dxexec - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_autocolor.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_autogray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_cat_util.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_color.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_colormap.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compcmplx.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compexec.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compinput.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_complex.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compoper.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compoper1.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compoper2.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compparse.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compputils.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_connectgrids.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_connectvor.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_construct.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_divcurl.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_getfield.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_gif.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_glyph.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_gradient.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_grid.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_helper_jea.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_im_image.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_irregstream.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_isosurface.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_maptoplane.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_newtri.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_normals.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_partnbrs.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_plot.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_post.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_postscript.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_refine.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_refineirr.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_refinereg.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_refinetopo.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_regstream.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_rgb_image.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_rubbersheet.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_rw_image.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_sample.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_simplesurf.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_tiff.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_tube.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_unpart.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\ambientlight.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\append.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\arrange.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\array.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\arrayClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\attribute.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\autoaxes.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\autocolor.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\autoglyph.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\autogray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\autoregrid.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\axes.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\background.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\band.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\basic.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\binSort.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\bounds.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\box.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\bspline.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\buffer.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\cache.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\cachegraph.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\cachescene.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\callm_winit.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\camera.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cameraClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\caption.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\categorize.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\catstats.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\ccm.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\changemember.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\changetype.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\client.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\clipbox.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\clipped.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\clippedClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\clipplane.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\collect.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\collectmulti.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\collectnamed.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\collectser.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\color.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\colorbar.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\colormap.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\command.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\component.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\composite.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\compute.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\compute2.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\connect.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\construct.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\context.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\convert.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\copy.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\crc.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cstarray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cubesII.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cubesIIClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cubesRR.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cubesRRClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\d.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\ddx.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\definter.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\describe.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\direction.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\display.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\displayfb.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\displayutil.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\displayw.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\distconnect.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\distpacket.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\distqueue.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\divcurl.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\dpattribute.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\dpparse.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\dxlinnamed.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\dxlmessage.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\dxloutvalue.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\dxmain.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\dxpfsmgr.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\echo.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\edfdata.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\edfdict.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\edfio.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\edflex.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\edfobj.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\edfparse.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\edfprint.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\eigen.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\enumerate.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\equalize.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\evalgraph.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\executive.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\exobject.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\exp_gai.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\export.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\extract.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\facenormals.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\field.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\fieldClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\fieldinterp.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\fieldinterpClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\fileio.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\filter.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\fle2D.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\fle2DClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\format.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\fourier.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\function.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\gather.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\genimp.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\genimp_io.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\genimp_parse.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\getscene.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\getset.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\gradient.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\graph.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\graph2.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\graphqueue.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\grid.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\group.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\groupClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\groupinterp.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\groupinterpClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\grow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\hash.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\help.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\helper.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\histogram.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwClientMessage.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwClipped.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwCursorInteractor.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\opengl\hwDisplayListsOGL.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwDraw.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwGather.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwGroupInteractor.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwInitScreen.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwInteractor.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\opengl\hwInteractorEchoOGL.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwList.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\opengl\hwLoadOGL.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwMaterials.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwMatrix.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwMemory.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwNavigateInteractor.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwObject.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwObjectHash.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwPaint.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwPolyline.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwPortHandle.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\opengl\hwPortOGL.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\opengl\hwPortUtilOGL.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwQmesh.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwRender.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwRotateInteractor.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwScreen.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwSort.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwStereo.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwStereoCams.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwStereoSys.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwTexture.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwTmesh.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwUpdateview.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwUserInteractor.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwView.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwWindow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwXfield.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwZoomInteractor.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\image.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\imagemessage.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\import.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\import_cdf.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\import_cm.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\import_hdf.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\import_ncdf.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\import_ss.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\importtable.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\include.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\init.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\inquire.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\instrument.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\integer.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\integerlist.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\interp.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\interpClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\invalid.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\irreggrow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\isolate.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\isosurface.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\keyin.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbcamera.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbcolor.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbextract.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbgrid.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lblight.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbmap.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbmessage.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbmsgs.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbpartition.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbpick.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbprint.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbprivate.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbscreen.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbshade.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbtext.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbtransform.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbvector.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\lex.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\license.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\light.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lightClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\line.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\linesII1D.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\linesII1DClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\linesRI1D.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\linesRI1DClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\linesRR1D.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\linesRR1DClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\list.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\loader.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lock.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\log.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\lookup.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\loop.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\macro.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\macroutil.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxexec\main.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\map.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\maptoplane.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\mark.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\matrix.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\measure.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\mem.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\memory.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\mesharray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\message.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\multigrid.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\neighbors.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\nodereadb.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\nodewriteb.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\normals.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\notify.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\object.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\objectClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\optarg.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\options.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\overlay.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\packet.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\paint.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\parse.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\parsemdf.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\partition.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\partreg.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\parts.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\path.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\patharray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\pendingcmds.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\permute.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\pick.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\pickinv.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\pie.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\plane.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\plock.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\plot.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\point.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\post.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\print.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\private.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\privateClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\productarray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\programctl.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\quad.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\quadsII2D.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\quadsII2DClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\quadsRR2D.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\quadsRR2DClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\quantize.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\queue.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\rdimagewin.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\readimage.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\reduce.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\refine.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\reggrow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\regrid.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\regulararray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\remote.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\remove.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\rename.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\render.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\reorient.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\replace.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\ribbon.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\rih.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\rotate.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\route.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\rq.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\rubbersheet.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\rwobject.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\sample.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\scalar.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\scalarlist.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\scale.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\scalescreen.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\screen.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\screenClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\seglist.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\select.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\selector.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\separate.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\sequencer.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\series.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\sfile.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\shade.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\sharedarray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\showboundary.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\showbox.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\showconnect.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\showposition.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\simplesurf.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\slab.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\slice.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\socket.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\socketconnect.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\sort.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\stack.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\statistics.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\stats.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\status.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\streakline.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\streamline.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\string.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\stringClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\stringlegend.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\stringtable.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\superstate.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\superwin.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\superwinW.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\swap.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\switch.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\system.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\task.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\tetras.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\tetrasClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\text.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\tile.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\timing.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\toggle.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\trace.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\tracevisual.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\transform.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\translate.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\transpose.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\triangle.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\trisRI2D.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\trisRI2DClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\tube.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\unmark.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\usage.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\user.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\userinit.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\userinter.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\utils.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\v3.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\variable.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\vcr.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\vector.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\vectorlist.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\vectors.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\verify.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\version.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\visualobject.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\volume.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\vrml.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\vsincos.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\windows.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\writeimage.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\xfield.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\xform.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\xformClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\yuiif.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\zclipQ.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\zclipT.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_autocolor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_autogray.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_colormap.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compoper.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compparse.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compputils.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_compute.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_connectgrids.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_connectvor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_construct.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_divcurl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\_eval.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_getfield.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_glyph.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_gradient.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_grid.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_helper_jea.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_isosurface.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\_macro.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_maptoplane.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_newtri.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_normals.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_partnbrs.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_plot.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_post.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_refine.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_rubbersheet.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_rw_image.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\_sample.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\_variable.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\arrayClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\attribute.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\autoaxes.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\background.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\binSort.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\bounds.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\cache.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\cachegraph.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cameraClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\cases.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\cat.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\ccm.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\changemember.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\clippedClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\color.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\command.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\compile.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\context.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\crc.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cubesIIClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cubesRRClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\d.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\diskio.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\displayutil.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\displayw.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\distp.h
# End Source File
# Begin Source File

SOURCE=..\dxconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\dxmain.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\dxpfsmgr.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\echo.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\edf.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\eigen.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\evalgraph.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\exobject.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\exp_gai.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\fieldClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\fieldinterpClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\fle2DClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\function.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\genimp.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_ARRW.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_ARRW2D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_BOX.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_CIRCLE10.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_CIRCLE20.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_CIRCLE4.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_CIRCLE40.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_CIRCLE6.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_CIRCLE8.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_DMND.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_NDDL.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_NDDL2D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_PNT.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_RCKT12.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_RCKT20.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_RCKT2D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_RCKT3.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_RCKT4.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_RCKT6.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_RCKT8.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_SPHR114.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_SPHR12.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_SPHR14.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_SPHR146.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_SPHR26.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_SPHR266.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_SPHR42.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_SPHR62.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\glyph_SQUARE.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\graph.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\graphIntr.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\graphqueue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\groupClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\groupinterpClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\help.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\histogram.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwClientMessage.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwClipped.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwCursorInteractor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwDebug.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwDeclarations.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwFlags.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwGather.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwGlobeEchoDef.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwInteractor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwInteractorEcho.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwMaterials.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwMatrix.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwMemory.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwObject.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwObjectHash.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwPortLayer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\opengl\hwPortOGL.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\opengl\hwPortUtilOGL.help
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwQmesh.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwRotateInteractor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwScreen.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwSort.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwStereo.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwTmesh.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwUserInteractor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwView.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwWindow.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwXfield.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\hwrender\hwZoomInteractor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\impCDF.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\import.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\instrument.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\integer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\interact.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\internals.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\interpClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbmsgs.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\lex.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\license.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lightClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\linesII1DClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\linesRI1DClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\linesRR1DClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\list.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\loader.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\log.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\macroutil.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\mark.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\measure.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\nodeb.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\objectClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\obmodule.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\packet.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\parse.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\parsemdf.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\path.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\pendingcmds.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\plock.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\plot.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\pmodflags.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\privateClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\quadsII2DClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\quadsRR2DClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\quant.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\queue.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\remote.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\render.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\rih.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\rq.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\scalar.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\screenClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\separate.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\sfile.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\showboundary.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\simplesurf.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\socket.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\status.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\stream.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\stringClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\superwin.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\swap.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\sysvars.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\task.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\tetrasClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\trace.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\triangles.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\trisRI2DClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\unpart.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\userinter.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\userInteractors.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\utils.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\vcr.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\vectors.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\verify.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\version.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\vrml.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dxmods\vsincos.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\xformClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\dpexec\yuiif.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\zclip.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\builder.ico
# End Source File
# Begin Source File

SOURCE=".\dx-cfg.ico"
# End Source File
# Begin Source File

SOURCE=".\dx-cm.ico"
# End Source File
# Begin Source File

SOURCE=".\dx-doc.ico"
# End Source File
# Begin Source File

SOURCE=".\dx-dx.ico"
# End Source File
# Begin Source File

SOURCE=..\DX\dxexec.def
# End Source File
# Begin Source File

SOURCE=.\dxexec.rc
# End Source File
# Begin Source File

SOURCE=.\editor.ico
# End Source File
# Begin Source File

SOURCE=.\prompter.ico
# End Source File
# Begin Source File

SOURCE=.\script.ico
# End Source File
# Begin Source File

SOURCE=.\startup.ico
# End Source File
# Begin Source File

SOURCE=.\tutor.ico
# End Source File
# End Group
# End Target
# End Project
