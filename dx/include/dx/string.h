/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/


#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* TeX starts here.  Do not remove this comment. */

String DXNewString(char *s);
/**
\index{DXNewString}
Creates a new string object and initializes it with a copy of the specified
null-terminated string.  Returns the object or null to indicate an error.
**/

char *DXGetString(String s);
/**
\index{DXGetString}
Returns a pointer to the string value of an object, or null to indicate
an error.
**/

String DXMakeString(char *s);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
