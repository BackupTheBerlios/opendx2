///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/DXLInputNode.h,v 1.1 1999/03/24 15:17:39 gda Exp $
 *
 */


#ifndef _DXLInputNode_h
#define _DXLInputNode_h


#include "UIConfig.h"

#include "defines.h"
#include "UniqueNameNode.h"


//
// Class name definition:
//
#define ClassDXLInputNode	"DXLInputNode"

//
// Referenced Classes

//
// DXLInputNode class definition:
//				
class DXLInputNode : public UniqueNameNode
{
  private:
    //
    // Private member data:
    //
    static boolean Initializing;

  protected:
    //
    // Protected member data:
    //
    virtual char *netNodeString(const char *prefix);

    virtual boolean initialize();

    virtual char        *valuesString(const char *prefix);

  public:
    //
    // Constructor:
    //
    DXLInputNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~DXLInputNode();

    virtual boolean     sendValues(boolean     ignoreDirty = TRUE);

    //
    // This is the same as the super-class except that we restrict the
    // label with this->verifyRestrictedLabel().
    //
    virtual boolean setLabelString(const char *label);

    //
    // In addition to the superclass' work, make a new label string if our
    // labelString is still of the form DXLIinput_%d
    //
    virtual int assignNewInstanceNumber();

    //
    // Determine if this node is a node of the given class
    //
    virtual boolean isA(Symbol classname);

    //
    // Java Beans
    //
    virtual boolean printAsBean(FILE*);
    virtual boolean printAsBeanInitCall(FILE*);


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDXLInputNode;
    }
};


#endif // _DXLInputNode_h
