//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// AnnotationGroupManager.h -						    //
//                                                                          //
// Definition for the AnnotationGroupManager class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/AnnotationGroupManager.h,v 1.1 1999/03/24 15:17:38 gda Exp $
 */


#ifndef _AnnotationGroupManager_h
#define _AnnotationGroupManager_h


#include "defines.h"
#include "GroupManager.h"
#include "Dictionary.h"
#include "Strings.h"

//
// Class name definition:
//
#define ClassAnnotationGroupManager	"AnnotationGroupManager"
#define ANNOTATION_GROUP "annotation"

class Network;


//
// The class to hold the group info
//
class AnnotationGroupRecord : public GroupRecord
{
  friend class AnnotationGroupManager;
  private:
    
  protected:
     AnnotationGroupRecord(Network *net, const char *name): GroupRecord(net, name) {}

    ~AnnotationGroupRecord() { }

  public:
};


//
// AnnotationGroupManager class definition:
//				
class AnnotationGroupManager : public GroupManager
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //

    virtual GroupRecord *recordAllocator(Network *net, const char *name) { 
	return new AnnotationGroupRecord(net, name);
    }

  public:
    //
    // Destructor:
    //
    ~AnnotationGroupManager(){}

    static SupportsMacros() { return TRUE; }

    //
    // Constructor:
    //
    AnnotationGroupManager(Network *net);

    virtual boolean printComment (FILE*);
    virtual boolean parseComment (const char*, const char*, int, Network*);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassAnnotationGroupManager;
    }
};


#endif // _AnnotationGroupManager_h
