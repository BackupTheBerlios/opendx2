//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// Link.C -								    //
//                                                                          //
// Link Class methods and other related functions/procedures.		    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/Link.C,v 1.1 1999/03/24 15:17:23 gda Exp $
 */


#include "Link.h"


inline void Link::setElement(const void* element)
{
    this->element = element;
}


inline void Link::setNext(Link* next)
{
    this->next = next;
}


