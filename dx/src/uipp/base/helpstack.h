/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/helpstack.h,v 1.1 1999/03/24 15:17:25 gda Exp $
 */


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

