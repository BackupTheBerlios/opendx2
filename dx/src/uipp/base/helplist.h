/*  Open Visualization Data Explorer Source File */


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

