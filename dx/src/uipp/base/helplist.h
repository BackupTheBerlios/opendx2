/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/helplist.h,v 1.1 1999/03/24 15:17:25 gda Exp $
 */

#ifndef _helplist_h
#define _helplist_h

typedef struct ListNodeType_ {
    char   *refname;
    int    offset;
    struct ListNodeType_   *next;
    struct ListNodeType_   *prev;
} ListNodeType;


typedef struct {
    ListNodeType  *head;
    ListNodeType  *tail;
    ListNodeType  *current;
    int       length;
} SpotList;

#endif /* _helplist_h */

