/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/history.h,v 1.1 1999/03/24 15:17:25 gda Exp $
 */

#ifndef _history_h
#define _history_h

#if defined(__cplusplus) || defined(c_plusplus)
# define EXTERN extern "C"
#else
# define EXTERN extern
#endif


typedef struct HistoryNodeType_
{
    Widget 			outputWidget;
    Widget			menu;
    Widget			button;
    int				type;
    char			filename[127];
    char			label[127];
    int				position;
    struct HistoryNodeType_*	next;
    struct HistoryNodeType_*	prev;

} HistoryNodeType;


typedef struct
{
    HistoryNodeType*	head;
    HistoryNodeType*	tail;
    HistoryNodeType*	current;
    int			length;

} HistoryList;


EXTERN
HistoryList* NewHistoryList();

EXTERN
Widget CreatePopupMenu(Widget parent);


#endif /* _history_h */
