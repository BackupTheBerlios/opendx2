//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// CmdEntry.h -								    //
//                                                                          //
// Definition for the CmdEntry class.					    //
// A CmdEntry object is inserted into a Dictionary and is used to handle    //
// command parsing.  A CmdEntry may be either a function to execute, a      //
// Command to execute, or a new dictionary to recurse to.                   //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/CmdEntry.h,v 1.1 1999/03/24 15:17:22 gda Exp $
 */


#ifndef _CmdEntry_h
#define _CmdEntry_h


#include "defines.h"
#include "Base.h"


//
// Class name definition:
//
#define ClassCmdEntry	"CmdEntry"

typedef boolean (*CmdEntryFunction)(const char *, int , void *);


//
// Referenced Classes
//
class Dictionary;
class Command;

//
// CmdEntry class definition:
//				
class CmdEntry : public Base
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //
    CmdEntryFunction function;
    Dictionary *dictionary;
    Command *command;
    void *clientData;


  public:
    //
    // Constructor:
    //
    CmdEntry(Dictionary *, void *clientData);
    CmdEntry(Command *);
    CmdEntry(CmdEntryFunction f, void *clientData);

    //
    // Destructor:
    //
    ~CmdEntry();

    //
    // Function to handle a character string (a command) with this CmdEntry
    //
    boolean parse(const char *, int packetId = -1);

    //
    //
    //
    Dictionary *getDictionary();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassCmdEntry;
    }
};


#endif // _CmdEntry_h
