/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>



#include <math.h>
#include <string.h>
#include <dx/dx.h>
#include "internals.h"


/*
 * DXNeighbors routines
 */

Array _dxf_TetraNeighbors(Field f);
Array _dxf_CubeNeighbors(Field f);

static Array TriNeighbors(Field f);
static Array QuadNeighbors(Field f);

struct hash {		/* entry per face */
    int element;	/* element containing face */
    short face;		/* face number in element */
    short count;	/* number of occurences */
};

#define SORT(a,b) {int t; if (a<b) t=a, a=b, b=t;}

Array
DXNeighbors(Field f)
{
    Array a = NULL;

    /* just return if "neighbors" component is already present */
    a = (Array) DXGetComponentValue(f, NEIGHBORS);
    if (a)
	return a;

    DXMarkTime("start neighbors");

    /* try various types of neighbors */
    a = _dxf_TetraNeighbors(f);
    if (!a) a = TriNeighbors(f);
    if (!a) a = _dxf_CubeNeighbors(f);
    if (!a) a = QuadNeighbors(f);

    DXMarkTime("end neighbors");

    return a;
}

/*
 *
 * Given a tetrahedron defined by four points:
 *
 *     tetra
 *     a b c d
 *
 * then we number its four triangles 0,1,2,3 as follows:
 *
 *     tri 0   tri 1   tri 2   tri 3
 *     b c d   c d a   d a b   a b c
 */

static
Triangle
tetratri(Tetrahedron tetra, int i)
{
    Triangle tri;
    switch (i) {
    case 0: tri.p=tetra.q; tri.q=tetra.r; tri.r=tetra.s; break;
    case 1: tri.p=tetra.r; tri.q=tetra.s; tri.r=tetra.p; break;
    case 2: tri.p=tetra.s; tri.q=tetra.p; tri.r=tetra.q; break;
    case 3: tri.p=tetra.p; tri.q=tetra.q; tri.r=tetra.r; break;
    }
    SORT(tri.p, tri.q);
    SORT(tri.q, tri.r);
    SORT(tri.p, tri.q);
    return tri;
}


/*
 * Note - the following routine is called from DXEndField, so it must
 * put the neighbors into f, i.e. that can't be moved up to DXNeighbors().
 */

Array
_dxf_TetraNeighbors(Field f)
{
    Array a;
    int nsurface=0, ninner=0, ns, ni, ntetra, nhash;
    int tetra, tri, h, n, goal, goal2;
    Tetrahedron *tetrahedra;
    Triangle t, tt;
    int (*neighbors)[4];
    struct hash *hash;

    /* get tetrahedral connections */
    a = DXGetConnections(f, "tetrahedra");
    if (!a)
	return NULL;
    if (!DXTypeCheck(a, TYPE_INT, CATEGORY_REAL, 1, 4))
	DXErrorReturn(ERROR_BAD_TYPE, "tetrahedra have bad type");
    DXGetArrayInfo(a, &ntetra, NULL, NULL, NULL, NULL);
    tetrahedra = (Tetrahedron *) DXGetArrayData(a);

    /* "neighbors" component */
    a = DXNewArray(TYPE_INT, CATEGORY_REAL, 1, 4);
    if (!a)
	return NULL;
    if (!DXAddArrayData(a, 0, ntetra, NULL))
	return NULL;
    neighbors = (int (*)[4]) DXGetArrayData(a);
    memset((int *)neighbors, -1, ntetra*sizeof(*neighbors));

    /* put it in the field */
    DXSetComponentValue(f, NEIGHBORS, (Object)a);
    DXSetAttribute((Object)a, REF, O_CONNECTIONS);
    DXSetAttribute((Object)a, DEP, O_CONNECTIONS);
    DXSetAttribute((Object)a, DER, O_CONNECTIONS);

    /*
     * goal = 4*ntetra faces is conservative upper bound
     * goal2 is estimate of number hash entries plus 10%
     * NB - nhash should be power of 2
     */
    goal = 4*ntetra;
    goal2 = (2*ntetra + 6*pow(ntetra/5.0,2.0/3.0)) * 1.1;
    for (nhash=1; nhash<goal; nhash*=2)
	continue;
    DXDebug("N", "ntetra %d goal %d goal2 %d nhash %d",
	  ntetra, goal, goal2, nhash);
    hash = (struct hash *) DXAllocateLocalZero(nhash * sizeof(struct hash));
    if (!hash) {
	DXResetError();
	hash = (struct hash *) DXAllocateZero(nhash * sizeof(struct hash));
    }
    if (!hash) {
	DXResetError();
	goal = goal2;
	for (nhash=1; nhash<goal; nhash*=2)
	    continue;
	DXDebug("N", "new goal %d nhash %d", goal, nhash);
	hash = (struct hash *) DXAllocateLocalZero(nhash * sizeof(struct hash));
	if (!hash) {
	    DXResetError();
	    hash = (struct hash *) DXAllocateZero(nhash * sizeof(struct hash));
	}
	if (!hash)
	    return NULL;
    }

    /* put triangles into hash table */
    for (tetra=0, n=0; tetra<ntetra; tetra++) {

	/* four triangles per tetra */
	for (tri=0; tri<4; tri++) {

	    /* compute canonical triangle tri for tetrahedron tetra */
	    t = tetratri(tetrahedra[tetra], tri);

	    /* find hash table entry */
	    h = (t.p + 17*t.q + 513*t.r) & (nhash-1);
	    while (hash[h].count) {
		tt = tetratri(tetrahedra[hash[h].element], hash[h].face);
		if (t.p==tt.p && t.q==tt.q && t.r==tt.r)
		    break;
		h = (h+1) & (nhash-1);
	    }

	    /* increment the count */
	    hash[h].count += 1;

	    /* do neighbors, count inner/surface */
	    if (hash[h].count==1) {		/* new face: */
		if (++n>nhash)
		    DXErrorGoto(ERROR_NO_MEMORY, "neighbors hash table is full");
		nsurface += 1;			/*     assume surface */
		hash[h].element = tetra;	/*     put entry in table */
		hash[h].face = tri;
	    } else if (hash[h].count&1) {	/* count now odd, was even: */
		nsurface += 1;			/*     now surface */
		ninner -= 1;			/*     was inner */
	    } else {				/* count now even, was odd: */
		nsurface -= 1;			/*     was surface */
		ninner += 1;			/*     now inner */
		if (hash[h].count==2) {
		    neighbors[tetra][tri] = hash[h].element;
		    neighbors[hash[h].element][hash[h].face] = tetra;
		}
	    }
	}
    }

    /* check number of faces */
    if (DXQueryDebug("N")) {

	for (ns=0, ni=0, tetra=0; tetra<ntetra; tetra++) {
	    for (tri=0; tri<4; tri++) {
		if (neighbors[tetra][tri]<0)
		    ns++;
		else
		    ni++;
	    }
	}
	DXDebug("N", "%d faces (%d surface, %d inner), %d entries",
	      ns+ni, ns, ni, n);
	if (nsurface!=ns || ninner!=ni)
	    DXWarning("multiply shared faces! (%d surface, %d inner)",
		    nsurface, ninner);
    }

    DXFree((Pointer)hash);
    return a;

error:
    DXFree((Pointer)hash);
    return NULL;
}

/*
 *
 * Given a triangle defined by three points:
 *
 *     triangle
 *      a b c
 *
 * then we number its three edges 0,1,2 as follows:
 *
 *     edge 0   edge 1   edge 2
 *      b  c     c  a     a  b
 */

static
Line
triedge(Triangle tri, int i)
{
    Line edge;

    switch (i) {
    case 0: edge.p=tri.q; edge.q=tri.r; break;
    case 1: edge.p=tri.r; edge.q=tri.p; break;
    case 2: edge.p=tri.p; edge.q=tri.q; break;
    }

    SORT(edge.p, edge.q);

    return edge;
}

static Array
TriNeighbors(Field f)
{
    Array a;
    int ntriangles, nhash;
    int tri, edge, h;
    Triangle *triangle;
    Line t, tt;
    int (*neighbors)[3];
    struct hash *hash;

    /* get triangle connections */
    a = DXGetConnections(f, "triangles");
    if (!a)
	return NULL;
    if (!DXTypeCheck(a, TYPE_INT, CATEGORY_REAL, 1, 3))
	DXErrorReturn(ERROR_BAD_TYPE, "triangles have bad type");
    DXGetArrayInfo(a, &ntriangles, NULL, NULL, NULL, NULL);
    triangle = (Triangle *) DXGetArrayData(a);

    /* "neighbors" component */
    a = DXNewArray(TYPE_INT, CATEGORY_REAL, 1, 3);
    if (!a)
	return NULL;
    if (!DXAddArrayData(a, 0, ntriangles, NULL))
	return NULL;
    neighbors = (int (*)[3]) DXGetArrayData(a);
    memset((int *)neighbors, -1, ntriangles*sizeof(*neighbors));

    /* put it in the field */
    DXSetComponentValue(f, NEIGHBORS, (Object)a);
    DXSetAttribute((Object)a, REF, O_CONNECTIONS);
    DXSetAttribute((Object)a, DEP, O_CONNECTIONS);
    DXSetAttribute((Object)a, DER, O_CONNECTIONS);

    /* 4*ntriangles edges is conservative upper bound;
       2*ntriangles more likely */
    /* NB - nhash should be power of 2 */
    for (nhash=1; nhash<4*ntriangles; nhash*=2)
	continue;
    hash = (struct hash *) DXAllocateLocalZero(nhash * sizeof(struct hash));
    if (!hash) {
	DXResetError();
	hash = (struct hash *) DXAllocateZero(nhash * sizeof(struct hash));
	if (!hash)
	    return NULL;
    }

    /* put triangles into hash table */
    for (tri=0; tri<ntriangles; tri++) {

	/* four triangles per tetra */
	for (edge=0; edge<3; edge++) {

	    /* compute canonical triangle tri for tetrahedron tetra */
	    t = triedge(triangle[tri], edge);

	    /* find hash table entry */
	    h = (t.p + 513*t.q) & (nhash-1);
	    while (hash[h].count) {
		tt = triedge(triangle[hash[h].element], hash[h].face);
		if (t.p==tt.p && t.q==tt.q)
		    break;
		h = (h+1) & (nhash-1);
	    }

	    /* increment the count */
	    hash[h].count += 1;

	    /* do neighbors, count inner/surface */
	    if (hash[h].count==1) {		/* new face: */
		hash[h].element = tri;		/*     put entry in table */
		hash[h].face = edge;
	    } else {				/* count now even, was odd: */
		if (hash[h].count==2) {
		    neighbors[tri][edge] = hash[h].element;
		    neighbors[hash[h].element][hash[h].face] = tri;
		}
	    }
	}
    }

    DXFree((Pointer)hash);

    return a;
}

/*
 *
 * Given a quad defined by four points:
 *
 *    q-----s
 *    |     |
 *    |     |
 *    p-----r
 *
 * where the horizontal axis iterates slowest,
 * we number its four edges 0,1,2,3 as follows:
 *
 *     edge 0   edge 1   edge 2   edge 3
 *      p  q     r  s     p  r     q  s
 *
 * which corresponds to (-x +x -y +y)
 */

static
Line
quadedge(Quadrilateral quad, int i)
{
    Line edge;

    switch (i) {
    case 0: edge.p=quad.p; edge.q=quad.q; break;
    case 1: edge.p=quad.r; edge.q=quad.s; break;
    case 2: edge.p=quad.p; edge.q=quad.r; break;
    case 3: edge.p=quad.q; edge.q=quad.s; break;
    }

    SORT(edge.p, edge.q);

    return edge;
}

static Array
QuadNeighbors(Field f)
{
    Array a;
    int nquads, nhash;
    int quad, edge, h;
    Quadrilateral *quadrilateral;
    Line t, tt;
    int (*neighbors)[4];
    struct hash *hash;

    /* get triangle connections */
    a = DXGetConnections(f, "quads");
    if (!a)
	return NULL;
    if (DXQueryGridConnections(a, NULL, NULL))
	return NULL;
    if (!DXTypeCheck(a, TYPE_INT, CATEGORY_REAL, 1, 4))
	DXErrorReturn(ERROR_BAD_TYPE, "quads have bad type");
    DXGetArrayInfo(a, &nquads, NULL, NULL, NULL, NULL);
    quadrilateral = (Quadrilateral *) DXGetArrayData(a);

    /* "neighbors" component */
    a = DXNewArray(TYPE_INT, CATEGORY_REAL, 1, 4);
    if (!a)
	return NULL;
    if (!DXAddArrayData(a, 0, nquads, NULL))
	return NULL;
    neighbors = (int (*)[4]) DXGetArrayData(a);
    memset((int *)neighbors, -1, nquads*sizeof(*neighbors));

    /* put it in the field */
    DXSetComponentValue(f, NEIGHBORS, (Object)a);
    DXSetAttribute((Object)a, REF, O_CONNECTIONS);
    DXSetAttribute((Object)a, DEP, O_CONNECTIONS);
    DXSetAttribute((Object)a, DER, O_CONNECTIONS);

    /* 4*nquads edges is conservative upper bound;
       2*nquads more likely */
    /* NB - nhash should be power of 2 */
    for (nhash=1; nhash<4*nquads; nhash*=2)
	continue;
    hash = (struct hash *) DXAllocateLocalZero(nhash * sizeof(struct hash));
    if (!hash) {
	DXResetError();
	hash = (struct hash *) DXAllocateZero(nhash * sizeof(struct hash));
	if (!hash)
	    return NULL;
    }

    /* put quad faces into hash table */
    for (quad=0; quad<nquads; quad++) {

	/* four edges per quadrilateral */
	for (edge=0; edge<4; edge++) {

	    t = quadedge(quadrilateral[quad], edge);

	    /* find hash table entry */
	    h = (t.p + 513*t.q) & (nhash-1);
	    while (hash[h].count) {
		tt = quadedge(quadrilateral[hash[h].element], hash[h].face);
		if (t.p==tt.p && t.q==tt.q)
		    break;
		h = (h+1) & (nhash-1);
	    }

	    /* increment the count */
	    hash[h].count += 1;

	    /* do neighbors, count inner/surface */
	    if (hash[h].count==1) {		/* new face: */
		hash[h].element = quad;		/*     put entry in table */
		hash[h].face = edge;
	    } else {				/* count now even, was odd: */
		if (hash[h].count==2) {
		    neighbors[quad][edge] = hash[h].element;
		    neighbors[hash[h].element][hash[h].face] = quad;
		}
	    }
	}
    }

    DXFree((Pointer)hash);

    return a;
}


/*
 *
 * Given a cube defined by eight points:
 *      
 *      r---- v
 *     /|    /|
 *    s-----w |
 *    | p- -|-t
 *    |/    |/
 *    q-----u
 *
 * where the horizontal axis iterates slowest,
 * we number its six faces 0,1,2,3,4,5 as follows:
 *
 *     face 0   face 1   face 2   face 3   face 4   face 5
 *      pqrs     tuvw     pqtu     rsvw     ptrv     qusw
 *
 * which corresponds to (-x +x -y +y -z +z)
 */

static
Quadrilateral
cubeface(Cube cube, int i)
{
    Quadrilateral face;

    switch (i) {
    case 0: face.p=cube.p; face.q=cube.q; face.r=cube.r; face.s=cube.s; break;
    case 1: face.p=cube.t; face.q=cube.u; face.r=cube.v; face.s=cube.w; break;
    case 2: face.p=cube.p; face.q=cube.q; face.r=cube.t; face.s=cube.u; break;
    case 3: face.p=cube.r; face.q=cube.s; face.r=cube.v; face.s=cube.w; break;
    case 4: face.p=cube.p; face.q=cube.t; face.r=cube.r; face.s=cube.v; break;
    case 5: face.p=cube.q; face.q=cube.u; face.r=cube.s; face.s=cube.w; break;
    }

    SORT(face.p, face.q);
    SORT(face.r, face.s);
    SORT(face.q, face.r);
    SORT(face.r, face.s);
    SORT(face.p, face.q);
    SORT(face.q, face.r);

    return face;
}

Array
_dxf_CubeNeighbors(Field f)
{
    Array a;
    int ncubes, nhash;
    int cubenum, face, h, n, goal, goal2;
    Cube *cube;
    Quadrilateral t, tt;
    int (*neighbors)[6];
    struct hash *hash;
    int nsurface = 0, ninner = 0;

    /* get cube connections */
    a = DXGetConnections(f, "cubes");
    if (!a)
	return NULL;
    if (DXQueryGridConnections(a, NULL, NULL))
	return NULL;
    if (!DXTypeCheck(a, TYPE_INT, CATEGORY_REAL, 1, 8))
	DXErrorReturn(ERROR_BAD_TYPE, "cubes have bad type");
    DXGetArrayInfo(a, &ncubes, NULL, NULL, NULL, NULL);
    cube = (Cube *) DXGetArrayData(a);

    /* "neighbors" component */
    a = DXNewArray(TYPE_INT, CATEGORY_REAL, 1, 6);
    if (!a)
	return NULL;
    if (!DXAddArrayData(a, 0, ncubes, NULL))
	return NULL;
    neighbors = (int (*)[6]) DXGetArrayData(a);
    memset((int *)neighbors, -1, ncubes*sizeof(*neighbors));

    /* put it in the field */
    DXSetComponentValue(f, NEIGHBORS, (Object)a);
    DXSetAttribute((Object)a, REF, O_CONNECTIONS);
    DXSetAttribute((Object)a, DEP, O_CONNECTIONS);
    DXSetAttribute((Object)a, DER, O_CONNECTIONS);

    /*
     * goal = 6*ncubes edges is conservative upper bound
     * goal2 is estimate of number hash entries plus 10%
     * NB - nhash should be power of 2
     */
    goal = 6*ncubes;
    goal2 = (3*ncubes + 3*pow((float)ncubes, 2.0/3.0)) * 1.1;
    for (nhash=1; nhash<goal; nhash*=2)
	continue;
    DXDebug("N", "ncubes %d goal %d goal2 %d nhash %d",
	  ncubes, goal, goal2, nhash);
    hash = (struct hash *) DXAllocateLocalZero(nhash * sizeof(struct hash));
    if (!hash) {
	DXResetError();
	hash = (struct hash *) DXAllocateZero(nhash * sizeof(struct hash));
    }
    if (!hash) {
	goal = goal2;
	for (nhash=1; nhash<goal; nhash*=2)
	    continue;
	DXDebug("N", "new goal %d nhash %d", goal, nhash);
	DXResetError();
	hash = (struct hash *) DXAllocateLocalZero(nhash * sizeof(struct hash));
	if (!hash) {
	    DXResetError();
	    hash = (struct hash *) DXAllocateZero(nhash * sizeof(struct hash));
	}
	if (!hash)
	    return NULL;
    }


    /* put quad faces into hash table */
    for (cubenum=0, n=0; cubenum<ncubes; cubenum++) {

	/* six faces per cube */
	for (face=0; face<6; face++) {

	    t = cubeface(cube[cubenum], face);

	    /* find hash table entry */
	    h = (t.p + 17*t.q + 513*t.r + 2377*t.s) & (nhash-1);
	    while (hash[h].count) {
		tt = cubeface(cube[hash[h].element], hash[h].face);
		if (t.p==tt.p && t.q==tt.q && t.r == tt.r && t.s == tt.s)
		    break;
		h = (h+1) & (nhash-1);
	    }

	    /* increment the count */
	    hash[h].count += 1;

	    /* do neighbors, count inner/surface */
	    if (hash[h].count==1) {		/* new face: */
		if (++n>nhash)
		    DXErrorGoto(ERROR_NO_MEMORY, "neighbors hash table is full");
		nsurface += 1;			/*     assume surface */
		hash[h].element = cubenum;	/*     put entry in table */
		hash[h].face = face;
	    } else if (hash[h].count&1) {	/* count now odd, was even: */
		nsurface += 1;			/*     now surface */
		ninner -= 1;			/*     was inner */
	    } else {				/* count now even, was odd: */
		nsurface -= 1;			/*     was surface */
		ninner += 1;			/*     now inner */
		if (hash[h].count==2) {
		    neighbors[cubenum][face] = hash[h].element;
		    neighbors[hash[h].element][hash[h].face] = cubenum;
		}
	    }
	}
    }

    DXDebug("N", "%d faces (%d surface, %d inner), %d entries",
	  nsurface+ninner, nsurface, ninner, n);

    DXFree((Pointer)hash);
    return a;

error:
    DXFree((Pointer)hash);
    return NULL;

}
