/*  Open Visualization Data Explorer Source File */


#ifdef OS2
#   define INCL_DOSFILEMGR
#   include <os2.h>
#endif

#include <sys/types.h>
#include <errno.h>
#if !defined(DXD_WIN) && !defined(OS2)           //SMH get the right NT/DOS world functions
#include <dirent.h>
#else
#include <stdio.h>
#include <io.h>
#include <sys/stat.h>
#endif

#include "defines.h"
#include "lex.h"
#include "MacroDefinition.h"
#include "MacroNode.h"
#include "ListIterator.h"
#include "DXApplication.h"
#include "Network.h"
#include "ErrorDialogManager.h"
#include "WarningDialogManager.h"
#include "ParseMDF.h"
#include "ParameterDefinition.h"
#include "ToolSelector.h"
#include "EditorWindow.h"
#include "SaveMacroCommand.h"

#define OLD_DUMMY_DESCRIPTION_STRING "Generated dummy input"

#ifndef LACKS_ANY_REGCMP
#ifdef REGCMP_EXISTS
extern "C" char *regcmp(...);
extern "C" char *regex(char *, char *, ...);
#else
extern "C" char *re_comp(char *s);
extern "C" int re_exec(char *);
#endif
#endif

MacroDefinition::MacroDefinition(boolean system) : 
    NodeDefinition()
{
    this->systemMacro = system;
    this->fileName = NULL;
    this->body = NULL;
    this->initialRead = FALSE;
    this->updatingServer = FALSE;
    if (!system)
	this->saveCmd = new SaveMacroCommand("saveMacroCommand",
                                         theDXApplication->getCommandScope(),
                                         TRUE,
                                         this);
}
MacroDefinition::~MacroDefinition()
{
    if (this->saveCmd) delete this->saveCmd;

    if (this->body) 
    {
	this->body->setDefinition(NULL);
	theDXApplication->macroList.removeElement(this->body);
	if (!this->body->isDeleted())
	    delete this->body;
	this->body = NULL;
    }
    if (this->fileName)
	delete this->fileName;
}

void MacroDefinition::finishDefinition()
{
}


Node *MacroDefinition::newNode(Network *net, int instance)
{
    MacroNode *d = new MacroNode(this, net, instance);
    return d;
}

void MacroDefinition::reference(MacroNode *n)
{
    ListIterator li(this->referencingNodes);
    Node *listNode;
    while (listNode = (MacroNode*)li.getNext())
	if (n == listNode)
	    return;
    this->referencingNodes.appendElement(n);
}

void MacroDefinition::dereference(MacroNode *n)
{
    ListIterator li(this->referencingNodes);
    Node *listNode;
    while (listNode = (MacroNode*)li.getNext())
    {
	if (n == listNode)
	{
	    this->referencingNodes.deleteElement(li.getPosition()-1);
	    break;
	}
    }
//    if (this->referencingNodes.getSize() == 0 && this->body != NULL)
//    {
//	theDXApplication->macroList.removeElement(this->body);
//	delete this->body;
//	this->body = NULL;
//    }
}

boolean MacroDefinition::printNetworkBody(FILE *f, PrintType ptype)
{
    if (!this->loadNetworkBody())
	return FALSE;
    return this->body->printNetwork(f,ptype);
}
boolean MacroDefinition::loadNetworkBody()
{
    if (this->body == NULL)
    {
	this->body = theDXApplication->newNetwork(TRUE);
	this->body->setDefinition(this);
	this->initialRead = TRUE;
	boolean r = this->body->readNetwork(this->fileName);
	this->initialRead = FALSE;
        if (!r) {
            this->body->setDefinition(NULL);
            Network *n = this->body;
            this->body = NULL;
            delete n;
	    return FALSE;
        } else {
            theDXApplication->macroList.appendElement(this->body);
        }
    }
    return TRUE;
}
boolean MacroDefinition::updateServer()
{
    if (!this->loadNetworkBody())
	return FALSE;

    if (this->body && !this->updatingServer) {
	//
	// There is a recursive loop between DXExecCtl::updateMacros(),
	// Network::sendValues(), MacroNode::sendValues() and 
 	// this->updateServer() that we try and avoid here.   
	//
	this->updatingServer = TRUE;
	theDXApplication->getExecCtl()->updateMacros(FALSE);
	this->updatingServer = FALSE;
    }
    return (this->body != NULL);
}

boolean MacroDefinition::setNodeDefinitions(MacroDefinition *newDef)
{
    ListIterator li(this->referencingNodes);
    MacroNode *n;
    char *p;

    while (n = (MacroNode*)li.getNext())
    {
	n->setDefinition(newDef);
	n->updateDefinition();
	if (newDef != this)
	    newDef->reference(n);
    }

    return TRUE;
}

void MacroDefinition::setFileName(const char *n)
{
    char *fileName = DuplicateString(n);
    if (this->fileName)
	delete this->fileName;
    this->fileName = fileName;
}

boolean MacroDefinition::LoadMacroFile(FILE *f,
				       const char *fileName,
				       boolean replace,
				       boolean *wasMacro,
					boolean asSystemMacro)
{

    if (theDXApplication->inDebugMode())
	printf("read macro from %s\n", fileName);

    char *p, line[1000];
    boolean inMDF = FALSE;
    int lineNo = 0;
    MacroDefinition *md = NULL;
    NodeDefinition *nd = NULL;
    MacroDefinition *oldMd = NULL;
    SymbolManager  *symbolManager = theNodeDefinitionDictionary->
					getSymbolManager();

#define EQUAL_STRING_SECOND_LEN(s1,s2) (EqualSubstring((s1), (s2), STRLEN(s2)))
    while(fgets(line, sizeof(line), f) == line)
    {
	// Convert possible dos-land carriage returns (ctrl-M) to white space
	int len = STRLEN(line);
	if (len > 1 && line[len-2] == '\15')
	{
	    line[len-2] = line[len-1];
	    line[len-1] = '\0';
	    len--;
	}
	lineNo++;
	if (EQUAL_STRING_SECOND_LEN(line, "// Begin MDF"))
	{
	    inMDF = TRUE;
	}
	else if (inMDF && EQUAL_STRING_SECOND_LEN(line, "// End MDF"))
	{
	    inMDF = FALSE;
	    break;
	}
	else if (!inMDF && EQUAL_STRING_SECOND_LEN(line, "// MODULE"))
	{
	    if (theDXApplication->inDebugMode())
		printf("Macro rejected\n");
	    if (wasMacro)
		*wasMacro = FALSE;
	    goto error;
	}
	else if (inMDF && EQUAL_STRING_SECOND_LEN(line, "// MODULE"))
	{
	    if (wasMacro)
		*wasMacro = TRUE;

	    char name[1000];
	    int items_parsed = sscanf(line, "// MODULE %[^\n]", name);
	    if (items_parsed != 1)
	    {
		ErrorMessage("Invalid MODULE comment at line %d of %s.", 
		    lineNo, fileName);
		goto error;
	    }

	    int index = 0;
	    if (!IsRestrictedIdentifier(name, index) ||
		(index != STRLEN(name) && !IsWhiteSpace(name, index)))
	    {
		ErrorMessage("Invalid macro name: %s must start with a letter "
			     "and contain only letters and numbers "
			     "at line %d of %s.", 
		    name, lineNo, fileName);
		goto error;
	    }

	    if (EqualString("main", name))
	    {
		ErrorMessage("The macro name must not be \"main\" "
			     "at line %d of %s.", lineNo, fileName);
		goto error;
	    }

	    nd =
		(NodeDefinition*)theNodeDefinitionDictionary->
		    findDefinition(name);
	    if (nd)
	    {
		if (!nd->isDerivedFromMacro())
		{
		    ErrorMessage("Standard module \"%s\" cannot be redefined.\n"
				 "Macro file \"%s\" not loaded.",
			name, fileName);
		    goto error;
		}
		else if (!replace)
		{
//		    WarningMessage("Macro \"%s\" is already defined.\n"
//				   "Macro file \"%s\" not loaded.",
//			name, fileName);
		    goto error;
		}
		oldMd = (MacroDefinition*)nd;
	    }
	    md = new MacroDefinition(asSystemMacro);
	    md->setName(name);
	    md->setFileName(fileName);
	    if (nd)
		md->setNextInstance(nd->newInstanceNumber());
	}
	else if (inMDF && EQUAL_STRING_SECOND_LEN(line, "// CATEGORY"))
	{
	    char cat[1000];
	    int items_parsed = sscanf(line, "// CATEGORY %[^\n]", cat);
	    if (items_parsed != 1)
	    {
		ErrorMessage("Invalid CATEGORY comment at line %d of %s.", 
		    lineNo, fileName);
		goto error;
	    }
	    md->setCategory(symbolManager->registerSymbol(cat));
	}
	else if (inMDF && EQUAL_STRING_SECOND_LEN(line, "// DESCRIPTION"))
	{
	    char desc[1000];
	    int items_parsed = sscanf(line, "// DESCRIPTION %[^\n]", desc);
	    if (items_parsed != 1)
	    {
		ErrorMessage("Invalid DESCRIPTION comment at line %d of %s.", 
		    lineNo, fileName);
		goto error;
	    }
	    md->setDescription(desc);
	}
	else if (inMDF && EQUAL_STRING_SECOND_LEN(line, "// INPUT"))
	{
	    char name[1000];
	    char types[1000];
	    char deflt[1000];
	    char descr[1000];
	    int items_parsed = sscanf(line,
		    "// INPUT %[^;]; %[^;]; %[^;]; %[^\n]",
		    name, types, deflt, descr);
	    if (items_parsed != 3 && items_parsed != 4)
	    {
		ErrorMessage("Invalid INPUT comment at line %d of %s.", 
		    lineNo, fileName);
		goto error;
	    }

	    int index = 0;
	    // ... to avoid millions of purify umrs
	    int len = STRLEN(name);
	    name[len] = name[len+1] = '\0';
	    if (!IsIdentifier(name, index) ||
		(index != STRLEN(name) && !IsWhiteSpace(name, index) &&
			name[index] != '['))
	    {
		ErrorMessage("Invalid parameter name at line %d of %s.", 
		    lineNo, fileName);
		goto error;
	    }
	    name[index++] = '\0';
  	    int visattr = 1;
	    if (p = strstr(&name[index],"visible:")) {
		p += strlen("visible:");
		visattr = atoi(p);
	    } 
		
	    ParameterDefinition *pd = new 
		ParameterDefinition(symbolManager->registerSymbol(name));
	    if (items_parsed == 4) {
		if (strstr(descr,DUMMY_DESCRIPTION_STRING) ||
		    strstr(descr,OLD_DUMMY_DESCRIPTION_STRING))
		    pd->setDummy(TRUE);
		else
		    pd->setDescription(descr);
	    }
	    switch (visattr) {
	  	case 0:	pd->setDefaultVisibility(FALSE); break;
	  	case 1:	pd->setDefaultVisibility(TRUE); break;
	  	case 2:	pd->setViewability(FALSE); break;
	    }
	    pd->markAsInput();
	    if (!ParseMDFTypes(pd, types, lineNo))
	    {
		delete pd;
		goto error;
	    }
	    
	    if (*deflt == '(')
	    {
		pd->setDescriptiveValue(deflt);
		if (EqualString(deflt,"(none)"))
		    pd->setRequired();
	    }
	    else if (!pd->setDefaultValue(deflt))
	    {
		ErrorMessage(
		    "Invalid default parameter value at line %d of %s.", 
		    lineNo, fileName);

		delete pd;
		goto error;
	    }
	    md->addInput(pd);
	}
	else if (inMDF && EQUAL_STRING_SECOND_LEN(line, "// OUTPUT"))
	{
	    char name[1000];
	    char types[1000];
	    char descr[1000];
	    int items_parsed = sscanf(line,
		    "// OUTPUT %[^;]; %[^;]; %[^\n]",
		    name, types, descr);
	    if (items_parsed != 2 && items_parsed != 3)
	    {
		ErrorMessage("Invalid OUTPUT comment at line %d of %s.", 
		    lineNo, fileName);
		goto error;
	    }

	    int index = 0;
	    // ... to avoid millions of purify umrs
	    int len = STRLEN(name);
	    name[len] = name[len+1] = '\0';
	    if (!IsIdentifier(name, index) ||
		(index != STRLEN(name) && !IsWhiteSpace(name, index) &&
			name[index] != '['))
	    {
		ErrorMessage("Invalid parameter name at line %d of %s.", 
		    lineNo, fileName);
		goto error;
	    }

	    name[index++]='\0';
  	    int visattr = 1;
	    if (p = strstr(&name[index],"visible:")) {
		p += strlen("visible:");
		visattr = atoi(p);
	    } 

	    ParameterDefinition *pd = new 
		ParameterDefinition(symbolManager->registerSymbol(name));
	    if (items_parsed == 3) {
		if (strstr(descr,DUMMY_DESCRIPTION_STRING) ||
		    strstr(descr,OLD_DUMMY_DESCRIPTION_STRING))
		    pd->setDummy(TRUE);
		else
		    pd->setDescription(descr);
	    }
	    switch (visattr) {
	  	case 0:	pd->setDefaultVisibility(FALSE); break;
	  	case 1:	pd->setDefaultVisibility(TRUE); break;
	  	case 2:	pd->setViewability(FALSE); break;
	    }
	    pd->markAsOutput();
	    if (!ParseMDFTypes(pd, types, lineNo))
	    {
		delete pd;
		goto error;
	    }
	    
	    md->addOutput(pd);
	}
	else if (inMDF)
	{
	    WarningMessage("Encountered unrecognized MDF line "
			   "at line %d of `%s', ignored.",
		lineNo, fileName);
	}
    }

    if (!md)
	goto error;

    md->completeDefinition();

    if (!asSystemMacro) {
	if (oldMd)
	{
	    oldMd->setNodeDefinitions(md);
	    ToolSelector::RemoveTool(oldMd->getCategorySymbol(),
				     oldMd->getNameSymbol());
	    //
	    // Check if the macro is changed.
	    //
	    if (oldMd->body &&oldMd->saveCmd && 
		oldMd->body->saveToFileRequired())
	    {
		((SaveMacroCommand*)oldMd->saveCmd)->setNext(NULL);
		oldMd->saveCmd->execute();
	    }
	    else
		delete oldMd;
	}
    }

    theNodeDefinitionDictionary->replaceDefinition(md->getNameString(), md);

    if (!asSystemMacro) {
	ToolSelector::AddTool(md->getCategorySymbol(),
			      md->getNameSymbol(),
			      (void *)md);
	ToolSelector::UpdateCategoryListWidget();
	ToolSelector::UpdateToolListWidget();
    }


    if (theDXApplication->inDebugMode())
	printf("Macro %s accepted\n", md->getNameString());

    return TRUE;

error:
    if (md)
	delete md;
    return FALSE;
}

//
// Load all .net files in the given directory that are macros.
// If replace is TRUE, then replace any current definitions with the
// new one, otherwise ignore the .net file.
// If errmsg is not NULL and an error occurs then, no error messages are 
// posted, and instead a string buffer is allocated to hold the error 
// message that would have been posted and returned.  The returned 
// string must be freed by the caller.
//
boolean MacroDefinition::LoadMacroDirectories(const char *path, 
					boolean replace, char **errmsg,
					boolean asSystemMacro)
{
 
   boolean return_code = TRUE;

    if (path == NULL)
	return TRUE;
   
#ifdef OS2
#   define NORMAL_FILES 0
#   define FILE_ATTRIBUTE NORMAL_FILES
    HDIR         FindHandle;
    FILEFINDBUF3 FindBuffer;
    ULONG        FindCount;
    APIRET       rc;
#endif

#ifndef DXD_NON_UNIX_ENV_SEPARATOR
#define SEP_CHAR ':'
#else
#define SEP_CHAR ';'
#endif

    char *originalString = DuplicateString(path);
    char *sptr = originalString;

    if (errmsg)
	*errmsg = NULL;

    while(sptr)
    {
	char *nsptr = sptr;
	char *sep = strchr(nsptr, SEP_CHAR);
	if (sep)
	{
	    *sep = '\0';
	    sptr = sep + 1;
	}
	else
	{
	    sptr = NULL;
	}
#if !defined(DXD_WIN) && !defined(OS2)           //SMH get correct way to test directories existence
        DIR *d = opendir(nsptr);
	if (!d)
#else
        char *srch_string = new char[STRLEN(nsptr) + 7];  
        strcpy(srch_string,nsptr);                        
	if (strlen(srch_string)>0) {
	    char c = srch_string[strlen(srch_string)-1];
	    if (c != '/' && c != '\\' && c != ':')
		strcat(srch_string, "/");                   
	}
	strcat(srch_string, "*.net");
#ifndef OS2
        struct _stat b;
#else
        struct stat b;
#endif
        int d=_stat(nsptr,&b);
        if (d)                       
#endif
	{
 	    char *errtxt = "Failed opening directory %s: %s";
	    if (errmsg) {
		int size = STRLEN(errtxt) + STRLEN(nsptr) + 256;
		char *p;
		if (!*errmsg) {
		    *errmsg = (char*)MALLOC(size);
		    p = *errmsg;
		} else {
		    int errmsg_size = STRLEN(*errmsg);
		    *errmsg = (char*)REALLOC(*errmsg,errmsg_size + size + 2);
		    p = *errmsg + errmsg_size; 
		    *p = '\n';
		    p++;
		}
		sprintf(p,errtxt,nsptr, strerror(errno));
	    } else {
		ErrorMessage(errtxt, nsptr, strerror(errno));
	    }
	    return_code = FALSE;
	}
	else
	{
	    boolean wasEncoded; 

#ifndef DXD_LACKS_ANY_REGCMP
#ifdef REGCMP_EXISTS
	    char *net_file = regcmp(".[.]*\\.net$", NULL);
	    ASSERT(net_file != NULL);
#else                 // use re_comp
	    char *net_file = re_comp(".[.]*\\.net$");
	    ASSERT(net_file == NULL);
#endif                
	    struct dirent *entry;
	    while (entry = readdir(d))
	    {
#ifdef REGCMP_EXISTS
		boolean exists = regex(net_file, entry->d_name) != NULL;
#else                 // use re_exec
		boolean exists = re_exec(entry->d_name) > 0;
#endif                // REGCMP
		if (exists)
#elif !defined(OS2)   // Lack REGCMP and not OS2      
            struct _finddata_t entry;
            long handle = _findfirst(srch_string,&entry);
            int exists = (handle == -1) ? -1: 0;
                while (exists != -1)
#else                // Lack REGCMP and is OS2
            FindHandle = 0x0001;
            FindCount = 1;
            rc = DosFindFirst((PSZ) srch_string, &FindHandle, FILE_ATTRIBUTE,
                              (PVOID) &FindBuffer, sizeof(FindBuffer), &FindCount, FIL_STANDARD);
            int exists = (rc == 0) ? 0: -1;
                while (exists != -1)
#endif               // DXD_LACKS_ANY_REGCMP           
		{
		    char path[1000];
		    strcpy(path, nsptr);
		    strcat(path, "/");
#if !defined(DXD_WIN) && !defined(OS2)
                    strcat(path, entry->d_name);
#elif !defined(OS2)
                    strcat(path, entry.name);
#else
                    strcat(path, (char *) FindBuffer.achName);
#endif
		    char *ignore = NULL;
		    FILE *f = Network::OpenNetworkFILE(path,
						&wasEncoded,&ignore); 
		    if (ignore) delete ignore;
		    if (f == NULL)
		    {
			char *errtxt = "Failed to load macro file %s: %s";
			if (errmsg) {
			    int size = STRLEN(errtxt) + STRLEN(path) + 256;
			    char *p;
			    if (!*errmsg) {
				*errmsg = (char*)MALLOC(size);
				p = *errmsg;
			    } else {
				int errmsg_size = STRLEN(*errmsg);
				*errmsg = (char*)REALLOC(*errmsg,
							errmsg_size + size + 2);
				p = *errmsg + errmsg_size; 
				*p = '\n';
				p++;
			    }
			    sprintf(p,errtxt,path, strerror(errno));
			} else {
			    ErrorMessage(errtxt, path, strerror(errno));
	    		}
			return_code = FALSE;
		    }
		    else
		    {
			MacroDefinition::LoadMacroFile(f, path, 
						replace, NULL, asSystemMacro);
			Network::CloseNetworkFILE(f,wasEncoded);
		    }
#ifdef DXD_WIN                    //SMH loop on the right thing
                    exists=_findnext(handle,&entry);
                }
            _findclose(handle);
	    delete srch_string;
#elif defined(OS2)
                    rc = DosFindNext(FindHandle,
                                     (PVOID) &FindBuffer, sizeof(FindBuffer), &FindCount);
                    exists = (rc == 0) ? 0 : -1;
                }
 
            DosFindClose(FindHandle);
            delete srch_string;
#else
		}
	    }
#ifdef REGCMP_EXISTS
	    free(net_file);
#endif
	    closedir(d);
#endif          // NOT NT and NOT OS2
	}
    }

    delete originalString;
    return return_code;
}

//
// If errmsg is not NULL and an error occurs then, no error messages are 
// posted, and instead a string buffer is allocated to hold the error 
// message that would have been posted and returned.  The returned 
// string must be freed by the caller.
//
boolean MacroDefinition::LoadMacro(const char *fileName, char **errmsg,
					boolean asSystemMacro)
{
    char *netFile = Network::FilenameToNetname(fileName);
    boolean return_code = TRUE;

    if (errmsg)	
	*errmsg = NULL;

    boolean wasEncoded; 
    FILE *f = Network::OpenNetworkFILE(netFile,&wasEncoded, errmsg); 

 
    if (f == NULL) {
	return_code = FALSE;
    } else {
	boolean wasMacro;
	MacroDefinition::LoadMacroFile(f, netFile, TRUE, 
						&wasMacro, asSystemMacro);
	Network::CloseNetworkFILE(f,wasEncoded);
	if (!wasMacro) {
	    char *errtxt = "File %s doesn't contain a macro and was not loaded";
	    if (errmsg) {
		*errmsg = new char[STRLEN(errtxt) + STRLEN(netFile)];
		sprintf(*errmsg,errtxt,netFile);
	    } else {
		ErrorMessage(errtxt, netFile);
	    }
	    return_code = FALSE;
	}
    }
    delete netFile;

    return return_code;
}

void MacroDefinition::openMacro()
{
    if (this->updateServer()) {
	EditorWindow *e = this->body->getEditor();
	if (e == NULL)
	    e = theDXApplication->newNetworkEditor(this->body);
	if (e) {
	    e->manage();
	    XMapRaised(XtDisplay(e->getRootWidget()), 
			XtWindow(e->getRootWidget()));
	}
    }
}

boolean MacroDefinition::removeIODef(List *l, ParameterDefinition *pd)
{
    boolean result = l->removeElement((void*)pd);
    if (!this->initialRead)
	this->setNodeDefinitions(this);
    return result;
}
boolean MacroDefinition::addIODef(List *l, ParameterDefinition *pd)
{
    boolean result = TRUE;
    if (!this->initialRead) {
        result = this->NodeDefinition::addIODef(l, pd) &&
		 this->setNodeDefinitions(this);
    }
    return result;
}
boolean MacroDefinition::replaceIODef(List *l,
				      ParameterDefinition *newPd,
				      ParameterDefinition *pd)
{
    int position = l->getPosition((void*)pd);
    if (position == 0)
	return FALSE;
    boolean result = l->removeElement((void*)pd);
    if (result)
    {
	result = l->insertElement((void*)newPd, position);
    }

    int  i;
    //
    // Remove trailing DUMMY parameters.
    //
    if (result) {
	for (i = l->getSize(); (i > 0); i--)
	{
	    pd = (ParameterDefinition*)l->getElement(i);
	    if (pd->isDummy()) {
		if (l->removeElement((void*)pd))
		    delete pd;
	    } else
		break;
	}
    }
    if (!this->initialRead)
	this->setNodeDefinitions(this);

    return result;
}

//
// Get the Nth input that is not a dummy parameter definition.
//
ParameterDefinition *MacroDefinition::getNonDummyIODefinition(List *l, int n)
{
   ASSERT(n > 0);
   ASSERT(l);

   ParameterDefinition *pd;
   ListIterator iterator(*l);
   int count = 0;

   while ((count != n) &&
	  (pd = (ParameterDefinition*)iterator.getNext())) {
	if (!pd->isDummy())
	    count++;
   }
   if (count != n)
	pd = NULL;

   return pd;
}
//
// Find the first available spot to place a new parameter in the given
// list (expected to be either inputDefs or outputDefs). If there are dummy
// parameters in the list, then the index of the first dummy is returned.
// If no dummies, then N+1 is returned, where N is the current number of
// items in the list.
//
int MacroDefinition::getFirstAvailableIOPosition(List *l)
{
   ASSERT(l);

   ParameterDefinition *pd;
   ListIterator iterator(*l);
   int n = 0;
   boolean found_dummy = FALSE;

   while ((pd = (ParameterDefinition*)iterator.getNext())) {
	n++;
	if (pd->isDummy()) {
	   found_dummy = TRUE;
	   break; 
	}
   }
   if (!found_dummy)
	n++;

   ASSERT(n>0);
   return n;
}

boolean MacroDefinition::setNetwork(Network *net)
{
    this->body = net;
    this->initialRead = FALSE;

    return TRUE;
}

