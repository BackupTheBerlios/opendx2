/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/stream.h,v 1.3 1999/05/10 15:45:32 gda Exp $:
 */

#define DEFAULT_C	0.1

typedef struct instanceVars *InstanceVars;
typedef struct vectorPart   *VectorPart;
typedef struct vectorGrp    *VectorGrp;
typedef struct vectorField  *VectorField;

struct instanceVars
{
    VectorGrp	currentVectorGrp;
};

struct vectorPart
{
    Field  	field;
    int         dependency;       /* data dependency: pos or con       */
    float	min[3];
    float	max[3];
};
 
#define DEP_ON_POSITIONS        0x01
#define DEP_ON_CONNECTIONS      0x02

struct vectorField
{
    VectorGrp	 current;
    VectorGrp	 *members;
    int		 nmembers;
    int		 nDim;
};

#define POINT_TYPE	double
#define VECTOR_TYPE	double

struct vectorGrp
{
    InstanceVars (*NewInstanceVars)(VectorGrp);
    Error        (*FreeInstanceVars)(InstanceVars);
    int          (*FindElement)(InstanceVars, POINT_TYPE *);
    int          (*FindMultiGridContinuation)(InstanceVars, POINT_TYPE *);
    Error        (*Interpolate)(InstanceVars, POINT_TYPE *, VECTOR_TYPE *);
    Error        (*StepTime)(InstanceVars, double, VECTOR_TYPE *, double *);
    Error        (*FindBoundary)(InstanceVars, 
					POINT_TYPE *, VECTOR_TYPE *, double *);
    int          (*Neighbor)(InstanceVars, VECTOR_TYPE *);
    Error        (*CurlMap)(VectorGrp, MultiGrid);
    int          (*Weights)(InstanceVars, POINT_TYPE *);
    int          (*FaceWeights)(InstanceVars, POINT_TYPE *);
    Error        (*Delete)(VectorGrp);
    Error        (*Reset)(VectorGrp);
    int          n, nDim, multigrid;
    VectorPart   *p;
};


#define STREAM_BUF_POINTS	32

struct stream
{
    float *points;
    float *vectors;
    float *time;
    Array pArray;
    Array vArray;
    Array tArray;
    int   nDim;
    int   bufKnt, arrayKnt;
};

typedef struct stream *Stream;

Error      _dxfMinMaxBox(Field, float *, float *);
int        _dxfIsInBox(VectorPart, POINT_TYPE *, int, int);

