/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


/*	Construct and manage the "frame sequencer guide" to be used as a
 *	popup of the "sequence controller" (alias VCR control)
 *
 *	August 1990
 *	IBM T.J. Watson Research Center
 *	R. T. Maganti
 */

/*
 * $Log: SlideBarP.h,v $
 * Revision 1.4  1999/05/03 14:09:04  gda
 * dxconfig.h, plus other post-new-shapshot fixes
 *
 * Revision 1.4  1999/05/03 14:09:04  gda
 * dxconfig.h, plus other post-new-shapshot fixes
 *
 * Revision 1.3  1999/04/30 13:10:08  gda
 * After re-snapshotting, ripping out headers and adding linux changes
 *
 * Revision 9.1  1997/05/22 18:48:29  svs
 * Copy of release 3.1.4 code
 *
 * Revision 8.0  1995/10/03  18:50:09  nsc
 * Copy of release 3.1 code
 *
 * Revision 7.1  1994/01/18  19:02:51  svs
 * changes since release 2.0.1
 *
 * Revision 6.1  93/11/16  10:51:09  svs
 * ship level code, release 2.0
 * 
 * Revision 1.1  93/02/26  15:47:43  danz
 * Initial revision
 * 
 * 
 */

#ifndef _Slidebar_h
#define _Slidebar_h

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#include <Xm/DrawingA.h>
#include <Xm/DrawingAP.h>
#include <Xm/SeparatoG.h>
#include <Xm/SeparatoGP.h>


/*  New fields for the SlideBar widget class record  */

typedef struct
{
   int mumble;   /* No new procedures */
} XmSlideBarClassPart;


/* Full class record declaration */

typedef struct _XmSlideBarClassRec
{
	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ConstraintClassPart	constraint_class;
	XmManagerClassPart	manager_class;
	XmDrawingAreaClassPart	drawing_area_class;
	XmSlideBarClassPart	slide_bar_class;
} XmSlideBarClassRec;

extern XmSlideBarClassRec xmSlideBarClassRec;



typedef struct ArrowRec
{
    XRectangle	*top;		/* Array to draw top and left shadow	   */
    XRectangle	*bot;		/* Array to draw right shadow		   */
    XRectangle	*cen;		/* Array to draw center area		   */
    short	top_count;	/* Sizes of arrays			   */
    short	bot_count;
    short	cen_count;
    short	base_x;		/* Reference to put initial top[0] at ...  */
    short	base_y;		/* ... known location in window		   */
    short	x;		/* X coord to which array is currently set */
} *Arrow;

typedef struct
{
    Pixmap	out_pixmap;	/* Pixmap of arrow for fast rendering	   */
    Pixmap	in_pixmap;	
    Arrow	arrow;		/* Struct with XRectangles to draw arrow   */
    GC		cenGC;		/* GC for drawing center of arrow	   */
    short	x;		/* x in bar coords (0-max)		   */
    short	x_edge_offset;	/* Pixels from left edge to marker point   */
    short	y;		/* True y coordinate			   */
    short	width;		/* Size of pixmap			   */
    short	height;
    short	detent;		/* Index value used by application	   */
} Marker;


typedef struct _XmSlideBarPart
{
    /*  Public (resource accessable)  */
    Marker	start_mark;		/* Pixmaps for drawing limit arrows   */
    Marker	stop_mark;
    Marker	next_mark;		/* Pixmaps for drawing marker arrow   */
    Marker	current_mark;		/* Pixmaps for drawing marker arrow   */
    Pixel	current_mark_color;	/* Color of current marker	      */
    Pixel	value_mark_color;	/* Color of central marker	      */
    Pixel	limit_mark_color;	/* Color of edge marker		      */
    XtCallbackList value_callback;	/* Callback list for any change	      */
    short	num_detents;		/* Number of detent stops on bar      */
    short	min_detent;		/* Offset: detent to external value   */
    short	x_margin;		/* Space on either side of bar	      */
    short	arrow_width;		/* Size of arrow marker		      */
    short	arrow_height;
    Boolean	jump_to_grab;		/* Grabbed mark moves under pointer   */
    Boolean	drop_to_detent;		/* Dropped mark aligns on detent      */
    Boolean	sensitive;		/* Whether to accept user input	      */
    /*  Private (local use)  */
    Boolean	init;			/* Set 'til drawing stuff initialized */
    XmSeparatorGadget	line;
    Marker*	grabbed;
    short	max_detent;		/* num_detents - 1		      */
    short	y_margin;		/* Offset to top of tallest arrow     */
    short	width;			/* Length of slider bar		      */
    short	grab_x_offset;		/* Pointer grab to left edge offset   */
    short	arrow_x_offset;		/* Offset from arrow tip to left edge */
    short	provisional_grab;	/* X coord of grab to be determined   */
    Boolean	current_visible;	/* Display current marker ?	      */
} XmSlideBarPart;


typedef struct _XmSlideBarRec
{
	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmDrawingAreaPart	drawing_area;
	XmSlideBarPart		slide_bar;
} XmSlideBarRec;

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
