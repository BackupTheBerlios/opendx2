///////////////////////////////////////////////////////////////////////
//                        DX  SOURCEFILE                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////

//
// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/libdx/old/Attic/quadsRR2DClass.X,v 1.1 1999/03/24 15:18:39 gda Exp $
//


typedef	struct quadsrr2dinterpolator *QuadsRR2DInterpolator;

INCLUDE  	fieldinterpClass.X
SUBCLASS    	QuadsRR2DInterpolator OF FieldInterpolator
IMPLEMENTS  	PrimitiveInterpolate Delete Copy LocalizeInterpolator
				
QuadsRR2DInterpolator _dxfNewQuadsRR2DInterpolator(Field, 
			enum interp_init, double, Matrix *);
int   _dxfRecognizeQuadsRR2D(Field);

struct quadsrr2dinterpolator
{
    struct fieldinterpolator	fieldInterpolator;

    int	  size[2];	/* sizeof subarray size for indexing */
    int   counts[2];

    Array pointsArray;
    Array dataArray;
    int	  nElements;
    int   meshOffsets[2];

    ArrayHandle dHandle;

    float  fuzz;
};

QuadsRR2DInterpolator _dxf_NewQuadsRR2DInterpolator(Field, 
			enum interp_init, float, Matrix *,
			struct quadsrr2dinterpolator_class *);

QuadsRR2DInterpolator _dxf_CopyQuadsRR2DInterpolator(QuadsRR2DInterpolator, 
			QuadsRR2DInterpolator, enum copy);
