/*  Open Visualization Data Explorer Source File */


#include <ctype.h>	/*  issspace(), isdigit(), isalnum()  */
#include <stdlib.h>	/*  strtod()  */
#include <errno.h>	/*  errno, ERANGE  */
#define XK_MISCELLANY 1
#include <X11/keysymdef.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
 *  Define locally used macros
 */
#define KeyValue(c) ((double)((c)-'0'))
#define IsExponentSymbol(c) (((c)=='e')||((c)=='E'))
#define DECIMAL_POINT '.'


/*
 *  Define structure used locally to handle a related set of parameters
 *  (These are provisional new values not installed until all tests passed)
 */
struct TestStruct {
    double value;
    short insert_position;
    short string_len;
    Boolean mantissa_negative;
    Boolean exponent_negative;
    char string[MAX_EDITOR_STRLEN];
};


/*
 *  Forward declarations of locally defined subroutines
 */
static void	Activate		(XmNumberWidget	nw,
					 XEvent *	event);
static void	ArmOrDisarm		(XmNumberWidget	nw,
					 XEvent *	event);
/*  Set up number widget for keybourd input.				      */
static void	Arm			(XmNumberWidget	nw,
					 XEvent *	event);
/*  Take number widget out of keyboard input mode			      */
static void	Disarm			(XmNumberWidget	nw,
					 XEvent *	event);
/*  Remove number widget from Xt grab list 				      */
static void	UnGrabKbd		(XmNumberWidget	nw);

/*  Register new value and deactivate keyboard input mode		      */
static void	ActivateAndDisarm	(XmNumberWidget	nw,
					 XEvent *	event);
/*  Call a help routine if one was registered				      */
static void	Help			(XmNumberWidget nw, XEvent* event);
static void	SelfInsert		(XmNumberWidget	nw,
					 XEvent *	event,
					 char **	params,
					 Cardinal *	num_params);
static void	DeleteForwardChar	(XmNumberWidget	nw,
					 XEvent *	event,
					 char **	params,
					 Cardinal*	num_params);
static void	DeleteBackwardChar	(XmNumberWidget	nw,
					 XEvent *	event,
					 char **	params,
					 Cardinal*	num_params);
static void	MoveBackwardChar	(XmNumberWidget	nw,
					 XEvent*	event,
					 char**		params,
					 Cardinal*	num_params);
static void	MoveForwardChar		(XmNumberWidget	nw,
					 XEvent*	event,
					 char**		params,
					 Cardinal*	num_params);
static void	MoveToLineEnd		(XmNumberWidget	nw,
					 XEvent*	event,
					 char**		params,
					 Cardinal*	num_params);
static void	MoveToLineStart		(XmNumberWidget	nw,
					 XEvent*	event,
					 char**		params,
					 Cardinal*	num_params);
/*  Check editor value against registered Number limits			      */
static Boolean	ValueWithinLimits	(XmNumberWidget nw);
/*  Generic move insert position					      */
static Boolean	MovePosition		(XmNumberWidget nw,
					 int		num_chars);
/*  Generic insertion into the editor string				      */
static Boolean	InsertChars		(XmNumberWidget nw,
					 char*		in_string,
					 int		num_chars);
/*  Generic deletion from the editor string				      */
static Boolean	DeleteChars		(XmNumberWidget	nw,
					 int		num_chars);
/*  Test string for acceptability and install in nw->editor if acceptable     */
static Boolean	TestParse		(XmNumberWidget nw,
					 char*		in_string,
					 int		insert_position);
/*  Report type of error						      */
static Boolean	EditError		(XmNumberWidget	nw,
					 char*		string,
					 int		msg,
				 	 int		char_place);

/*
 *  Define codes for the error types
 */
#define BadInput	0
#define NoNegative	1
#define InvalidChar	2
#define NoFloat		3
#define NoExponent	4
#define ExcessPrecision	5
#define StringEmpty	6
#define AboveMaximum	7
#define BelowMinimum	8


/*  Subroutine:	Activate
 *  Effect:	Processes "activate" and "disarm" type actions in the stepper
 *		widget field that might belong to its gadgets.
 */
/* ARGSUSED */
static void Activate( XmNumberWidget nw, XEvent* event )
{
    XmDoubleCallbackStruct call_value;

    /*  Register the new value if in editor mode  */
    if( nw->number.key_entry_mode && ValueWithinLimits(nw) )
    {
	nw->number.value.d = nw->editor.value;
	if (nw->number.data_type == FLOAT)
	    nw->number.value.f = (float)nw->number.value.d;
	if (nw->number.data_type == INTEGER)
	{
	    if( nw->number.value.d >= 0.0 )
		nw->number.value.i = (int)(nw->number.value.d + 0.5);
	    else
		nw->number.value.i = (int)(nw->number.value.d - 0.5);
	}
    }
    if( XtHasCallbacks((Widget)nw, XmNactivateCallback)
        == XtCallbackHasSome )
    {
	call_value.value = nw->number.value.d;
	call_value.reason = XmCR_ACTIVATE;
	XtCallCallbacks((Widget)nw, XmNactivateCallback, &call_value);
    }
}


/*  Subroutine:	ArmOrDisarm
 *  Purpose:	Toggle arm/disarm with button clicking
 */
static void ArmOrDisarm( XmNumberWidget nw, XEvent* event )
{
    if( nw->number.key_entry_mode ) {
	UnGrabKbd(nw);
	Disarm(nw, event);
    } else
	Arm(nw, event);
}


/*  Subroutine:	Arm
 *  Purpose:	Set up number widget for keybourd input.
 */
static void Arm( XmNumberWidget nw, XEvent* event )
{
    XmDoubleCallbackStruct call_value;
    Boolean		   is_fixed;
#if (XmVersion > 1001)
    Window                 window;
#endif


    if( (!nw->number.visible) || (!nw->number.allow_key_entry_mode ) )
	return;
#if (XmVersion >= 1001)
    XmProcessTraversal((Widget)nw, XmTRAVERSE_CURRENT);
#if (XmVersion > 1001)
    window = XtWindow(nw);
    XSetInputFocus(XtDisplay(nw),window,RevertToPointerRoot,CurrentTime);
#endif
    XtAddGrab((Widget)nw, True, True);
#else
    _XmGrabTheFocus(nw);
#endif
    if( (XtHasCallbacks((Widget)nw, XmNarmCallback) == XtCallbackHasSome) )
    {
	call_value.value = nw->number.value.d;
	call_value.reason = XmCR_ARM;
	XtCallCallbacks((Widget)nw, XmNarmCallback, &call_value);
    }
    /*  Perform all initializations to simplify synchronization issues  */
    is_fixed = nw->editor.is_fixed;
    (void)memset(&(nw->editor), 0, sizeof(XmNumberEditorPart));
    nw->editor.is_fixed = is_fixed;
    if( nw->number.decimal_places == 0 ) 
	{
	nw->editor.is_float = False;
	} 
    else 
	{
	nw->editor.is_float = True;
	if( nw->number.decimal_places > 0 ) 
	    {
	    nw->editor.decimal_minimum =
	      pow(0.1, (double)(nw->number.decimal_places));
	    } 
	}
    if( nw->number.value_minimum.d < 0.0 ) {
	nw->editor.is_signed = True;
    }
    nw->number.key_entry_mode = True;
    if( nw->primitive.shadow_thickness > 0 )
	DisplayNumberShadow(nw);
    UpdateNumberEditorDisplay(nw);
}

/*
 * release the keyboard
 * split out from Disarm 2/15/95 because you don't always have it grabbed
 * when calling Disarm()
 */
static void ReleaseKbd( XmNumberWidget nw, XEvent* event ) 
{ if( nw->number.key_entry_mode ) UnGrabKbd(nw); }
static void UnGrabKbd( XmNumberWidget nw)
{
#if (XmVersion >= 1001)
    XtRemoveGrab((Widget)nw);
#if (XmVersion > 1001)
    XSetInputFocus(XtDisplay(nw),PointerRoot,RevertToPointerRoot,CurrentTime);
#endif
#endif
}

/*  Subroutine:	Disarm
 *  Purpose:	Take number widget out of keyboard input mode
 */
static void Disarm( XmNumberWidget nw, XEvent* event )
{
    XmDoubleCallbackStruct call_value;


    if( nw->number.key_entry_mode ) {
	nw->number.key_entry_mode = False;
	if( nw->primitive.shadow_thickness > 0 )
	    DisplayNumberShadow(nw);
	XmShowNumberValue(nw);
	if( (XtHasCallbacks((Widget)nw, XmNdisarmCallback)
	     == XtCallbackHasSome) )
	{
	    call_value.value = nw->number.value.d;
	    call_value.reason = XmCR_DISARM;
	    XtCallCallbacks((Widget)nw, XmNdisarmCallback, &call_value);
	}
    }
}


/*  Subroutine:	ActivateAndDisarm
 *  Purpose:	Register new value and deactivate keyboard input mode
 */
static void ActivateAndDisarm( XmNumberWidget nw, XEvent* event )
{
    if( nw->number.key_entry_mode && ValueWithinLimits(nw) ) {
	UnGrabKbd(nw);
	Activate(nw, event);
	Disarm(nw, event);
    }
}


/* Subroutine:	Help
 * Purpose:	Call the application registered help callbacks
 * Note:	Uses Xm efficient alternative extensions to Xt (XtWidget...)
 */
static void Help( XmNumberWidget nw, XEvent* event )
{
    XmAnyCallbackStruct call_value;

    if( XtHasCallbacks((Widget)nw, XmNhelpCallback) == XtCallbackHasSome )
    {
	call_value.reason = XmCR_HELP;
	call_value.event = event;
	XtCallCallbacks((Widget)nw, XmNhelpCallback, &call_value);
    }
}


/*  Subroutine:	SelfInsert
 *  Purpose:	Insert characters as they are typed from keyboard input
 *		(In response to KeyPress events)
 */
/* ARGSUSED */
static void SelfInsert
  ( XmNumberWidget nw, XEvent *event, char **params, Cardinal *num_params )
#ifdef EXPLAIN
     XmNumberWidget nw;
     XEvent *event;
     char **params;
     Cardinal *num_params;
#endif
{
    KeySym keysym;			/* X code for key that was struck    */
    XComposeStatus compose;
    int num_chars;
    char string[2*MAX_EDITOR_STRLEN];	/* buffer to recieve ASCII code	     */

    if( nw->number.key_entry_mode ) {
	num_chars = XLookupString((XKeyEvent *)event, string, sizeof(string),
				  &keysym, &compose);
	/*  Trivially omit modifiers and multi-char entries, then try input  */
	/* ((keysym & 0xff00) == 0xff00) */
	if( (!IsFunctionKey(keysym)) && (!IsMiscFunctionKey(keysym)) &&
	    (!IsPFKey(keysym)) && (!IsModifierKey(keysym)) &&
	    (InsertChars(nw, string, num_chars)) )
	    UpdateNumberEditorDisplay(nw);
    }
}


/* ARGSUSED */
static void DeleteForwardChar
  ( XmNumberWidget nw, XEvent *event, char **params, Cardinal *num_params )
{
    if( nw->number.key_entry_mode ) {
	if( DeleteChars(nw, 1) )
	    UpdateNumberEditorDisplay(nw);
    }
}


/* ARGSUSED */
static void DeleteBackwardChar
  ( XmNumberWidget nw, XEvent *event, char **params, Cardinal *num_params )
{
    if( nw->number.key_entry_mode ) {
	if( DeleteChars(nw, -1) )
	    UpdateNumberEditorDisplay(nw);
    }
}


/* ARGSUSED */
static void MoveBackwardChar
  ( XmNumberWidget nw, XEvent *event, char **params, Cardinal *num_params )
{
    if( nw->number.key_entry_mode && MovePosition(nw, -1) )
	UpdateNumberEditorDisplay(nw);
}


/* ARGSUSED */
static void MoveForwardChar
  ( XmNumberWidget nw, XEvent *event, char **params, Cardinal *num_params )
{
    if( nw->number.key_entry_mode && MovePosition(nw, 1) )
	UpdateNumberEditorDisplay(nw);
}


/* ARGSUSED */
static void MoveToLineStart
  ( XmNumberWidget nw, XEvent *event, char **params, Cardinal *num_params )
{
    if( nw->number.key_entry_mode && MovePosition(nw, -nw->editor.string_len) )
	UpdateNumberEditorDisplay(nw);
}


/* ARGSUSED */
static void MoveToLineEnd
  ( XmNumberWidget nw, XEvent *event, char **params, Cardinal *num_params )
{
    if( nw->number.key_entry_mode && MovePosition(nw, nw->editor.string_len) )
	UpdateNumberEditorDisplay(nw);
}


/*  Subroutine:	ValueWithinLimits
 *  Purpose:	Check the editor value to verify that it is within the limits
 */
static Boolean ValueWithinLimits( XmNumberWidget nw )
{
     if (nw->number.data_type == INTEGER)
        {
	if( nw->editor.value < nw->number.value_minimum.i )
	    return EditError(nw, nw->editor.string, BelowMinimum, -1);
	else if( nw->editor.value > nw->number.value_maximum.i )
	    return EditError(nw, nw->editor.string, AboveMaximum, -1);
	else
	    return TRUE;
        }
    if (nw->number.data_type == FLOAT)
        {
	if( nw->editor.value < nw->number.value_minimum.f )
	    return EditError(nw, nw->editor.string, BelowMinimum, -1);
	else if( nw->editor.value > nw->number.value_maximum.f )
	    return EditError(nw, nw->editor.string, AboveMaximum, -1);
	else
	    return TRUE;
        }
    if (nw->number.data_type == DOUBLE)
        {
	if( nw->editor.value < nw->number.value_minimum.d )
	    return EditError(nw, nw->editor.string, BelowMinimum, -1);
	else if( nw->editor.value > nw->number.value_maximum.d )
	    return EditError(nw, nw->editor.string, AboveMaximum, -1);
	else
	    return TRUE;
        }
}


/*  Subroutine:	MovePosition
 *  Purpose:	Generic routine to move the insert position
 */
static Boolean MovePosition( XmNumberWidget nw, int num_chars )
{
    int old_position = nw->editor.insert_position;
    nw->editor.insert_position += num_chars;
    if( nw->editor.insert_position < 0 )
	nw->editor.insert_position = 0;
    else if( nw->editor.insert_position > nw->editor.string_len )
	nw->editor.insert_position = nw->editor.string_len;
    if( nw->editor.insert_position != old_position )
	return TRUE;
    else
	return FALSE;
}


/*  Subroutine:	InsertChars
 *  Purpose:	Generic routine to insert a character or string into the
 *		Number.Editor string.
 *  Note:	Leading and trailing spaces are stripped from the inserted
 *		string.
 */
static Boolean InsertChars( XmNumberWidget nw, char* in_string, int num_chars )
{
    char temp_string[MAX_EDITOR_STRLEN];
    int old, new, temp, insert;
    int insert_position;

    if (nw->editor.string_len + num_chars > MAX_EDITOR_STRLEN) {
	XBell(XtDisplay(nw), 0);
	return False;
    }

    for( old=0; old<nw->editor.insert_position; old++ )
	temp_string[old] = nw->editor.string[old];
    for( new=0; isspace(in_string[new]); new++ );
    for( insert=0, temp=old;
	   (new < num_chars)
	&& (in_string[new] != '\0')
	&& (!isspace(in_string[new]));
	 new++, temp++, insert++ )
	temp_string[temp] = in_string[new];
    for( ; old<nw->editor.string_len; old++, temp++ )
	temp_string[temp] = nw->editor.string[old];
    temp_string[temp] = '\0';
    insert_position = nw->editor.insert_position + insert;
    return TestParse(nw, temp_string, insert_position);
}


/*  Subroutine:	DeleteChars
 *  Purpose:	Generic routine to remove consecutive characters from the
 *		Number.Editor string.
 *  Note:	Positive num_chars deletes from the insert_position forward.
 *		Negative num_chars deletes before the insert_position.
 */
static Boolean DeleteChars( XmNumberWidget nw, int num_chars )
{
    int i, j;
    int start_position, end_position, insert_position;

    char temp_string[MAX_EDITOR_STRLEN];
    if( num_chars > 0 )
    {
	start_position = nw->editor.insert_position;
	end_position = start_position + num_chars;
    }
    else if( num_chars < 0 )
    {
	end_position = nw->editor.insert_position;
	start_position = end_position + num_chars;
    }
    else
	/*  No deletion requested  */
	return FALSE;
    /*  If string is already empty, just beep  */
    if( nw->editor.string_len <= 0 )
	return EditError(nw, nw->editor.string, StringEmpty, -1);
    if( start_position < 0 )
	start_position = 0;
    if( end_position > nw->editor.string_len )
	end_position = nw->editor.string_len;
    if( start_position >= end_position )
	return FALSE;
    for( i=0; i<start_position; i++ )
	temp_string[i] = nw->editor.string[i];
    for( j=end_position; j<nw->editor.string_len; j++, i++ )
	temp_string[i] = nw->editor.string[j];
    temp_string[i] = '\0';
    if( num_chars < 0 )
	insert_position = Max(0, nw->editor.insert_position + num_chars);
    else
	insert_position = nw->editor.insert_position;
    if( temp_string[0] == '\0' )
    {
	nw->editor.string_len = 0;
	nw->editor.insert_position = 0;
	nw->editor.string[0] = '\0';
	nw->editor.value = 0.0;
    } else
	return TestParse(nw, temp_string, insert_position);
}


/*  Subroutine:	TestParse
 *  Purpose:	Parse through the string checking for specific errors
 *		and install in nw->editor if no errors found.
 *  Returns:	TRUE if new string was installed, else FALSE
 */
static Boolean
  TestParse( XmNumberWidget nw, char* in_string, int insert_position )
{
    int i, j;
    struct TestStruct edit;

    edit.insert_position = insert_position;

    /* If the leading char is a '.', prepend a zero */
    if( in_string[0] == '.' ) {
	for (i=strlen(in_string); i >= 0; i--)
	    {
	    in_string[i+1] = in_string[i];
	    }
	in_string[0] = '0';
	insert_position++;
    }

    /*  Initialize input string and remove leading spaces  */
    for( i=0; isspace(in_string[i]); i++ )
	--insert_position;
    /*  Parse for a sign  */
    if( !isdigit(in_string[i]) )
    {
	if( in_string[i] == '-' ) {
	    if( nw->editor.is_signed )
		edit.mantissa_negative = TRUE;
	    else
		return EditError(nw, in_string, NoNegative, i);
	} else if( in_string[i] == '+' ) {
	    --insert_position;
	    edit.mantissa_negative = FALSE;
	} else
	    return EditError(nw, in_string, InvalidChar, i);
	i = 1;
    }
    else
	edit.mantissa_negative = FALSE;
    /*  Initialize output string and handle mantissa sign indication  */
    if( nw->editor.is_signed && edit.mantissa_negative ) {
	edit.string[0] = '-';
	j = 1;
    } else
	j = 0;
    /*  Parse through the mantissa integer part  */
    while( isdigit(in_string[i]) ) {
	edit.string[j] = in_string[i];
	++j;
	++i;
    }
    /*  Parse for mantissa fractional part  */
    if( in_string[i] == DECIMAL_POINT )
    {
	double decimal = 0.1;
	int unwarned = 1;

	if( !nw->editor.is_float )
	    return EditError(nw, in_string, NoFloat, i);
	/*  Copy over the decimal 'point'  */
	edit.string[j] = in_string[i];
	++i;
	++j;
	/*  Parse the mantissa fraction  */
	while( isdigit(in_string[i]) ) {
	    if( nw->editor.is_fixed
	       && (decimal < nw->editor.decimal_minimum) ) {
		/*  Omit all excess, but give warning only on first case  */
		if( unwarned )
		    EditError(nw, in_string, ExcessPrecision, i);
		/*  Realign position with shortened string  */
		if( insert_position > i )
		    --edit.insert_position;
	    } else {
		edit.string[j] = in_string[i];
		j++;
	    }
	    decimal *= 0.1;
	    ++i;
	}
    }
    /*  Parse for Exponent  */
    if( IsExponentSymbol(in_string[i]) )
    {
	if( nw->editor.is_fixed )
	    return EditError(nw, in_string, NoExponent, i);
	edit.string[j] = in_string[i];
	j++;
	i++;
	/*  Check for exponent sign or other garbage  */
	if( !isdigit(in_string[i]) )
	{
	    if( in_string[i] == '-' ) {
		if( !nw->editor.is_float )
		    return EditError(nw, in_string, NoFloat, i);
		edit.string[j] = '-';
		j++;
		i++;
	    } else if( in_string[i] == '+' ) {
		++i;
	    } else if( in_string[i] == '\0' ) {
	    } else
		return EditError(nw, in_string, InvalidChar, i);
	}
	/*  Parse exponent value (or initialize to 0  */
	if( isdigit(in_string[i]) ) {
	    while( isdigit(in_string[i]) ) {
		edit.string[j] = in_string[i];
		++j;
		++i;
	    }
	    edit.string[j] = '\0';
	} else {
	    edit.string[j] = '0';
	    edit.string[j+1] = '\0';
	}
    }
    else
	edit.string[j] = '\0';
    /*  Make sure that string ends reasonably  */
    if( (!isspace(in_string[i])) && (in_string[i] != '\0') )
	return EditError(nw, in_string, InvalidChar, i);
    edit.string_len = j;
    if( insert_position < 0 )
	edit.insert_position = 0;
    else if( insert_position > j )
	edit.insert_position = j;
    else
	edit.insert_position = insert_position;
    edit.value = strtod(edit.string, NULL);
    if( errno == ERANGE )
	return EditError(nw, in_string, BadInput, -1);
    /*  Check limits if subsequent entries won't bring us back into range  */
    if( nw->editor.is_fixed ) 
    {
	if( edit.value < 0.0 ) 
	{
	    if( edit.value < nw->number.value_minimum.d )
		return EditError(nw, in_string, BelowMinimum, -1);
	} 
	else 
	{
	    if( nw->number.value_maximum.d > 0.0 )
		if( edit.value > nw->number.value_maximum.d )
		    return EditError(nw, in_string, AboveMaximum, -1);
	}
    }
    (void)strcpy(nw->editor.string, edit.string);
    nw->editor.insert_position = edit.insert_position;
    nw->editor.value = edit.value;
    nw->editor.string_len = edit.string_len;
    return TRUE;
}


/*  Subroutine:	EditError
 *  Purpose:	Centralized handling of parsing errors to provide meaningful
 *		feedback.
 */
static Boolean
  EditError( XmNumberWidget nw, char* string, int msg, int char_place )
{
    int place;
    char message[100];
    XmNumberWarningCallbackStruct call_value;

    /*
     * Don't generate error messages for now...
     */
    switch(msg)
    {
      case NoNegative:
	call_value.reason = XmCR_NUM_WARN_NO_NEG;
	(void)sprintf(message, "Negative value not permitted.");
	break;

      case InvalidChar:
#ifdef JUST_BELL
	call_value.reason = XmCR_NUM_WARN_INVALID_CHAR;
	place = sprintf(message, "Invalid character.");
	if( char_place >= 0 ) {
	    if( isalnum(string[char_place]) )
		(void)sprintf(&message[place - 1], ": '%c'\n",
			      string[char_place]);
	    else
		(void)sprintf(&message[place - 1], ": <%o>\n",
			      string[char_place]);
	}
#endif
	XBell(XtDisplay(nw), 0);
	return FALSE;
	break;

      case StringEmpty:
	 return FALSE;
	 break;

      case NoFloat:
	call_value.reason = XmCR_NUM_WARN_NO_FLOAT;
	(void)sprintf(message, "Value must be integer.");
	break;

      case NoExponent:
	call_value.reason = XmCR_NUM_WARN_NO_EXPONENT;
	(void)sprintf(message, "Exponential notation not permitted.");
	break;

      case ExcessPrecision:
	call_value.reason = XmCR_NUM_WARN_EXCESS_PRECISION;
	(void)sprintf(message, 
		      "Precision of entered value exceeds decimal places: %d",
                      nw->number.decimal_places);
	break;

      case AboveMaximum:
	call_value.reason = XmCR_NUM_WARN_ABOVE_MAX;
	(void)sprintf(message, "Value is greater than the maximum: %g.",
		      nw->number.value_maximum.d);
	break;

      case BelowMinimum:
	call_value.reason = XmCR_NUM_WARN_BELOW_MIN;
	(void)sprintf(message, "Value is less than the minimum: %g.",
		      nw->number.value_minimum.d);
	break;

      case BadInput:
	call_value.reason = XmCR_NUM_WARN_BAD_INPUT;

      default:
	(void)sprintf(message, "Input not parseable.");
	break;
    }
    call_value.message = message;

    XBell(XtDisplay(nw), 0);
    UnGrabKbd(nw);
    Disarm(nw, NULL);
    XtCallCallbacks((Widget)nw, XmNwarningCallback, &call_value);
    return FALSE;
}

#if defined(__cplusplus) || defined(c_plusplus)
 }
#endif
