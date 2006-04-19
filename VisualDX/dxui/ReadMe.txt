========================================================================
    APPLICATION : dxui Project Overview
========================================================================

AppWizard has created this dxui Application for you.  

This file contains a summary of what you will find in each of the files that
make up your dxui application.

dxui.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

AssemblyInfo.cpp
    Contains custom attributes for modifying assembly metadata.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Win32.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////

ChangeLog:

11.19.2004
	Added to cvs repository. This currently will build a dxui in VisualStudio
	without any Motif code. XrmDatabase calls have been replaced with an
	Xml class to do the similar work. Our first Windows Form code has been
	added and the main Application loop has been changed to start working
	with forms. Still a long long way to go, but we're finally seeing how
	this is all going to play out.
	
	A lot of work has gone into converting the C++ code, boolean has been
	completely replaced with bool, some function overloading has been fixed.
	
	Command line parsing had to be rewritten since Xrm did all this for us
	before. Will need to still update code to write out the XmlPreferences
	when the application quits.
	