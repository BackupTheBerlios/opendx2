///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/MacroNode.h,v 1.1 1999/03/31 22:32:44 gda Exp $
 *
 */


#ifndef _MacroNode_h
#define _MacroNode_h


#include "defines.h"
#include "Node.h"


//
// Class name definition:
//
#define ClassMacroNode	"MacroNode"

//
// Referenced Classes
class EditorWindow;
class Network;

//
// MacroNode class definition:
//				
class MacroNode : public Node
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //

  public:
    //
    // Constructor:
    //
    MacroNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~MacroNode();

    virtual void updateDefinition();

    virtual boolean initialize();

    virtual boolean     sendValues(boolean     ignoreDirty = TRUE);

    virtual void openMacro();

    //
    // Determine if this node is a node of the given class
    //
    virtual boolean isA(Symbol classname);

    virtual boolean needsFastSort() { return TRUE; }

    //
    // WebOptions is a macro.  I would like to represent it with its own
    // Node subclass but that would require sending down the text of the
    // macro the way the image macro is sent and it seems too cumbersome
    // to include it in every .net file.  this->getJavaNodeName() will
    // only be called from printAsJava and only in the case where the
    // macro is WebOptions
    //
    virtual boolean hasJavaRepresentation();
    virtual const char* getJavaNodeName() { return "WebOptionsNode"; }
    virtual boolean printInputAsJava(int input);


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassMacroNode;
    }
};


#endif // _MacroNode_h
