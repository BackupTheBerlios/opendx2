/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#define WINDOW_CLOSED	    0
#define WINDOW_OPEN	    1
#define WINDOW_OPEN_RAISED  2

typedef struct _imageWindow
{
    char 	        *displayString;
    char 	  	*mod_id;
    int		  	depth;
    int		  	size[2], sizeFlag;
    int		  	offset[2], offsetFlag;
    struct _iwx	  	*iwx;
    Array		events;
    int			state[3];
    int			x, y, time;
    int			parentId;
    int			pickFlag;
    char		*title;
    char		*cacheTag;
    int			map;
    Object		object;
    char		*where;
    int			decorations;
    int			kstate;
} ImageWindow;

