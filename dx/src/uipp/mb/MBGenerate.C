/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>



#include "defines.h"
#include <stdio.h>
#include <string.h>
#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif
#if defined(HAVE_MALLOC_H)
#include <malloc.h>
#endif
#include "ErrorDialogManager.h"
#include "WarningDialogManager.h"
#include "MBGenerate.h"
#include "MBApplication.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

static int process_input(char *, Module *, Parameter **, Parameter **);
static int do_mdf(char *, Module *, Parameter **, Parameter **);
static int do_makefile(char *, Module *);
static int do_builder(char *, Module *, Parameter **, Parameter **);
static int cleanup(Module *m, Parameter **in, Parameter **out);

static int GetDXDataType(enum datatype, char **);
static int GetCDataType(enum datatype, char **);
static int GetDXDataShape(enum datashape, char **, char **);
static int GetElementTypeString(enum elementtype, char **);
static int copy_comments(char *, FILE *, char *, char *, char *);

#define MAX_IN	128
#define MAX_OUT 128

#define DO_MDF	0x1
#define DO_C    0x2
#define DO_MAKE 0x4

int Generate(int which, char *filename)
{
    Module module;
    Parameter *inputs[MAX_IN], *outputs[MAX_OUT];
    int i;
    char *c, *fnamecopy = (char *)malloc(strlen(filename) + 1);

    inputs[0] = outputs[0] = NULL;
    memset(&module, 0, sizeof(module));
    strcpy(fnamecopy, filename);

    for (i = 0; i < strlen(fnamecopy); i++)
	if (fnamecopy[i] == '.')
	{
	    fnamecopy[i] = '\0';
	    break;
	}
    
    if (! process_input(fnamecopy, &module, inputs, outputs))
	return 0;
    
    if (which & DO_MDF)
	if (! do_mdf(fnamecopy, &module, inputs, outputs))
	    return 0;
    
    if (which & DO_C)
	if (! do_builder(fnamecopy, &module, inputs, outputs))
	    return 0;
    
    if (which & DO_MAKE)
	if (! do_makefile(fnamecopy, &module))
	    return 0;
    
    if (! cleanup(&module, inputs, outputs))
	return 0;
    
    return 1;
}

static int
cleanup(Module *m, Parameter **in, Parameter **out)
{
    Parameter **p;

    if (m->name)                free(m->name);
    if (m->category)            free(m->category);
    if (m->description)         free(m->description);
    if (m->outboard_host)       free(m->description);
    if (m->outboard_executable) free(m->outboard_executable);
    if (m->loadable_executable) free(m->loadable_executable);
    if (m->include_file)        free(m->include_file);

    for (p = in; *p != NULL; p++)
    {
	if ((*p)->name)          free((*p)->name);
	if ((*p)->description)   free((*p)->description);
	if ((*p)->default_value) free((*p)->default_value);
	if ((*p)->types)         free((*p)->types);
	free((char *)*p);
    }

    for (p = out; *p != NULL; p++)
    {
	if ((*p)->name)          free((*p)->name);
	if ((*p)->description)   free((*p)->description);
	if ((*p)->default_value) free((*p)->default_value);
	if ((*p)->types)         free((*p)->types);
	free((char *)*p);
    }

    return 1;
}

static int
do_makefile(char *basename, Module *mod)
{
    FILE      *fd = NULL;
    char      *buf = (char *)malloc(strlen(basename) + 7);
    char      *makefilename;
    char      *c;
    const char *uiroot = NULL;
    #define OBJ_EXT "$(OBJEXT)"

    if (! buf)
    {
	WarningMessage("allocation error");
	goto error;
    }

    sprintf(buf, "%s.make", basename);

    fd = fopen(buf, "w");
    if (! fd)
    {
	ErrorMessage("error opening output file");
	goto error;
    }

    if (! copy_comments(basename, fd, NULL, "# ", NULL))
	goto error;
    
    for (c = basename; *c; c++)
	if (*c == '/')
	    basename = c+1;

    uiroot = theMBApplication->getUIRoot();
    // This should not be necessary, but we'll be very
    // careful just before the 3.1 release
    if (!uiroot)
        uiroot = "/usr/local/dx";

    fprintf(fd, "SHELL = /bin/sh\n");
    fprintf(fd, "BASE = %s\n\n",uiroot);

    fprintf(fd, "# need arch set, e.g. by\n");
    fprintf(fd, "# setenv DXARCH `dx -whicharch`\n");
    fprintf(fd, "include $(BASE)/lib_$(DXARCH)/arch.mak\n\n");

    if(mod->outboard_executable != NULL)
	fprintf(fd, "FILES_%s = %s.%s\n\n", basename, basename, OBJ_EXT);
    else if(mod->loadable_executable != NULL)
	fprintf(fd, "FILES_%s = user%s.%s %s.%s\n\n", 
                basename, basename, OBJ_EXT, basename, OBJ_EXT);
    else
	fprintf(fd, "FILES_%s = user%s.%s %s.%s\n\n", 
	    basename, basename, OBJ_EXT, basename, OBJ_EXT);

    fprintf(fd, "BIN = $(BASE)/bin\n\n");
    fprintf(fd, "#windows BIN = $(BASE)\\bin\n\n");
    fprintf(fd, "CFLAGS = -I./ -I$(BASE)/include $(DX_CFLAGS)\n\n");
    fprintf(fd, "LDFLAGS = -L$(BASE)/lib_$(DXARCH)\n\n");
    fprintf(fd, "LIBS = -lDX $(DX_GL_LINK_LIBS) $(DXEXECLINKLIBS)\n\n");
    fprintf(fd, "OLIBS = -lDXlite -lm\n\n");
    fprintf(fd, "BIN = $(BASE)/bin\n\n");


    fprintf(fd, "# create the necessary executable\n");
    if(mod->outboard_executable != NULL)
    {
	fprintf(fd, "%s: $(FILES_%s) outboard.$(OBJEXT)\n",
		mod->outboard_executable,
		basename);
	fprintf(fd, 
		"\t$(CC) $(DXABI) $(LDFLAGS) $(FILES_%s) outboard.$(OBJEXT) $(OLIBS) -o %s$(DOT_EXE_EXT)\n\n",
		basename,
		mod->outboard_executable);

	  fprintf(fd, "# how to make the outboard main routine\n");
	  fprintf(fd, "outboard.$(OBJEXT): $(BASE)/lib/outboard.c\n");
	  fprintf(fd, "\t%s%s%s\n",
	     "$(CC) $(DXABI) $(CFLAGS) -DUSERMODULE=m_",
	    mod->name,
	     " -c $(BASE)/lib/outboard.c");
	  fprintf(fd, "\n\n");
    }
    else if(mod->loadable_executable != NULL)
    {   
       fprintf(fd, "%s: $(FILES_%s) \n",
               mod->loadable_executable, basename);

       fprintf(fd, "\t$(SHARED_LINK) $(DXABI) $(LDFLAGS) -o %s user%s.$(OBJEXT) %s.$(OBJEXT) $(DX_RTL_ALDFLAGS) $(SYSLIBS)\n\n",
               mod->loadable_executable, basename, basename);
#if 0
#ifdef alphax
       fprintf(fd, "\tld $(LDFLAGS) -o %s user%s.$(OBJEXT) %s.$(OBJEXT) $(SYSLIBS)\n\n",
               mod->loadable_executable, basename, basename);
#endif
#ifdef hp700
       fprintf(fd, "\tld $(LDFLAGS) -o %s user%s.$(OBJEXT) %s.$(OBJEXT) $(SYSLIBS)\n\n",
               mod->loadable_executable, basename, basename);
#endif
#ifdef ibm6000 
       fprintf(fd, "\tcc -o %s user%s.$(OBJEXT) %s.$(OBJEXT) -e DXEntry -bI:$(EXP)\n\n",
               mod->loadable_executable, basename, basename);
#endif
#ifdef DXD_WIN 
       fprintf(fd, "\t$(CC) $(CFLAGS) -o %s  user%s.$(OBJEXT) %s.$(OBJEXT)  $(SYSLIBS) $(OLIBS) \n\n",
               mod->loadable_executable, basename, basename);
#endif
#ifdef sgi 
       fprintf(fd, "\tcc $(LDFLAGS) -o %s user%s.$(OBJEXT) %s.$(OBJEXT) $(SYSLIBS)\n\n",
               mod->loadable_executable, basename, basename);
#endif
#ifdef solaris 
       fprintf(fd, "\tcc $(LDFLAGS) -o %s user%s.$(OBJEXT) %s.$(OBJEXT)n\n",
               mod->loadable_executable, basename, basename);
#endif
#endif /* zero */
    }
    else
    {
	fprintf(fd, "dxexec: $(FILES_%s) \n",
		basename);
	fprintf(fd, "\t$(CC) $(LDFLAGS) $(FILES_%s) $(LIBS) -o dxexec\n\n",
		basename);
#if 0
#if defined(DXD_WIN)  || defined(OS2)
	fprintf(fd, "dxexec.exe: $(FILES_%s) \n",
		basename);
#else
	fprintf(fd, "dxexec: $(FILES_%s) \n",
		basename);
#endif
#endif /* zero */

#if 0
#if   defined(DXD_WIN)
	fprintf(fd, "\t$(CC) (DXABI) $(LDFLAGS) $(FILES_%s) $(LIBS) -o dxexec.exe\n\n",
		basename);
#else
	fprintf(fd, "\t$(CC) $(DXABI) $(LDFLAGS) $(FILES_%s) $(LIBS) -o dxexec\n\n",
		basename);
#endif
#endif /* zero */
    }

      fprintf(fd, ".c.o: ; cc -c $(DXABI) $(DX_RTL_CFLAGS) $(CFLAGS) $*.c \n\n");
      fprintf(fd, ".C.o: ; cc -c $(DXABI) $(DX_RTL_CFLAGS) $(CFLAGS) $*.C \n\n");


    /* a target to run dx using the user module */

    fprintf(fd, "# a command to run the user module\n");
    /* outboard module */
    if(mod->outboard_executable != NULL) {
      fprintf(fd, "run: %s \n", mod->outboard_executable);
      fprintf(fd, "\tdx -edit -mdf %s.mdf &\n", basename);
      fprintf(fd, "\n");
    }
    else if(mod->loadable_executable != NULL) {
    /* runtime loadable module */
      fprintf(fd, "run: %s \n", mod->loadable_executable);
      fprintf(fd, "\tdx -edit -mdf %s.mdf &\n", basename);
      fprintf(fd, "\n");
    }
    else {
    /* inboard module */
      fprintf(fd, "run: dxexec \n");
      fprintf(fd, "\tdx -edit -exec ./dxexec -mdf %s.mdf &\n", basename);
      fprintf(fd, "\n");
    }

    fprintf(fd, "# make the user files\n");
    fprintf(fd, "user%s.c: %s.mdf\n", basename, basename);
  
#ifdef DXD_WIN    /* just to change forward and back slashes    */
    if(mod->loadable_executable != NULL) 
       fprintf(fd, "\t$(BIN)\\mdf2c -m %s.mdf > user%s.c\n", basename, basename);
    else
       fprintf(fd, "\t$(BIN)\\mdf2c %s.mdf > user%s.c\n", basename, basename);

#else
    if(mod->loadable_executable != NULL) 
       fprintf(fd, "\t$(BIN)/mdf2c -m %s.mdf > user%s.c\n", basename, basename);
    else
       fprintf(fd, "\t$(BIN)/mdf2c %s.mdf > user%s.c\n", basename, basename);
#endif

    fprintf(fd, "# kluge for when DXARCH isn't set\n");
    fprintf(fd, "$(BASE)/lib_/arch.mak:\n");
    makefilename=strrchr(buf,'/');
    if(!makefilename) makefilename = buf;
	else makefilename++;
    fprintf(fd, "\t(export DXARCH=`dx -whicharch` ; $(MAKE) -f %s )\n",makefilename);
    fprintf(fd, "\techo YOU NEED TO SET DXARCH via dx -whicharch\n");
    fclose(fd);
    return 1;

error:
    if (fd)
    {
	fclose(fd);
	unlink(buf);
    }
    return 0;
}

static int
do_mdf(char *basename, Module *mod, Parameter **in, Parameter **out)
{
    FILE      *fd = NULL;
    char      *buf = (char *)malloc(strlen(basename) + 5);

    if (! buf)
    {
	ErrorMessage("allocation error");
	goto error;
    }

    sprintf(buf, "%s.mdf", basename);

    fd = fopen(buf, "w");
    if (! fd)
    {
	ErrorMessage("error opening output file");
	goto error;
    }

    if (! copy_comments(basename, fd, NULL, "# ", NULL))
	goto error;

    fprintf(fd, "MODULE %s\n", mod->name);
    fprintf(fd, "CATEGORY %s\n", mod->category);
    fprintf(fd, "DESCRIPTION %s\n", mod->description);

    if (mod->outboard_persistent == TRUE ||
	mod->asynchronous  == TRUE       ||
	mod->pinned  == TRUE             ||
	mod->side_effect == TRUE)
    {
	int first = 1;
	fprintf(fd, "FLAGS");
	if (mod->outboard_persistent == TRUE)
	    fprintf(fd, "%sPERSISTENT", first++ ? " " : ", ");
	if (mod->asynchronous == TRUE)
	    fprintf(fd, "%sASYNC", first++ ? " " : ", ");
	if (mod->pinned == TRUE)
	    fprintf(fd, "%sPIN", first++ ? " " : ", ");
	if (mod->side_effect == TRUE)
	    fprintf(fd, "%sSIDE_EFFECT", first++ ? " " : ", ");
	fprintf(fd, "\n");
    }

    if (mod->outboard_executable)
    {
	fprintf(fd, "OUTBOARD %s;", mod->outboard_executable);
	if (mod->outboard_host)
	    fprintf(fd, "%s", mod->outboard_host);
	fprintf(fd, "\n");
    }

    if (mod->loadable_executable)
    {
	fprintf(fd, "LOADABLE %s;", mod->loadable_executable);
	fprintf(fd, "\n");
    }

    while (*in)
    {
	char *c;
	fprintf(fd, "INPUT %s; ", (*in)->name);

	if ((*in)->types)
	{
	    char *buf, *b, *c;
	    int i, nc;

	    for (c = (*in)->types, nc = 0; *c; c++)
		if (*c == ',') nc++;
	  
            /* integer vector and integer vector list are not understood by
               the ui */ 
            if (!strcmp((*in)->types,"integer vector")) {
	        buf = b = (char *)malloc(strlen("vector") + 4*nc + 1);
	        for (c = "vector", nc = 0; *c; c++)
	           *b++ = *c;
            }
            else if (!strcmp((*in)->types,"integer vector list")) {
	        buf = b = (char *)malloc(strlen("vector list") + 4*nc + 1);
	        for (c = "vector list", nc = 0; *c; c++)
	           *b++ = *c;
            }
            else {
	        buf = b = (char *)malloc(strlen((*in)->types) + 4*nc + 1);
	        for (c = (*in)->types, nc = 0; *c; c++)
		    *b++ = *c;
            }
         

	    *b = '\0';

	    fprintf(fd, "%s; ", buf);

	    free(buf);
	}
	else if ((*in)->structure == VALUE)
	    fprintf(fd, "value; ");
	else if ((*in)->structure == GROUP_FIELD)
	    fprintf(fd, "group; ");
	else
	{
	    ErrorMessage("input %s has no STRUCTURE parameter\n", (*in)->name);
	    goto error;
	}
	if ((*in)->required == TRUE)
	    fprintf(fd, " (none);");
	else if ((*in)->descriptive == TRUE)
	    fprintf(fd, " (%s);", (*in)->default_value);
	else
	    fprintf(fd, " %s;", (*in)->default_value);
	fprintf(fd, " %s\n", (*in)->description);
	in++;
    }

    while (*out)
    {
	char *c;
	fprintf(fd, "OUTPUT %s; ", (*out)->name);

	if ((*out)->types)
	{
	    char *buf, *b, *c;
	    int i, nc;

	    for (c = (*out)->types, nc = 0; *c; c++)
		if (*c == ',') nc++;
	    
	    buf = b = (char *)malloc(strlen((*out)->types) + 4*nc + 1);

	    for (c = (*out)->types, nc = 0; *c; c++)
		if (*c == ',')
		{
		    *b++ = ' ';
		    *b++ = 'o';
		    *b++ = 'r';
		    *b++ = ' ';
		}
		else
		    *b++ = *c;
	    
	    *b = '\0';

	    fprintf(fd, "%s; ", buf);

	    free(buf);
	}
	else if ((*out)->structure == VALUE)
	    fprintf(fd, "value; ");
	else if ((*out)->structure == GROUP_FIELD)
	    fprintf(fd, "group; ");
	else
	{
	    ErrorMessage("output %s has no STRUCTURE parameter\n", (*out)->name);
	    goto error;
	}
	fprintf(fd, " %s\n", (*out)->description);
	out++;
    }
    
    fclose(fd);
    return 1;

error:
    if (fd)
    {
	fclose(fd);
	unlink(buf);
    }
    return 0;
}

static int
do_builder(char *basename, Module *mod, Parameter **in, Parameter **out)
{
    FILE       *fd = NULL;
    int        i, nin, nout, n_GF_in, n_GF_out, open;
    char       *buf = (char *)malloc(strlen(basename) + 4);

    if (! buf)
    {
	ErrorMessage("allocation error");
	goto error;
    }

    sprintf(buf, "%s.c", basename);

    fd = fopen(buf, "w");
    if (! fd)
    {
	ErrorMessage("error opening output file");
	goto error;
    }

    if (! copy_comments(basename, fd, "/*\n", " * ", " */\n"))
	goto error;

    for (nin  = 0; in[nin] != NULL; nin++);
    for (nout = 0; out[nout] != NULL; nout++);

fprintf(fd, "/*\n");
fprintf(fd, " * Automatically generated on \"%s.mb\" by DX Module Builder\n",
				basename);
fprintf(fd, " */\n\n");

fprintf(fd, "/* define your pre-dx.h include file for inclusion here*/ \n");
fprintf(fd, "#ifdef PRE_DX_H\n");
fprintf(fd, "#include \"%s_predx.h\"\n",mod->name);
fprintf(fd, "#endif\n");
fprintf(fd, "#include \"dx/dx.h\"\n");
fprintf(fd, "/* define your post-dx.h include file for inclusion here*/ \n");
fprintf(fd, "#ifdef POST_DX_H\n");
fprintf(fd, "#include \"%s_postdx.h\"\n",mod->name);
fprintf(fd, "#endif\n");
fprintf(fd, "\n");
fprintf(fd, "static Error traverse(Object *, Object *);\n");
fprintf(fd, "static Error doLeaf(Object *, Object *);\n");
fprintf(fd, "\n");
fprintf(fd, "/*\n");
fprintf(fd, " * Declare the interface routine.\n");
fprintf(fd, " */\n");
fprintf(fd, "int\n%s_worker(\n", mod->name);

    open = 0;

    if (in[0]->positions == GRID_REGULAR)
    {
	open = 1;
fprintf(fd, "    int, int, int *, float *, float *");
    }
    else if (in[0]->positions == GRID_IRREGULAR)
    {
	open = 1;
fprintf(fd, "    int, int, float *");
    }

    if (in[0]->connections == GRID_REGULAR)
    {
fprintf(fd, "%s   int, int, int *", (open)?",\n":"");
	open = 1;
    }
    else if (in[0]->connections == GRID_IRREGULAR)
    {
fprintf(fd, "%s    int, int, int *", (open)?",\n":"");
	open = 1;
    }

    for (i = 0; i < nin; i++)
    { 
	char *type;
	GetCDataType(in[i]->datatype, &type);
fprintf(fd, "%s    int, %s *", (open)?",\n":"", type);
	open = 1;
    }

    for (i = 0; i < nout; i++)
    { 
	char *type;
	GetCDataType(out[i]->datatype, &type);
fprintf(fd, "%s    int, %s *", (open)?",\n":"", type);
	open = 1;
    }

fprintf(fd, ");\n\n");

fprintf(fd, "#if defined (__cplusplus) || defined (c_plusplus)\n");
fprintf(fd, "extern \"C\"\n");
fprintf(fd, "#endif\n");
fprintf(fd, "Error\nm_%s(Object *in, Object *out)\n", mod->name);
fprintf(fd, "{\n");
fprintf(fd, "  int i;\n");
fprintf(fd, "\n");
fprintf(fd, "  /*\n");
fprintf(fd, "   * Initialize all outputs to NULL\n");
fprintf(fd, "   */\n");
    if (nout == 1)
fprintf(fd, "  out[0] = NULL;\n");
    else if (nout > 1)
    {
fprintf(fd, "  for (i = 0; i < %d; i++)\n", nout);
fprintf(fd, "    out[i] = NULL;\n");
    }

fprintf(fd, "\n");

fprintf(fd, "  /*\n");
fprintf(fd, "   * Error checks: required inputs are verified.\n");
fprintf(fd, "   */\n\n");

    n_GF_in = 0;
    for (i = 0; i < nin; i++)
    {
	if (in[i]->structure == GROUP_FIELD)
	    n_GF_in ++;

	if (in[i]->required == TRUE || i == 0)
	{
fprintf(fd, "  /* Parameter \"%s\" is required. */\n", in[i]->name);
fprintf(fd, "  if (in[%d] == NULL)\n", i);
fprintf(fd, "  {\n");
fprintf(fd, "    DXSetError(ERROR_MISSING_DATA, ");
fprintf(fd, "\"\\\"%s\\\" must be specified\");\n", in[i]->name);
fprintf(fd, "    return ERROR;\n");
fprintf(fd, "  }\n\n");
	}
    }

    n_GF_out = 0;
    for (i = 0; i < nout; i++)
    {
fprintf(fd, "\n");

	if (out[i]->structure == GROUP_FIELD)
	{
	    n_GF_out ++;

fprintf(fd, "  /*\n");
fprintf(fd, "   * Since output \"%s\" is structure Field/Group, it initially\n", out[i]->name);
fprintf(fd, "   * is a copy of input \"%s\".\n", in[0]->name);
fprintf(fd, "   */\n");
fprintf(fd, "  out[%d] = DXCopy(in[0], COPY_STRUCTURE);\n", i);
fprintf(fd, "  if (! out[%d])\n", i);
fprintf(fd, "    goto error;\n\n");
fprintf(fd, "  /*\n");
fprintf(fd, "   * If in[0] was an array, then no copy is actually made - Copy \n");
fprintf(fd, "   * returns a pointer to the input object.  Since this can't be written to\n");
fprintf(fd, "   * we postpone explicitly copying it until the leaf level, when we'll need\n");
fprintf(fd, "   * to be creating writable arrays anyway.\n");
fprintf(fd, "   */\n");
fprintf(fd, "  if (out[%d] == in[0])\n", i);
fprintf(fd, "    out[%d] = NULL;\n", i);
	}
	else if (out[i]->structure == VALUE)
	{
	    char *t;
	    char *r, *s;
	    char *l;

	    if (! GetDXDataType(out[i]->datatype, &t))
	    {
		ErrorMessage("cannot create array without DATATYPE");
		goto error;
	    }

	    if (! GetDXDataShape(out[i]->datashape, &r, &s))
	    {
		ErrorMessage("cannot create array without DATASHAPE");
		goto error;
	    }

#if 0
	    switch(out[i]->counts)
	    {
		case COUNTS_1: l = "1"; break;
		default:
		    ErrorMessage("cannot create array without COUNTS");
		    goto error;
	    }
#endif
	    l = "1";

fprintf(fd, "  /*\n");
fprintf(fd, "   * Output \"%s\" is a value; set up an appropriate array\n", out[i]->name);
fprintf(fd, "   */\n");
fprintf(fd, "  out[%d] = (Object)DXNewArray(%s, CATEGORY_REAL, %s, %s);\n", i, t, r, s);
fprintf(fd, "  if (! out[%d])\n", i);
fprintf(fd, "    goto error;\n");
fprintf(fd, "  if (! DXAddArrayData((Array)out[%d], 0, %s, NULL))\n", i, l);
fprintf(fd, "    goto error;\n");
fprintf(fd, "  memset(DXGetArrayData((Array)out[%d]), 0, %s*DXGetItemSize((Array)out[%d]));\n", i, l, i);
fprintf(fd, "\n");
	}
    }

fprintf(fd, "\n");

fprintf(fd, "  /*\n");
fprintf(fd, "   * Call the hierarchical object traversal routine\n");
fprintf(fd, "   */\n");
fprintf(fd, "  if (!traverse(in, out))\n");
fprintf(fd, "    goto error;\n");

fprintf(fd, "\n");

fprintf(fd, "  return OK;\n");
fprintf(fd, "\n");
fprintf(fd, "error:\n");
fprintf(fd, "  /*\n");
fprintf(fd, "   * On error, any successfully-created outputs are deleted.\n");
fprintf(fd, "   */\n");
fprintf(fd, "  for (i = 0; i < %d; i++)\n", nout);
fprintf(fd, "  {\n");
fprintf(fd, "    if (in[i] != out[i])\n");
fprintf(fd, "      DXDelete(out[i]);\n");
fprintf(fd, "    out[i] = NULL;\n");
fprintf(fd, "  }\n");
fprintf(fd, "  return ERROR;\n");
fprintf(fd, "}\n");

fprintf(fd, "\n\n");
fprintf(fd, "static Error\n");
fprintf(fd, "traverse(Object *in, Object *out)\n");
fprintf(fd, "{\n");
fprintf(fd, "  switch(DXGetObjectClass(in[0]))\n");
fprintf(fd, "  {\n");
fprintf(fd, "    case CLASS_FIELD:\n");
fprintf(fd, "    case CLASS_ARRAY:\n");
fprintf(fd, "    case CLASS_STRING:\n");
fprintf(fd, "      /*\n");
fprintf(fd, "       * If we have made it to the leaf level, call the leaf handler.\n");
fprintf(fd, "       */\n");
fprintf(fd, "      if (! doLeaf(in, out))\n");
fprintf(fd, "  	     return ERROR;\n");
fprintf(fd, "\n");
fprintf(fd, "      return OK;\n");
fprintf(fd, "\n");
fprintf(fd, "    case CLASS_GROUP:\n");
fprintf(fd, "    {\n");
fprintf(fd, "      int   i, j;\n");
fprintf(fd, "      int   memknt;\n");
fprintf(fd, "      Class groupClass  = DXGetGroupClass((Group)in[0]);\n");
fprintf(fd, "\n");
fprintf(fd, "      DXGetMemberCount((Group)in[0], &memknt);\n");
fprintf(fd, "\n");
if (n_GF_in > 1)
{
fprintf(fd, "      /*\n");
fprintf(fd, "       * All inputs that are not NULL and are type Field/Group must\n");
fprintf(fd, "       * match the structure of input[0].  Verify that this is so.\n");
fprintf(fd, "       */\n");
    for (i = 1; i < nin; i++)
	if (in[i]->structure == GROUP_FIELD)
	{
fprintf(fd, "       if (in[%d] &&\n", i);
fprintf(fd, "            (DXGetObjectClass(in[%d]) != CLASS_GROUP ||\n", i);
fprintf(fd, "             DXGetGroupClass((Group)in[%d])  != groupClass  ||\n", i);
fprintf(fd, "             !DXGetMemberCount((Group)in[%d], &i) || i != memknt))\n", i);
fprintf(fd, "	      {\n");
fprintf(fd, "  		DXSetError(ERROR_DATA_INVALID,\n");
fprintf(fd, "	            \"structure of \\\"%s\\\" doesn't match that of \\\"%s\\\"\");\n",
			    in[i]->name, in[0]->name);
fprintf(fd, "  	         return ERROR;\n");
fprintf(fd, "         }\n\n");
	}
}
else
fprintf(fd, "\n");

fprintf(fd, "       /*\n");
fprintf(fd, "        * Create new in and out lists for each child\n");
fprintf(fd, "        * of the first input. \n");
fprintf(fd, "        */\n");
fprintf(fd, "        for (i = 0; i < memknt; i++)\n");
fprintf(fd, "        {\n");
fprintf(fd, "          Object new_in[%d], new_out[%d];\n", nin, nout);
fprintf(fd, "\n");

fprintf(fd, "         /*\n");
fprintf(fd, "          * For all inputs that are Values, pass them to \n");
fprintf(fd, "          * child object list.  For all that are Field/Group, get \n");
fprintf(fd, "          * the appropriate decendent and place it into the\n");
fprintf(fd, "          * child input object list.\n");
fprintf(fd, "          */\n\n");
for (i = 0; i < nin; i++)
    if (in[i]->structure == VALUE)
    {
fprintf(fd, "          /* input \"%s\" is Value */\n", in[i]->name);
fprintf(fd, "          new_in[%d] = in[%d];\n\n", i, i);
    }
    else if (in[i]->structure == GROUP_FIELD)
    {
fprintf(fd, "          /* input \"%s\" is Field/Group */\n", in[i]->name);
fprintf(fd, "          if (in[%d])\n", i);
fprintf(fd, "            new_in[%d] = DXGetEnumeratedMember((Group)in[%d], i, NULL);\n", i, i);
fprintf(fd, "          else\n");
fprintf(fd, "            new_in[%d] = NULL;\n", i);
fprintf(fd, "\n");
    }

fprintf(fd, "         /*\n");
fprintf(fd, "          * For all outputs that are Values, pass them to \n");
fprintf(fd, "          * child object list.  For all that are Field/Group,  get\n");
fprintf(fd, "          * the appropriate decendent and place it into the\n");
fprintf(fd, "          * child output object list.  Note that none should\n");
fprintf(fd, "          * be NULL (unlike inputs, which can default).\n");
fprintf(fd, "          */\n\n");
for (i = 0; i < nout; i++)
    if (out[i]->structure == VALUE)
    {
fprintf(fd, "          /* output \"%s\" is Value */\n", out[i]->name);
fprintf(fd, "          new_out[%d] = out[%d];\n\n", i, i);
    }
    else
    {
fprintf(fd, "          /* output \"%s\" is Field/Group */\n", out[i]->name);
fprintf(fd, "          new_out[%d] = DXGetEnumeratedMember((Group)out[%d], i, NULL);\n\n", i, i);
    }

fprintf(fd, "          if (! traverse(new_in, new_out))\n");
fprintf(fd, "            return ERROR;\n");
fprintf(fd, "\n");

if (n_GF_out)
{
fprintf(fd, "         /*\n");
fprintf(fd, "          * Now for each output that is not a Value, replace\n");
fprintf(fd, "          * the updated child into the object in the parent.\n");
fprintf(fd, "          */\n\n");
    for (i = 0; i < nout; i++)
	if (out[i]->structure == GROUP_FIELD)
	{
fprintf(fd, "          /* output \"%s\" is Field/Group */\n", out[i]->name);
fprintf(fd, "          DXSetEnumeratedMember((Group)out[%d], i, new_out[%d]);\n\n", i, i);
	}
}

fprintf(fd, "        }\n");
fprintf(fd, "      return OK;\n");
fprintf(fd, "    }\n");
fprintf(fd, "\n");
fprintf(fd, "    case CLASS_XFORM:\n");
fprintf(fd, "    {\n");
fprintf(fd, "      int    i, j;\n");
fprintf(fd, "      Object new_in[%d], new_out[%d];\n", nin, nout);
fprintf(fd, "\n");

if (n_GF_in > 1)
{
fprintf(fd, "      /*\n");
fprintf(fd, "       * All inputs that are not NULL and are type Field/Group must\n");
fprintf(fd, "       * match the structure of input[0].  Verify that this is so.\n");
fprintf(fd, "       */\n");
    for (i = 1; i < nin; i++)
	if (in[i]->structure == GROUP_FIELD)
	{
fprintf(fd, "      if (in[%d] && DXGetObjectClass(in[%d]) != CLASS_XFORM)\n", i, i);
fprintf(fd, "      {\n");
fprintf(fd, "        DXSetError(ERROR_DATA_INVALID,\n");
fprintf(fd, "	            \"structure of \\\"%s\\\" doesn't match that of \\\"%s\\\"\");\n",
			    in[i]->name, in[0]->name);
fprintf(fd, "        return ERROR;\n");
fprintf(fd, "      }\n\n");
	}
}
else
fprintf(fd, "\n");

fprintf(fd, "      /*\n");
fprintf(fd, "       * Create new in and out lists for the decendent of the\n");
fprintf(fd, "       * first input.  For inputs and outputs that are Values\n");
fprintf(fd, "       * copy them into the new in and out lists.  Otherwise\n");
fprintf(fd, "       * get the corresponding decendents.\n");
fprintf(fd, "       */\n\n");
for (i = 0; i < nin; i++)
    if (in[i]->structure == VALUE)
    {
fprintf(fd, "      /* input \"%s\" is Value */\n", in[i]->name);
fprintf(fd, "      new_in[%d] = in[%d];\n\n", i, i);
    }
    else
    {
fprintf(fd, "      /* input \"%s\" is Field/Group */\n", in[i]->name);
fprintf(fd, "      if (in[%d])\n", i);
fprintf(fd, "        DXGetXformInfo((Xform)in[%d], &new_in[%d], NULL);\n", i, i);
fprintf(fd, "      else\n");
fprintf(fd, "        new_in[%d] = NULL;\n", i);
fprintf(fd, "\n");
    }
fprintf(fd, "      /*\n");
fprintf(fd, "       * For all outputs that are Values, copy them to \n");
fprintf(fd, "       * child object list.  For all that are Field/Group,  get\n");
fprintf(fd, "       * the appropriate decendent and place it into the\n");
fprintf(fd, "       * child output object list.  Note that none should\n");
fprintf(fd, "       * be NULL (unlike inputs, which can default).\n");
fprintf(fd, "       */\n\n");
for (i = 0; i < nout; i++)
    if (out[i]->structure == VALUE)
    {
fprintf(fd, "      /* output \"%s\" is Value */\n", out[i]->name);
fprintf(fd, "      new_out[%d] = out[%d];\n\n", i, i);
    }
    else
    {
fprintf(fd, "      /* output \"%s\" is Field/Group */\n", out[i]->name);
fprintf(fd, "      DXGetXformInfo((Xform)out[%d], &new_out[%d], NULL);\n\n", i,i);
    }
fprintf(fd, "      if (! traverse(new_in, new_out))\n");
fprintf(fd, "        return ERROR;\n");
fprintf(fd, "\n");

if (n_GF_out)
{
fprintf(fd, "      /*\n");
fprintf(fd, "       * Now for each output that is not a Value replace\n");
fprintf(fd, "       * the updated child into the object in the parent.\n");
fprintf(fd, "       */\n\n");
    for (i = 0; i < nout; i++)
	if (out[i]->structure == GROUP_FIELD) 
	{
fprintf(fd, "      /* output \"%s\" is Field/Group */\n", out[i]->name);
fprintf(fd, "      DXSetXformObject((Xform)out[%d], new_out[%d]);\n\n", i, i);
	}
}

fprintf(fd, "      return OK;\n");
fprintf(fd, "    }\n");
fprintf(fd, "\n");
fprintf(fd, "    case CLASS_SCREEN:\n");
fprintf(fd, "    {\n");
fprintf(fd, "      int    i, j;\n");
fprintf(fd, "      Object new_in[%d], new_out[%d];\n", nin, nout);
fprintf(fd, "\n");
if (n_GF_in > 1)
{
fprintf(fd, "      /*\n");
fprintf(fd, "       * All inputs that are not NULL and are type Field/Group must\n");
fprintf(fd, "       * match the structure of input[0].  Verify that this is so.\n");
fprintf(fd, "       */\n\n");
    for (i = 1; i < nin; i++)
	if (in[i]->structure == GROUP_FIELD)
	{
fprintf(fd, "       if (in[%d] && DXGetObjectClass(in[%d]) != CLASS_SCREEN)\n", i, i);
fprintf(fd, "       {\n");
fprintf(fd, "           DXSetError(ERROR_DATA_INVALID,\n");
fprintf(fd, "	            \"structure of \\\"%s\\\" doesn't match that of \\\"%s\\\"\");\n",
			    in[i]->name, in[0]->name);
fprintf(fd, "           return ERROR;\n");
fprintf(fd, "       }\n\n");
	}
}
else
fprintf(fd, "\n");

fprintf(fd, "      /*\n");
fprintf(fd, "       * Create new in and out lists for the decendent of the\n");
fprintf(fd, "       * first input.  For inputs and outputs that are Values\n");
fprintf(fd, "       * copy them into the new in and out lists.  Otherwise\n");
fprintf(fd, "       * get the corresponding decendents.\n");
fprintf(fd, "       */\n\n");
for (i = 0; i < nin; i++)
    if (in[i]->structure == VALUE)
    {
fprintf(fd, "      /* input \"%s\" is Value */\n", in[i]->name);
fprintf(fd, "      new_in[%d] = in[%d];\n\n", i, i);
    }
    else
    {
fprintf(fd, "      /* input \"%s\" is Field/Group */\n", in[i]->name);
fprintf(fd, "      if (in[%d])\n", i);
fprintf(fd, "        DXGetScreenInfo((Screen)in[%d], &new_in[%d], NULL, NULL);\n",i,i);
fprintf(fd, "      else\n");
fprintf(fd, "        new_in[%d] = NULL;\n\n", i);
    }
fprintf(fd, "\n");
fprintf(fd, "      /*\n");
fprintf(fd, "       * For all outputs that are Values, copy them to \n");
fprintf(fd, "       * child object list.  For all that are Field/Group,  get\n");
fprintf(fd, "       * the appropriate decendent and place it into the\n");
fprintf(fd, "       * child output object list.  Note that none should\n");
fprintf(fd, "       * be NULL (unlike inputs, which can default).\n");
fprintf(fd, "       */\n\n");
for (i = 0; i < nout; i++)
    if (out[i]->structure == VALUE)
    {
fprintf(fd, "       /* output \"%s\" is Value */\n", out[i]->name);
fprintf(fd, "       new_out[%d] = out[%d];\n\n", i, i);
    }
    else
    {
fprintf(fd, "       /* output \"%s\" is Field/Group */\n", out[i]->name);
fprintf(fd, "       DXGetScreenInfo((Screen)out[%d], &new_out[%d], NULL, NULL);\n\n", i,i);
    }

fprintf(fd, "       if (! traverse(new_in, new_out))\n");
fprintf(fd, "         return ERROR;\n");
fprintf(fd, "\n");

if (n_GF_out)
{
fprintf(fd, "      /*\n");
fprintf(fd, "       * Now for each output that is not a Value, replace\n");
fprintf(fd, "       * the updated child into the object in the parent.\n");
fprintf(fd, "       */\n\n");
for (i = 0; i < nout; i++)
    if (out[i]->structure == GROUP_FIELD)
    {
fprintf(fd, "      /* output \"%s\" is Field/Group */\n", out[i]->name);
fprintf(fd, "       DXSetScreenObject((Screen)out[%d], new_out[%d]);\n\n", i,i);
    }
}

fprintf(fd, "       return OK;\n");
fprintf(fd, "     }\n");
fprintf(fd, "\n");
fprintf(fd, "     case CLASS_CLIPPED:\n");
fprintf(fd, "     {\n");
fprintf(fd, "       int    i, j;\n");
fprintf(fd, "       Object new_in[%d], new_out[%d];\n", nin, nout);
fprintf(fd, "\n");
if (n_GF_in > 1)
{
fprintf(fd, "      /*\n");
fprintf(fd, "       * All inputs that are not NULL and are type Field/Group must\n");
fprintf(fd, "       * match the structure of input[0].  Verify that this is so.\n");
fprintf(fd, "       */\n\n");
    for (i = 1; i < nin; i++)
	if (in[i]->structure == GROUP_FIELD)
	{
fprintf(fd, "       if (in[%d] && DXGetObjectClass(in[%d]) != CLASS_CLIPPED)\n", i, i);
fprintf(fd, "       {\n");
fprintf(fd, "           DXSetError(ERROR_DATA_INVALID,\n");
fprintf(fd, "               \"mismatching Field/Group objects\");\n");
fprintf(fd, "           return ERROR;\n");
fprintf(fd, "       }\n\n");
	}
}
else
fprintf(fd, "\n");

for (i = 0; i < nin; i++)
    if (in[i]->structure == VALUE)
    {
fprintf(fd, "       /* input \"%s\" is Value */\n", in[i]->name);
fprintf(fd, "       new_in[%d] = in[%d];\n\n", i, i);
    }
    else
    {
fprintf(fd, "       /* input \"%s\" is Field/Group */\n", in[i]->name);
fprintf(fd, "       if (in[%d])\n", i);
fprintf(fd, "         DXGetClippedInfo((Clipped)in[%d], &new_in[%d], NULL);\n",i,i);
fprintf(fd, "       else\n");
fprintf(fd, "         new_in[%d] = NULL;\n\n", i);
    }
fprintf(fd, "\n");
fprintf(fd, "      /*\n");
fprintf(fd, "       * For all outputs that are Values, copy them to \n");
fprintf(fd, "       * child object list.  For all that are Field/Group,  get\n");
fprintf(fd, "       * the appropriate decendent and place it into the\n");
fprintf(fd, "       * child output object list.  Note that none should\n");
fprintf(fd, "       * be NULL (unlike inputs, which can default).\n");
fprintf(fd, "       */\n\n");
for (i = 0; i < nout; i++)
    if (out[i]->structure == VALUE)
    {
fprintf(fd, "       /* output \"%s\" is Value */\n", out[i]->name);
fprintf(fd, "       new_out[%d] = out[%d];\n\n", i, i);
    }
    else
    {
fprintf(fd, "       /* output \"%s\" is Field/Group */\n", out[i]->name);
fprintf(fd, "       DXGetClippedInfo((Clipped)out[%d], &new_out[%d], NULL);\n\n", i,i);
    }

fprintf(fd, "       if (! traverse(new_in, new_out))\n");
fprintf(fd, "         return ERROR;\n");
fprintf(fd, "\n");

if (n_GF_out)
{
fprintf(fd, "      /*\n");
fprintf(fd, "       * Now for each output that is not a Value, replace\n");
fprintf(fd, "       * the updated child into the object in the parent.\n");
fprintf(fd, "       */\n\n");
for (i = 0; i < nout; i++)
    if (out[i]->structure == GROUP_FIELD)
    {
fprintf(fd, "       /* output \"%s\" is Field/Group */\n", out[i]->name);
fprintf(fd, "       DXSetClippedObjects((Clipped)out[%d], new_out[%d], NULL);\n\n", i, i);
    }
}

fprintf(fd, "       return OK;\n");
fprintf(fd, "     }\n");
fprintf(fd, "\n");
fprintf(fd, "     default:\n");
fprintf(fd, "     {\n");
fprintf(fd, "       DXSetError(ERROR_BAD_CLASS, ");
fprintf(fd, "\"encountered in object traversal\");\n");
fprintf(fd, "       return ERROR;\n");
fprintf(fd, "     }\n");
fprintf(fd, "  }\n");
fprintf(fd, "}\n");
fprintf(fd, "\n");


fprintf(fd, "static int\n");
fprintf(fd, "doLeaf(Object *in, Object *out)\n");
fprintf(fd, "{\n");
fprintf(fd, "  int i, result=0;\n");
fprintf(fd, "  Array array;\n");
fprintf(fd, "  Field field;\n");
fprintf(fd, "  Pointer *in_data[%d], *out_data[%d];\n", nin, nout);
fprintf(fd, "  int in_knt[%d], out_knt[%d];\n", nin, nout);
fprintf(fd, "  Type type;\n");
fprintf(fd, "  Category category;\n");
fprintf(fd, "  int rank, shape;\n");
fprintf(fd, "  Object attr, src_dependency_attr = NULL;\n");
fprintf(fd, "  char *src_dependency = NULL;\n");
  if (in[0]->elementtype != ELT_NOT_REQUIRED)
  {
fprintf(fd, "  Object element_type_attr;\n");
fprintf(fd, "  char *element_type;\n");
  }

  if (in[0]->positions == GRID_REGULAR)
  {
fprintf(fd, "  /*\n");
fprintf(fd, "   * Regular positions info\n");
fprintf(fd, "   */\n");
fprintf(fd, "  int p_knt = -1, p_dim, *p_counts = NULL;\n");
fprintf(fd, "  float *p_origin = NULL, *p_deltas = NULL;\n");
  }
  else if (in[0]->positions == GRID_IRREGULAR)
  {
fprintf(fd, "  /*\n");
fprintf(fd, "   * Irregular positions info\n");
fprintf(fd, "   */\n");
fprintf(fd, "  int p_knt, p_dim;\n");
fprintf(fd, "  float *p_positions;\n");
  }
  else
fprintf(fd, "  int p_knt = -1;\n");

  if (in[0]->connections == GRID_REGULAR)
  {
fprintf(fd, "  /*\n");
fprintf(fd, "   * Regular connections info\n");
fprintf(fd, "   */\n");
fprintf(fd, "  int c_knt, c_nv, c_dim, *c_counts = NULL;\n");
  }
  else if (in[0]->connections == GRID_IRREGULAR)
  {
fprintf(fd, "  /*\n");
fprintf(fd, "   * Irregular connections info\n");
fprintf(fd, "   */\n");
fprintf(fd, "  int c_knt, c_dim, c_nv;\n");
fprintf(fd, "  float *c_connections;\n");
  }
  else
fprintf(fd, "  int c_knt = -1;\n");

fprintf(fd, "\n");

if (in[0]->connections != GRID_NOT_REQUIRED ||
    in[0]->positions   != GRID_NOT_REQUIRED)
{ 
fprintf(fd, "  /*\n");
fprintf(fd, "   * positions and/or connections are required, so the first must\n");
fprintf(fd, "   * be a field.\n");
fprintf(fd, "   */\n");
fprintf(fd, "  if (DXGetObjectClass(in[0]) != CLASS_FIELD)\n");
fprintf(fd, "  {\n");
fprintf(fd, "      DXSetError(ERROR_DATA_INVALID,\n");
fprintf(fd, "           \"positions and/or connections unavailable in array object\");\n");
fprintf(fd, "      goto error;\n");
fprintf(fd, "  }\n");
fprintf(fd, "  else\n");
}
else
fprintf(fd, "  if (DXGetObjectClass(in[0]) == CLASS_FIELD)\n");

fprintf(fd, "  {\n");
fprintf(fd, "\n");
fprintf(fd, "    field = (Field)in[0];\n");
fprintf(fd, "\n");
fprintf(fd, "    if (DXEmptyField(field))\n");
fprintf(fd, "      return OK;\n");
fprintf(fd, "\n");
fprintf(fd, "    /* \n");
fprintf(fd, "     * Determine the dependency of the source object's data\n");
fprintf(fd, "     * component.\n");
fprintf(fd, "     */\n");
fprintf(fd, "    src_dependency_attr = DXGetComponentAttribute(field, \"data\", \"dep\");\n");
fprintf(fd, "    if (! src_dependency_attr)\n");
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_MISSING_DATA, \"\\\"%s\\\" data component is missing a dependency attribute\");\n", in[0]->name);
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n");
fprintf(fd, "\n");
fprintf(fd, "    if (DXGetObjectClass(src_dependency_attr) != CLASS_STRING)\n");
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_BAD_CLASS, \"\\\"%s\\\" dependency attribute\");\n", in[0]->name);
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n");
fprintf(fd, "\n");
fprintf(fd, "    src_dependency = DXGetString((String)src_dependency_attr);\n");
fprintf(fd, "\n");
fprintf(fd, "    array = (Array)DXGetComponentValue(field, \"positions\");\n");
fprintf(fd, "    if (! array)\n");
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_BAD_CLASS, \"\\\"%s\\\" contains no positions component\");\n", in[0]->name);
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n");
fprintf(fd, "\n");
    if (in[0]->positions == GRID_REGULAR)
    {
fprintf(fd, "    /* \n");
fprintf(fd, "     * Input[0] should have regular positions.  First check\n");
fprintf(fd, "     * that they are, and while you're at it, get the\n");
fprintf(fd, "     * dimensionality so we can size arrays later.\n");
fprintf(fd, "     */\n");
fprintf(fd, "    if (! DXQueryGridPositions(array, &p_dim, NULL, NULL, NULL))\n");
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_BAD_CLASS, \"\\\"%s\\\" positions component is not regular\");\n", in[0]->name);
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n");
fprintf(fd, "\n");
fprintf(fd, "    /* \n");
fprintf(fd, "     * Allocate arrays for position counts, origin and deltas.\n");
fprintf(fd, "     * Check that the allocations worked, then get the info.\n");
fprintf(fd, "     */\n");
fprintf(fd, "    p_counts = (int   *)DXAllocate(p_dim*sizeof(int));\n");
fprintf(fd, "    p_origin = (float *)DXAllocate(p_dim*sizeof(float));\n");
fprintf(fd, "    p_deltas = (float *)DXAllocate(p_dim*p_dim*sizeof(float));\n");
fprintf(fd, "    if (! p_counts || ! p_origin || ! p_deltas)\n");
fprintf(fd, "      goto error;\n");
fprintf(fd, "\n");
fprintf(fd, "    DXQueryGridPositions(array, NULL, p_counts, p_origin, p_deltas);\n");
fprintf(fd, "    DXGetArrayInfo(array, &p_knt, NULL, NULL, NULL, NULL);\n");
fprintf(fd, "\n");
    }
    else if (in[0]->positions == GRID_IRREGULAR)
    {
fprintf(fd, "    /* \n");
fprintf(fd, "     * The user requested irregular positions.  So we\n");
fprintf(fd, "     * get the count, the dimensionality and a pointer to the\n");
fprintf(fd, "     * explicitly enumerated positions.  If the positions\n");
fprintf(fd, "     * are in fact regular, this will expand them.\n");
fprintf(fd, "     */\n");
fprintf(fd, "    DXGetArrayInfo(array, &p_knt, NULL, NULL, NULL, &p_dim);\n");
fprintf(fd, "\n");
fprintf(fd, "    p_positions = (float *)DXGetArrayData(array);\n");
fprintf(fd, "    if (! p_positions)\n");
fprintf(fd, "      goto error;\n");
fprintf(fd, "\n");
    }
    else
fprintf(fd, "    DXGetArrayInfo(array, &p_knt, NULL, NULL, NULL, NULL);\n");

    if (in[0]->connections == GRID_REGULAR ||
        in[0]->connections == GRID_IRREGULAR ||
	in[0]->elementtype != ELT_NOT_REQUIRED)
    {
fprintf(fd, "    array = (Array)DXGetComponentValue(field, \"connections\");\n");
fprintf(fd, "    if (! array)\n");
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_BAD_CLASS, \"\\\"%s\\\" contains no connections component\");\n", in[0]->name);
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n");
fprintf(fd, "\n");

	if (in[0]->elementtype != ELT_NOT_REQUIRED)
	{
	    char *str;

	    if (! GetElementTypeString(in[0]->elementtype, &str))
		goto error;

fprintf(fd, "    /*\n");
fprintf(fd, "     * Check that the field's element type matches that requested\n");
fprintf(fd, "     */\n");
fprintf(fd, "    element_type_attr = DXGetAttribute((Object)array, \"element type\");\n");
fprintf(fd, "    if (! element_type_attr)\n");
fprintf(fd, "    {\n");
fprintf(fd, "        DXSetError(ERROR_DATA_INVALID,\n");
fprintf(fd, "            \"input \\\"%s\\\" has no element type attribute\");\n", in[0]->name);
fprintf(fd, "        goto error;\n");
fprintf(fd, "    }\n\n");
fprintf(fd, "    if (DXGetObjectClass(element_type_attr) != CLASS_STRING)\n");
fprintf(fd, "    {\n");
fprintf(fd, "        DXSetError(ERROR_DATA_INVALID,\n");
fprintf(fd, "            \"input \\\"%s\\\" element type attribute is not a string\");\n", in[0]->name);
fprintf(fd, "        goto error;\n");
fprintf(fd, "    }\n\n");
fprintf(fd, "    if (strcmp(DXGetString((String)element_type_attr), \"%s\"))\n", str);
fprintf(fd, "    {\n");
fprintf(fd, "        DXSetError(ERROR_DATA_INVALID,\n");
fprintf(fd, "            \"input \\\"%s\\\" invalid element type\");\n", in[0]->name);
fprintf(fd, "        goto error;\n");
fprintf(fd, "    }\n\n");
	}

	if (in[0]->connections == GRID_REGULAR)
	{
fprintf(fd, "    /* \n");
fprintf(fd, "     * Input[0] should have regular connections.  First check\n");
fprintf(fd, "     * that they are, and while you're at it, get the\n");
fprintf(fd, "     * dimensionality so we can size an array later.\n");
fprintf(fd, "     */\n");
fprintf(fd, "    if (! DXQueryGridConnections(array, &c_dim, NULL))\n");
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_BAD_CLASS, \"\\\"%s\\\" connections component is not regular\");\n", in[0]->name);
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n");
fprintf(fd, "\n");
fprintf(fd, "    /* \n");
fprintf(fd, "     * Allocate arrays for connections counts.\n");
fprintf(fd, "     * Check that the allocation worked, then get the info.\n");
fprintf(fd, "     */\n");
fprintf(fd, "    c_counts = (int   *)DXAllocate(c_dim*sizeof(int));\n");
fprintf(fd, "    if (! c_counts)\n");
fprintf(fd, "      goto error;\n");
fprintf(fd, "\n");
fprintf(fd, "    DXQueryGridConnections(array, NULL, c_counts);\n");
fprintf(fd, "    DXGetArrayInfo(array, &c_knt, NULL, NULL, NULL, &c_nv);\n");
fprintf(fd, "\n");
	}
	else if (in[0]->connections == GRID_IRREGULAR)
	{
fprintf(fd, "    /* \n");
fprintf(fd, "     * The user requested irregular connections.  So we\n");
fprintf(fd, "     * get the count, the dimensionality and a pointer to the\n");
fprintf(fd, "     * explicitly enumerated elements.  If the positions\n");
fprintf(fd, "     * are in fact regular, this will expand them.\n");
fprintf(fd, "     */\n");
fprintf(fd, "    DXGetArrayInfo(array, &c_knt, NULL, NULL, NULL, &c_nv);\n");
fprintf(fd, "\n");
fprintf(fd, "    c_connections = (float *)DXGetArrayData(array);\n");
fprintf(fd, "    if (! c_connections)\n");
fprintf(fd, "      goto error;\n");
fprintf(fd, "\n");
	}
	else
fprintf(fd, "    DXGetArrayInfo(array, &c_knt, NULL, NULL, NULL, NULL);\n");
    }
    else
    {
fprintf(fd, "    /* \n");
fprintf(fd, "     * If there are connections, get their count so that\n");
fprintf(fd, "     * connections-dependent result arrays can be sized.\n");
fprintf(fd, "     */\n");
fprintf(fd, "    array = (Array)DXGetComponentValue(field, \"connections\");\n");
fprintf(fd, "    if (array)\n");
fprintf(fd, "        DXGetArrayInfo(array, &c_knt, NULL, NULL, NULL, NULL);\n");
    }

fprintf(fd, "  }\n");

  for (i = 0; i < nin; i++)
  {
    char *type, *rank, *shape;

    if (! GetDXDataType(in[i]->datatype, &type) ||
          ! GetDXDataShape(in[i]->datashape, &rank, &shape))
          goto error;


fprintf(fd, "  /*\n");
fprintf(fd, "   * If the input argument is not NULL then we get the \n");
fprintf(fd, "   * data array: either the object itself, if its an \n");
fprintf(fd, "   * array, or the data component if the argument is a field\n");
fprintf(fd, "   */\n");
fprintf(fd, "  if (! in[%d])\n", i);
fprintf(fd, "  {\n");
fprintf(fd, "    array = NULL;\n");
fprintf(fd, "    in_data[%d] = NULL;\n", i);
fprintf(fd, "    in_knt[%d] = NULL;\n", i);
fprintf(fd, "  }\n");
fprintf(fd, "  else\n");
fprintf(fd, "  {\n");
fprintf(fd, "    if (DXGetObjectClass(in[%d]) == CLASS_ARRAY)\n", i);
fprintf(fd, "    {\n");
fprintf(fd, "      array = (Array)in[%d];\n", i);
fprintf(fd, "    }\n");
fprintf(fd, "    else if (DXGetObjectClass(in[%d]) == CLASS_STRING)\n", i);
fprintf(fd, "    {\n");
fprintf(fd, "      in_data[%d] = (Pointer *)DXGetString((String)in[%d]);\n",i,i);
fprintf(fd, "      in_knt[%d] = 1;\n",i); 
fprintf(fd, "    }\n");
fprintf(fd, "    else\n");
fprintf(fd, "    {\n");
fprintf(fd, "      if (DXGetObjectClass(in[%d]) != CLASS_FIELD)\n", i);
fprintf(fd, "      {\n");
fprintf(fd, "        DXSetError(ERROR_BAD_CLASS, \"\\\"%s\\\" should be a field\");\n", in[i]->name);
fprintf(fd, "        goto error;\n");
fprintf(fd, "      }\n");
fprintf(fd, "\n");
fprintf(fd, "      array = (Array)DXGetComponentValue((Field)in[%d], \"data\");\n", i);
fprintf(fd, "      if (! array)\n");
fprintf(fd, "      {\n");
fprintf(fd, "        DXSetError(ERROR_MISSING_DATA, \"\\\"%s\\\" has no data component\");\n", in[i]->name);
fprintf(fd, "        goto error;\n");
fprintf(fd, "      }\n");
fprintf(fd, "\n");
fprintf(fd, "      if (DXGetObjectClass((Object)array) != CLASS_ARRAY)\n");
fprintf(fd, "      {\n");
fprintf(fd, "        DXSetError(ERROR_BAD_CLASS, \"data component of \\\"%s\\\" should be an array\");\n", in[i]->name);
fprintf(fd, "        goto error;\n");
fprintf(fd, "      }\n");
fprintf(fd, "    }\n");
fprintf(fd, "\n");

      if (in[i]->dependency != NO_DEPENDENCY)
      {
fprintf(fd, "    /* \n");
fprintf(fd, "     * get the dependency of the data component\n");
fprintf(fd, "     */\n");
fprintf(fd, "    attr = DXGetAttribute((Object)array, \"dep\");\n");
fprintf(fd, "    if (! attr)\n");
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_MISSING_DATA, \"data component of \\\"%s\\\" has no dependency\");\n", in[i]->name);
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n");
fprintf(fd, "\n");
fprintf(fd, "    if (DXGetObjectClass(attr) != CLASS_STRING)\n");
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_BAD_CLASS, \"dependency attribute of data component of \\\"%s\\\"\");\n", in[i]->name);
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n");
fprintf(fd, "\n");
	if (in[i]->dependency == DEP_INPUT && i != 0)
	{
fprintf(fd, "  /*\n");
fprintf(fd, "   * The dependency of this arg should match input[0].\n");
fprintf(fd, "   */\n"); 
fprintf(fd, "    if (strcmp(src_dependency, DXGetString((String)attr)))\n");
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_DATA_INVALID, \"data dependency of \\\"%s\\\" must match \\\"%s\\\"\");\n",
						in[i]->name, in[0]->name);
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n");
	}
	else if (in[i]->dependency == DEP_POSITIONS)
	{
fprintf(fd, "  /*\n");
fprintf(fd, "   * The dependency of this arg should be positions\n");
fprintf(fd, "   */\n"); 
fprintf(fd, "    if (strcmp(\"positions\", DXGetString((String)attr)))\n");
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_DATA_INVALID, \"data dependency of \\\"%s\\\" must be positions\");\n",
						in[i]->name);
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n");
	}
	else if (in[i]->dependency == DEP_CONNECTIONS)
	{
fprintf(fd, "  /*\n");
fprintf(fd, "   * The dependency of this arg should be connections\n");
fprintf(fd, "   */\n"); 
fprintf(fd, "    if (strcmp(\"connections\", DXGetString((String)attr)))\n");
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_DATA_INVALID, \"data dependency of \\\"%s\\\" must be connections\");\n",
						in[i]->name);
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n");
	}
      }
fprintf(fd, "\n");
fprintf(fd, "    if (DXGetObjectClass(in[%d]) != CLASS_STRING)", i);
fprintf(fd, "    {\n");
fprintf(fd, "       DXGetArrayInfo(array, &in_knt[%d], &type, &category, &rank, &shape);\n", i);
fprintf(fd, "       if (type != %s || category != CATEGORY_REAL ||\n", type);

  if (! strcmp(rank, "0"))
fprintf(fd, "             !((rank == 0) || ((rank == 1)&&(shape == 1))))\n");
  else
fprintf(fd, "           rank != %s || shape != %s)\n", rank, shape);

fprintf(fd, "       {\n");
fprintf(fd, "         DXSetError(ERROR_DATA_INVALID, \"input \\\"%s\\\"\");\n", in[i]->name);
fprintf(fd, "         goto error;\n");
fprintf(fd, "       }\n");
fprintf(fd, "\n");
fprintf(fd, "       in_data[%d] = DXGetArrayData(array);\n", i);
fprintf(fd, "       if (! in_data[%d])\n", i);
fprintf(fd, "          goto error;\n");
fprintf(fd, "\n");
fprintf(fd, "    }\n");
fprintf(fd, "  }\n");
    }

  for (i = 0; i < nout; i++)
  {
    char *type, *rank, *shape;

    if (! GetDXDataType(out[i]->datatype, &type) ||
	! GetDXDataShape(out[i]->datashape, &rank, &shape))
	goto error;

    if (out[i]->structure == VALUE)
    {
fprintf(fd, "  if (! out[%d])\n", i);
fprintf(fd, "  {\n");
fprintf(fd, "    DXSetError(ERROR_INTERNAL, \"Value output %d (\\\"%s\\\") is NULL\");\n", i, out[i]->name);
fprintf(fd, "    goto error;\n");
fprintf(fd, "  }\n");
fprintf(fd, "  if (DXGetObjectClass(out[%d]) != CLASS_ARRAY)\n", i);
fprintf(fd, "  {\n");
fprintf(fd, "    DXSetError(ERROR_INTERNAL, \"Value output %d (\\\"%s\\\") is not an array\");\n", i, out[i]->name);
fprintf(fd, "    goto error;\n");
fprintf(fd, "  }\n");
fprintf(fd, "\n");
fprintf(fd, "  array = (Array)out[%d];\n", i);
fprintf(fd, "\n");
fprintf(fd, "  DXGetArrayInfo(array, &out_knt[%d], &type, &category, &rank, &shape);\n", i);
fprintf(fd, "  if (type != %s || category != CATEGORY_REAL ||\n", type);
	if (out[i]->datashape == SCALAR)
fprintf(fd, "      !((rank == 0) || ((rank == 1)&&(shape == 1))))\n");
	else
fprintf(fd, "      rank != %s || shape != %s)\n", rank, shape);
fprintf(fd, "  {\n");
fprintf(fd, "    DXSetError(ERROR_DATA_INVALID, \"Value output \\\"%s\\\" has bad type\");\n", out[i]->name);
fprintf(fd, "    goto error;\n");
fprintf(fd, "  }\n");
fprintf(fd, "\n");
    }
    else
    {
fprintf(fd, "  /*\n");
fprintf(fd, "   * Create an output data array typed according to the\n");
fprintf(fd, "   * specification given\n");
fprintf(fd, "   */\n");
fprintf(fd, "  array = DXNewArray(%s, CATEGORY_REAL, %s, %s);\n", type, rank, shape);
fprintf(fd, "  if (! array)\n");
fprintf(fd, "    goto error;\n");
fprintf(fd, "\n");
      if (out[i]->dependency == DEP_INPUT)
      {
fprintf(fd, "  /*\n");
fprintf(fd, "   * Set the dependency of the array to the same as the first input\n");
fprintf(fd, "   */\n");
fprintf(fd, "  if (src_dependency_attr != NULL)\n");
fprintf(fd, "    if (! DXSetAttribute((Object)array, \"dep\", src_dependency_attr))\n");
fprintf(fd, "      goto error;\n\n");
fprintf(fd, "  /*\n");
fprintf(fd, "   * The size and dependency of this output data array will \n");
fprintf(fd, "   * match that of input[0]\n");
fprintf(fd, "   */\n");
fprintf(fd, "  out_knt[%d] = in_knt[0];\n", i);
      }
      else if (out[i]->dependency == DEP_POSITIONS)
      {
fprintf(fd, "  /*\n");
fprintf(fd, "   * This output data array will be dep positions - and sized\n");
fprintf(fd, "   * appropriately - if the appropriate size is known\n");
fprintf(fd, "   */\n");
fprintf(fd, "  if (p_knt == -1)\n");
fprintf(fd, "  {\n");
fprintf(fd, "    DXSetError(ERROR_DATA_INVALID,\n");
fprintf(fd, "      \"cannot make output \\\"%s\\\" dep on positions because no positions were found in input[0]\");\n", out[i]->name);
fprintf(fd, "    goto error;\n");
fprintf(fd, "  }\n\n");
fprintf(fd, "  out_knt[%d] = p_knt;\n", i);
fprintf(fd, "\n");
fprintf(fd, "  if (! DXSetAttribute((Object)array, \"dep\", (Object)DXNewString(\"positions\")))\n");
fprintf(fd, "    goto error;\n");
      }
      else if (out[i]->dependency == DEP_CONNECTIONS)
      {
fprintf(fd, "  /*\n");
fprintf(fd, "   * This output data array will be dep connections - and sized\n");
fprintf(fd, "   * appropriately - if the appropriate size is known\n");
fprintf(fd, "   */\n");
fprintf(fd, "  if (c_knt == -1)\n");
fprintf(fd, "  {\n");
fprintf(fd, "    DXSetError(ERROR_DATA_INVALID,\n");
fprintf(fd, "      \"cannot make output \\\"%s\\\" dep on connections because no connections were found in input \\\"%s\\\"\");\n", out[i]->name, in[i]->name);
fprintf(fd, "    goto error;\n");
fprintf(fd, "  }\n\n");
fprintf(fd, "  out_knt[%d] = c_knt;\n", i);
fprintf(fd, "\n");
fprintf(fd, "  if (! DXSetAttribute((Object)array, \"dep\", (Object)DXNewString(\"connections\")))\n");
fprintf(fd, "    goto error;\n");
      }
      else
      {
	ErrorMessage("field parameter must have a dependency set\n");
	goto error;
      }

fprintf(fd, "  /*\n");
fprintf(fd, "   * Actually allocate the array data space\n");
fprintf(fd, "   */\n");
fprintf(fd, "  if (! DXAddArrayData(array, 0, out_knt[%d], NULL))\n", i);
fprintf(fd, "    goto error;\n");
fprintf(fd, "\n");
fprintf(fd, "  /*\n");
fprintf(fd, "   * If the output vector slot is not NULL, then it better be a field, and\n");
fprintf(fd, "   * we'll add the new array to it as its data component (delete any prior\n");
fprintf(fd, "   * data component so that its attributes won't overwrite the new component's)\n");
fprintf(fd, "   * Otherwise, place the new array into the out vector.\n");
fprintf(fd, "   */\n");
fprintf(fd, "  if (out[%d])\n", i);
fprintf(fd, "  {\n");
fprintf(fd, "    if (DXGetObjectClass(out[%d]) != CLASS_FIELD)\n", i);
fprintf(fd, "    {\n");
fprintf(fd, "      DXSetError(ERROR_INTERNAL, \"non-field object found in output vector\");\n");
fprintf(fd, "      goto error;\n");
fprintf(fd, "    }\n\n");
fprintf(fd, "    if (DXGetComponentValue((Field)out[%d], \"data\"))\n", i);
fprintf(fd, "      DXDeleteComponent((Field)out[%d], \"data\");\n\n", i);
fprintf(fd, "    if (! DXSetComponentValue((Field)out[%d], \"data\", (Object)array))\n", i);
fprintf(fd, "      goto error;\n");
fprintf(fd, "\n");
fprintf(fd, "  }\n");
fprintf(fd, "  else\n");
fprintf(fd, "    out[%d] = (Object)array;\n", i);
    }

fprintf(fd, "  /*\n");
fprintf(fd, "   * Now get the pointer to the contents of the array\n");
fprintf(fd, "   */\n");
fprintf(fd, "  out_data[%d] = DXGetArrayData(array);\n", i);
fprintf(fd, "  if (! out_data[%d])\n", i);
fprintf(fd, "    goto error;\n");
fprintf(fd, "\n");
  }
fprintf(fd, "  /*\n");
fprintf(fd, "   * Call the user's routine.  Check the return code.\n");
fprintf(fd, "   */\n");
fprintf(fd, "  result = %s_worker(\n", mod->name);

    open = 0;

    if (in[0]->positions == GRID_REGULAR)
    {
fprintf(fd, "    p_knt, p_dim, p_counts, p_origin, p_deltas");
	open = 1;
    }
    else if (in[0]->positions == GRID_IRREGULAR)
    {
fprintf(fd, "    p_knt, p_dim, (float *)p_positions");
	open = 1;
    }

    if (in[0]->connections == GRID_REGULAR)
    {
fprintf(fd, "%s    c_knt, c_nv, c_counts", (open)?",\n":"");
	open = 1;
    }
    else if (in[0]->connections == GRID_IRREGULAR)
    {
fprintf(fd, "%s    c_knt, c_nv, (int *)c_connections", (open)?",\n":"");
	open = 1;
    }

    for (i = 0; i < nin; i++)
    { 
	char *type;
	GetCDataType(in[i]->datatype, &type);
fprintf(fd, "%s    in_knt[%d], (%s *)in_data[%d]", (open)?",\n":"", i, type, i);
	open = 1;
    }

    for (i = 0; i < nout; i++)
    { 
	char *type;
	GetCDataType(out[i]->datatype, &type);
fprintf(fd, "%s    out_knt[%d], (%s *)out_data[%d]", (open)?",\n":"", i, type, i);
	open = 1;
    }

fprintf(fd, ");\n\n");
fprintf(fd, "  if (! result)\n");
fprintf(fd, "     if (DXGetError()==ERROR_NONE)\n");
fprintf(fd, "        DXSetError(ERROR_INTERNAL, \"error return from user routine\");\n");
fprintf(fd, "\n");
fprintf(fd, "  /*\n");
fprintf(fd, "   * In either event, clean up allocated memory\n");
fprintf(fd, "   */\n");
fprintf(fd, "\n");
fprintf(fd, "error:\n");
if (in[0]->positions == GRID_REGULAR)
{
fprintf(fd, "  /*\n");
fprintf(fd, "   * Free the arrays allocated for the regular positions\n");
fprintf(fd, "   * counts, origin and deltas\n");
fprintf(fd, "   */\n");
fprintf(fd, "  DXFree((Pointer)p_counts);\n");
fprintf(fd, "  DXFree((Pointer)p_origin);\n");
fprintf(fd, "  DXFree((Pointer)p_deltas);\n");
}
if (in[0]->connections == GRID_REGULAR)
{
fprintf(fd, "  /*\n");
fprintf(fd, "   * Free the arrays allocated for the regular connections\n");
fprintf(fd, "   * counts\n");
fprintf(fd, "   */\n");
fprintf(fd, "  DXFree((Pointer)c_counts);\n");
}
fprintf(fd, "  return result;\n");
fprintf(fd, "}\n\n");

fprintf(fd, "int\n%s_worker(\n", mod->name);
    
    open = 0;

    if (in[0]->positions == GRID_REGULAR)
    {
fprintf(fd, "    int p_knt, int p_dim, int *p_counts, float *p_origin, float *p_deltas");
	open = 1;
    }
    else if (in[0]->positions == GRID_IRREGULAR)
    {
fprintf(fd, "    int p_knt, int p_dim, float *p_positions");
	open = 1;
    }

    if (in[0]->connections == GRID_REGULAR)
    {
fprintf(fd, "%s    int c_knt, int c_nv, int *c_counts", (open)?",\n":"");
	open = 1;
    }
    else if (in[0]->connections == GRID_IRREGULAR)
    {
fprintf(fd, "%s    int c_knt, int c_nv, int *c_connections", (open)?",\n":"");
	open = 1;
    }

    for (i = 0; i < nin; i++)
    { 
	char *type;
	GetCDataType(in[i]->datatype, &type);
fprintf(fd, "%s    int %s_knt, %s *%s_data", (open)?",\n":"", in[i]->name, type, in[i]->name);
	open = 1;
    }

    for (i = 0; i < nout; i++)
    { 
	char *type;
	GetCDataType(out[i]->datatype, &type);
fprintf(fd, "%s    int %s_knt, %s *%s_data", (open)?",\n":"", out[i]->name, type, out[i]->name);
	open = 1;
    }

fprintf(fd, ")\n{\n");
fprintf(fd, "  /*\n");
fprintf(fd, "   * The arguments to this routine are:\n");
fprintf(fd, "   *\n");

    if (in[0]->positions == GRID_REGULAR)
    {
fprintf(fd, "   *  p_knt:           total count of input positions\n");
fprintf(fd, "   *  p_dim:           dimensionality of input positions\n");
fprintf(fd, "   *  p_counts:        count along each axis of regular positions grid\n");
fprintf(fd, "   *  p_origin:        origin of regular positions grid\n");
fprintf(fd, "   *  p_deltas:        regular positions delta vectors\n");
    }
    else if (in[0]->positions == GRID_IRREGULAR)
    {
fprintf(fd, "   *  p_knt:           total count of input positions\n");
fprintf(fd, "   *  p_dim:           dimensionality of input positions\n");
fprintf(fd, "   *  p_positions:     pointer to positions list\n");
    }

    if (in[0]->connections == GRID_REGULAR)
    {
fprintf(fd, "   *  c_knt:           total count of input connections elements\n");
fprintf(fd, "   *  c_nv:            number of vertices per element\n");
fprintf(fd, "   *  c_counts:        vertex count along each axis of regular positions grid\n");
    }
    else if (in[0]->connections == GRID_IRREGULAR)
    {
fprintf(fd, "   *  c_knt:           total count of input connections elements\n");
fprintf(fd, "   *  c_nv:            number of vertices per element\n");
fprintf(fd, "   *  c_connections:   pointer to connections list\n");
    }

fprintf(fd, "   *\n");
fprintf(fd, "   * The following are inputs and therefore are read-only.  The default\n");
fprintf(fd, "   * values are given and should be used if the knt is 0.\n");
fprintf(fd, "   *\n");
    for (i = 0; i < nin; i++)
    {
fprintf(fd, "   * %s_knt, %s_data:  count and pointer for input \"%s\"\n", in[i]->name, in[i]->name, in[i]->name);
	if (in[i]->default_value)
	    if (in[i]->descriptive == TRUE)
fprintf(fd, "   *                   descriptive default value is \"%s\"\n", in[i]->default_value);
	    else
fprintf(fd, "   *                   non-descriptive default value is \"%s\"\n", in[i]->default_value);
        else
fprintf(fd, "   *                   no default value given.\n");
    }

fprintf(fd, "   *\n");
fprintf(fd, "   *  The output data buffer(s) are writable.\n");
fprintf(fd, "   *  The output buffer(s) are preallocated based on\n");
fprintf(fd, "   *     the dependency (positions or connections),\n");
fprintf(fd, "   *     the size of the corresponding positions or\n");
fprintf(fd, "   *     connections component in the first input, and\n");
fprintf(fd, "   *     the data type.\n");
fprintf(fd, "   *\n");
    for (i = 0; i < nout; i++)
    {
fprintf(fd, "   * %s_knt, %s_data:  count and pointer for output \"%s\"\n",
				out[i]->name, out[i]->name, out[i]->name);
    }
fprintf(fd, "   */\n\n");
fprintf(fd, "  /*\n");
fprintf(fd, "   * User's code goes here\n");
fprintf(fd, "   */\n");
fprintf(fd, "     \n");
fprintf(fd, "     \n");
/* was an include file specified? */
if(mod->include_file != NULL)
	fprintf(fd, "#include \"%s\" \n\n", mod->include_file);
fprintf(fd, "  /*\n");
fprintf(fd, "   * successful completion\n");
fprintf(fd, "   */\n");
fprintf(fd, "   return 1;\n");
fprintf(fd, "     \n");
fprintf(fd, "  /*\n");
fprintf(fd, "   * unsuccessful completion\n");
fprintf(fd, "   */\n");
fprintf(fd, "error:\n");
fprintf(fd, "   return 0;\n");
fprintf(fd, "  \n}\n");

    fclose(fd);

    return 1;

error:
    if (fd)
    {
	fclose(fd);
	unlink(buf);
    }

    return 0;
}


#define COPYSTRING(dst, src)					\
{								\
    (dst) = (char *)malloc(strlen((src))+1);			\
    if ((dst) == NULL) {					\
	ErrorMessage("allocation error");			\
	goto error;						\
    }								\
								\
    strcpy((dst), (src));					\
}

#define TRUEFALSE(dst, src)					\
{								\
    if (! strcmp((src), "TRUE"))				\
	(dst) = TRUE;						\
    else if (! strcmp((src), "FALSE"))				\
	(dst) = FALSE;						\
    else {							\
	ErrorMessage("invalid true/false: %s\n", src);	\
	goto error;						\
    }								\
}

static int
copy_comments(char *basename, FILE *out, char *hdr, char *ldr, char *trlr)
{
    FILE *in = NULL;
    int  first_comment = 1, comment_found = 0;
    int  first_char = 1, is_comment;
    int  i, c;
    char *buf = (char *)malloc(strlen(basename) + 4);

    if (! buf)
    {
	ErrorMessage("allocation error");
	goto error;
    }

    sprintf(buf, "%s.mb", basename);

    in = fopen(buf, "r");
    if (! in)
    {
	ErrorMessage("error opening mb file");
	return 0;
    }

    while (! feof(in))
    {
	c = getc(in);

	if (first_char)
	    is_comment = (c == '#');
	
	if (is_comment)
	{
	    comment_found = 1;

	    if (first_comment && hdr)
	    {
		for(i = 0; hdr[i] != '\0'; i++)
		    if (! putc(hdr[i], out))
			return 0;
		first_comment = 0;
	    }

	    if (first_char && ldr)
	    {
		for(i = 0; ldr[i] != '\0'; i++)
		    if (! putc(ldr[i], out))
			return 0;
	    }
	    else
		if (! putc(c, out))
		    return 0;
	}
	
	if (c == '\n')
	    first_char = 1;
	else
	    first_char = 0;
    }

    if (comment_found && trlr)
    {
	for(i = 0; trlr[i] != '\0'; i++)
	    if (! putc(trlr[i], out))
		return 0;
	first_comment = 0;
    }

    fclose(in);
    return 1;

error:
    if (in)
        fclose(in);
    return 0;
}

#define MAXLINE	    16384
char linebuf[MAXLINE];

#define WHITESPACE(l) ((l) == ' ' || (l) == '\t')

char *
_dxf_getline(FILE *fd)
{
    int i;
    int c;

    if (feof(fd))
	return NULL;
    
    do
    {
	c = getc(fd);
    } while (c != EOF && WHITESPACE(c));

    if (c == EOF)
	return NULL;
    
    for (i = 0; i < MAXLINE; i++, c = getc(fd))
    {
	linebuf[i] = c;

	if (c == EOF || c == '\n')
	{
	    while (i > 0 && WHITESPACE(linebuf[i-1]))
	      i--;
		
	    linebuf[i] = '\0';
	    break;
	}
    
    }

    if (i == MAXLINE)
    {
	ErrorMessage("line exceeds max length");
	return NULL;
    }

    return linebuf;
}

static void
parseline(char *line, char **name, char **value)
{
    *name = line;
    
    while (!WHITESPACE(*line) && *line != '=')
	line ++;
    
    *line = '\0';
    line++;

    while (WHITESPACE(*line) || *line == '=')
	line ++;
    
    *value = line;
}
    

#define ISTOKEN(a,b) (!strcmp(a, b))

static int
process_input(char *basename, Module *mod, Parameter **in, Parameter **out)
{
    FILE      *fd = NULL;
    int       nin = 0, nout = 0;
    int       linenum;
    char      *line, *name, *value;
    Parameter *parameter = NULL;
    char      *buf = (char *)malloc(strlen(basename) + 4);

    if (! buf)
    {
	ErrorMessage("allocation error");
	goto error;
    }

    sprintf(buf, "%s.mb", basename);

    mod->name                = NULL;
    mod->category            = NULL;
    mod->description         = NULL;
    mod->outboard_executable = NULL;
    mod->include_file        = NULL;
    mod->outboard_persistent = UNKNOWN;
    mod->asynchronous        = UNKNOWN;
    mod->pinned              = UNKNOWN;
    mod->side_effect         = UNKNOWN;

    in[0] = NULL; out[0] = NULL;

    fd = fopen(buf, "r");
    if (! fd)
    {
	ErrorMessage("error opening file: %s\n", basename);
	goto error;
    }

    linenum = -1;
    while (NULL != (line = _dxf_getline(fd)))
    {
	linenum ++;

	if (line[0] == '\0')
	    continue;
	
	if (line[0] == '#')
	    continue;
	
	/*  FIXME  */
	/*if (line[-1] == -1)
	  goto error;*/

	parseline(line, &name, &value);

	if (ISTOKEN(name, "MODULE_NAME")) {
	    COPYSTRING(mod->name, value);
	}
	else if (ISTOKEN(name, "CATEGORY")) {
	    COPYSTRING(mod->category, value);
	}
	else if (ISTOKEN(name, "MODULE_DESCRIPTION")) {
	    COPYSTRING(mod->description, value);
	}
	else if (ISTOKEN(name, "OUTBOARD_HOST")) {
	    COPYSTRING(mod->outboard_host, value);
	}
	else if (ISTOKEN(name, "OUTBOARD_EXECUTABLE")) {
	    COPYSTRING(mod->outboard_executable, value);
	}
	else if (ISTOKEN(name, "LOADABLE_EXECUTABLE")) {
	    COPYSTRING(mod->loadable_executable, value);
	}
	else if (ISTOKEN(name, "INCLUDE_FILE")) {
	    COPYSTRING(mod->include_file, value);
	}
	else if (ISTOKEN(name, "OUTBOARD_PERSISTENT")) {
	    TRUEFALSE(mod->outboard_persistent, value);
	}
	else if (ISTOKEN(name, "ASYNCHRONOUS")) {
	    TRUEFALSE(mod->asynchronous, value);
	}
	else if (ISTOKEN(name, "PINNED")) {
	    TRUEFALSE(mod->pinned, value);
	}
	else if (ISTOKEN(name, "SIDE_EFFECT")) {
	    TRUEFALSE(mod->side_effect, value);
	}
	else if (ISTOKEN(name, "LANGUAGE")) {
	    if (ISTOKEN(value, "C"))
		mod->language = C;
	    else if (ISTOKEN(value, "Fortran"))
		mod->language = FORTRAN;
	    else
	    {
		ErrorMessage("unrecognized LANGUAGE: %s\n", value);
		return 0;
	    }
	}

	else if (ISTOKEN(name, "INPUT"))
	{
	    in[nin] = (Parameter *)malloc(sizeof(Parameter));
	    if (in[nin] == NULL)
	    {
		ErrorMessage("allocation error");
		goto error;
	    }

	    parameter = in[nin];
	    nin ++;

	    COPYSTRING(parameter->name, value);

	    parameter->description   = NULL;
	    parameter->required      = UNKNOWN;
	    parameter->default_value = NULL;
	    parameter->types         = NULL;
	    parameter->structure     = NO_STRUCTURE;
	    parameter->datatype      = NO_DATATYPE;
	    parameter->datashape     = NO_DATASHAPE;
	    parameter->counts        = NO_COUNTS;
	    parameter->positions     = GRID_NOT_REQUIRED;
	    parameter->connections   = GRID_NOT_REQUIRED;
	    parameter->elementtype   = ELT_NOT_REQUIRED;
	    parameter->dependency    = NO_DEPENDENCY;
	}
	else if (ISTOKEN(name, "OUTPUT"))
	{
	    out[nout] = (Parameter *)malloc(sizeof(Parameter));
	    if (out[nout] == NULL)
	    {
		ErrorMessage("allocation error");
		goto error;
	    }

	    parameter = out[nout];
	    nout ++;

	    COPYSTRING(parameter->name, value);

	    parameter->description   = NULL;
	    parameter->required      = UNKNOWN;
	    parameter->default_value = NULL;
	    parameter->types         = NULL;
	    parameter->structure     = NO_STRUCTURE;
	    parameter->datatype      = NO_DATATYPE;
	    parameter->datashape     = NO_DATASHAPE;
	    parameter->counts        = NO_COUNTS;
	    parameter->positions     = GRID_NOT_REQUIRED;
	    parameter->connections   = GRID_NOT_REQUIRED;
	    parameter->elementtype   = ELT_NOT_REQUIRED;
	    parameter->dependency    = NO_DEPENDENCY;
	}
	else if (ISTOKEN(name, "DESCRIPTION"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\n DESCRIPTION encountered outside of parameter definition", linenum); 
		goto error;
	    }
	    COPYSTRING(parameter->description, value);
	}
	else if (ISTOKEN(name, "DESCRIPTIVE"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\n DESCRIPTIVE encountered outsideof parameter definition", linenum);
		goto error;
	    }
	    TRUEFALSE(parameter->descriptive, value);
	}
	else if (ISTOKEN(name, "REQUIRED"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\n REQUIRED encountered outsideof parameter definition", linenum);
		goto error;
	    }
	    TRUEFALSE(parameter->required, value);
	}
	else if (ISTOKEN(name, "DEFAULT_VALUE"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\nDEFAULT_VALUE encountered outside of parameter definition", linenum);
		goto error;
	    }
	    COPYSTRING(parameter->default_value, value);
	}
	else if (ISTOKEN(name, "TYPES"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\nTYPES encountered outsideof parameter definition", linenum);
		goto error;
	    }
	    COPYSTRING(parameter->types, value);
	}
	else if (ISTOKEN(name, "STRUCTURE"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\nSTRUCTURE encountered outside of parameter definition", linenum);
		goto error;
	    }

	    if (ISTOKEN(value, "Value"))
		parameter->structure = VALUE;
	    else if (ISTOKEN(value, "Field/Group"))
		parameter->structure = GROUP_FIELD;
	    else
	    {   
		ErrorMessage("unknown STRUCTURE: %s\n", value);
		goto error;
	    }
	}
	else if (ISTOKEN(name, "DATA_TYPE"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\nDATA_TYPE encountered outside of parameter definition", linenum);
		goto error;
	    }

	    if (ISTOKEN(value, "float"))
		parameter->datatype = FLOAT;
	    else if (ISTOKEN(value, "double"))
		parameter->datatype = DOUBLE;
	    else if (ISTOKEN(value, "int"))
		parameter->datatype = INT;
	    else if (ISTOKEN(value, "uint"))
		parameter->datatype = UINT;
	    else if (ISTOKEN(value, "short"))
		parameter->datatype = SHORT;
	    else if (ISTOKEN(value, "ushort"))
		parameter->datatype = USHORT;
	    else if (ISTOKEN(value, "byte"))
		parameter->datatype = BYTE;
	    else if (ISTOKEN(value, "ubyte"))
		parameter->datatype = UBYTE;
	    else if (ISTOKEN(value, "string"))
		parameter->datatype = STRING;
	    else
	    {   
		ErrorMessage("unknown DATATYPE: %s\n", value);
		goto error;
	    }
	}
	else if (ISTOKEN(name, "DATA_SHAPE"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %dDATA_SHAPE encountered outside of parameter definition\n", linenum);
		goto error;
	    }

	    if (ISTOKEN(value, "Scalar"))
		parameter->datashape = SCALAR;
	    else if (ISTOKEN(value, "1-vector"))
		parameter->datashape = VECTOR_1;
	    else if (ISTOKEN(value, "2-vector"))
		parameter->datashape = VECTOR_2;
	    else if (ISTOKEN(value, "3-vector"))
		parameter->datashape = VECTOR_3;
	    else if (ISTOKEN(value, "4-vector"))
		parameter->datashape = VECTOR_4;
	    else if (ISTOKEN(value, "5-vector"))
		parameter->datashape = VECTOR_5;
	    else if (ISTOKEN(value, "6-vector"))
		parameter->datashape = VECTOR_6;
	    else if (ISTOKEN(value, "7-vector"))
		parameter->datashape = VECTOR_7;
	    else if (ISTOKEN(value, "8-vector"))
		parameter->datashape = VECTOR_8;
	    else if (ISTOKEN(value, "9-vector"))
		parameter->datashape = VECTOR_9;
	    else
	    {   
		ErrorMessage("unknown DATASHAPE: %s\n", value);
		goto error;
	    }
	}
	else if (ISTOKEN(name, "ELEMENT_TYPE"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\nELEMENT_TYPE encountered outside of parameter definition", linenum);
		goto error;
	    }

	    if (ISTOKEN(value, "Lines"))
		parameter->elementtype = ELT_LINES;
	    else if (ISTOKEN(value, "Triangles"))
		parameter->elementtype = ELT_TRIANGLES;
	    else if (ISTOKEN(value, "Quads"))
		parameter->elementtype = ELT_QUADS;
	    else if (ISTOKEN(value, "Tetrahedra"))
		parameter->elementtype = ELT_TETRAHEDRA;
	    else if (ISTOKEN(value, "Cubes"))
		parameter->elementtype = ELT_CUBES;
	    else if (ISTOKEN(value, "Not required"))
		parameter->elementtype = ELT_NOT_REQUIRED;
	    else
	    {   
		ErrorMessage("unknown ELEMENT_TYPE: %s\n", value);
		goto error;
	    }
	}
	else if (ISTOKEN(name, "COUNTS"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\nCOUNTS encountered outside of parameter definition", linenum);
		goto error;
	    }

	    if (ISTOKEN(value, "1"))
		parameter->counts = COUNTS_1;
	    else if (ISTOKEN(value, "same as input"))
		parameter->counts = COUNTS_SAME_AS_INPUT;
	    else
	    {   
		ErrorMessage("unknown COUNTS: %s\n", value);
		goto error;
	    }
	}
	else if (ISTOKEN(name, "POSITIONS"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\nPOSITIONS encountered outside of parameter definition", linenum);
		goto error;
	    }

	    if (ISTOKEN(value, "Regular"))
		parameter->positions = GRID_REGULAR;
	    else if (ISTOKEN(value, "Irregular"))
		parameter->positions = GRID_IRREGULAR;
	    else if (ISTOKEN(value, "Not required"))
		parameter->positions = GRID_NOT_REQUIRED;
	    else
	    {   
		ErrorMessage("unknown POSITIONS: %s\n", value);
		goto error;
	    }
	}
	else if (ISTOKEN(name, "CONNECTIONS"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\nCONNECTIONS encountered outside of parameter definition", linenum);
		goto error;
	    }

	    if (ISTOKEN(value, "Regular"))
		parameter->connections = GRID_REGULAR;
	    else if (ISTOKEN(value, "Irregular"))
		parameter->connections = GRID_IRREGULAR;
	    else if (ISTOKEN(value, "Not required"))
		parameter->connections = GRID_NOT_REQUIRED;
	    else
	    {   
		ErrorMessage("unknown CONNECTIONS: %s\n", value);
		goto error;
	    }
	}
	else if (ISTOKEN(name, "DEPENDENCY"))
	{
	    if (! parameter) 
	    {
		ErrorMessage("syntax error line %d\nDEPENDENCY encountered outside of parameter definition", linenum);
		goto error;
	    }

	    if (ISTOKEN(value, "No dependency"))
		parameter->dependency = NO_DEPENDENCY;
	    else if (ISTOKEN(value, "Positions only"))
		parameter->dependency = DEP_POSITIONS;
	    else if (ISTOKEN(value, "Connections only"))
		parameter->dependency = DEP_CONNECTIONS;
	    else if (ISTOKEN(value, "Positions or connections"))
		parameter->dependency = DEP_INPUT;
	    else
	    {   
		ErrorMessage("unknown DEPENDENCY: %s\n", value);
		goto error;
	    }
	}
	else
	{
	    ErrorMessage("unrecognized keyword on line %d: %s\n",
			linenum, name);
	    goto error;
	}
    }

    in[nin]   = NULL;
    out[nout] = NULL;

    fclose(fd);

    return 1;

error:
    if (fd)
	fclose(fd);
    return 0;
}


static int
GetDXDataType(enum datatype t, char **type)
{
    switch(t)
    {
	case DOUBLE: *type = "TYPE_DOUBLE"; break;
	case FLOAT:  *type = "TYPE_FLOAT";  break;
	case INT:    *type = "TYPE_INT";    break;
	case UINT:   *type = "TYPE_UINT";   break;
	case SHORT:  *type = "TYPE_SHORT";  break;
	case USHORT: *type = "TYPE_USHORT"; break;
	case BYTE:   *type = "TYPE_BYTE";   break;
	case UBYTE:  *type = "TYPE_UBYTE";  break;
	case STRING: *type = "TYPE_STRING";  break;
	default:
	    ErrorMessage("cannot create array without DATATYPE");
	    return 0;
    }

    return 1;
}


static int
GetCDataType(enum datatype t, char **type)
{
    switch(t)
    {
	case DOUBLE: *type = "double"; 		break;
	case FLOAT:  *type = "float";  		break;
	case INT:    *type = "int";    		break;
	case UINT:   *type = "unsigned int";    break;
	case SHORT:  *type = "short"; 		break;
	case USHORT: *type = "unsigned short";	break;
	case BYTE:   *type = "byte";  		break;
	case UBYTE:  *type = "ubyte";  		break;
	case STRING: *type = "char"; 		break;
	default:
	    ErrorMessage("cannot create array without DATATYPE");
	    return 0;
    }

    return 1;
}

static int
GetDXDataShape(enum datashape t, char **r, char **s)
{
    switch(t)
    {  
	case SCALAR:   *r = "0"; *s = "0"; break;
	case VECTOR_1: *r = "1"; *s = "1"; break;
	case VECTOR_2: *r = "1"; *s = "2"; break;
	case VECTOR_3: *r = "1"; *s = "3"; break;
	case VECTOR_4: *r = "1"; *s = "4"; break;
	case VECTOR_5: *r = "1"; *s = "5"; break;
	case VECTOR_6: *r = "1"; *s = "6"; break;
	case VECTOR_7: *r = "1"; *s = "7"; break;
	case VECTOR_8: *r = "1"; *s = "8"; break;
	case VECTOR_9: *r = "1"; *s = "9"; break;
	default:
	    ErrorMessage("cannot create array without DATASHAPE");
	    return 0;
    }

    return 1;
}


static int
GetElementTypeString(enum elementtype t, char **r)
{
    switch(t)
    {  
	case ELT_LINES:      *r = "lines";      break;
	case ELT_TRIANGLES:  *r = "triangles";  break;
	case ELT_QUADS:      *r = "quads";      break;
	case ELT_TETRAHEDRA: *r = "tetrahedra"; break;
	case ELT_CUBES:      *r = "cubes";      break;
	default:
	    ErrorMessage("no element type string available");
	    return 0;
    }

    return 1;
}

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

