///////////////////////////////////////////////////////////////////////
//                        DX  SOURCEFILE                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////


/*
\section{Screen class}
A screen object specifies an object that maintains an alignment with the
screen (output image) independent of the transform or camera view.
*/

INCLUDE  objectClass.X

SUBCLASS Screen OF Object
IMPLEMENTS Copy BoundingBox Delete
IMPLEMENTS Shade Paint Gather

struct screen {				/* screen object */
    struct object object;		/* object preamble */
    Object o;				/* screen-aligned object */
    int position;			/* positioning option */
    int z;				/* -1=behind, 0=in-place, 1=in front */
};

