/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/
/*
 * $Header:
 */


#ifndef _Image_h
#define _Image_h

#include <Xm/DrawingA.h>
#include <Xm/DrawingAP.h>

/*  New fields for the Image widget class record  */

typedef struct
{
   int none;   /* No new procedures */
} XmImageClassPart;


/* Full class record declaration */

typedef struct _XmImageClassRec
{
	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ConstraintClassPart	constraint_class;
	XmManagerClassPart	manager_class;
	XmDrawingAreaClassPart	drawing_area_class;
	XmImageClassPart	image_class;
} XmImageClassRec;

extern XmImageClassRec xmImageClassRec;

typedef struct _XmImagePart
{
    /*  Public (resource accessable)  */
    XtCallbackList    	motion_callback;
    Boolean		send_motion_events;
    Boolean		frame_buffer;
    Boolean		supported8;
    Boolean		supported12;
    Boolean		supported16;
    Boolean		supported24;
    /*  Private (local use)  */
} XmImagePart;


typedef struct _XmImageRec
{
	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmDrawingAreaPart	drawing_area;
	XmImagePart		image;
} XmImageRec;

#endif
