/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


/*  Similar to a text widget, but only allows strings representing
 *  numerical values (base 10).
 *  (supports integer, fixed point, or floating point | scientific)
 *  IBM T.J. Watson Research Center	July 16, 1990
 */

/*
 */

/* Number resize logic:

	1. Default - XmNrecomputeSize = TRUE;  This means that the number 
	   widget will automatically resize itself based on the min and max
	   values of the widget, and the number of decimal places.  This was
	   done to prevent frequent resizes of steppers in the slider widget.

	2. XmNrecomputeSize = FALSE;  In this case, the widget sizes itself
	   based on the XmNcharPlaces resource.  This delimits the total size
	   of the widget.  This mode presents potentially unsightly operation
	   of the widget if the size in not adequate to handle the min/max
	   values of the widget
*/

#ifdef OS2
#include <stdlib.h>
#include <types.h>
#endif
#ifdef  DXD_WIN
#include <stdlib.h>
#include <sys/types.h>
#endif

#include <stdio.h>
#include <float.h>
#include <Xm/Xm.h>
#include <math.h>	/* Define pow */
#include "FFloat.h"
#include "NumberP.h"
#include "Number.h"
#include "gamma.h"
#include "findcolor.h"

#if !defined(Max)
#define Max(a,b)  ((a>b)?a:b)
#endif

#define superclass (&widgetClassRec)

/*  Hidden routine in NumberOutput.c called from here			     */
extern void	SetNumberSize			(XmNumberWidget nw,
						 Dimension*	width,
						 Dimension*	height);
/*  Forward declare routines used in NumberInput.h  */
static void	UpdateNumberEditorDisplay	(XmNumberWidget	nw);
static void	DisplayNumberShadow		(XmNumberWidget	nw);
void SyncMultitypeData( MultitypeData* new, short type );

static
Boolean	UpdateMultitypeData (XmNumberWidget nw, MultitypeData* new, 
		MultitypeData* current);


/*
 *  Forward declaration of locally defined and used subroutines
 */
/*  Install action table stuff in class core_class record		      */
static void	ClassInitialize		();
/*  Initialize parameters and resources					      */
static void	Initialize		(XmNumberWidget	request,
					 XmNumberWidget	new);
/*  Create the window							      */
static void	Realize			(register XmNumberWidget nw,
					 Mask *p_valueMask,
					 XSetWindowAttributes *attributes);
/*  Redraw the borders and display					      */
static void	Redisplay		(XmNumberWidget	nw,
					 XEvent	*		event,
					 Region			region);
/*  Render the shadowed frame appropriate for the occasion		      */
static void	DisplayShadow		(XmNumberWidget	nw);
/*  Adjust locations after widget size has changed			      */
static void	Resize			(XmNumberWidget	nw);
/*  Reviews requested widget size and indicates Number's own preferrences    */
static XtGeometryResult
		PreferredSize		(XmNumberWidget	nw,
					 XtWidgetGeometry *	request,
					 XtWidgetGeometry *	preferred);
/*  Free all resources used by an instance				      */
static void	Destroy			(XmNumberWidget nw);
/*  Respond to changes in client accessible parameters			      */
static Boolean	SetValues		(XmNumberWidget	current,
					 XmNumberWidget	request,
					 XmNumberWidget	new);
/*  Grab a display server Graphics Context for printing the text string	      */
static void	GetNumberGC		(XmNumberWidget	nw);
/*  Draw cursor at insert position					      */
static void	DrawCursor		(XmNumberWidget nw,
					 int		x,
					 int		y,
					 int		type);


/*
 *  Load the code for the input actions
 *   (The subroutines must be local to be available as constants for
 *    preinitializing the class record structure).
 */
#include "NumberInput.h"

/*
 *  Define number keyboard-input specific translations
 */
/*  This translation table should look like that of the Text Widget  */
#if (XmVersion < 1001)
static char defaultNumberActionsBindings[] =
       "<Btn1Down>:		arm-or-disarm()\n\
	Ctrl<Key>Right:		forward-word()\n\
	Ctrl<Key>Left:		backward-word()\n\
	<Key>BackSpace:		delete-previous-character()\n\
	<Key>Delete:		delete-next-character()\n\
	<Key>Return:		activate-insert()\n\
	<Key>KP_Enter:		activate-insert()\n\
	<Key>Escape:		cancel-insert()\n\
	<Key>Right:		forward-character()\n\
	<Key>Left:		backward-character()\n\
	~Ctrl ~Meta <Key>:	self-insert()";
#else
static char defaultNumberActionsBindings[] =
       "<Btn1Down>:		arm-or-disarm()\n\
	Ctrl<Key>osfRight:	forward-word()\n\
	Ctrl<Key>osfLeft:	backward-word()\n\
	<Key>osfBackSpace:	delete-previous-character()\n\
	<Key>osfDelete:		delete-next-character()\n\
	<Key>Return:		activate-insert()\n\
	<Key>osfActivate:	activate-insert()\n\
	<Key>KP_Enter:		activate-insert()\n\
	<Key>Escape:		release-kbd() cancel-insert()\n\
	<Key>osfRight:		forward-character()\n\
	<Key>osfLeft:		backward-character()\n\
	~Ctrl ~Meta <Key>:	self-insert()";
#endif

/*  The actions should have the same string identifiers as those of Text  */
XtActionsRec defaultNumberActionsTable[] = {
    {"delete-previous-character",	(XtActionProc)DeleteBackwardChar},
    {"delete-next-character",		(XtActionProc)DeleteForwardChar},
    {"self-insert",			(XtActionProc)SelfInsert},
    {"activate-insert",			(XtActionProc)ActivateAndDisarm},
    {"PrimitiveParentActivate",		(XtActionProc)ActivateAndDisarm},
    {"arm-or-disarm",			(XtActionProc)ArmOrDisarm},
    {"cancel-insert",			(XtActionProc)Disarm},
    {"release-kbd",			(XtActionProc)ReleaseKbd},
    {"forward-character",		(XtActionProc)MoveForwardChar},
    {"backward-character",		(XtActionProc)MoveBackwardChar},
    {"backward-word",			(XtActionProc)MoveToLineStart},
    {"forward-word",			(XtActionProc)MoveToLineEnd},
    {"beginning-of-line",		(XtActionProc)MoveToLineStart},
    {"end-of-line",			(XtActionProc)MoveToLineEnd},
    {"Help",				(XtActionProc)Help}
};


/*
 *  Resource list for Number
 */

/*  Declare defaults that can be assigned through values */
#ifndef MAXINT
#define MAXINT 2147483647
#endif
#define DEF_IVAL 0
#define DEF_IMIN -MAXINT 
#define DEF_IMAX  MAXINT 

#define DOUBLE_MAX  DBL_MAX
#define DOUBLE_MIN -DBL_MAX
#define FLOAT_MAX   FLT_MAX
#define FLOAT_MIN  -FLT_MAX


/*  Declare defaults that can be assigned through pointers  */
#if !defined(aviion)
/* on the data general, these 'constants' are defined to be other
 *  variables which are set in some assembly file.  the point is they
 *  cannot be used as static initializers, so they will be initialized
 *  in the startup code below.
 */
static double DefaultMinDbl = DOUBLE_MIN;
static double DefaultMaxDbl = DOUBLE_MAX;
static float DefaultMinFlt = FLOAT_MIN;
static float DefaultMaxFlt = FLOAT_MAX;
#else
static double DefaultMinDbl;
static double DefaultMaxDbl;
static float DefaultMinFlt;
static float DefaultMaxFlt;
static int DefaultInitialized = FALSE;
#endif

static double DefaultValueDbl = 0.0;
static float DefaultValueFlt = 0.0;
static double DefaultCrossOver = 1000000.0;
static double DefaultCrossUnder = 0.0001;

static XtResource resources[] = 
{
   {
      XmNdValue, XmCDValue, XmRDouble, sizeof(double),
      XtOffset(XmNumberWidget, number.value.d),
      XmRDouble, (caddr_t) &DefaultValueDbl
   },
   {
      XmNfValue, XmCFValue, XmRFloat, sizeof(float),
      XtOffset(XmNumberWidget, number.value.f),
      XmRFloat, (caddr_t) &DefaultValueFlt
   },
   {
      XmNiValue, XmCIValue, XmRInt, sizeof(int),
      XtOffset(XmNumberWidget, number.value.i),
      XmRImmediate, (caddr_t) DEF_IVAL
   },
   {
      XmNdMinimum, XmCDMinimum, XmRDouble, sizeof(double),
      XtOffset(XmNumberWidget, number.value_minimum.d),
      XmRDouble, (caddr_t) &DefaultMinDbl
   },
   {
      XmNfMinimum, XmCFMinimum, XmRFloat, sizeof(float),
      XtOffset(XmNumberWidget, number.value_minimum.f),
      XmRFloat, (caddr_t) &DefaultMinFlt
   },
   {
      XmNiMinimum, XmCIMinimum, XmRInt, sizeof(int),
      XtOffset(XmNumberWidget, number.value_minimum.i),
      XmRImmediate, (caddr_t) DEF_IMIN
   },
   {
      XmNdMaximum, XmCDMaximum, XmRDouble, sizeof(double),
      XtOffset(XmNumberWidget, number.value_maximum.d),
      XmRDouble, (caddr_t) &DefaultMaxDbl
   },
   {
      XmNfMaximum, XmCFMaximum, XmRFloat, sizeof(float),
      XtOffset(XmNumberWidget, number.value_maximum.f),
      XmRFloat, (caddr_t) &DefaultMaxFlt
   },
   {
      XmNiMaximum, XmCIMaximum, XmRInt, sizeof(int),
      XtOffset(XmNumberWidget, number.value_maximum.i),
      XmRImmediate, (caddr_t) DEF_IMAX
   },
   {
      XmNfontList, XmCFontList, XmRFontList, sizeof(XmFontList),
      XtOffset(XmNumberWidget, number.font_list),
      XmRString, "Fixed"
   },
   {
      XmNcharPlaces, XmCCharPlaces, XmRShort, sizeof(short),
      XtOffset(XmNumberWidget, number.char_places),
      XmRImmediate, (caddr_t) 4
   },
   {
      XmNdecimalPlaces, XmCDecimalPlaces, XmRShort, sizeof(short),
      XtOffset(XmNumberWidget, number.decimal_places),
      XmRImmediate, (caddr_t) 0
   },
   {
      XmNdataType, XmCDataType, XmRShort, sizeof(short),
      XtOffset(XmNumberWidget, number.data_type),
      XmRImmediate, (caddr_t) INTEGER
   },
   {
      XmNoverflowCallback, XmCCallback, XmRCallback, sizeof(XtCallbackList),
      XtOffset(XmNumberWidget, number.overflow_callback),
      XmRPointer, (caddr_t) NULL
   },
   {
      XmNarmCallback, XmCArmCallback, XmRCallback,  sizeof(XtCallbackList),
      XtOffset(XmNumberWidget, number.arm_callback),
      XmRPointer, (caddr_t) NULL
   },
   {
      XmNactivateCallback, XmCActivateCallback, XmRCallback,
      sizeof(XtCallbackList),
      XtOffset(XmNumberWidget, number.activate_callback),
      XmRPointer, (caddr_t) NULL
   },
   {
      XmNdisarmCallback, XmCDisarmCallback, XmRCallback, sizeof(XtCallbackList),
      XtOffset(XmNumberWidget, number.disarm_callback),
      XmRPointer, (caddr_t) NULL
   },
   {
      XmNwarningCallback, XmCCallback,XmRCallback,sizeof(XtCallbackList),
      XtOffset(XmNumberWidget, number.warning_callback),
      XmRPointer, (caddr_t) NULL
   },
   {
      XmNcenter, XmCCenter, XmRBoolean, sizeof(Boolean),
      XtOffset(XmNumberWidget, number.center),
      XmRImmediate, (caddr_t) True
   },
   {
      XmNraised, XmCRaised, XmRBoolean, sizeof(Boolean),
      XtOffset(XmNumberWidget, number.raised),
      XmRImmediate, (caddr_t) False
   },
   {
      XmNvisible, XmCVisible, XmRBoolean, sizeof(Boolean),
      XtOffset(XmNumberWidget, number.visible),
      XmRImmediate, (caddr_t) True
   },
   {
      XmNeditable, XmCEditable, XmRBoolean, sizeof(Boolean),
      XtOffset(XmNumberWidget, number.allow_key_entry_mode),
      XmRImmediate, (caddr_t) False
   },
   {
      XmNnoEvents, XmCNoEvents, XmRBoolean, sizeof(Boolean),
      XtOffset(XmNumberWidget, number.propogate_events),
      XmRImmediate, (caddr_t) False
   },
   {
      XmNrecomputeSize, XmCRecomputeSize, XmRBoolean, sizeof(Boolean),
      XtOffset(XmNumberWidget, number.recompute_size),
      XmRImmediate, (caddr_t) TRUE
   },
   {
      XmNfixedNotation, XmCFixedNotation, XmRBoolean, sizeof(Boolean),
      XtOffset(XmNumberWidget, editor.is_fixed),
      XmRImmediate, (caddr_t) True
   },
   {
      XmNcrossOver, XmCCrossOver, XmRDouble, sizeof(double),
      XtOffset(XmNumberWidget, number.cross_over),
      XmRDouble, (caddr_t) &DefaultCrossOver
   },
   {
      XmNcrossUnder, XmCCrossUnder, XmRDouble, sizeof(double),
      XtOffset(XmNumberWidget, number.cross_under),
      XmRDouble, (caddr_t) &DefaultCrossUnder
   },
};


/*
 *  The Number class record definition
 */
XmNumberWidgetClassRec xmNumberWidgetClassRec =
{
    /*
     *  CoreClassPart:
     */
    {
      (WidgetClass) &xmPrimitiveClassRec,  /* superclass	    */
      "XmNumber",			   /* class_name	    */
      sizeof(XmNumberWidgetRec),	   /* widget_size	    */
      ClassInitialize,			   /* class_initialize      */
      NULL,				   /* class_part_initialize */
      FALSE,				   /* class_inited	    */
      (XtInitProc)Initialize,		   /* initialize	    */
      NULL,				   /* initialize_hook	    */
      (XtRealizeProc)Realize,		   /* realize		    */
      defaultNumberActionsTable,	   /* actions		    */
      XtNumber(defaultNumberActionsTable), /* num_actions    	    */
      resources,			   /* resources		    */
      XtNumber(resources),		   /* num_resources	    */
      NULLQUARK,			   /* xrm_class		    */
      TRUE,				   /* compress_motion	    */
      FALSE,				   /* compress_exposure	    */
      TRUE,				   /* compress_enterleave   */
      FALSE,				   /* visible_interest	    */	
      (XtWidgetProc) Destroy,		   /* destroy		    */	
      (XtWidgetProc) Resize, 		   /* resize		    */
      (XtExposeProc) Redisplay,		   /* expose		    */	
      (XtSetValuesFunc) SetValues,	   /* set_values	    */	
      NULL,				   /* set_values_hook 	    */
      XtInheritSetValuesAlmost,		   /* set_values_almost	    */
      NULL,				   /* get_values_hook	    */
      NULL,				   /* accept_focus	    */	
      XtVersion,			   /* version		    */
      NULL,				   /* callback private	    */
      defaultNumberActionsBindings,	   /* tm_table		    */
      (XtGeometryHandler)PreferredSize,	   /* query_geometry	    */
      NULL,				   /* display_accelerator   */
      NULL,				   /* extension		    */
    },
    /*
     *  XmPrimitiveClassPart:
     */
    {
      (XtWidgetProc)_XtInherit,		   /* Border highlight	    */
      (XtWidgetProc)_XtInherit,		   /* Border_unhighlight    */
#if (XmVersion >= 1001)
      XtInheritTranslations,     		/* translations           */
#else
      (XtTranslations)_XtInherit,     		/* translations           */
#endif
      NULL,				   /* Arm_and_activate	    */
      NULL,				   /* Get_resources	    */
      0,				   /* Num_get_resources	    */
      NULL,		 		   /* Extension		    */
    },
    /*
     *  XmStepperClassPart:
     */
    {
      NULL,	 			   /* extension		    */
    }
};


WidgetClass xmNumberWidgetClass = (WidgetClass)&xmNumberWidgetClassRec;


/*  Subroutine:	ClassInitialize
 *  Purpose:	Install non-standard type converters needed by this widget class
 */
static void ClassInitialize()
{
#if defined(aviion)
    if (!DefaultInitialized) {
	DefaultMinDbl = -DBL_MAX;
	DefaultMaxDbl = DBL_MAX;
	DefaultMinFlt = -FLT_MAX;
	DefaultMaxFlt = FLT_MAX;
	DefaultInitialized = TRUE;
    }
#endif

    /*  Install converters for type XmRDouble and XmRFloat  */
    XmAddFloatConverters();
}


/*  Subroutine:	Initialize
 *  Purpose:	Initialize number resources and internal parameters.
 */
static void Initialize( XmNumberWidget request, XmNumberWidget new )
{
    Dimension width, height;

    /*  Clear things needing to be clear  */
    new->number.timer = 0;
    new->number.key_entry_mode = 0;
    new->number.last_char_cnt = 0;
    /*  Set the value parameters  */
    SyncMultitypeData(&new->number.value, new->number.data_type);
    SyncMultitypeData(&new->number.value_minimum, new->number.data_type);
    SyncMultitypeData(&new->number.value_maximum, new->number.data_type);
    (void)UpdateMultitypeData(new, &new->number.value, &request->number.value);
    (void)UpdateMultitypeData(new, &new->number.value_minimum,
			      &request->number.value_minimum);
    (void)UpdateMultitypeData(new, &new->number.value_maximum,
			      &request->number.value_maximum); 
    /*  Set the fontinfo and GC  */
    new->number.font_struct = NULL;
    GetNumberGC(new);

    if (new->number.decimal_places < 0)
	new->editor.is_fixed = False;
    /*  Calculate best sizes and impose them only if needed  */
    SetNumberSize(new, &width, &height);
    if( width > new->core.width )
	new->core.width = width;
    if( height > new->core.height )
	new->core.height = height;
    Resize(new);
    new->number.initialized = True;
#if (XmVersion < 1001)
    XmAddTabGroup(new);
#endif
    new->number.cross_under = pow(0.1,(double)new->number.decimal_places);
}


/*  Subroutine: Realize
 *  Purpose:	Create the widget's window with a special twist for the Number
 *		widget.
 *  Note:	Based on XmPrimitive's Realize (which lets bit gravity default
 *		to Forget) but with the DontPropogate switchable.
 */
static void Realize( register XmNumberWidget nw, Mask *p_valueMask,
		     XSetWindowAttributes *attributes )
{
    register Mask eventMask, valueMask;

    valueMask = *p_valueMask;
    eventMask = ButtonPressMask | ButtonReleaseMask
	| KeyPressMask | KeyReleaseMask | PointerMotionMask;
    if( nw->number.propogate_events == FALSE )
    {
	valueMask |= CWDontPropagate;
	attributes->do_not_propagate_mask = eventMask;
    }
    else
    {
	/*  I don't care what Xt expects, I don't want these events!  */
	attributes->event_mask &= ~eventMask;
    }
    XtCreateWindow((Widget)nw, InputOutput, CopyFromParent, valueMask, attributes);
}


/*  Subroutine:	Redisplay
 *  Purpose:	General redisplay function called on exposure events.
 */
/* ARGSUSED */
static void Redisplay( XmNumberWidget nw, XEvent *event, Region region )
{
    /*  Draw the frame  */
    if( nw->primitive.shadow_thickness > 0 )
	DisplayNumberShadow(nw);
    if( nw->primitive.highlight_thickness > 0 )
    {
	/*  Do (or undo) any highlighting  */
	if( nw->primitive.highlighted )
	    _XmHighlightBorder((Widget)nw);
	else if( _XmDifferentBackground((Widget)nw, XtParent(nw)) )
	    _XmUnhighlightBorder((Widget)nw);
    }
    /*  Finally, print the value  */
    if( nw->number.visible )
    {
	if( nw->number.key_entry_mode )
	    UpdateNumberEditorDisplay(nw);
	else
	    XmShowNumberValue(nw);
    }
}


/*  Subroutine:	DisplayNumberShadow
 *  Purpose:	Render the shadowed frame appropriate for the occasion
 */
static
void DisplayNumberShadow( XmNumberWidget nw )
{
#if !defined(cygwin)
    register int border, borders;
    border = nw->primitive.highlight_thickness;
    borders = border + border;
    if( nw->number.raised != nw->number.key_entry_mode ) {
	_XmDrawShadow(XtDisplay(nw), XtWindow(nw),
		      nw->primitive.top_shadow_GC,
		      nw->primitive.bottom_shadow_GC,
		      nw->primitive.shadow_thickness, border, border,
		      nw->core.width - borders, nw->core.height - borders);
    } else {
	_XmDrawShadow(XtDisplay(nw), XtWindow(nw), 
		      nw->primitive.bottom_shadow_GC,
		      nw->primitive.top_shadow_GC,
		      nw->primitive.shadow_thickness, border, border,
		      nw->core.width - borders, nw->core.height - borders);
    }
#endif
}


/*  Subroutine:	Resize
 *  Purpose:	Calculate the drawing area and redraw the widget
 */
static void Resize( XmNumberWidget nw )
{
    Dimension width, height;

    /*  Make sure widget was properly initialized  */
    if( nw->number.font_struct == NULL )
	return;
    SetNumberSize(nw, &width, &height);
    /*  Center the text field  */
    nw->number.x = (int)((int)nw->core.width - (int)nw->number.width) / 2;
    nw->number.x = Max(0, nw->number.x);
    nw->number.y = (int)((int)nw->core.height - (int)nw->number.height) / 2;
    nw->number.y = Max(0, nw->number.y);
}


/*  Subroutine:	PreferredSize
 *  Purpose:	Calculate the drawing area and report what it should be
 */
static XtGeometryResult PreferredSize( XmNumberWidget nw,
				       XtWidgetGeometry* request,
				       XtWidgetGeometry* preferred )
{
    Dimension min_width, min_height, borders;

    /*  If no size changes are being requested, just agree  */
    if( ((request->request_mode & CWWidth) == 0) &&
        ((request->request_mode & CWHeight) == 0) )
	return XtGeometryYes;
    /*  Make sure widget was properly initialized  */
    if( nw->number.font_struct == NULL )
    {
	Dimension width, height;

	if( nw->number.initialized == True )
	    /*  If record shows an initialize was attempted, it's no dice  */
	    return XtGeometryNo;
	GetNumberGC(nw);
	SetNumberSize(nw, &min_width, &min_height);
    }
    preferred->request_mode = CWWidth | CWHeight;
    /*  If no size change would result, tell requestor to give up  */
    if( (request->width > 0) && (request->width == nw->core.width) &&
        (request->height > 0) && (request->height == nw->core.height) )
	{
	preferred->width = request->width;
	preferred->height = request->height;
	return XtGeometryNo;
	}
    borders =
      2 * (nw->primitive.highlight_thickness + nw->primitive.shadow_thickness);
    min_width = nw->number.width + borders;
#if 0
    min_height = nw->number.height + borders;
#else
    min_height = 
	nw->number.font_struct->ascent + nw->number.font_struct->descent + 2 + borders;
#endif
    preferred->width = min_width + (2 * nw->number.h_margin);
    preferred->height = min_height + (2 * nw->number.v_margin);
    if( (request->request_mode & CWWidth) &&
        (request->request_mode & CWHeight) )
    {
	if( (request->width >= preferred->width) &&
	    (request->height >= preferred->height) )
	{
	    /*  If both dimensions are acceptable, say yes  */
	    return XtGeometryAlmost;
	}
	else if( (request->width <  preferred->width) &&
		 (request->height < preferred->height) )
	    /*  If both are unacceptable, say no  */
	    return XtGeometryAlmost;
    }
    else if( request->request_mode & CWWidth )
    {
	preferred->width = request->width;
	if( request->width != preferred->width )
	    return XtGeometryAlmost;
    }
    else
    {
	preferred->height = request->height;
	if( request->height != preferred->height )
	    return XtGeometryAlmost;
    }
}


/*  Subroutine:	Destroy
 *  Purpose:	Clean up allocated resources when the widget is destroyed.
 */
static void Destroy( XmNumberWidget nw )
{
    XtReleaseGC((Widget)nw, nw->number.gc);
    XtRemoveAllCallbacks((Widget)nw, XmNoverflowCallback);
    XtRemoveAllCallbacks((Widget)nw, XmNactivateCallback);
}


/*  Subroutine:	SetValues
 *  Purpose:	Make sure that everything changes correctly if the client
 *		makes any changes on things available as resources
 */
/* ARGSUSED */
static Boolean SetValues( XmNumberWidget current, XmNumberWidget request,
			  XmNumberWidget new )

{
    Boolean resize_width_flag = FALSE;
    Boolean resize_height_flag = FALSE;
    Boolean redraw_flag = FALSE;
    unsigned long highlight_mask;
    XmNumberWarningCallbackStruct call_value;

    /*
     * Check for a change of sensitivity
     */
    if( (new->core.sensitive != current->core.sensitive) ||
        (new->core.ancestor_sensitive != current->core.ancestor_sensitive) )
    {
	redraw_flag = TRUE;
    }
    /*  Check for a change of font  */
    if( new->number.font_list != current->number.font_list )
    {
	XtReleaseGC((Widget)new, new->number.gc);
	new->number.font_struct = NULL;
	GetNumberGC(new);
	resize_width_flag = TRUE;
	resize_height_flag = TRUE;
	redraw_flag = TRUE;
    }
    /*  Check for change of color  */
    if(   (new->primitive.foreground != current->primitive.foreground)
	    || (new->core.background_pixel != current->core.background_pixel) )
    {
	XtReleaseGC((Widget)new, new->number.gc);
	GetNumberGC(new);
	redraw_flag = TRUE;
    }
    /*  Check all the other things that could affect the size  */
    if(   (new->number.char_places != current->number.char_places)
	    || (new->primitive.shadow_thickness
		!= current->primitive.shadow_thickness)
	    || (new->primitive.highlight_thickness
		!= current->primitive.highlight_thickness)
	    || (new->number.decimal_places != current->number.decimal_places)
	    || (new->number.v_margin != current->number.v_margin)
	    || (new->number.h_margin != current->number.h_margin))
    {
	resize_width_flag = TRUE;
	redraw_flag = TRUE;
    }
    if ( (new->number.data_type == INTEGER) &&
	(new->number.decimal_places != current->number.decimal_places) )
	{
	call_value.reason = XmCR_NUM_WARN_DP_INT;
	call_value.message = "XmNdecimalPlaces resource should not be modified\nif XmNdataType resource is set to INTEGER.";
	XtCallCallbacks((Widget)new, XmNwarningCallback, &call_value);
	new->number.decimal_places = 0;
	}
    if(new->number.decimal_places != current->number.decimal_places)
	{
	new->number.cross_under = pow(0.1,(double)new->number.decimal_places);
	}
    /*  Just check resize on things not affecting visuals  */
    SyncMultitypeData(&new->number.value, new->number.data_type);
    SyncMultitypeData(&new->number.value_minimum, new->number.data_type);
    SyncMultitypeData(&new->number.value_maximum, new->number.data_type);
    if(   UpdateMultitypeData(new, &new->number.value_minimum,
				   &current->number.value_minimum) )
	resize_width_flag = TRUE;
    if(   UpdateMultitypeData(new, &new->number.value_maximum,
				   &current->number.value_maximum) )
	resize_width_flag = TRUE;
    if (resize_width_flag || resize_height_flag)
    {
	Dimension width, height, reply_w, reply_h;

	/*  Negotiate over size  */
	SetNumberSize(new, &width, &height);
	/* If actual resize is warranted, try for it but redraw in any case  */
	if( (new->core.width != width) || (new->core.height != height) )
	{
#if 0
 /* Don't do this... You're supposed to change the values in your own
  * core struct and then fini.  Let others negotiate over it.
  */
	    if (XtMakeResizeRequest((Widget)new, width, height, &reply_w, &reply_h) == 
								XtGeometryYes)
#else
            if (1)
#endif
	    {	
		if (resize_width_flag) new->core.width = width;
		if (resize_height_flag) new->core.height = height;
		redraw_flag = TRUE;
	    }
	    else
	    {
		/* This only appears to happen when the number is not w/in
		   the bounds of its parent.  In this case, simply roll back
		   all changes */
		*new = *current;
		SetNumberSize(new, &width, &height);
		XtWarning("Number widget resize request denied by parent.");
		redraw_flag = TRUE;
	    }
	}
    }
    if( UpdateMultitypeData(new, &new->number.value, &current->number.value) )
	XmShowNumberValue(new);
    return redraw_flag;
}



/*  Subroutine:	SyncMultitypeData
 *  Purpose:	Change all elements of the struct to the type specified in the
 *		call
 */
void SyncMultitypeData( MultitypeData* new, short type )
{
    if (type == INTEGER)
        {
        new->d = (double)new->i;
        new->f = (float)new->i;
        }
    if (type == FLOAT)
        {
        new->d = (double)new->f;
        new->i = 0;
        }
    if (type == DOUBLE)
        {
        new->f = 0;
        new->i = 0;
        }
}
/*  Subroutine: UpdateMultitypeData
 *  Purpose:    Check for and handle a value change following priority for
 *              the value's optional data types
 */
static
Boolean UpdateMultitypeData(XmNumberWidget nw, MultitypeData* new, 
		MultitypeData* current )
{

    if (nw->number.data_type == INTEGER)
    {
        if( new->i != current->i )
        {
            new->d = (double)new->i;
            new->f = (float)new->i;
	    return True;
        }
    }
    else if (nw->number.data_type == FLOAT)
    {
        if( new->f != current->f )
        {
            new->d = (double)new->f;
            new->i = 0;
	    return True;
        }
    }
    else if (nw->number.data_type == DOUBLE)
    {
        if( new->d != current->d )
        {
            new->f = 0;
            new->i = 0;
	    return True;
        }
    }
    return False;
}


/*  Subroutine:	GetNumberGC
 *  Purpose:	Get a GC with the right resources for drawing the text string
 */
static void GetNumberGC( XmNumberWidget nw )
{
    XGCValues values;
    XtGCMask  valueMask;
    XColor    fg_cell_def, bg_cell_def;

    if( nw->number.font_struct == NULL )
    {
	if( nw->number.font_list )
	{
#if (XmVersion < 1001)
            int index;
            _XmFontListSearch(nw->number.font_list, XmSTRING_DEFAULT_CHARSET,
                              &index, &nw->number.font_struct);
#else
            XmFontContext   context;
            XmStringCharSet charset;
	    XmFontListEntry flent;
	    XmFontType flent_type;
	    XtPointer xtp;
            XmFontListInitFontContext(&context, nw->number.font_list);
	    flent = XmFontListNextEntry (context);
	    xtp = XmFontListEntryGetFont (flent, &flent_type);
	    if (flent_type != XmFONT_IS_FONT) {
		XtWarning("Unable to access font list.");
		nw->number.font_struct = XLoadQueryFont(XtDisplay(nw), "fixed");
	    } else {
		nw->number.font_struct = xtp;
	    }
            XmFontListFreeFontContext(context);
#endif
	}
	else
	    nw->number.font_struct = XLoadQueryFont(XtDisplay(nw), "fixed");
    }
    values.graphics_exposures = False;
    values.foreground = nw->primitive.foreground;
    values.background = nw->core.background_pixel;
    values.font = nw->number.font_struct->fid;
    valueMask = GCForeground | GCBackground | GCFont | GCGraphicsExposures;
    nw->number.gc = XtGetGC((Widget)nw, valueMask, &values);
    /*
     *  Get the foreground and background colors, and use the average
     *  for the insensitive color
     */
    fg_cell_def.flags = DoRed | DoGreen | DoBlue;
    bg_cell_def.flags = DoRed | DoGreen | DoBlue;
    fg_cell_def.pixel = nw->primitive.foreground;
    XQueryColor(XtDisplay(nw), 
		DefaultColormapOfScreen(XtScreen(nw)),
		&fg_cell_def);

    bg_cell_def.pixel = nw->core.background_pixel;
    XQueryColor(XtDisplay(nw),
                DefaultColormapOfScreen(XtScreen(nw)),
                &bg_cell_def);
    fg_cell_def.red   = fg_cell_def.red/2   + bg_cell_def.red/2;
    fg_cell_def.green = fg_cell_def.green/2 + bg_cell_def.green/2;
    fg_cell_def.blue  = fg_cell_def.blue/2  + bg_cell_def.blue/2;
    
    /*
     * Fudge factor to offset the gamma correction
     */
    fg_cell_def.red = fg_cell_def.red/2;
    fg_cell_def.green = fg_cell_def.green/2;
    fg_cell_def.blue = fg_cell_def.blue/2;
    gamma_correct(&fg_cell_def);
    if(!XAllocColor(XtDisplay(nw),
                DefaultColormapOfScreen(XtScreen(nw)),
		&fg_cell_def))
	{
	find_color((Widget)nw, &fg_cell_def);
	}
    values.foreground = fg_cell_def.pixel;
    nw->number.inv_gc = XtGetGC((Widget)nw, valueMask, &values);
    
}


/*  Subroutine:	XmCreateNumber
 *  Purpose:	This function creates and returns a Number widget.
 */
Widget XmCreateNumber( Widget parent, String name,
		       ArgList args, Cardinal num_args )
#ifdef EXPLAIN
     Widget	parent;		/* Parent widget		 */
     String	name;		/* Name for this widget instance */
     ArgList	args;		/* Widget specification arg list */
     Cardinal	num_args;	/* Number of args in the ArgList */
#endif
{
    return XtCreateWidget(name, xmNumberWidgetClass, parent, args, num_args);
}


/*  Subroutine:	UpdateNumberEditorDisplay
 *  Purpose:	Draw the string being entered in the widget
 */
static
void UpdateNumberEditorDisplay( XmNumberWidget nw )
{
    int x, y, pad;
    pad = nw->number.char_places - nw->editor.string_len;
    if( nw->editor.string_len < nw->number.last_char_cnt )
	XClearArea(XtDisplay(nw), XtWindow(nw),
		   nw->number.x, nw->number.y,
		   nw->number.width + nw->number.h_margin, 
		   nw->number.height, False);
    y = nw->number.y + nw->number.font_struct->ascent + 1;
    /*  Calculate the text position x coordinate and print  */
    if( pad <= 0 )
    {
	x = nw->number.x;
    }
    else
    {
	if( nw->number.center && (pad > 0) )
	    x = nw->number.x + ((pad * nw->number.char_width) / 2) + 
			nw->number.h_margin;
	else
	    x = nw->number.x + (pad * nw->number.char_width);
    }
    XDrawImageString(XtDisplay(nw), XtWindow(nw), nw->number.gc,
		     x, y, nw->editor.string, nw->editor.string_len);
    x += XTextWidth(nw->number.font_struct,
		    nw->editor.string, nw->editor.insert_position);
    DrawCursor(nw, x, y, 2);
    nw->number.last_char_cnt = nw->editor.string_len + 1;
}


/*  Subroutine:	DrawCursor
 *  Purpose:	Draw a cursor to indicate the insert position (offering
 *		several different types of appearances).
 */
static void DrawCursor( XmNumberWidget nw, int x, int y, int type )
{
    XSegment segment[3];

    switch( type ) {
      case 0:
	/*  Underbar  */
	XDrawLine(XtDisplay(nw), XtWindow(nw), nw->number.gc,
		  x, y, x + nw->number.char_width, y);
	break;
      case 1:
	/*  Vertical line  */
	XDrawLine(XtDisplay(nw), XtWindow(nw), nw->number.gc,
		  x, nw->number.y, x, nw->number.y + nw->number.height - 1);
	break;
      case 2:
	/*  I beam  */
	segment[0].x1 = segment[2].x1 = x - 1;
	segment[1].x1 = segment[1].x2 = x;
	segment[0].x2 = segment[2].x2 = x + 1;
	segment[0].y1 = segment[0].y2 = segment[1].y1 = nw->number.y+1;
	segment[1].y2 = segment[2].y1 = segment[2].y2 =
	  nw->number.y + nw->number.height - 2;
	XDrawSegments(XtDisplay(nw), XtWindow(nw), nw->number.gc, segment, 3);
	break;
    }
}

void XmUnlimitNumberBounds(XmNumberWidget w)
{
    XmSetNumberBounds(w,1.0,0.0);
}
void XmSetNumberBounds(XmNumberWidget w, double dmin, double dmax)
{
    short type;
    Arg wargs[4];
    float fmin, fmax;
    int   imin, imax, n = 0;

    XtVaGetValues((Widget)w, XmNdataType, &type, NULL);

    if (dmin > dmax) { 		/* Implies an unlimit */
	switch (type) {
	  case DOUBLE:
	    dmin = DOUBLE_MIN;
	    dmax = DOUBLE_MAX;
	    break;
	  case FLOAT:
	    dmin = FLOAT_MIN;
	    dmax = FLOAT_MAX;
	    break;
	  case INTEGER:
	    dmin = -MAXINT;
	    dmax =  MAXINT;
	    break;
 	}
    } 

    if (type == DOUBLE) {
        DoubleSetArg(wargs[n], XmNdMinimum, dmin); n++;
        DoubleSetArg(wargs[n], XmNdMaximum, dmax); n++;
    } else if (type == FLOAT) {
	fmin = dmin;
	fmax = dmax;
        XtSetArg(wargs[n], XmNfMinimum, &fmin); n++;
        XtSetArg(wargs[n], XmNfMaximum, &fmax); n++;
    } else {
	imin = dmin;
	imax = dmax;
        XtSetArg(wargs[n], XmNiMinimum, imin); n++;
        XtSetArg(wargs[n], XmNiMaximum, imax); n++;
    }
    XtSetValues((Widget)w, wargs, n);

}

void XmGetNumberBounds(XmNumberWidget w, double *dmin, double *dmax)
{
    short type;
    Arg wargs[4];
    float fmin, fmax;
    int   imin, imax, n = 0;

    XtVaGetValues((Widget)w, XmNdataType, &type, NULL);

    switch (type) {
      case INTEGER:
	XtSetArg(wargs[n], XmNiMinimum, &imin); n++;
	XtSetArg(wargs[n], XmNiMaximum, &imax); n++;
	XtGetValues((Widget)w,wargs,n);
	*dmin = imin; 
	*dmax = imax;
	break;
      case FLOAT:
	XtSetArg(wargs[n], XmNfMinimum, &fmin); n++;
	XtSetArg(wargs[n], XmNfMaximum, &fmax); n++;
	XtGetValues((Widget)w,wargs,n);
	*dmin = fmin; 
	*dmax = fmax;
	break;
      case DOUBLE:
	XtSetArg(wargs[n], XmNdMinimum, dmin); n++;
	XtSetArg(wargs[n], XmNdMaximum, dmax); n++;
	XtGetValues((Widget)w,wargs,n);
	break;
    }
}
double XmGetNumberValue(XmNumberWidget w)
{
    short type;
    int ivalue;
    float fvalue;
    double dvalue;

    XtVaGetValues((Widget)w, XmNdataType, &type, NULL);

    switch (type) {
        case INTEGER:
            XtVaGetValues((Widget)w, XmNiValue, &ivalue, NULL);
            dvalue = (double) ivalue;
	    break;
        case FLOAT:
            XtVaGetValues((Widget)w, XmNfValue, &fvalue, NULL);
            dvalue = (double) fvalue;
	    break;
        case DOUBLE:
            XtVaGetValues((Widget)w, XmNdValue, &dvalue, NULL);
	    break;
    }

    return dvalue;
}


