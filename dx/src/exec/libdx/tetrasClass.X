/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

//
// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/libdx/tetrasClass.X,v 1.2 1999/05/10 15:45:47 gda Exp $
//

typedef struct tetrasinterpolator *TetrasInterpolator;

INCLUDE      fieldinterpClass.X
SUBCLASS    TetrasInterpolator OF FieldInterpolator
IMPLEMENTS  PrimitiveInterpolate Delete Copy LocalizeInterpolator

#include "binSort.h"

TetrasInterpolator  _dxfNewTetrasInterpolator(Field,
				enum interp_init, double, Matrix *);
int   		    _dxfRecognizeTetras(Field);

typedef struct baryCoord	 BaryCoord;
typedef struct neighbors	 TetNeighbors;

struct baryCoord
{
    float p, q, r, s;
};

struct neighbors
{
    int p, q, r, s;
};

struct tetrasinterpolator
{
    struct fieldinterpolator	fieldInterpolator;

    Array		neighborsArray;
    TetNeighbors	*neighbors;

    Array 		pointsArray;
    ArrayHandle		points;
    int			nPoints;

    Array 		tetrasArray;
    Tetrahedron		*tetras;
    int			nTetras;

    Array 		dataArray;
    ArrayHandle		data;
    int			nElements;

    int			*visited;
    int			vCount;
    int			searchLimit;

    int			hint;		/* last tet interpolated */

    /*
     * Stuff for regular array of bins used to locate containing
     * tetrahedra quickly
     */
    int			gridFlag;
    Grid		grid;

    Array		mmArray;
    Point		*mm;
};

TetrasInterpolator _dxf_NewTetrasInterpolator(Field,
			enum interp_init, float, Matrix *,
			struct tetrasinterpolator_class *);

TetrasInterpolator _dxf_CopyTetrasInterpolator(TetrasInterpolator,
			TetrasInterpolator, enum copy);
