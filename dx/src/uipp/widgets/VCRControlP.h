/*  Open Visualization Data Explorer Source File */


#ifndef _VCRControlP_h
#define _VCRControlP_h

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif


#include <stdio.h>
#include <X11/IntrinsicP.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/CoreP.h>
#include <X11/Shell.h>
#include <X11/CompositeP.h>
#include <X11/Composite.h>
#include <X11/Constraint.h>
#include <Xm/XmP.h>
#include <Xm/Xm.h>
#include <Xm/BulletinBP.h>
#include <Xm/FormP.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/Frame.h>
#include <Xm/FrameP.h>
#include <Xm/Label.h>
#include <Xm/LabelP.h>
#include <Xm/LabelG.h>
#include <Xm/LabelGP.h>
#include <Xm/DrawingA.h>
#include <Xm/DrawingAP.h>
#include <Number.h>
#include <NumberP.h>
#include <Stepper.h>
#include <FrameControl.h>

typedef struct 
{
	int	mumble;
} XmVCRControlClassPart;

typedef struct _XmVCRControlClassRec
{
	CoreClassPart			core_class;
	CompositeClassPart		composite_class;
	ConstraintClassPart		constraint_class;
	XmManagerClassPart		manager_class;
	XmBulletinBoardClassPart	bulletin_board_class;
	XmFormClassPart			form_class;
	XmVCRControlClassPart		vcr_control_class;
} XmVCRControlClassRec;

extern XmVCRControlClassRec xmVCRControlClassRec;

typedef struct ButtonImageRec {
    XImage*	 image;
    GC		 gc;
    unsigned int background;
    short	 width, height;
    Pixmap pixid;
} ButtonImage;

typedef struct _XmVCRControlPart {
    Widget              parent;
    short		min_value;		/* Min app frame number i.e.1 */
    short		max_value;
    short		start_value;
    short		next_value;
    short		current_value;
    short		stop_value;
    short		frame_increment;
    XtCallbackList	action_callback;	/* Callback for VCR switches  */
    XtCallbackList	frame_callback;		/* Callback for frame numbers */
    caddr_t		user_data;		/* To be passed with callback */
    XmPushButtonWidget	title_bar;
    XmFrameWidget	frame[10];
    XmDrawingAreaWidget	button[10];
    XmLabelWidget	label;
    XmLabelWidget	dot_dot_dot;
    XmFrameControlWidget	frame_control;
    ButtonImage		button_image[10];
    Boolean		button_is_in[10];
    XtIntervalId	button_timeout;		/* Delay pushbutton release   */
    Boolean		step_being_held;	/* Don't release while held   */
    Widget		shell;
    Boolean		frame_control_is_up;
    Pixel		limit_color;
    Pixel		next_color;
    Pixel		current_color;
    Boolean		frame_sensitive;
    Boolean		min_sensitive;
    Boolean		max_sensitive;
    Boolean		inc_sensitive;
    Boolean		current_visible;
    Time		last_frame_control_press; /* used to ignore 2x clicks */
} XmVCRControlPart;

typedef struct _XmVCRControlRec
{
	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmBulletinBoardPart	bulletin_board;
	XmFormPart		form;
	XmVCRControlPart	vcr_control;
} XmVCRControlRec;

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif


#endif
