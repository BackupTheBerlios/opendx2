//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// FileSelectorNode.C -							    //
//                                                                          //
// FileSelectorNode Class methods and other related functions/procedures.	    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/FileSelectorNode.C,v 1.1 1999/03/31 22:31:43 gda Exp $
 */


 
#include <string.h>

#include "UIConfig.h"
#include "defines.h"
#include "FileSelectorNode.h"
#include "FileSelectorInstance.h"
#include "ErrorDialogManager.h"

//
// The Constructor... 
//
FileSelectorNode::FileSelectorNode(NodeDefinition *nd, Network *net, int instnc) :
                        ValueNode(nd, net, instnc)
{ 
}

//
// Destructure: needs to delete all its instances. 
//
FileSelectorNode::~FileSelectorNode()
{
}

InteractorInstance* FileSelectorNode::newInteractorInstance()
{
    FileSelectorInstance *ii;

    ii = new FileSelectorInstance(this);

    return ii;
}
//
// Print the file filter comment 
//
boolean FileSelectorNode::cfgPrintInstanceAuxInfo(FILE *f,
					InteractorInstance *ii)
{
    FileSelectorInstance *fsi = (FileSelectorInstance*)ii;
    const char *filter = fsi->getFileFilter();

    if (!this->ValueNode::cfgPrintInstanceAuxInfo(f,ii))
	return FALSE;

    if (filter && (fprintf(f,"// filter = %s\n",filter) < 0))
	return FALSE;
    return TRUE;
}
//
// Parse the file filter and all the super class's comments.
//
boolean FileSelectorNode::cfgParseComment(const char *comment,
			const char *filename, int lineno)
{
    if (!EqualSubstring(comment," filter = ",10)) 
	return this->ValueNode::cfgParseComment(comment,filename,lineno);
   
    int instance = this->getInstanceCount();
    FileSelectorInstance *fsi = (FileSelectorInstance*)
					this->getInstance(instance);
    if (!fsi) {
        ErrorMessage("'filter' comment out of order (file %s, line%d)",
                        filename, lineno);
	// Return TRUE though since we acknowledged the comment.
    } else  {
        fsi->setFileFilter(comment + 10);
    }
    return TRUE;
}
//
// We implement this for FileSelector node so that we can keep the
// 2nd output (the basename of the full file name) up to date.
// One should never use this method to set the 2nd output, only the 1st.
// Well, this is used when we parse a .net file.
//
Type FileSelectorNode::setOutputValue(
                                int indx,
                                const char *value,
                                Type t,
                                boolean send)
{

    if (indx == 2)
	return this->ValueNode::setOutputValue(2,value,t,send);

    Type type = this->ValueNode::setOutputValue(1,value,t,FALSE);
    if (type != DXType::UndefinedType) {
	char *basename = (char*)this->getOutputValueString(1);
	basename = DuplicateString(basename);
#ifdef DXD_NON_UNIX_DIR_SEPARATOR
	for (int i=0; i<strlen(basename); i++) {
	    if (basename[i] == '\\')
		basename[i] = '/';
	}
#endif
	char *p = strrchr(basename,'/');
	if (!p) {
	    type = this->ValueNode::setOutputValue(2,value,type,send);
	} else {
	    char *c;
	    p++;
	    c = strchr(p,(int)'"');
	    *c = '\0';
	    type = this->ValueNode::setOutputValue(2,p,type,send);
	}
	delete basename;
    }
    return type;
}

//
// Determine if this node is of the given class.
//
boolean FileSelectorNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassFileSelectorNode);
    if (s == classname)
	return TRUE;
    else
	return this->ValueNode::isA(classname);
}