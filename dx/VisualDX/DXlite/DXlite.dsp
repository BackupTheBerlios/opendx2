# Microsoft Developer Studio Project File - Name="DXlite" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DXlite - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DXlite.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DXlite.mak" CFG="DXlite - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DXlite - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DXlite - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DXlite - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DXLITE_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".." /I "../../include" /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DXLITE_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "DXlite - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DXLITE_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "../../include" /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DXLITE_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DXlite - Win32 Release"
# Name "DXlite - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\exec\libdx\array.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\arrayClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\basic.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\box.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cameraClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\client.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\clipped.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\clippedClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\component.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\composite.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cstarray.c
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

SOURCE=..\..\src\exec\libdx\field.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\fieldClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\fileio.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\group.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\groupClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\hash.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\helper.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\init.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\invalid.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbcache.c
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

SOURCE=..\..\src\exec\libdx\lbmessage.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbmsgs.c
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

SOURCE=..\..\src\exec\libdx\lbtask.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lbvector.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lightClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\lock.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\matrix.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\memorystubs.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\mesharray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\multigrid.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\neighbors.c
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

SOURCE=..\..\src\exec\libdx\outglue.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\parts.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\patharray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\privateClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\productarray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\qmessage.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\regulararray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\renderstubs.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\rwobject.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\screenClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\seglist.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\series.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\sharedarray.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\string.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\stringClass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\stringtable.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\timing.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\userinit.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\version.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\xform.c
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\xformClass.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\exec\libdx\arrayClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\binSort.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cameraClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\clippedClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cubesIIClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\cubesRRClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\diskio.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\displayx.h
# End Source File
# Begin Source File

SOURCE=..\dxconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\edf.h
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

SOURCE=..\..\src\exec\libdx\groupClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\groupinterpClass.h
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

SOURCE=..\..\src\exec\libdx\objectClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\plock.h
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

SOURCE=..\..\src\exec\libdx\render.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\screenClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\stringClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\tetrasClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\triangles.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\trisRI2DClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\xformClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\exec\libdx\zclip.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\DXlite.def
# End Source File
# End Group
# End Target
# End Project
