///////////////////////////////////////////////////////////////////////
//                        DX  SOURCEFILE                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////
/*
\section{Group class}
*/

INCLUDE  objectClass.X

SUBCLASS Group OF Object
IMPLEMENTS Delete GetType Copy
IMPLEMENTS BoundingBox Gather Paint Shade
DEFINES Group SetMember(Group, char *, Object)
DEFINES Group SetEnumeratedMember(Group, int, Object)
IMPLEMENTS SetMember SetEnumeratedMember

SUBCLASS Series OF Group
IMPLEMENTS SetMember SetEnumeratedMember Copy

SUBCLASS CompositeField OF Group
IMPLEMENTS SetMember SetEnumeratedMember BoundingBox

SUBCLASS MultiGrid OF Group
IMPLEMENTS SetMember SetEnumeratedMember

struct group {

    struct object object;	/* object preamble */
    lock_type lock;		/* for Set(Enumerated)Member only */

    /* the members */
    struct member {		/* the members */
	char *name;		/* the member name */
	Object value;		/* the member */
	float position;		/* position on series axis for series group */
    } *members;			/* the members */
    int nmembers;		/* number of members */
    int alloc;			/* space allocated */

    /* SetGroupType()/GetType() */
    int typed;			/* whether type was set */
    Type type;			/* the type */
    Category category;		/* the category */
    int rank;			/* rank */
    int *shape;			/* shape */
};

struct series {			/* series object */
    struct group group;		/* group preamble */
};

struct compositefield {		/* composite field object */
    struct group group;		/* group preamble */
};

struct multigrid {		/* multigrid object */
    struct group group;		/* group preamble */
};

Group _dxf_NewGroup(struct group_class *class);

static Group _CopyGroup(Group old, Group new, enum copy copy);
static Series _CopySeries(Series old, Series new, enum copy copy);

Group _dxf_SetEnumeratedMember(Group g, int n, double position, Object value);
/**
Internal routine to support both {\tt SetEnumeratedMember()} and
{\tt SetSeriesMember()}.
**/

Object _dxf_GetEnumeratedMember(Group g, int n, float *position, char **name);
/**
Internal routine to support both {\tt GetEnumeratedMember()} and
{\tt GetSeriesMember()}.
**/

static Series _NewSeries(struct series_class *class);

static CompositeField _dxf_NewCompositeField(struct compositefield_class *class);

static MultiGrid _dxf_NewMultiGrid(struct multigrid_class *class);

