//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// SaveMacroCommand.h -                                                     //
//                                                                          //
// Definition for the SaveMacroCommand class.                               //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/SaveMacroCommand.h,v 1.1 1999/03/31 22:34:07 gda Exp $
 */

#ifndef _SaveMacroCommand_h
#define _SaveMacroCommand_h


#include "defines.h"
#include "NoUndoCommand.h"

//
// Class name definition:
//
#define ClassSaveMacroCommand    "SaveMacroCommand"

//
// Referenced classes
class MacroDefinition;

//
// SaveMacroCommand class definition:
//
class SaveMacroCommand : public NoUndoCommand 
{
  private:
    //
    // Private member data:
    //
    MacroDefinition *md;

    // Pointer to the next macro that is dirty.
    //
    Command *next;

  protected:
    //
    // Protected member data:
    //
    virtual  boolean doIt(CommandInterface*);

    //
    // Used by saving confirmation dialog.
    //
    static void SaveMacro(void *);
    static void DiscardMacro(void *);

  public:

    SaveMacroCommand(const char*   name,
                     CommandScope* scope,
                     boolean       active,
                     MacroDefinition *md);

    ~SaveMacroCommand();

    //
    // Set the pointer to the next macro that is dirty. 
    //
    void setNext(Command *next);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
        return ClassSaveMacroCommand;
    }

};


#endif // _SaveMacroCommand_h
