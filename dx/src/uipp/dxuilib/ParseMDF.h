//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ParseMDF.h,v 1.1 1999/03/24 15:17:44 gda Exp $
 */


#ifndef _ParseMDF_h
#define _ParseMDF_h


#include "defines.h"

class Dictionary;
class ParameterDefinition;

extern boolean ReadMDFFiles(const char* root, Dictionary* mdf, boolean uiOnly);
extern boolean LoadMDFFile(const char* file, const char* type, 
			Dictionary *mdf, boolean uiOnly);
extern boolean ParseMDFTypes(ParameterDefinition *param,
    char *line,
    int lineNumber = 0);

// 
// A dictionary of strings that are filenames of dynamically loadable object 
// files containing module entry points for the executive to use.  The string
// keys in the dictionary are actually the names of the loadable files.
//
extern Dictionary *theDynamicPackageDictionary;

#endif // _ParseMDF_h
