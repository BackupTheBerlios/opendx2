///////////////////////////////////////////////////////////////////////
//                        DX  SOURCEFILE                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////

//
// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/libdx/cubesIIClass.X,v 1.1 1999/03/24 15:18:37 gda Exp $
//


typedef struct cubesiiinterpolator *CubesIIInterpolator;

INCLUDE  	fieldinterpClass.X
SUBCLASS    	CubesIIInterpolator OF FieldInterpolator
IMPLEMENTS  	PrimitiveInterpolate Delete Copy LocalizeInterpolator

CubesIIInterpolator _dxfNewCubesIIInterpolator(Field,
			enum interp_init, double, Matrix *);

int   RecognizeCubesII(Field);

#include "binSort.h"

struct cubesiiinterpolator
{
    struct fieldinterpolator	fieldInterpolator;

    Array 		pointsArray;
    ArrayHandle		pHandle;
    int			nPoints;

    Array 		cubesArray;
    ArrayHandle		cHandle;
    int			nCubes;

    Array 		dataArray;
    ArrayHandle		dHandle;
    int			nElements;

    Array               nbrsArray;
    int                 *nbrs;

    int			gridCounts[3];
    int			Cyz, Cz;

    /*
     * grid for fast search
     */
    int			gridFlag;
    Grid		grid;

    int			*visited;
    int			vCount;

    int			hint;			/* last cube interpolated */
};

CubesIIInterpolator _dxf_NewCubesIIInterpolator(Field, 
				enum interp_init, float, Matrix *,
				struct cubesiiinterpolator_class *);

CubesIIInterpolator _dxf_CopyCubesIIInterpolator(CubesIIInterpolator,
				CubesIIInterpolator, enum copy);

