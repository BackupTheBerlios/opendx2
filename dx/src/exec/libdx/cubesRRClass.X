///////////////////////////////////////////////////////////////////////
//                        DX  SOURCEFILE                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////

//
// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/libdx/cubesRRClass.X,v 1.1 1999/03/24 15:18:37 gda Exp $
//


typedef struct cubesrrinterpolator	*CubesRRInterpolator;

INCLUDE 		fieldinterpClass.X
SUBCLASS    	CubesRRInterpolator OF FieldInterpolator
IMPLEMENTS  	PrimitiveInterpolate Delete Copy LocalizeInterpolator

CubesRRInterpolator _dxfNewCubesRRInterpolator(Field,
					enum interp_init, double, Matrix *);
int   RecognizeCubesRR(Field);

struct cubesrrinterpolator
{
    struct fieldinterpolator	fieldInterpolator;

    int	    size[3];	/* sizeof subarray size for indexing */
    int	    counts[3];	/* regular array counts for bounds check */
    int	    eltStrides[3]; /* strides in element space */

    Array   pointsArray;
    Array   dataArray;
    int	    nElements;

    ArrayHandle data;

    float   fuzz;
    int     meshOffsets[3];
};

CubesRRInterpolator _dxf_NewCubesRRInterpolator(Field,
			enum interp_init, float, Matrix *,
			struct cubesrrinterpolator_class *);

CubesRRInterpolator _dxf_CopyCubesRRInterpolator(CubesRRInterpolator, 
			CubesRRInterpolator, enum copy);
