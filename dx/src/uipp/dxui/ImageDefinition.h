///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImageDefinition.h,v 1.1 1999/03/31 22:31:59 gda Exp $
 *
 */


#ifndef _ImageDefinition_h
#define _ImageDefinition_h


#include "UIConfig.h"
#include "defines.h"
#include "NodeDefinition.h"


//
// Class name definition:
//
#define ClassImageDefinition	"ImageDefinition"

//
// Referenced classes
class Network;

//
// ImageDefinition class definition:
//				
class ImageDefinition : public NodeDefinition
{
  private:
    //
    // Private member data:
    //
    Cacheability defaultInternalCacheability;    // are the image mods cached by default

  protected:
    //
    // Protected member data:
    //

    //
    // Defines the function that allocates CDBs for this node.
    //
    virtual CDBAllocator getCDBAllocator();

    //
    // Allocate a new Node of the corresponding type.
    //
    virtual Node *newNode(Network *net, int instance = -1); 

  public:
    Cacheability getDefaultInternalCacheability()
                                { return this->defaultInternalCacheability; }

    //
    // Constructor:
    //
    ImageDefinition();

    //
    // Destructor:
    //
    ~ImageDefinition(){}

    //
    // Create a new Module and NodeDefinition of 'this' type. 
    //
    static NodeDefinition *AllocateDefinition();

    virtual void finishDefinition();

    virtual boolean isAllowedInMacro() { return FALSE; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageDefinition;
    }
};


#endif // _ImageDefinition_h
