/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/


#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* TeX starts here. Do not remove this comment. */

/*
\section{Xform class}
\label{xformsec}
An {\tt Xform} is a renderable object that specifies a modeling
transformation matrix applied to another renderable object.  It is
included in groups that are input to the renderer to specify the
transformation from modeling coordinates to world coordinates.  See
the description of the {\tt DXTransform()} routine in section
\ref{transformsec}.
*/

Xform DXNewXform(Object o, Matrix m);
/**
\index{DXNewXform}
Creates a new object representing {\tt o} transformed by a modeling
transform specified by matrix {\tt m}, as described in Section
\ref{matrixsec}.  Returns the xform object, or returns null and sets the
error code to indicate an error.
**/

Xform DXGetXformInfo(Xform x, Object *o, Matrix *m);
/**
\index{DXGetXformInfo}
If {\tt o} is not null, this routine returns the object to be
transformed in {\tt *o}. If {\tt m} is not null, it returns the
transformation matrix in {\tt *m}.  Returns {\tt x}, or returns null
and sets the error code to indicate an error.
**/

Xform DXSetXformObject(Xform x, Object o);
Xform DXSetXformMatrix(Xform x, Matrix m);
/**
\index{DXSetXformObject}
Sets the object to which the transform is applied to {\tt o}.  Returns
{\tt x}, or returns null and sets the error code to indicate an error.
**/

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
