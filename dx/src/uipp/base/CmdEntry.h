/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




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
