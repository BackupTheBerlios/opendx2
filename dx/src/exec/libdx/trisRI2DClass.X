///////////////////////////////////////////////////////////////////////
//                        DX  SOURCEFILE                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////

//
// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/libdx/trisRI2DClass.X,v 1.1 1999/03/24 15:18:40 gda Exp $
//


typedef struct trisri2dinterpolator *TrisRI2DInterpolator;

INCLUDE      fieldinterpClass.X
SUBCLASS    TrisRI2DInterpolator OF FieldInterpolator
IMPLEMENTS  PrimitiveInterpolate Delete Copy LocalizeInterpolator

#include "binSort.h"
				
TrisRI2DInterpolator _dxfNewTrisRI2DInterpolator(Field, 
			enum interp_init, double, Matrix *);
int   _dxfRecognizeTrisRI2D(Field);

typedef struct triCoord	 	 TriCoord;

struct triCoord
{
    float p, q, r;
};

struct trisri2dinterpolator
{
    struct fieldinterpolator	fieldInterpolator;

    Array 		pArray;
    ArrayHandle		pHandle;
    int			nPoints;

    Array		nArray;
    Triangle		*neighbors;

    Array 		tArray;
    Triangle		*triangles;
    int			nTriangles;

    Array 		dArray;
    ArrayHandle		dHandle;
    int			nElements;

    /*
     * Stuff for regular array of bins used to locate containing
     * triangle quickly
     */
    Grid		grid;

    int			hint;			/* last tet interpolated */
};

TrisRI2DInterpolator _dxf_NewTrisRI2DInterpolator(Field, 
			enum interp_init, float, Matrix *,
			struct trisri2dinterpolator_class *);

TrisRI2DInterpolator _dxf_CopyTrisRI2DInterpolator(TrisRI2DInterpolator,
			TrisRI2DInterpolator, enum copy);

