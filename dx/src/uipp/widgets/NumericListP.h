/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/widgets/NumericListP.h,v 1.1 1999/03/24 15:17:35 gda Exp $
 */


#ifndef _NumericList_h
#define _NumericList_h

#include <Xm/ScrolledW.h>
#include <Xm/BulletinB.h>
#include <Xm/BulletinBP.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*  New fields for the NumericList widget class record  */

typedef struct
{
   int none;   /* No new procedures */
} XmNumericListClassPart;


/* Full class record declaration */

typedef struct _XmNumericListClassRec
{
	CoreClassPart		 core_class;
	CompositeClassPart	 composite_class;
	ConstraintClassPart	 constraint_class;
	XmManagerClassPart	 manager_class;
	XmBulletinBoardClassPart bulletin_board_class;
	XmNumericListClassPart	 numeric_list_class;
} XmNumericListClassRec;

extern XmNumericListClassRec xmNumericListClassRec;

typedef struct _XmNumericListPart
{
    /*  Public (resource accessable)  */
    int                     tuples;         	/* XmNtuples    */
    VectorList              vectors;        	/* XmNvectors   */
    int                     vector_count;   	/* XmNvectorCount       */
    int                     *decimal_places;   	/* XmNdecimalPlaces       */
    Boolean		    scrolled_window;
    XmScrolledWindowWidget  sw;
    Dimension		    vector_spacing; 	/* Dist between vector elem's */
    XtCallbackList	    select_callback;	/* XmNselectCallback	*/
    Dimension		    min_column_width;

    /*  Private (local use)  */
    VectorList          local_vectors;
    Dimension		line_height;
    Dimension		*vector_width_left;
    Dimension		*vector_width_right;
    int			ascent;
    int			descent;
    GC			normal_gc;
    GC			inverse_gc;
    int			selected;
    int			first_selected;
    XFontStruct		*font;
    Widget		hsb;
    Widget		vsb;
    int			vsb_increment;
    int			hsb_increment;
    Boolean		incrementing;
    Boolean		decrementing;
    unsigned long	norm_space;
    XtIntervalId	tid;
    int                 *local_decimal_places;

} XmNumericListPart;


typedef struct _XmNumericListRec
{
	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmBulletinBoardPart	bulletin_board;
	XmNumericListPart	numeric_list;
} XmNumericListRec;

#define XmCVector       "Vector"
#define XmRVector       "Vector"
#define XmRVectorList   "VectorList"


#if defined(__cplusplus) || defined(c_plusplus)
 }
#endif


#endif
