/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>



#include <math.h>
#include <string.h>
#include "lightClass.h"
#include "render.h"
#include "internals.h"

/*
 * forward declarations
 */

static Error work(struct xfield *, struct shade *, Array, Array *, Array *);


/*
 * Shading parameters
 */

struct shade {
    Object o;			/* root of input hierarchy */
    Group g;			/* group for output */
    Field f;			/* input field */
    Camera c;			/* camera */
    Matrix m;			/* the transformation matrix */
    char xflag;			/* whether a matrix was specified */
    char xonly;			/* do only transform */
    char notight;		/* whether to compute tight bbox */
    char nocolors;		/* whether colors are required */
    struct docount {		/* keep the docount structs in a list */
	int docount;		/* whether we count */
	struct docount *next;	/* list of them to allow freeing */
    } *docount, **docountlist;	/* our docount struct, and ptr to list */
    struct count *count;	/* pointer to count structure */
    short i;			/* field number for debugging */
    struct l {
	int nl;			/* number of lights */
	RGBColor ambient;	/* total ambient light */
	int na;			/* number of ambient lights specified */
	Light lights[100];	/* the transformed light object */
    } *l;
    struct parms {
	float ambient;		/* coefficient of ambient component */
	float diffuse;		/* coefficient of diffuse component */
	float specular;		/* coefficent of specular component */
	int shininess;		/* exponent of specular component */
    } front, back;
    float fuzz;			/* fuzz */
    float ff;			/* multiplier for fuzz: supports screen obj */
    enum approx approx;		/* rendering approximation */
    Private lightList;		/* light list object */
};


static struct parms default_parms = {
    1,		/* ambient */
    .7,		/* diffuse */
    .5,		/* specular */
    10,		/* shininess */
};

#define PARAMETER2(parm, name, type, get, msg) {			      $\
    type p;								      $\
    Object a;								      $\
    a = DXGetAttribute(o, name);						      $\
    if (a) {								      $\
	if (!get(DXGetAttribute(o, name), &p))				      $\
	    DXErrorReturn(ERROR_BAD_PARAMETER, name " must be " msg);	      $\
        new->front.parm = new->back.parm = p;				      $\
    }									      $\
    a = DXGetAttribute(o, "front " name);					      $\
    if (a && !get(a, &(new->front.parm)))				      $\
	    DXErrorReturn(ERROR_BAD_PARAMETER,				      $\
		"front " name " must be " msg);				      $\
    a = DXGetAttribute(o, "back " name);					      $\
    if (a && !get(a, &(new->back.parm)))				      $\
	    DXErrorReturn(ERROR_BAD_PARAMETER,				      $\
		"back " name " must be " msg);				      $\
}
    
#define PARAMETER1(parm, name, type, get, rhs, msg) {			      $\
    type p;								      $\
    Object a;								      $\
    a = DXGetAttribute(o, name);						      $\
    if (a) {								      $\
	if (!get(DXGetAttribute(o, name), &p))				      $\
	    DXErrorReturn(ERROR_BAD_PARAMETER, name " must be " msg);	      $\
        new->parm = rhs;						      $\
    }									      $\
}
    

Error
_dxf_approx(Object o, enum approx *approx)
{
    Object oo;
    char *s;

    if (oo=DXGetAttribute(o, "rendering approximation")) {
	if (!DXExtractString(oo, &s))
	    DXErrorReturn(ERROR_BAD_PARAMETER,
			"bad rendering approximation attribute");
	if (strcmp(s,"box")==0)
	    *approx = approx_box;
	else if (strcmp(s,"dots")==0)
	    *approx = approx_dots;
    }
    return OK;
}

static Error
parameters(Object o, struct shade *new, struct shade *old)
{
    Object a;

    *new = *old;
    if (old->xonly)
	return;

    PARAMETER2(ambient,   "ambient",   float, DXExtractFloat,   "a float");
    PARAMETER2(specular,  "specular",  float, DXExtractFloat,   "a float");
    PARAMETER2(diffuse,   "diffuse",   float, DXExtractFloat,   "a float");
    PARAMETER2(shininess, "shininess", int,   DXExtractInteger, "an integer");

    if (NULL != (a = DXGetAttribute(o, "fuzz")))
    {
	float f;

	if (! DXExtractFloat(a, &f))
	{
	    DXSetError(ERROR_BAD_PARAMETER, "\"fuzz\" must be a float");
	    return ERROR;
	}

	new->fuzz += f * new->ff;
    }
	    
    if (DXGetAttribute(o, "interference object")) old->count->fast = 0;
    if (DXGetAttribute(o, "interference group")) old->count->fast = 0;
    if (!_dxf_approx(o, &new->approx))
	return ERROR;
	
    return OK;
}


/*
 * Shade calls DXTransform to transform to world coordinates (making
 * a copy of the object), gathers the lights into an array, and then
 * calls _Shade to recursively traverse the object doing shading,
 * replacing the colors component in the copy.
 */

#define THREE(p) p.x, p.y, p.z
#define TWO(p)   p.x, p.y

Object
_dxfXShade(Object o, Camera c, struct count *count, Point *box)
{
    struct shade shade;
    Light distant_light = NULL;
    struct docount *docountlist = NULL, *dcl, *dclnext;
    int i;

    /* set up the arg block */
    shade.o = o;
    shade.c = c;
    shade.front = default_parms;
    shade.back = default_parms;
    shade.fuzz = 0;
    shade.ff = 1;
    shade.g = DXNewGroup();
    if (!shade.g) goto error;
    shade.xflag = 0;
    shade.xonly = 0;
    shade.nocolors = 0;
    shade.count = count;
    shade.l = (struct l *) DXAllocate(sizeof(struct l));
    if (!shade.l) goto error;
    shade.l->nl = 0;
    shade.l->ambient = DXRGB(0,0,0);
    shade.l->na = 0;
    shade.notight = DXGetAttribute(o, "notight")? 1 : 0;
    shade.docount = NULL;
    shade.docountlist = &docountlist;
    shade.approx = approx_none;
    shade.lightList = NULL;

    shade.lightList = _dxfGetLights(shade.o, shade.c);
    if (! shade.lightList)
	goto error;
    
    DXReference((Object)shade.lightList);

    /* create and execute the tasks */
    DXCreateTaskGroup();
    if (!_dxfShade(o, &shade)) goto error;
    ASSERT(shade.l->nl<100);

    /* default lights */
    if (shade.l->nl + shade.l->na == 0) {
	Point from, to;
	Vector eye, up, left, dir;
	DXGetView(c, &from, &to, &up);
	eye = DXNormalize(DXSub(from,to));
	left = DXCross(eye,up);
	dir = DXAdd(eye,left);
	distant_light = DXNewDistantLight(dir, DXRGB(1,1,1));
	if (!distant_light)
	    return NULL;
	shade.l->lights[shade.l->nl++] = distant_light;
	shade.l->ambient = DXRGB(.2, .2, .2);
    }

    /* do the tasks */
    if (!DXExecuteTaskGroup()) goto error;

    /* delete the list of docunt blocks allocated during traversal in _Shade */
    for (dcl=docountlist; dcl; dcl=dclnext) {
	dclnext = dcl->next;
	DXFree((Pointer)dcl);
    }	

    /* clean up and return */
    for (i=0; i<shade.l->nl; i++)
	DXDelete((Object)shade.l->lights[i]);
    DXFree((Pointer) shade.l);

    if (shade.lightList)
	DXDelete((Object)shade.lightList);

    return (Object) shade.g;

error:
    if (shade.l) {
	for (i=0; i<shade.l->nl; i++)
	    DXDelete((Object)shade.l->lights[i]);
	DXFree((Pointer)shade.l);
    }

    if (shade.g)
	DXDelete((Object)shade.g);

    if (shade.lightList)
	DXDelete((Object)shade.lightList);

    return NULL;
}


/*
 * Use the Shade traversal mechanism, but do only the
 * transform part.
 */

Object
DXTransform(Object o, Matrix *mp, Camera c)
{
    struct shade shade;

    memset(&shade, 0, sizeof(shade));
    shade.c = c;
    if (mp) {
	shade.m = *mp;
	shade.xflag = 1;
    }
    shade.xonly = 1;
    shade.nocolors = 1;
    shade.g = DXNewGroup();

    DXCreateTaskGroup();
    if (!_dxfShade(o, &shade)) return NULL;
    if (!DXExecuteTaskGroup()) return NULL;

    if (!DXCopyAttributes((Object)shade.g, o)) return NULL;
    return (Object) shade.g;
}



/* 
 * _Shade assumes that its first argument is a copy, and changes
 * the "colors" component.  The class implementations of the _Shade
 * method follow.
 */

static float
ipow(float x, int n)
{
    float xn;
    for (xn=1.0; n; n>>=1, x*=x)
	if (n&1)
	    xn *= x;
    return xn;
}

static Error
count(struct xfield *xf, struct shade *shade, Point *box);

static Error
task(struct shade *shade)
{
    int m, nl;
    RGBColor *fcolors=NULL, *bcolors=NULL;
    static RGBColor zero = {0,0,0};
    Array a, normals_array = NULL, box = NULL;
    Vector *normals;
    struct xfield xf;
    Field f = NULL;
    Matrix *mp = shade->xflag? &shade->m : NULL;
    Object o;
    int behind = 0;

    /* Get the components we need */
    if (DXEmptyField(shade->f))
	return OK;

    /* our result field */
    f = (Field) DXCopy((Object)shade->f, COPY_HEADER);
    if (!f)
	goto error;

    if (DXGetComponentValue(f, "faces"))
	if (! _dxfTriangulateField(f))
	    goto error;

    _dxf_XZero(&xf);
    if (!shade->nocolors) {
	if (!_dxf_XColors(f, &xf, XR_REQUIRED, XD_GLOBAL)) goto error;
	if (shade->approx!=approx_dots)
	    if (!_dxf_XOpacities(f, &xf, XR_OPTIONAL, XD_NONE)) goto error;
    }
    if (! _dxf_XPositions(f, &xf, XR_REQUIRED, XD_NONE)) goto error;
    if (shade->approx!=approx_dots) {
	if (!_dxf_XConnections(f, &xf, XR_OPTIONAL)) goto error;
	if (!_dxf_XPolylines(f, &xf, XR_OPTIONAL)) goto error;
	if (!_dxf_XNormals(f, &xf, XR_OPTIONAL, XD_NONE)) goto error;
	if (xf.colors_dep==dep_connections || xf.normals_dep==dep_connections) 
	    if (! _dxf_XInvalidConnections(f, &xf)) goto error;
	if (xf.colors_dep==dep_positions || xf.normals_dep==dep_positions) 
	    if (! _dxf_XInvalidPositions(f, &xf)) goto error;
	if (xf.colors_dep==dep_polylines || xf.normals_dep==dep_polylines) 
	    if (! _dxf_XInvalidPolylines(f, &xf)) goto error;
    }
    if (xf.colors_dep==dep_positions) {
	if (xf.ncolors && xf.ncolors!=xf.npositions) {
	    DXSetError(ERROR_BAD_PARAMETER, 
	    "colors are dependent on positions but have different number of entries");
	    goto error;
	}
    } else {
	if (xf.ncolors && xf.nconnections && xf.ncolors!=xf.nconnections) {
	    DXSetError(ERROR_BAD_PARAMETER,
	    "colors are dependent on connections but have different number of entries");
	    goto error;
	}
    }

    DXMarkTimeLocal("extract");
    if (! DXInvalidateConnections((Object)f))
	goto error;
    
    if (shade->approx!=approx_dots) {
	if (xf.colors_dep==dep_connections || xf.normals_dep==dep_connections) 
	    if (! _dxf_XInvalidConnections(f, &xf)) goto error;
	if (xf.colors_dep==dep_positions || xf.normals_dep==dep_positions) 
	    if (! _dxf_XInvalidPositions(f, &xf)) goto error;
	if (xf.colors_dep==dep_polylines || xf.normals_dep==dep_polylines) 
	    if (! _dxf_XInvalidPolylines(f, &xf)) goto error;
    }

    /* transform positions and box */
    a = _dxf_TransformArray(mp, shade->c, xf.positions_array,
			shade->notight? NULL : &box,
			f, &behind, shade->fuzz);
    if (!a)
	goto error;
    DXSetComponentValue(f, POSITIONS, (Object) a);
    if (!box) {
	box = (Array) DXGetComponentValue(f, BOX);
	box = _dxf_TransformBox(mp, shade->c, box, &behind, shade->fuzz);
	if (!box) goto error;
    }
    DXSetComponentValue(f, BOX, (Object) box);
    if (behind) {
	DXDelete((Object)f);
	DXDebug("R", "1 field (%d connections) rejected", xf.nconnections);
	DXMarkTimeLocal("rejected");
	return OK;
    }

    /* use volume color and opacity multipliers to undo effects of scaling */
    if (mp) {
	float l, mul;
	l = DXDeterminant(*mp);
	if (l<0) l = -l;
	if (l) {
	    l = pow(l, -1.0/3.0);
	    o = DXGetAttribute((Object)f, "color multiplier");
	    if (!DXExtractFloat(o, &mul)) mul = 1;
	    DXSetFloatAttribute((Object)f, "color multiplier", l*mul);
	    o = DXGetAttribute((Object)f, "opacity multiplier");
	    if (!DXExtractFloat(o, &mul)) mul = 1;
	    DXSetFloatAttribute((Object)f, "opacity multiplier", l*mul);
	}
	DXMarkTimeLocal("multiplier");
    }

    /* stop here if xform only */
    if (shade->xonly) {
	DXDelete((Object)f);
	return OK;
    }

    /* count */
    count(&xf, shade, (Point *)DXGetArrayData(box));
    DXMarkTimeLocal("count");

    /* stop here if no colors */
    if (!xf.fcolors_array && !xf.bcolors_array)
    {
	if (! DXSetMember(shade->g, NULL, (Object)f))
	    goto error;
	_dxf_XFreeLocal(&xf);
	return OK;
    }

    /*
     * Supply default color if doing dots approximation and colors
     * are dep connections.  XXX - Note we use a regular array and expand
     * here while in parallel.  Ideally we would leave it compact or use
     * a field color, but neither are implemented yet.
     */
    if (shade->approx==approx_dots && xf.colors_dep!=dep_positions) {
	static RGBColor color = {1, 1, 0};
	static RGBColor zero = {0, 0, 0};
	Object a = (Object) DXNewRegularArray(TYPE_FLOAT, 3, xf.npositions,
					    (Pointer)&color, (Pointer)&zero);
	if (!DXGetArrayData((Array)a))
	    goto error;
	if (!DXSetComponentValue(f, FRONT_COLORS, (Object) a))
	    goto error;
	if (!DXSetAttribute(a, DEP, O_POSITIONS))
	    goto error;
	DXDeleteComponent(f, BACK_COLORS);
	DXDeleteComponent(f, COLORS);
    }

    /* stop here if a volume, no normals or no camera */
    if (xf.volume || !xf.normals_array || !shade->c)
    {
	if (! DXSetMember(shade->g, NULL, (Object)f))
	    goto error;
	_dxf_XFreeLocal(&xf);
	return OK;
    }
	
    /* transform normals to world coordinates */
    normals_array = _dxf_TransformNormals(mp, xf.normals_array);
    if (!normals_array) goto error;

    /*
     * If colors and normals differ in dependency, we postpone
     * shading.  This requires that we stick the transformed normals into
     * the result field and add in the attribute
     */
    if (xf.colors_dep != xf.normals_dep)
    {
	if (! DXSetComponentValue(f, NORMALS, (Object)normals_array))
	    goto error;
	
	normals_array = NULL;

	if (! shade->lightList)
	{
	    DXSetError(ERROR_INTERNAL, "missing light list");
	    return ERROR;
	}
	
	if (! DXSetAttribute((Object)f, "lights", (Object)shade->lightList))
	    goto error;
    }
    else
    {
	char *resultName;
	Array fcolors_array = NULL, bcolors_array = NULL;

	normals = (Vector *) DXGetArrayData(normals_array);

	/* do the shading */

	if (! work(&xf, shade, normals_array, &fcolors_array, &bcolors_array))
	    goto error;

	DXDeleteComponent(f, NORMALS);
	DXDeleteComponent(f, COLORS);
	DXDeleteComponent(f, FRONT_COLORS);
	DXDeleteComponent(f, BACK_COLORS);

	if (fcolors_array)
	{
	    DXSetComponentValue(f, "front colors", (Object) fcolors_array);
	    if (xf.normals_dep==dep_connections)
		DXSetAttribute((Object)fcolors_array, DEP, O_CONNECTIONS);
	    else if (xf.normals_dep==dep_positions)
		DXSetAttribute((Object)fcolors_array, DEP, O_POSITIONS);
	    else if (xf.normals_dep==dep_polylines)
		DXSetAttribute((Object)fcolors_array, DEP, O_POLYLINES);
	}

	if (bcolors_array)
	{
	    DXSetComponentValue(f, "back colors", (Object) bcolors_array);
	    if (xf.normals_dep==dep_connections)
		DXSetAttribute((Object)bcolors_array, DEP, O_CONNECTIONS);
	    else if (xf.normals_dep==dep_positions)
		DXSetAttribute((Object)bcolors_array, DEP, O_POSITIONS);
	    else if (xf.normals_dep==dep_polylines)
		DXSetAttribute((Object)bcolors_array, DEP, O_POLYLINES);
	}

	if (normals_array != xf.normals_array)
	    DXDelete((Object)normals_array);

    }

    if (! DXSetMember(shade->g, NULL, (Object)f))
	goto error;
    f = NULL;

    _dxf_XFreeLocal(&xf);
    return OK;

error:
    DXDelete((Object)f);
    if (normals_array != xf.normals_array)
	DXDelete((Object)normals_array);
    _dxf_XFreeLocal(&xf);
    return ERROR;
}


static Error box_approx(Object o, struct shade *shade);

static int
IsInvisible(Object o)
{
    Object attr;
    int i;
    attr = DXGetAttribute(o, "visible");
    if (! attr)
	return 0;
    if (! DXExtractInteger(attr, &i))
	return 0;
    return i ? 0 : 1;
}

Error
_dxfField_Shade(Field f, struct shade *old)
{
    struct shade new;
    Array a;
    int n = 0;

    if (IsInvisible((Object)f)) return OK;

    if (!parameters((Object)f, &new, old)) return ERROR;
    if (new.approx==approx_box)
	return box_approx((Object)f, &new);

    a = (Array) DXGetComponentValue(f, POSITIONS);
    DXGetArrayInfo(a, &n, NULL, NULL, NULL, NULL);
    new.f = f;
    if (n)
	DXAddTask((Error(*)(Pointer))task, (Pointer)&new, sizeof(new), (float)n);
    return OK;
}


static Error
box_approx(Object o, struct shade *shade)
{
    int i;
    Field f;
    Point box[8];
    RGBColor colors[8];
    static Line lines[12] = {
	0,1, 0,2, 0,4, 1,3, 1,5, 2,3, 2,6, 3,7, 4,5, 4,6, 5,7, 6,7
    };
    
    /* bounding box? */
    if (!DXBoundingBox(o, box))
	return OK;

    /* set colors */
    for (i=0; i<8; i++)
	colors[i] = DXRGB(1,1,0);

    /* put values in field */
    f = DXNewField();
    if (!DXAddPoints(f, 0, 8, box)) return ERROR;
    if (!DXAddLines(f, 0, 12, lines)) return ERROR;
    if (!DXAddColors(f, 0, 8, colors)) return ERROR;
    if (!DXEndField(f)) return ERROR;

    /* don't call ourselves recursively */
    shade->approx = approx_none;

    /* call shade to do transform etc. */
    return _dxfField_Shade(f, shade);
}



/*
 * We could just return DXTransform(old->o, ...), but then we'd have
 * no place to put the attributes of old.  We can't just copy them
 * to the object we are returning, because it may already have
 * attributes.
 */

Error
_dxfXform_Shade(Xform x, struct shade *old)
{
    struct shade new;
    Object o;

    if (IsInvisible((Object)x)) return OK;

    if (!parameters((Object)x, &new, old)) return ERROR;
    if (new.approx==approx_box)
	return box_approx((Object)x, &new);

    DXGetXformInfo(x, &o, &new.m);

    if (old->xflag)
	new.m = DXConcatenate(new.m, old->m);
    new.xflag = 1;

    new.g = DXNewGroup();
    if (!new.g) goto error;
    if (!DXCopyAttributes((Object)new.g, (Object)x)) goto error;
    if (!_dxfShade(o, &new)) goto error;
    if (!DXSetMember(old->g, NULL, (Object)new.g)) goto error;
    return OK;

error:
    DXDelete((Object)new.g);
    return ERROR;
}

Error
_dxfScreen_Shade(Screen s, struct shade *old)
{
    Object ns = NULL, o, oo;
    struct shade new;
    int fixed, z, width, height;

    if (IsInvisible((Object)s)) return OK;

    if (!parameters((Object)s, &new, old)) return ERROR;
    if (new.approx==approx_box)
	return box_approx((Object)s, &new);

    if (!DXGetScreenInfo(s, &o, &fixed, &z)) return ERROR;
    DXGetCameraResolution(old->c, &width, &height);

    /* compute effect of camera on origin */
    if (fixed==SCREEN_VIEWPORT) {
	if (old->c) {
	    new.m.b[0] = new.m.b[0]*width - width/2;
	    new.m.b[1] = new.m.b[1]*height - height/2;
	}
    } else if (fixed==SCREEN_PIXEL) {
	if (old->c) {
	    new.m.b[0] -= width/2;
	    new.m.b[1] -= height/2;
	}
    } else if (fixed==SCREEN_WORLD) {
	if (old->xflag && old->c) {
	    Matrix cm;
	    cm = DXGetCameraMatrix(old->c);
	    new.m = DXConcatenate(new.m, cm);
	    new.xflag = 1;
	} else if (old->xflag) {
	    new.m = old->m;
	    new.xflag = 1;
	} else if (old->c) {
	    new.m = DXGetCameraMatrix(old->c);
	    new.xflag = 1;
	}
	if (DXGetPerspective(old->c, NULL, NULL)) {
	    new.m.b[0] = - new.m.b[0] / new.m.b[2];
	    new.m.b[1] = - new.m.b[1] / new.m.b[2];
	}
    } else if (fixed==SCREEN_STATIONARY) {
	new.m.b[0] = new.m.b[1] = new.m.b[2] = 0;
    }

    if (fixed!=SCREEN_STATIONARY) {
	/* hack to support depth flag */
	if (z>0) {
	    new.m.b[2] = DXD_MAX_FLOAT / 2;
	    new.ff = DXD_MAX_FLOAT / 1000000;
	} else if (z==0) {
	    new.m.b[2] = 0;
	} else {
	    new.m.b[2] = -DXD_MAX_FLOAT / 2;
	    new.ff = DXD_MAX_FLOAT / 1000000;
	}
	new.fuzz *= new.ff;
	new.c = NULL;
    }

    /* only origin gets affected by camera */
    new.m.A[0][0] = 1,  new.m.A[0][1] = 0,  new.m.A[0][2] = 0;
    new.m.A[1][0] = 0,  new.m.A[1][1] = 1,  new.m.A[1][2] = 0;
    new.m.A[2][0] = 0,  new.m.A[2][1] = 0,  new.m.A[2][2] = 1;

    new.g = DXNewGroup();
    if (!new.g) goto error;
    if (!DXCopyAttributes((Object)new.g, (Object)s)) goto error;
    if (!_dxfShade(o, &new)) goto error;

    /*
     * We insert an extra screen object in the hierarchy here to
     * prevent perspective transformation and clipping for the screen
     * object in the tiling phase.
     */
    oo = (Object) DXNewScreen((Object)new.g, 0, 0);
    if (!DXSetMember(old->g, NULL, oo)) goto error;
    return OK;

error:
    DXDelete((Object)new.g);
    DXDelete((Object)ns);
    return ERROR;
}


/*
 * A composite field only counts as one regular/irregular
 * field, so we use the docount variable so that only the first
 * volume field below this level counts.
 */

Error
_dxfGroup_Shade(Group g, struct shade *old)
{
    int i;
    Object m;
    struct shade new;
    Class class;

    if (IsInvisible((Object)g)) return OK;

    if (!parameters((Object)g, &new, old)) return ERROR;
    if (new.approx==approx_box)
	return box_approx((Object)g, &new);

    new.g = (Group) DXCopy((Object)g, COPY_ATTRIBUTES);

    /*
     * If composite this field, and we are not already inside a
     * composite field, we allocate a "docount" variable.  Only one
     * field below this guy (the first who counts) addt
     * field with
     */
    if (DXGetGroupClass(g)==CLASS_COMPOSITEFIELD && !new.docount) {
	new.docount = (struct docount *) DXAllocate(sizeof(struct docount));
	if (!new.docount) goto error;
	new.docount->docount = 1;		/* start out counting */
	new.docount->next = *new.docountlist;	/* put us on the ... */
	*new.docountlist = new.docount;		/* linked list, for freeing */
    }

    for (i=0; m=DXGetEnumeratedMember(g, i, NULL); i++) {
	if (!_dxfShade(m, &new))
	    return ERROR;
    }
    if (!DXSetMember(old->g, NULL, (Object)new.g)) goto error;
    return OK;

error:
    DXDelete((Object) new.g);
    return ERROR;
}


Error
_dxfLight_Shade(Light l, struct shade *shade)
{
    if (shade->xonly)
	return OK;
    if (l->kind==ambient) {
	shade->l->ambient.r += l->color.r;
	shade->l->ambient.g += l->color.g;
	shade->l->ambient.b += l->color.b;
	shade->l->na++;
    } else if (l->kind==distant) {
	if (l->relative==world) {
	    if (shade->xflag) {
		Matrix m;
		m = shade->m;
		m.b[0] = m.b[1] = m.b[2] = 0;
		shade->l->lights[shade->l->nl++]
		    = DXNewDistantLight(DXApply(l->direction,m), l->color);
	    } else {
		/*
		 * Kludge around compiler error
		 */
#if 1
		int i = shade->l->nl;
		shade->l->lights[i]=(Light)DXReference((Object)l);
		shade->l->nl = i+1;
#else
		shade->l->lights[shade->l->nl++]=(Light)DXReference((Object)l);
#endif
	    }		
	} else if (l->relative==camera) {
	    /* XXX - performance? */
	    Vector from, to, x, y, z, where;
	    DXGetView(shade->c, &from, &to, &y);
	    z = DXNormalize(DXSub(from,to));
	    y = DXNormalize(y);
	    x = DXCross(y,z);
	    where = DXMul(x, l->direction.x);
	    where = DXAdd(where, DXMul(y, l->direction.y));
	    where = DXAdd(where, DXMul(z, l->direction.z));
	    shade->l->lights[shade->l->nl++]
		= DXNewDistantLight(where, l->color);
	} else {
	    DXErrorReturn(ERROR_INTERNAL, "invalid light object");
	}
    } else {
	DXErrorReturn(ERROR_INVALID_DATA,
		    "only ambient and distant lights allowed");
    }
    return OK;
}


Error
_dxfClipped_Shade(Clipped c, struct shade *old)
{
    Object nc=NULL, render, clipping;
    Group nrender=NULL, nclipping=NULL;
    struct shade new;

    DXGetClippedInfo(c, &render, &clipping);

    if (IsInvisible((Object)c) || IsInvisible(render)) return OK;
    
    /* doesn't need DXlock protection */
    old->count->fast = 0;

    if (!parameters((Object)c, &new, old)) return ERROR;
    if (new.approx==approx_box)
	return box_approx((Object)c, &new);

    DXGetClippedInfo(c, &render, &clipping);

    nrender = new.g = DXNewGroup();
    if (!nrender) goto error;
    if (!_dxfShade(render, &new)) goto error;

    nclipping = new.g = DXNewGroup();
    new.nocolors = 1;
    if (!nclipping) goto error;
    if (!_dxfShade(clipping, &new)) goto error;

    nc = (Object) DXNewClipped((Object)nrender, (Object)nclipping);
    if (!nc) goto error;
    if (!DXCopyAttributes((Object)nc, (Object)c)) goto error;
    if (old->g && !DXSetMember(old->g, NULL, (Object)nc)) goto error;
    return OK;

error:
    DXDelete((Object)nrender);
    DXDelete((Object)nclipping);
    DXDelete((Object)nc);
    return ERROR;
}


/*
 * This routine is called by the shade task to do
 * the counting.
 */


/*
 * NB - this FLOOR suffers from precision problems at about -1e-13
 *
 * #define FLOOR(x) ((int)((x)+30000.0)-30000)
 *
 * The size of the elements that go into the sort array depends on such
 * factors as the element type (triangle, quad etc.); for faces derived
 * from connection-dependent volume elements, there is an additional word
 * naming the element that the face came from to identify the color.  This
 * size appears in SIZE macro in shade.c, the INFO macro in gather.c,
 * and the ADVANCE macro in volume.c, and these must be kept in sync.
 */

#define FLOOR(x) ((x)>=0 || (int)(x)==x? (int)(x) : (int)(x)-1)
#define SIZE(n) (sizeof(struct sort) + (n) * sizeof(int))


static Error
count(struct xfield *xf, struct shade *shade, Point *box)
{
    Point min, max;
    int lt, rt, tp, bt, i, j, n;
    int nconnections, tfields, nbytes, volume;
    int counts[100];
    int w, h, nx, ny;
    struct pcount *p, *pp;
    struct count *count = shade->count;

    /* get field info */
    nconnections = xf->ct==ct_none? xf->npositions : xf->nconnections;
    if (nconnections==0)
	return;

    /*
     * This is a little tricky: we have to calculate min and max partition
     * numbers based on our min and max points.  This calculation has to
     * agree exactly with CULLBOX in render.h and the tile bounds
     * calculation in tile.c.
     */
    min.x = min.y = DXD_MAX_FLOAT;
    max.x = max.y = -DXD_MAX_FLOAT;
    for (i=0; i<8; i++) {
	if (box[i].x<min.x) min.x = box[i].x;
	if (box[i].x>max.x) max.x = box[i].x;
	if (box[i].y<min.y) min.y = box[i].y;
	if (box[i].y>max.y) max.y = box[i].y;
    }
    min.x -= .5 /* for lines */;
    min.y -= .5 /* for lines */;
    max.x += .5 /* for lines */;
    max.y += .5 /* for lines */;
    w = count->width, h = count->height;
    nx = count->nx, ny = count->ny;

    /* compare here to avoid overflow */
    if (min.x<-w) min.x = -w; else if (min.x>w) min.x = w;
    if (max.x<-w) max.x = -w; else if (max.x>w) max.x = w;
    if (min.y<-h) min.y = -h; else if (min.y>h) min.y = h;
    if (max.y<-h) max.y = -h; else if (max.y>h) max.y = h;

    /* compute partiton numbers */
#   define K 1024 /* to truncate toward -infinity */
    lt = ((FLOOR(min.x)+1 + w/2) * nx - 1 + K*w) / w - K;
    rt = ((FLOOR(max.x)+1 + w/2) * nx - 1 + K*w) / w - K;
    bt = ((FLOOR(min.y)+1 + h/2) * ny - 1 + K*h) / h - K;
    tp = ((FLOOR(max.y)+1 + h/2) * ny - 1 + K*h) / h - K;

    /* limits */
    if (lt<0) lt=0;
    if (rt>=count->nx) rt = count->nx-1;
    if (bt<0) bt=0;
    if (tp>=count->ny) tp = count->ny-1;

    DXDebug("c", "lt %g rt %g bt %g tp %g -> lt %d rt %d  bt %d tp %d",
	  min.x, max.x, min.y, max.y, lt, rt, bt, tp);

    /* start modifying count structure */
    DXlock(&count->DXlock, 0);

    /* info for translucent fields */
    tfields = 0;
    nbytes = 0;
    if (xf->opacities_array || xf->volume) {
	int regular=0, irregular=0, volume=0;
	if (xf->ct==ct_none) {
	    nbytes = nconnections * SIZE(1);
	    irregular = 1;
	} else if (xf->ct==ct_lines) {
	    nbytes = nconnections * SIZE(1);
	    irregular = 1;
	} else if (xf->ct==ct_triangles) {
	    nbytes = nconnections * SIZE(1);
	    irregular = 1;
	} else if (xf->ct==ct_quads) {
	    nbytes = nconnections * SIZE(1);
	    irregular = 1;
	} else if (xf->ct==ct_tetrahedra) {
	    int size = SIZE(xf->colors_dep==dep_positions? 3 : 4); 
	    nbytes = 4*nconnections * size;
	    irregular = 1;
	    volume = 1;
	    count->fast = 0;
	} else if (xf->ct==ct_cubes) {
	    int size = SIZE(xf->colors_dep==dep_positions? 4 : 5);
	    if (DXQueryGridConnections(xf->connections_array,&n,counts)&&n==3) {
		int x = counts[0], y = counts[1], z = counts[2];
		nbytes = ((x-1)*(y-1)*z+(x-1)*y*(z-1)+x*(y-1)*(z-1)) * size;
		if (DXQueryGridPositions(xf->positions_array,
				       NULL, NULL, NULL, NULL))
		    regular = 1;
		else
		    irregular = 1;
	    } else {
		nbytes = 6*nconnections * size;
		irregular = 1;
	    }
	    volume = 1;
	    count->fast = 0;
	}
	tfields = 1;
	if (!shade->docount || shade->docount->docount) {
	    count->irregular += irregular;
	    count->regular += regular;
	    count->volume += volume;
	    if (shade->docount)
		shade->docount->docount = 0;
	}
    }

    /* increment counts */
    for (nx=count->nx, p=count->pcount+bt*nx, i=bt; i<=tp; i++, p+=nx) {
	for (pp=p+lt, j=lt; j<=rt; j++, pp++) {
	    pp->nconnections += nconnections;
	    pp->tfields += tfields;
	    pp->nbytes += nbytes;
	}
    }

    /* done modifying count structure */
    DXunlock(&count->DXlock, 0);

    return OK;
}



#if 0 /*hc860*/
#define DREG     == 34
#define FRSQR(d) _ASM("frsqr.ss f2,f2");
#else
#define DREG
#define FRSQR(d) d = ((float)1.0 / sqrt(d))
#endif


/*
 * This macro computes fdiffr,fdiffg,fdiffb and fspecr,fspecg,fspecb
 * given the normal norm-> and various lighting parameters.  These
 * are then used in one of COLSET, COLADD, MAPSET, or MAPADD to
 * compute the final contribution of this light to the color.
 */

#define LIGHT {						$\
							$\
    /* normal */					$\
    nx=norm->x, ny=norm->y, nz=norm->z;			$\
							$\
    /* specular */					$\
    d = hx*nx + hy*ny + hz*nz;				$\
    if (d>0) {						$\
        d = fspec * ipow(d, fshine);			$\
        fspecr=d*lr, fspecg=d*lg, fspecb=d*lb;		$\
        bspecr = bspecg = bspecb = 0;			$\
    } else {						$\
        d = bspec * ipow(-d, bshine);			$\
        bspecr=d*lr, bspecg=d*lg, bspecb=d*lb;		$\
        fspecr = fspecg = fspecb = 0;			$\
    }							$\
							$\
    /* diffuse */					$\
    d = lx*nx + ly*ny + lz*nz;				$\
    if (d>0) {						$\
        d = d * fdiff;					$\
        fdiffr=d*lr, fdiffg=d*lg, fdiffb=d*lb;		$\
        bdiffr = bdiffg = bdiffb = 0;			$\
    } else {						$\
        d = -d * bdiff;					$\
        bdiffr=d*lr, bdiffg=d*lg, bdiffb=d*lb;		$\
        fdiffr = fdiffg = fdiffb = 0;			$\
    }							$\
}

/*
 * After LIGHT calculates fdiffr,fdiffg,fdiffb and fspecr,fspecg,fspecb
 * one of these macros is invoked to compute the contribution of this
 * light to this color vertex.  COLSET/COLADD do this for direct color
 * while MAPSET/MAPADD do it for mapped color.  COLSET/MAPSET are invoked
 * for the first light and include the contribution of ambient light,
 * while COLADD/MAPADD are invoked for subsequent lights and add
 * only the diffuse and ambient contribution of those lights.  The
 * X argument to these macros is one of F or B, which are macros
 * that prepend f or b to a name to select front/back ambient (f/bambr/g/b),
 * diffuse (f/bdiffr/g/b), or specular parameters (f/bspecr/g/b).
 */

DEFINE2 CAT(x,y) x##y

#define F(x) CAT(f,x)
#define B(x) CAT(b,x)

static int byteTableFlag = 0;
static float byteTable[256];

#define COLSET(oc, ic, X, byte)						      $\
{									      $\
    if (byte)  								      $\
    {									      $\
	oc->r = byteTable[((unsigned char *)ic)[0]]			      $\
			* (X(diffr)+X(ambr)) + X(specr);  		      $\
	oc->g = byteTable[((unsigned char *)ic)[1]]			      $\
			* (X(diffg)+X(ambg)) + X(specg);  		      $\
	oc->b = byteTable[((unsigned char *)ic)[2]]			      $\
			* (X(diffb)+X(ambb)) + X(specb);  		      $\
    } else {								      $\
	oc->r = ((RGBColor *)ic)->r * (X(diffr)+X(ambr)) + X(specr);	      $\
	oc->g = ((RGBColor *)ic)->g * (X(diffg)+X(ambg)) + X(specg);	      $\
	oc->b = ((RGBColor *)ic)->b * (X(diffb)+X(ambb)) + X(specb);	      $\
    } 									      $\
}

#define COLADD(oc, ic, X, byte)						      $\
{									      $\
    if (byte)  								      $\
    {									      $\
	oc->r += byteTable[((unsigned char *)ic)[0]] * X(diffr) + X(specr);   $\
	oc->g += byteTable[((unsigned char *)ic)[1]] * X(diffg) + X(specg);   $\
	oc->b += byteTable[((unsigned char *)ic)[2]] * X(diffb) + X(specb);   $\
    } else {								      $\
	oc->r += ((RGBColor *)ic)->r * X(diffr) + X(specr);		      $\
	oc->g += ((RGBColor *)ic)->g * X(diffg) + X(specg);		      $\
	oc->b += ((RGBColor *)ic)->b * X(diffb) + X(specb);		      $\
    } 									      $\
}

#define COLBUMP(oc, ic, cst, byte)					$\
{									$\
    if (byte) {								$\
         oc++; if (!cst) ic=(Pointer)(((unsigned char *)ic)+3);		$\
    } else {								$\
	 oc++; if (!cst) ic=(Pointer)(((RGBColor *)ic)+1);		$\
    }									$\
}

#define MAPSET(oc,ic,X,byte)						$\
    col = &cmap[*(unsigned char *)ic];					$\
    oc->r = col->r * (X(diffr) + X(ambr)) + X(specr);			$\
    oc->g = col->g * (X(diffg) + X(ambg)) + X(specg);			$\
    oc->b = col->b * (X(diffb) + X(ambb)) + X(specb);		

#define MAPBUMP(oc, ic, cst,byte)					$\
    oc++; if (!cst) ic=(Pointer)(((unsigned char *)ic)+1)

#define MAPADD(oc,ic,X,byte)						$\
    col = &cmap[*(unsigned char *)ic];					$\
    oc->r += col->r * X(diffr) + X(specr);				$\
    oc->g += col->g * X(diffg) + X(specg);				$\
    oc->b += col->b * X(diffb) + X(specb);


/*
 * LOOP puts together LIGHT from above with one of {COL,MAP}{SET,ADD};
 * which one to invoke is determined by the store parameter.
 * LOOP also moves the test for front/back color presence out of the
 * inner loop.
 */

#define LOOP(store, bump, fcst, bcst, ncst, fbyte, bbyte) {	$\
    if (ich) {							$\
	if (ofc && obc) {					$\
	    if (ncst) norm = &cstnormal; else norm = normals;   $\
	    for (i=0; i < n; i++) {				$\
		if (DXIsElementValid(ich, i)) {			$\
		    LIGHT;					$\
		    store(ofc, ifc, F, fbyte);			$\
		    store(obc, ibc, B, bbyte);			$\
		}						$\
		bump(ofc, ifc, fcst, fbyte);			$\
		bump(obc, ibc, bcst, bbyte);			$\
		if (!ncst) norm ++;				$\
	    }							$\
	} else if (ofc) {					$\
	    if (ncst) norm = &cstnormal; else norm = normals;   $\
	    for (i=0; i < n; i++) {				$\
		if (DXIsElementValid(ich, i)) {			$\
		    LIGHT;					$\
		    store(ofc,ifc,F, fbyte);			$\
		}						$\
		bump(ofc, ifc, fcst, fbyte);			$\
		if (!ncst) norm ++;				$\
	    }							$\
	} else if (obc) {					$\
	    if (ncst) norm = &cstnormal; else norm = normals;   $\
	    for (i=0; i < n; i++) {				$\
		if (DXIsElementValid(ich, i)) {			$\
		    LIGHT;					$\
		    store(obc,ibc,B, bbyte);			$\
		}						$\
		bump(obc, ibc, bcst, fbyte);			$\
		if (!ncst) norm ++;				$\
	    }							$\
	}							$\
    } else {							$\
	if (ofc && obc) {					$\
	    if (ncst) norm = &cstnormal; else norm = normals;   $\
	    for (i=0; i < n; i++) {				$\
		LIGHT;						$\
		store(ofc,ifc, F, fbyte);			$\
		store(obc,ibc, B, bbyte);			$\
		bump(ofc, ifc, fcst, fbyte);			$\
		bump(obc, ibc, bcst, bbyte);			$\
		if (!ncst) norm ++;				$\
	    }							$\
	} else if (ofc) {					$\
	    if (ncst) norm = &cstnormal; else norm = normals;   $\
	    for (i=0; i < n; i++) {				$\
		LIGHT;						$\
		store(ofc,ifc, F, fbyte);			$\
		bump(ofc, ifc, fcst, fbyte);			$\
		if (!ncst) norm ++;				$\
	    }							$\
	} else if (obc) {					$\
	    if (ncst) norm = &cstnormal; else norm = normals;   $\
	    for (i=0; i < n; i++) {				$\
		LIGHT;						$\
		store(obc,ibc, B, bbyte);			$\
		bump(obc, ibc, bcst, bbyte);			$\
		if (!ncst) norm ++;				$\
	    }							$\
	}							$\
    }								$\
}

#define CLAMP(a) ((a) = ((a) > 1.0) ? 1.0 : ((a) < 0.0) ? 0.0 : (a))

static Error
work(struct xfield *xf, struct shade *shade, 
	Array normals_array, Array *front_colors, Array *back_colors)
{
    struct l *l = shade->l;
    int nl = l->nl;
    Array result;
    float fambr = shade->front.ambient * l->ambient.r;
    float fambg = shade->front.ambient * l->ambient.g;
    float fambb = shade->front.ambient * l->ambient.b;
    float bambr = shade->back.ambient * l->ambient.r;
    float bambg = shade->back.ambient * l->ambient.g;
    float bambb = shade->back.ambient * l->ambient.b;
    float fspec = shade->front.specular;
    float bspec = shade->back.specular;
    float fdiff = shade->front.diffuse;
    float bdiff = shade->back.diffuse;
    int fshine = shade->front.shininess;
    int bshine = shade->back.shininess;
    int n = xf->ncolors, i, j;

    RGBColor *ofc, *obc, *col, *cmap = xf->cmap;
    Pointer ifc, ibc;
    Point from, to, eye;
    Vector *norm, *normals;
    float ex, ey, ez;
    float fspecr, fspecg, fspecb, bspecr, bspecg, bspecb;
    float fdiffr, fdiffg, fdiffb, bdiffr, bdiffg, bdiffb;
    float nx, ny, nz;
    float lr, lg, lb, lx, ly, lz, hx, hy, hz;
    float d DREG;
    InvalidComponentHandle ich;
    int  fcst = xf->fcst, bcst = xf->bcst, ncst;
    Point cstnormal;
    int m;
    RGBColor  *fcolors, *bcolors;
    int fbyte = xf->fbyte, bbyte = xf->bbyte;

    if ((fbyte || bbyte) && !byteTableFlag)
    {    
	int i;

	for (i = 0; i < 256; i++)
	   byteTable[i] = i / 256.0;
	
	byteTableFlag = 1;
    }

    *front_colors = NULL;
    *back_colors  = NULL;

    /*
     * eye vector
     */
    DXGetView(shade->c, &from, &to, NULL);
    eye = DXNormalize(DXSub(from, to));
    ex=eye.x, ey=eye.y, ez=eye.z;

    /* check shininess >0 */
    if (fshine<0 || bshine<0)
	DXErrorReturn(ERROR_BAD_PARAMETER, "shininess may not be negative");
    
    if (xf->normals_dep == dep_positions)
	ich = xf->iPts;
    else
	ich = xf->iElts;
    
    /*
     * Check if normals is constant array.  If so, we can create constant output
     * color components for constant input colors components.
     */
    if (DXQueryConstantArray(normals_array, &m, (Pointer)&cstnormal))
    {
	norm = (Vector *)&cstnormal;

	if (fcst || bcst)
	{
	    RGBColor fout, bout;

	    if (fcst)
	    {
		if (fbyte)
		{
		    unsigned char *fin = (unsigned char *)xf->fcolors;

		    fout.r = byteTable[*fin++] * fambr;
		    fout.g = byteTable[*fin++] * fambg;
		    fout.b = byteTable[*fin++] * fambb;
		    
		}
		else
		{
		    RGBColor *fin;

		    if (cmap) fin = cmap + *(unsigned char *)&(xf->fcolors);
		    else      fin = (RGBColor *)xf->fcolors;

		    fout.r = fin->r * fambr;
		    fout.g = fin->g * fambg;
		    fout.b = fin->b * fambb;
		}
	    }

	    if (bcst)
	    {
		if (bbyte)
		{
		    unsigned char *bin = (unsigned char *)xf->bcolors;

		    bout.r = byteTable[*bin++] * bambr;
		    bout.g = byteTable[*bin++] * bambg;
		    bout.b = byteTable[*bin++] * bambb;
		}
		else
		{
		    RGBColor *bin;

		    if (cmap) bin = cmap + *(unsigned char *)&(xf->bcolors);
		    else      bin = (RGBColor *)xf->bcolors;

		    bout.r = bin->r * bambr;
		    bout.g = bin->g * bambg;
		    bout.b = bin->b * bambb;
		}
	    }

	    for (j = 0; j < nl; j++)
	    {
		Light light = l->lights[j];
		lr = light->color.r;
		lg = light->color.g;
		lb = light->color.b;
		lx = light->direction.x,
		ly = light->direction.y;
		lz = light->direction.z;

		hx=ex+lx,  hy=ey+ly,  hz=ez+lz;
		d = hx*hx + hy*hy + hz*hz;
		if (d != 0.0)
		    d = (float)1.0 / sqrt(d);
		hx*=d, hy*=d, hz*=d;

		if (light->kind == distant)
		{
		    LIGHT;
		    if (fcst)
		    {
			if (fbyte)
			{
			    unsigned char *fin = (unsigned char *)xf->fcolors;
			    fout.r += (byteTable[*fin++] * fdiffr) + fspecr;
			    fout.g += (byteTable[*fin++] * fdiffg) + fspecg;
			    fout.b += (byteTable[*fin++] * fdiffb) + fspecb;
			}
			else
			{
			    RGBColor *fin = (RGBColor *)xf->fcolors;
			    fout.r += (fin->r * fdiffr) + fspecr;
			    fout.g += (fin->g * fdiffg) + fspecg;
			    fout.b += (fin->b * fdiffb) + fspecb;
			}
		    }
		    if (bcst)
		    {
			if (fbyte)
			{
			    unsigned char *bin = (unsigned char *)xf->bcolors;
			    bout.r += (byteTable[*bin++] * bdiffr) + bspecr;
			    bout.g += (byteTable[*bin++] * bdiffg) + bspecg;
			    bout.b += (byteTable[*bin++] * bdiffb) + bspecb;
			}
			else
			{
			    RGBColor *bin = (RGBColor *)xf->bcolors;
			    bout.r += (bin->r * bdiffr) + bspecr;
			    bout.g += (bin->g * bdiffg) + bspecg;
			    bout.b += (bin->b * bdiffb) + bspecb;
			}
		    }
		}
	    }

	    if (fcst)
	    {
		CLAMP(fout.r);
		CLAMP(fout.g);
		CLAMP(fout.b);

		*front_colors = (Array)DXNewConstantArray(m, (Pointer)&fout,
					    TYPE_FLOAT, CATEGORY_REAL, 1, 3);
		if (! *front_colors)
		    goto error;
	    }

	    if (bcst)
	    {
		CLAMP(bout.r);
		CLAMP(bout.g);
		CLAMP(bout.b);

		*back_colors = (Array)DXNewConstantArray(m, (Pointer)&bout,
					    TYPE_FLOAT, CATEGORY_REAL, 1, 3);
		if (! *back_colors)
		    goto error;
	    }
	}

	ncst = 1;
    }
    else
    { 
	normals = (Vector *)DXGetArrayData(normals_array);
	ncst = 0;
    }

    if ((!fcst || !ncst) && xf->fcolors_array)
    {
	*front_colors = DXNewArray(TYPE_FLOAT, CATEGORY_REAL, 1, 3);
	if (! *front_colors)
	    goto error;

	if (! DXAddArrayData(*front_colors, 0, xf->ncolors, NULL))
	    goto error;

	fcolors = (RGBColor *)DXGetArrayData(*front_colors);
	if (!fcolors)
	    goto error;
    }
    else
	fcolors = NULL;
    
    if ((!bcst || !ncst) && xf->bcolors_array)
    {
	*back_colors = DXNewArray(TYPE_FLOAT, CATEGORY_REAL, 1, 3);
	if (! *back_colors)
	    goto error;

	if (! DXAddArrayData(*back_colors, 0, xf->ncolors, NULL))
	    goto error;

	bcolors = (RGBColor *)DXGetArrayData(*back_colors);
	if (!bcolors)
	    goto error;
    }
    else
	bcolors = NULL;

    /* if no lights, ambient only */
    if (nl==0) {
	ifc = xf->fcolors, ofc = fcolors;
	ibc = xf->bcolors, obc = bcolors;
	if (cmap) {
	    if (ofc) {
		if (fcst)
		{
		    col = &cmap[*(unsigned char *)ifc];
		    fcolors->r = col->r * fambr;
		    fcolors->g = col->g * fambg;
		    fcolors->b = col->b * fambb;

		    for (ofc++, i=1; i<n; i++) {
			*ofc++ = *fcolors;
		    }
		}
		else
		{
		    for (i=0; i<n; i++) {
			col = &cmap[*(unsigned char *)ifc];
			ofc->r = col->r * fambr;
			ofc->g = col->g * fambg;
			ofc->b = col->b * fambb;
			ofc++, ifc=(Pointer)(((unsigned char *)ifc)+1);
		    }
		}
	    }
	    if (obc) {
		if (bcst)
		{
		    col = &cmap[*(unsigned char *)ibc];
		    bcolors->r = col->r * bambr;
		    bcolors->g = col->g * bambg;
		    bcolors->b = col->b * bambb;

		    for (obc++, i=1; i<n; i++) {
			*obc++ = *bcolors;
		    }
		}
		else
		{
		    for (i=0; i<n; i++) {
			col = &cmap[*(unsigned char *)ibc];
			obc->r = col->r * bambr;
			obc->g = col->g * bambg;
			obc->b = col->b * bambb;
			obc++, ibc=(Pointer)(((unsigned char *)ibc)+1);
		    }
		}
	    }
	} else {
	    if (ofc) {
		if (fcst)
		{
		    if (fbyte)
		    {
			fcolors->r = byteTable[((unsigned char *)ifc)[0]] * fambr;
			fcolors->g = byteTable[((unsigned char *)ifc)[1]] * fambg;
			fcolors->b = byteTable[((unsigned char *)ifc)[2]] * fambb;
		    }
		    else
		    {
			fcolors->r = ((RGBColor *)ifc)->r * fambr;
			fcolors->g = ((RGBColor *)ifc)->g * fambg;
			fcolors->b = ((RGBColor *)ifc)->b * fambb;
		    }

		    for (ofc++, i=1; i<n; i++) {
			*ofc++ = *fcolors;
		    }
		}
		else
		{
		    if (fbyte)
		    {
			unsigned char *ifc_uchar = (unsigned char *)ifc;

			for (i=0; i<n; i++) {
			    ofc->r = byteTable[*ifc_uchar++] * fambr;
			    ofc->g = byteTable[*ifc_uchar++] * fambg;
			    ofc->b = byteTable[*ifc_uchar++] * fambb;
			    ofc++;
			}
		    }
		    else
		    {
			for (i=0; i<n; i++) {
			    ofc->r = ((RGBColor *)ifc)->r * fambr;
			    ofc->g = ((RGBColor *)ifc)->g * fambg;
			    ofc->b = ((RGBColor *)ifc)->b * fambb;
			    ofc++, ifc=(Pointer)(((RGBColor *)ifc)+1);
			}
		    }
		}
	    }
	    if (obc) {
		if (bcst)
		{
		    if (bbyte)
		    {
			bcolors->r = byteTable[((unsigned char *)ibc)[0]] * bambr;
			bcolors->g = byteTable[((unsigned char *)ibc)[1]] * bambg;
			bcolors->b = byteTable[((unsigned char *)ibc)[2]] * bambb;
		    }
		    else
		    {
			bcolors->r = ((RGBColor *)ibc)->r * bambr;
			bcolors->g = ((RGBColor *)ibc)->g * bambg;
			bcolors->b = ((RGBColor *)ibc)->b * bambb;
		    }
		    for (obc++, i=1; i<n; i++) {
			*obc++ = *bcolors;
		    }
		}
		else
		{
		    if (bbyte)
		    {
			unsigned char *ibc_uchar = (unsigned char *)ibc;

			for (i=0; i<n; i++) {
			    obc->r = byteTable[*ibc_uchar++] * bambr;
			    obc->g = byteTable[*ibc_uchar++] * bambg;
			    obc->b = byteTable[*ibc_uchar++] * bambb;
			    obc++;
			}
		    }
		    else
		    {
			for (i=0; i<n; i++) {
			    obc->r = ((RGBColor *)ibc)->r * bambr;
			    obc->g = ((RGBColor *)ibc)->g * bambg;
			    obc->b = ((RGBColor *)ibc)->b * bambb;
			    obc++, ibc=(Pointer)(((RGBColor *)ibc)+1);
			}
		    }
		}
	    }
	}

    }

    /* for each light */
    for (j=0;  j<nl;  j++) {

	Light light = l->lights[j];
	lr = light->color.r;
	lg = light->color.g;
	lb = light->color.b;
	lx = light->direction.x,
	ly = light->direction.y;
	lz = light->direction.z;

	if (light->kind==distant) {

	    ifc = xf->fcolors, ofc = fcolors;
	    ibc = xf->bcolors, obc = bcolors;

	    hx=ex+lx,  hy=ey+ly,  hz=ez+lz;
	    d = hx*hx + hy*hy + hz*hz;
	    if (d != 0.0)
		d = (float)1.0 / sqrt(d);
	    hx*=d, hy*=d, hz*=d;

	    if (cmap) {
		/* mapped color */
		if (j==0) {
		    LOOP(MAPSET, MAPBUMP, fcst, bcst, ncst, fbyte, bbyte);
		} else {
		    LOOP(MAPADD, MAPBUMP, fcst, bcst, ncst, fbyte, bbyte);
		}
	    } else {
		/* direct color */
		if (j==0) {
		    LOOP(COLSET, COLBUMP, fcst, bcst, ncst, fbyte, bbyte);
		} else {
		    LOOP(COLADD, COLBUMP, fcst, bcst, ncst, fbyte, bbyte);
		}
	    }

	}
	else
	    DXErrorReturn(ERROR_BAD_PARAMETER, "bad light type");
    }


    /* clamp results */
    if (ich)
    {
	if (fcolors) {
	    for (i=0, ofc=fcolors; i<n; i++) {
		if (DXIsElementValid(ich, i)) {
		    CLAMP(ofc->r);
		    CLAMP(ofc->g);
		    CLAMP(ofc->b);
		}
		else
		    ofc->r = ofc->g = ofc->b = 0.0;
		ofc++;
	    }
	}
	if (bcolors) {
	    for (i=0, obc=bcolors; i<n; i++) {
		if (DXIsElementValid(ich, i)) {
		    CLAMP(obc->r);
		    CLAMP(obc->g);
		    CLAMP(obc->b);
		}
		else
		    obc->r = obc->g = obc->b = 0.0;
		obc++;
	    }
	}
    } else {
	if (fcolors) {
	    for (i=0, ofc=fcolors; i<n; i++) {
		CLAMP(ofc->r);
		CLAMP(ofc->g);
		CLAMP(ofc->b);
		ofc++;
	    }
	}
	if (bcolors) {
	    for (i=0, obc=bcolors; i<n; i++) {
		CLAMP(obc->r);
		CLAMP(obc->g);
		CLAMP(obc->b);
		obc++;
	    }
	}
    }

    return OK;

error:
    DXDelete((Object)*front_colors);
    DXDelete((Object)*back_colors);
    return ERROR;
}

static Error
_GatherLights(LightList lightlist, Object obj, Matrix *stack, Camera cam)
{
    Class class = DXGetObjectClass(obj);
    if (class == CLASS_GROUP)
	class = DXGetGroupClass((Group)obj);

    switch (class)
    {
	case CLASS_LIGHT:
	{
	    Light l = (Light)obj;

	    if (l->kind == ambient)
	    {
		lightlist->ambient.r += l->color.r;
		lightlist->ambient.g += l->color.g;
		lightlist->ambient.b += l->color.b;
		lightlist->na++;
	    }
	    else if (l->kind == distant)
	    {
		if (l->relative == world)
		{
		    if (stack)
		    {
			Matrix m = *stack;
			m.b[0] = m.b[1] = m.b[2] = 0;
			lightlist->lights[lightlist->nl]
			    = DXNewDistantLight(DXApply(l->direction,m),
								l->color);
		    }
		    else
			lightlist->lights[lightlist->nl] = l;
		    
		    DXReference((Object)lightlist->lights[lightlist->nl]);
		}
		else if (l->relative == camera)
		{
		    Vector from, to, x, y, z, where;
		    DXGetView(cam, &from, &to, &y);
		    z = DXNormalize(DXSub(from,to));
		    y = DXNormalize(y);
		    x = DXCross(y,z);
		    where = DXMul(x, l->direction.x);
		    where = DXAdd(where, DXMul(y, l->direction.y));
		    where = DXAdd(where, DXMul(z, l->direction.z));
		    lightlist->lights[lightlist->nl]
			    = DXNewDistantLight(where, l->color);

		    DXReference((Object)lightlist->lights[lightlist->nl]);
		}
		else
		{
		    DXErrorReturn(ERROR_INTERNAL, "invalid light object");
		}
		 
		lightlist->nl++;
	    }
	    else
	    {
		DXErrorReturn(ERROR_INVALID_DATA,
			"only ambient and distant lights allowed");
	    }

	    return OK;
	}

	case CLASS_XFORM:
	{
	   Xform x = (Xform)obj;
	   Object child;
	   Matrix m;

	   if (! DXGetXformInfo(x, &child, &m))
	       return ERROR;
	    
	    if (stack)
	    {
		Matrix product;
		
		product = DXConcatenate(m, *stack);
		return _GatherLights(lightlist, child, &product, cam);
	    }
	    else
		return _GatherLights(lightlist, child, &m, cam);
	}

	case CLASS_CLIPPED:
	{
	   Clipped c = (Clipped)obj;
	   Object child;

	   if (! DXGetClippedInfo(c, &child, NULL))
	       return ERROR;
	    
	    return _GatherLights(lightlist, child, stack, cam);
	}

	case CLASS_SERIES:
	case CLASS_GROUP:
	{
	    Group g = (Group)obj;
	    Object child;
	    int i = 0;

	    while (NULL != (child = DXGetEnumeratedMember(g, i++, NULL)))
		if (! _GatherLights(lightlist, child, stack, cam))
		    return ERROR;
	    
	    return OK;
	}

	default:
	    return OK;
    }
}

static Error
_dxfFreeLightListPrivate(Pointer p)
{
    _dxfFreeLightList((LightList)p);
    return OK;
}

Private
_dxfGetLights(Object obj, Camera cam)
{
    int i;
    Private p;
    Point from, to, up, eye;
    LightList lightlist = (LightList)DXAllocateZero(sizeof(struct lightList));
    if (! lightlist)
	return NULL;
    
    lightlist->na = lightlist->nl = 0;

    if (! _GatherLights(lightlist, obj, NULL, cam))
	goto error;

    DXGetView(cam, &from, &to, &up);
    eye = DXNormalize(DXSub(from, to));

    if (lightlist->na == 0 && lightlist->nl == 0)
    {
	Vector left;
	Vector dir;

	left = DXCross(eye,up);
	dir = DXAdd(eye,left);

	lightlist->lights[0] = DXNewDistantLight(dir, DXRGB(1,1,1));
	if (!lightlist->lights[0])
	    return NULL;
	lightlist->nl ++;
    }

    if (lightlist->na == 0)
	lightlist->ambient = DXRGB(.2, .2, .2);

    for (i = 0; i < lightlist->nl; i++)
    {
	Light l = lightlist->lights[i];
	float hx = eye.x+l->direction.x;
	float hy = eye.y+l->direction.y;
	float hz = eye.z+l->direction.z;
	float d = hx*hx + hy*hy + hz*hz;
	if (d != 0.0)
	    d = 1.0 / sqrt(d);
	lightlist->h[i] = DXVec(hx*d, hy*d, hz*d);
    }

    p = DXNewPrivate((Pointer)lightlist, _dxfFreeLightListPrivate);
    if (! p)
	goto error;

    return p;

error:
    _dxfFreeLightList(lightlist);
    return NULL;
}

Error
_dxfFreeLightList(LightList lightlist)
{
    if (lightlist)
    {
	int i;
	for (i = 0; i < lightlist->nl; i++)
	    DXDelete((Object)(lightlist->lights[i]));
	DXFree((Pointer)lightlist);
    }

    return OK;
}

static float      _kaf, _kdf, _ksf;
static int   	  _kspf;
static float      _kab, _kdb, _ksb;
static int   	  _kspb;
static Pointer    _fc, _bc;
static Vector     *_normals;
static RGBColor   *_map;
static LightList  _lights;
static dependency _cdep, _ndep;
static RGBColor	  *_fbuf;
static RGBColor	  *_bbuf;
static int    	  _vPerE;
static char       _fcst, _bcst, _ncst;
static char       _fbyte, _bbyte;
static RGBColor	  _ffltcolor;
static RGBColor	  _bfltcolor;

Error
_dxfInitApplyLights(float kaf, float kdf, float ksf, int kspf,
		    float kab, float kdb, float ksb, int kspb,
		    Pointer fc, Pointer bc, RGBColor *map,
		    Vector *normals, LightList lights,
		    dependency cdep, dependency ndep, 
		    RGBColor *fbuf, RGBColor *bbuf, int vPerE,
		    char fcst, char bcst, char ncst,
		    char fbyte, char bbyte)
{
    _kaf  = kaf; _kdf = kdf; _ksf = ksf; _kspf   = kspf;
    _kab  = kab; _kdb = kdb; _ksb = ksb; _kspb   = kspb;
    _map = map; _lights = lights;
    _normals = normals; _cdep = cdep; _ndep = ndep;
    _fbuf = fbuf; _bbuf = bbuf; _vPerE = vPerE;
    _fcst = fcst; _bcst = bcst, _ncst = ncst;
    _fbyte = fbyte; _bbyte = bbyte;

    _fc = fc;
    _bc = bc;

    if (_fbyte || _bbyte)
	_dxf_initUbyteToFloat();

    return OK;
}

struct lighting
{
    float frspec; float fgspec; float fbspec;
    float frdiff; float fgdiff; float fbdiff;
    float brspec; float bgspec; float bbspec;
    float brdiff; float bgdiff; float bbdiff;
};

Error
_dxfApplyLights(int *vertices, int *indices, int knt)
{
    int i, j, k, n, nknt, rknt, *iPtr;
    struct lighting *lighting, _lighting[4], *l;
    RGBColor *f, *b;
    Vector *normal;
    RGBColor fbuf, bbuf;

    /*
     * number of resulting lit colors is total number of vertices 
     * because (presumably) either normals or colors are positions-dependent.
     */
    rknt = _vPerE * knt;

    /*
     * Number of lighting calculations is the number of normal vectors:
     * either the number of elements (if normals are c_dep) or the number
     * of vertices (if normals are p_dep).
     */
    if (_ndep == dep_positions)
        nknt = rknt;
    else
	nknt = knt;
    
    /*
     * Use local buffer for lighting results if no more than 4 normals
     * are involved.
     */
    if (nknt > 4)
    {
	lighting = (struct lighting *)DXAllocate(nknt*sizeof(struct lighting));
	if (! lighting)
	    goto error;
    }
    else lighting = _lighting;

    if (_ndep == dep_positions)
	iPtr = vertices;
    else
	iPtr = indices;
    
    memset((char *)lighting, 0, nknt*sizeof(struct lighting));

    if (_ncst)
	normal = _normals;

    for (j = 0; j < nknt; j++)
    {
	if (!_ncst)
	    normal = _normals + *iPtr++;

	for (i = 0; i < _lights->nl; i++)
	{
	    Light l   = _lights->lights[i];
	    Vector *h = _lights->h + i;
	    float  d  = normal->x*h->x + normal->y*h->y + normal->z*h->z;

	    if (d > 0)
	    {
		d = _ksf * ipow(d, _kspf);
		lighting[j].frspec += d * l->color.r;
		lighting[j].fgspec += d * l->color.g;
		lighting[j].fbspec += d * l->color.b;
	    }
	    else
	    {
		d = -d;
		d = _ksb * ipow(d, _kspb);
		lighting[j].brspec += d * l->color.r;
		lighting[j].bgspec += d * l->color.g;
		lighting[j].bbspec += d * l->color.b;
	    }

	    d = l->direction.x*normal->x +
		l->direction.y*normal->y +
		l->direction.z*normal->z;
	    
	    if (d > 0)
	    {
		d *= _kdf;
		lighting[j].frdiff += d * l->color.r;
		lighting[j].fgdiff += d * l->color.g;
		lighting[j].fbdiff += d * l->color.b;
	    }
	    else
	    {
		d = -d;
		d *= _kdb;
		lighting[j].brdiff += d * l->color.r;
		lighting[j].bgdiff += d * l->color.g;
		lighting[j].bbdiff += d * l->color.b;
	    }

	    CLAMP(lighting[j].frspec);
	    CLAMP(lighting[j].fgspec);
	    CLAMP(lighting[j].fbspec);
	    CLAMP(lighting[j].frdiff);
	    CLAMP(lighting[j].fgdiff);
	    CLAMP(lighting[j].fbdiff);
	    CLAMP(lighting[j].brspec);
	    CLAMP(lighting[j].bgspec);
	    CLAMP(lighting[j].bbspec);
	    CLAMP(lighting[j].brdiff);
	    CLAMP(lighting[j].bgdiff);
	    CLAMP(lighting[j].bbdiff);
	}
    }

    if (_cdep == dep_positions)
	iPtr = vertices;
    else
	iPtr = indices;

    if (_fcst)
        if (_map)
            f = _map;
        else if (_fbyte)
        {
            unsigned char *ptr = (unsigned char *)_fc;
            fbuf.r = _dxd_ubyteToFloat[*ptr++];
            fbuf.g = _dxd_ubyteToFloat[*ptr++];
            fbuf.b = _dxd_ubyteToFloat[*ptr++];
            f = &fbuf;
        }
        else
            f = _fc;

    if (_bcst)
        if (_map)
            b = _map;
        else if (_bbyte)
        {
            unsigned char *ptr = (unsigned char *)_bc;
            bbuf.r = _dxd_ubyteToFloat[*ptr++];
            bbuf.g = _dxd_ubyteToFloat[*ptr++];
            bbuf.b = _dxd_ubyteToFloat[*ptr++];
            b = &bbuf;
        }
        else
            b = _bc;

    l = lighting;
    for (i = k = 0; i < knt; i++)
    {
	for (j = 0; j < _vPerE; j++, k++)
	{
	    int ci = *iPtr;

	    if (_map)
	    {
		if (! _fcst)
		    f = _map + ((unsigned char *)_fc)[ci];
		if (! _bcst)
		    b = _map + ((unsigned char *)_bc)[ci];
	    }
	    else
	    {
		if (! _fcst)
		{
		    if (_fbyte)
		    {
			unsigned char *ptr = ((unsigned char *)_fc) + ci*3;

			fbuf.r = _dxd_ubyteToFloat[*ptr++];
			fbuf.g = _dxd_ubyteToFloat[*ptr++];
			fbuf.b = _dxd_ubyteToFloat[*ptr++];
			f = &fbuf;
		    }
		    else
			f = ((RGBColor *)_fc) + ci;
		}

		if (! _bcst)
		{
		    if (_bbyte)
		    {
			unsigned char *ptr = ((unsigned char *)_bc) + ci*3;

			bbuf.r = _dxd_ubyteToFloat[*ptr++];
			bbuf.g = _dxd_ubyteToFloat[*ptr++];
			bbuf.b = _dxd_ubyteToFloat[*ptr++];
			b = &bbuf;
		    }
		    else
			b = ((RGBColor *)_bc) + ci;
		}
	    }
	
	    if (_fbuf)
	    {
		_fbuf[k].r = f->r*(_lights->ambient.r + l->frdiff) + l->frspec;
		_fbuf[k].g = f->g*(_lights->ambient.g + l->fgdiff) + l->fgspec;
		_fbuf[k].b = f->b*(_lights->ambient.b + l->fbdiff) + l->fbspec;
	    }

	    if (_bbuf)
	    {
		_bbuf[k].r = b->r*(_lights->ambient.r + l->brdiff) + l->brspec;
		_bbuf[k].g = b->g*(_lights->ambient.g + l->bgdiff) + l->bgspec;
		_bbuf[k].b = b->b*(_lights->ambient.b + l->bbdiff) + l->bbspec;
	    }

	    if (_cdep == dep_positions) iPtr++;
	    if (_ndep == dep_positions) l++;
	}

	if (_cdep == dep_connections) iPtr++;
	if (_ndep == dep_connections) l++;
    }

    if (lighting != _lighting)
	DXFree(lighting);

    return OK;

error:

    if (lighting != _lighting)
	DXFree(lighting);

    return ERROR;
}

static int _dxd_firstUbyteToFloat = 1;
float _dxd_ubyteToFloat[256];


void
_dxf_initUbyteToFloat()
{
    int i;

    if (_dxd_firstUbyteToFloat)
    {
	_dxd_firstUbyteToFloat = 0;

	for (i = 0; i < 256; i++)
	    _dxd_ubyteToFloat[i] = i / 256.0;
    }
}

