// 
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
// 
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
// 

//
// Purpose of this clase:
// Provide a mechanism for storing Node's in a list for the use of Network.
// Network had always used List for storing its Nodes but this turned out
// to be very expensive in the case where a large Network contained many many
// Receivers.  The problem is the lookup strategy used by Network.  When a Receiver
// is parsed, ReceiverNode will start a complete scan of the existing Network
// in order to find a like-named Transmitter.  ...too expensive.  The NodeList
// class will reduce that cost.
//
// We'll always do exactly what the superclass does plus a little extra bookkeeping
// for keeping certain node types quickly accessible.
//

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/NodeList.h,v 1.1 1999/03/31 22:33:26 gda Exp $
 */

#ifndef _NodeList_h
#define _NodeList_h


#include "List.h"
#include "Dictionary.h"


//
// Class name definition:
//
#define ClassNodeList	"NodeList"


//
// Referenced classes:
//
class Node;


class NodeList : public List
{
  private:
    //
    // Private member data:
    //
    Dictionary nodeDict;

  protected:
    List* getSubList(Node*);

  public:
    //
    // Constructor:
    //
    NodeList();

    //
    // Destructor:
    //
    ~NodeList();

    //
    // We always do what the superclass does plus a little extra work for
    // keeping certain node types in sorted order.  This provides a faster
    // lookup.  
    //
    virtual void clear();
    virtual boolean insertElement(const void* , const int);
    virtual boolean replaceElement(const void* , const int);
    virtual boolean deleteElement(const int position);
    virtual List *dup();

    List* makeClassifiedNodeList( const char* );

    const char* getClassName() { return ClassNodeList; }
};


#endif // _NodeList_h 
