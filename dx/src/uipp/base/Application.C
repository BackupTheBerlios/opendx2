/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#include <X11/cursorfont.h>
#include <stdio.h>

#include "Application.h"
#include "Client.h"
#include "Command.h"
#include "Strings.h"
#include "TimedMessage.h"

Application* theApplication = NUL(Application*);


boolean Application::ApplicationClassInitialized = FALSE;
Cursor  Application::BusyCursor                  = NUL(Cursor);


Symbol Application::MsgCreate        = NUL(Symbol);
Symbol Application::MsgManage        = NUL(Symbol);
Symbol Application::MsgUnmanage      = NUL(Symbol);
Symbol Application::MsgSetBusyCursor = NUL(Symbol);
Symbol Application::MsgResetCursor   = NUL(Symbol);

Symbol Application::MsgManageByLeafClassName   = NUL(Symbol);
Symbol Application::MsgUnmanageByLeafClassName = NUL(Symbol);
Symbol Application::MsgManageByTitle 		= NUL(Symbol);
Symbol Application::MsgUnmanageByTitle 		= NUL(Symbol);

//
// This is used by the ASSERT macro in defines.h
// It should NOT be an Application method, because otherwise
// it requires that defines.h include Application.h.
//
extern "C" void AssertionFailure(const char *file, int line)
{
    fprintf(stderr,"Internal error detected at \"%s\":%d.\n",
		file, line);
    if (theApplication)
	theApplication->abortApplication();
    else
	abort();
}

Application::Application(char* className): UIComponent(className)
{
    ASSERT(className);

    //
    // Perform class initializtion, if necessary.
    //
    if (NOT Application::ApplicationClassInitialized)
    {
	ASSERT(theSymbolManager);

	Application::MsgCreate =
	    theSymbolManager->registerSymbol("Create");
	Application::MsgManage =
	    theSymbolManager->registerSymbol("Manage");
	Application::MsgUnmanage =
	    theSymbolManager->registerSymbol("Unmanage");
	Application::MsgSetBusyCursor =
	    theSymbolManager->registerSymbol("SetBusyCursor");
	Application::MsgResetCursor =
	    theSymbolManager->registerSymbol("ResetCursor");
	Application::MsgManageByLeafClassName   = 
	    theSymbolManager->registerSymbol("ManageByLeafClassName");
	Application::MsgUnmanageByLeafClassName = 
	    theSymbolManager->registerSymbol("UnmanageByLeafClassName");
	Application::MsgManageByTitle = 
	    theSymbolManager->registerSymbol("ManageByTitle");
	Application::MsgUnmanageByTitle= 
	    theSymbolManager->registerSymbol("UnmanageByTitle");

	Application::ApplicationClassInitialized = TRUE;
    }

    //
    // Set the global Application pointer.
    //
    theApplication = this;

    //
    // Initialize member data.
    //
    this->busyCursors	     = 0; 
    this->display            = NUL(Display*);
    this->applicationContext = NUL(XtAppContext);

    this->applicationClass   = DuplicateString(className);
    this->show_bubbles 	     = FALSE;
    this->help_viewer	     = NUL(Widget);
}


Application::~Application()
{
    delete this->applicationClass;
    theApplication = NULL;
}

//
// Install the default resources for this class.
//
void Application::installDefaultResources(Widget baseWidget)
{
    //this->setDefaultResources(baseWidget, Application::DefaultResources);
}


boolean Application::initializeWindowSystem(unsigned int *argcp, char **argv) 
{

    //
    // Initialize Xt Intrinsics; create the initial shell widget.
    //
    this->setRootWidget(
	XtAppInitialize
	    (&this->applicationContext, // returned application context
	     this->applicationClass,	// application class name
	     NULL,			// command line options table
	     0,				// number of entries in options table
#if XtSpecificationRelease > 4
	     (int*)argcp,
#else
	     argcp,
#endif
	     argv,			 // "argv" command line arguments
#if XtSpecificationRelease > 4
	     NULL,			 // fallback resource list
#else
	     NUL(const char**),		 // fallback resource list
#endif
	     NUL(ArgList),		 // override argument list
	     0),			 // number of entries in argument list
	     FALSE			// Don't install destroy callback
    );

    //
    // Get and save the X display structure pointer.
    //
    this->display = XtDisplay(this->getRootWidget());

    //
    // Center the shell and make sure it is not visible.
    //
    XtVaSetValues
	(this->getRootWidget(),
	 XmNmappedWhenManaged, FALSE,
	 XmNx,                 DisplayWidth(this->display, 0) / 2,
	 XmNy,                 DisplayHeight(this->display, 0) / 2,
	 XmNwidth,             1,
	 XmNheight,            1,
	 NULL);


    //
    // Force the initial shell window to exist so dialogs popped up
    // from this shell behave correctly.
    //
    XtRealizeWidget(this->getRootWidget());

	
    //
    // Install error and warning handlers.
    //
    XtSetWarningHandler((XtErrorHandler)Application_XtWarningHandler);
    XSetErrorHandler(Application_XErrorHandler);

    return TRUE;
}

void Application::parseCommand(unsigned int* argcp, char** argv,
                               XrmOptionDescList optlist, int optlistsize)
{
    XrmDatabase resourceDatabase = XrmGetStringDatabase("");

    char *appname = GetFileBaseName(argv[0],NULL);
    XrmParseCommand(&resourceDatabase, optlist, optlistsize, 
	                  appname, (int *)argcp, argv);
    delete appname;

    //
    // Merge the resources into the Xt database with highest precedence.
    //
    if (resourceDatabase)
    {
	//
	// display->db overrides contents of resourceDatabase.
	// O'Reilly, R5 prog. supplement, pg. 127
	//
#if defined XlibSpecificationRelease && XlibSpecificationRelease > 4
        XrmDatabase db = XrmGetDatabase(display);
        XrmCombineDatabase(resourceDatabase, &db, True);
#else
	
	XrmMergeDatabases(resourceDatabase, &(display->db));
#endif
    }
}

boolean Application::initialize(unsigned int* argcp, char** argv)
{
    //
    // Initialize the window system if not done already.
    //
    if (!this->getRootWidget() && 
	!this->initializeWindowSystem(argcp, argv))
	return FALSE;
	
    //
    // Since the instance name of this object was set in the UIComponent
    // constructor before the name of the program was visible, delete the
    // old name and set it to argv[0].
    //
    delete this->name;
    this->name = DuplicateString(argv[0]);

    //
    // Add Application specific actions.
    //
    this->addActions();

    //
    // Create the busy status indicator cursor.
    //
    Application::BusyCursor = XCreateFontCursor(this->display, XC_watch);

    //
    // Initialize and manage any windows registered with this
    // application at this point.
    //
    this->notifyClients(Application::MsgCreate);

    return TRUE;
}


//
// Post the copyright notice that is returned by this->getCopyrightNotice().
// If it returns NULL, then don't post any notice.
//
void Application::postCopyrightNotice()
{
    const char *c = this->getCopyrightNotice();

    if (c) {
	//
	// Post the copyright message.
	//
	TimedMessage *copyright =
	    new TimedMessage("copyrightMessage",
	    this->getRootWidget(),
	    c, 
	    "Welcome",
	    5000);
	copyright->post();
    }
}

void Application::handleEvents()
{
XEvent event;
    //
    // Loop forever...
    //
    for (;;) {
	XtAppNextEvent (this->applicationContext, &event);
	this->handleEvent(&event);
    }
}

void Application::handleEvent (XEvent *xev)
{
    XtDispatchEvent (xev);
}


void Application::manage()
{
    //
    // Notify the client windows to manage themselves.
    //
    this->notifyClients(Application::MsgManage);
}


void Application::unmanage()
{
    //
    // Notify the client windows to unmanage themselves.
    //
    this->notifyClients(Application::MsgUnmanage);
}


//
// Calls to this routine can be 'stacked' so that the first call
// sets the cursor and the last call resets the cursor.
// setBusyCursor(TRUE);		// Sets busy cursor
// setBusyCursor(TRUE);		// does not effect cursor
// setBusyCursor(TRUE);		// does not effect cursor
// setBusyCursor(FALSE);	// does not effect cursor
// setBusyCursor(TRUE);		// does not effect cursor
// setBusyCursor(FALSE);	// does not effect cursor
// setBusyCursor(FALSE);	// does not effect cursor
// setBusyCursor(FALSE);	// resets cursor
//
void Application::setBusyCursor(boolean setting)
{
    ASSERT(this->getRootWidget());
    ASSERT(Application::BusyCursor);
    ASSERT(this->busyCursors >= 0);

    if (setting)
    {
	this->busyCursors++;	
    }
    else
    {
	this->busyCursors--;	
    }

    switch (this->busyCursors) {
	case 0:
	    this->notifyClients(Application::MsgResetCursor);
	    break;
	case 1:
	    if (setting)
		this->notifyClients(Application::MsgSetBusyCursor);
	    break;
    }
	
    ASSERT(this->busyCursors >= 0);
}


//
// This is currently only used for debugging.
//
void Application::DumpApplicationResources(const char *filename)
{
    Display *display = theApplication->getDisplay();
 
#if defined XlibSpecificationRelease && XlibSpecificationRelease > 4
    XrmPutFileDatabase(XrmGetDatabase(display), filename);
#else
    XrmPutFileDatabase(display->db, filename);
#endif

}	
//
// Virtual methods that are called by Command::ExecuteCommandCallback()
// before and after Command::execute().
//
void Application::startCommandInterfaceExecution()
{
    this->notifyClients(Command::MsgBeginExecuting);
}
void Application::endCommandInterfaceExecution()
{
    this->notifyClients(Command::MsgEndExecuting);
}


const char *Application::getFormalName() 
{
    return "'Your Application's Formal Name Here'";
}

const char *Application::getInformalName() 
{
    return "'Your Application's Informal Name Here'";
}

const char *Application::getCopyrightNotice() 
{
    return "'Your Application's Copyright Notice Here'";
}

void Application::helpOn(const char *topic)
{
    printf("Your Application specific help on `%s' here\n", topic);
}
const char *Application::getHelpDirectory()
{
    return ".";
}

const char *Application::getHelpDirFileName()
{
    return "HelpDir";
}

extern "C" int Application_XErrorHandler(Display *display, XErrorEvent *event)
{
    if (theApplication)
        return theApplication->handleXError(display, event);
    else
	return 1;
}

int Application::handleXError(Display *display, XErrorEvent *event)
{
    char buffer[BUFSIZ];
    char mesg[BUFSIZ];
    char number[32];
    XGetErrorText(display, event->error_code, buffer, BUFSIZ);
    XGetErrorDatabaseText(display, "XlibMessage", "XError",
        "X Error", mesg, BUFSIZ);
    fprintf(stderr, "%s:  %s\n", mesg, buffer);
    XGetErrorDatabaseText(display, "XlibMessage", "MajorCode",
        "Request Major code %d", mesg, BUFSIZ);
    fprintf(stderr, mesg, event->request_code);
    if (event->request_code < 128) {
        sprintf(number, "%d", event->request_code);
        XGetErrorDatabaseText(display, "XRequest", number, "", buffer, BUFSIZ);
    } else {
        sprintf(buffer, "Extension %d", event->request_code);
    }
    fprintf(stderr, " (%s)\n  ", buffer);
    XGetErrorDatabaseText(display, "XlibMessage", "MinorCode",
        "Request Minor code %d", mesg, BUFSIZ);
    fprintf(stderr, mesg, event->minor_code);
    if (event->request_code >= 128) {
        sprintf(mesg, "Extension %d.%d",
            event->request_code, event->minor_code);
        XGetErrorDatabaseText(display, "XRequest", mesg, "", buffer, BUFSIZ);
        fprintf(stderr, " (%s)", buffer);
    }
    fputs("\n  ", stderr);
    XGetErrorDatabaseText(display, "XlibMessage", "ResourceID",
        "ResourceID 0x%x", mesg, BUFSIZ);
    fprintf(stderr, mesg, event->resourceid);
    fputs("\n  ", stderr);
    XGetErrorDatabaseText(display, "XlibMessage", "ErrorSerial",
        "Error Serial #%d", mesg, BUFSIZ);
    fprintf(stderr, mesg, event->serial);
    fputs("\n  ", stderr);

#if defined(XlibSpecificationRelease) && XlibSpecificationRelease <= 4
    // R5 does not allow one to get at display->request.
    XGetErrorDatabaseText(display, "XlibMessage", "CurrentSerial",
        "Current Serial #%d", mesg, BUFSIZ);
    fprintf(stderr, mesg, display->request);
    fputs("\n", stderr);
#endif

    if (event->error_code == BadImplementation) return 0;

    return 1;
}

extern "C" void Application_XtWarningHandler(char *message)
{
    if(theApplication)
        theApplication->handleXtWarning(message);
}
void Application::handleXtWarning(char *message)
{
   if(strstr(message, "non-existant accelerators") ||
      strstr(message, "to remove non-existant passive grab") ||
      strstr(message, "remove accelerators"))
        return;

   fprintf(stderr, "XtWarning: %s\n", message);

}
//
// Start a tutorial on behalf of the application.
// Return TRUE if successful.  At this level in the class hierachy
// we don't know how to start a tutorial so we always return FALSE.
//
boolean Application::startTutorial()
{
    return FALSE;
}
//
// A virtual method that allows other applications to handle ASSERT
// failures among other things.
//
void Application::abortApplication()
{
    abort();
}

