/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




typedef struct EntryType_ {
    char        *value;
    struct EntryType_   *next;
    struct EntryType_   *prev;
} EntryType;


typedef struct {
    EntryType  *top;
    EntryType  *bottom;
    EntryType  *current;
    int       length;
} Stack;

