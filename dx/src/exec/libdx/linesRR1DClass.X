///////////////////////////////////////////////////////////////////////
//                        DX  SOURCEFILE                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////

//
// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/libdx/linesRR1DClass.X,v 1.1 1999/03/24 15:18:38 gda Exp $
//


typedef struct linesrr1dinterpolator *LinesRR1DInterpolator;

INCLUDE  	fieldinterpClass.X
SUBCLASS    	LinesRR1DInterpolator OF FieldInterpolator
IMPLEMENTS  	PrimitiveInterpolate Delete Copy LocalizeInterpolator

LinesRR1DInterpolator _dxfNewLinesRR1DInterpolator(Field, 
			enum interp_init, double, Matrix *);
int   	_dxfRecognizeLinesRR1D(Field);

struct linesrr1dinterpolator
{
    struct fieldinterpolator	fieldInterpolator;

    float 			origin;	  /* origin for each axis */
    float 			invDelta; /* inverse of stepsz for each axis */

    int				count;

    Array 			pointsArray;
    Array 			dataArray;
    int	  			nElements;

    ArrayHandle			data;

    float			fuzz;
};

LinesRR1DInterpolator _dxf_NewLinesRR1DInterpolator(Field, 
			enum interp_init, float, Matrix *m,
			    struct linesrr1dinterpolator_class *);

LinesRR1DInterpolator _dxf_CopyLinesRR1DInterpolator(LinesRR1DInterpolator,
			LinesRR1DInterpolator, enum copy);

