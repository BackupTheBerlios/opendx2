///////////////////////////////////////////////////////////////////////
//                        DX  SOURCEFILE                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////

/*
\section{Light class}
*/

INCLUDE  objectClass.X

SUBCLASS Light OF Object
IMPLEMENTS Delete Gather
IMPLEMENTS Paint Shade Copy

struct light {
    struct object object;	/* object preamble */

    enum {invalid, point, distant, ambient} kind;
				/* what kind of light */
    enum {camera, world} relative;
				/* relative to what */

    Point position;		/* position, if point */
    Vector direction;		/* direction, if distant */
    RGBColor color;		/* color, if point, distant, or ambient */
};

