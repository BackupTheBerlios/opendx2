typedef struct color *Color;

#include <dxconfig.h>


struct color
{
    unsigned char r, g, b;
};

typedef struct treeNode *TreeNode;

struct treeNode 
{
    int      leaf;
    int      knt;
    int	     r, g, b;
    TreeNode kids[8];
    TreeNode next;
    TreeNode last;
};

typedef struct treeNodeBuf *TreeNodeBuf;

#define ALLOC 100

struct treeNodeBuf
{
    struct treeNode nodes[ALLOC];
    TreeNodeBuf     nextbuf;
    int             nextfree;
};

static TreeNodeBuf buflist   = NULL;
static TreeNode    freenodes = NULL;

static int nLeaves;

#define BRANCH(color, depth, index)		 \
{						 \
        int d = 7 - depth;			 \
	index = (((color->r >> d) & 0x1) << 0) + \
		(((color->g >> d) & 0x1) << 1) + \
		(((color->b >> d) & 0x1) << 2);	 \
}

TreeNode
GetTreeNode()
{
    TreeNode new = NULL;

    if (freenodes)
    {
	new = freenodes;
	freenodes = freenodes->next;
    }
    else
    {
	if (!buflist || buflist->nextfree == ALLOC)
	{
	    TreeNodeBuf newbuf =
		(TreeNodeBuf)DXAllocateZero(sizeof(struct treeNodeBuf));
	    if (! newbuf)
		return NULL;
	    
	    newbuf->nextfree = 0;

	    newbuf->nextbuf = buflist;
	    buflist = newbuf;
	}

	new = buflist->nodes + buflist->nextfree;
	buflist->nextfree ++;
    }

    return new;
}

void
FreeNode(TreeNode node)
{
    memset(node, 0, sizeof(struct treeNode));
    node->next = freenodes;
    freenodes = node;
}

void
CleanupNodes()
{
    while (buflist)
    {
	TreeNodeBuf this = buflist->nextbuf;
	DXFree((Pointer)buflist);
	buflist = this;
    }

    freenodes = NULL;
}

struct treeNode depthlist[8];

TreeNode
InsertTree(TreeNode node, Color color, int depth)
{
    int index;

    if (! node)
    {
	node = GetTreeNode();
	if (! node)
	    goto error;

	node->r    = 0;
	node->g    = 0;
	node->b    = 0;
	node->knt  = 0;
	node->leaf = depth == 7;

	if (! node->leaf)
	{
	    node->next = depthlist[depth].next;
	    depthlist[depth].next = node;
	    depthlist[depth].knt ++;
	}

	if (node->leaf)
	    nLeaves ++;
    }

    if (node->leaf)
    {
	node->r += color->r;
	node->g += color->g;
	node->b += color->b;
    }
    else
    {
	BRANCH(color, depth, index);
	node->kids[index] =
		InsertTree(node->kids[index], color, depth+1);
	if (! node->kids[index])
	    goto error;
    }

    node->knt ++;

    return node;

error:
    return NULL;
}

int
SearchTree(TreeNode node, Color color, int depth)
{
    int index;

    if (! node)
    {
	DXSetError(ERROR_INTERNAL, "null node in SearchTree");
	return -1;
    }

    if (node->leaf)
	return node->knt;
    else
    {
	BRANCH(color, depth, index);
	return SearchTree(node->kids[index], color, depth+1);
    }
}

struct treeNode depthlist[8];

static int reduce_max = 1;

int
ReduceTree()
{
    int i, j, bestknt;
    TreeNode last, next, best, node;

    for (i = 6; i >= 0; i--)
    {
	if (depthlist[i].next)
	{
	    if (reduce_max)
		bestknt = 0;
	    else
		bestknt = 99999999;

	    last = depthlist + i;
	    next = last->next;
	    while(next)
	    {
		if (reduce_max)
		{
		    if (next->knt > bestknt)
			best = last;
		}
		else
		{
		    if (next->knt < bestknt)
			best = last;
		}
		
		last = next;
		next = next->next;
	    }

	    node = best->next;
	    best->next = node->next;
	    depthlist[i].knt --;

	    for (j = 0; j < 8; j++)
	    {
		TreeNode child = node->kids[j];
		if (child)
		{
		    node->r += child->r;
		    node->g += child->g;
		    node->b += child->b;
		    FreeNode(child);
		    nLeaves --;
		}
	    }

	    node->leaf = 1;
	    nLeaves ++;

	    if (i > 0)
	    {
#if 0
		node->next = depthlist[i-1].next;
		depthlist[i-1].next = node;
		depthlist[i-1].knt ++;
#endif
	    }
	    else
	    {
		DXSetError(ERROR_INTERNAL, "reduce at level 0?");
		return ERROR;
	    }

	    return OK;
	}
    }

    return ERROR;
}


int
CountLeaves(TreeNode tree, int *n)
{
    if (tree->leaf)
    {
	*n = *n + 1;
    }
    else
    {
	int i;
	TreeNode child;

	for (i = 0; i < 8; i++)
	    if (NULL != (child = tree->kids[i]))
		if (! CountLeaves(child, n))
		    return ERROR;
    }

    return OK;
}

static int find_me = -1;

void
found(){}

static int skip = 11;

TreeNode
CreateTree(Pointer pixdata, int knt, int nColors, int float_pixels)
{
    TreeNode tree = NULL;
    struct color pbuf;
    int skipsize;
    ubyte *u_pixdata = (ubyte *)pixdata;
    int i, j;
    int r = 0;

    if (float_pixels)
	skipsize = skip*3*sizeof(float);
    else
	skipsize = skip*sizeof(struct color);

    for (i = 0; i < 8; i++)
    {
	depthlist[i].next = NULL;
	depthlist[i].knt = 0;
    }

    nLeaves = 0;

    for (j = 0; j < skip; j++)
    {
	ubyte *p;

	if (float_pixels)
	    p = u_pixdata + j*3*sizeof(float);
	else
	    p = u_pixdata + j*sizeof(struct color);

	for (i = j; i < knt; i += skip, p += skipsize)
	{
	    if (i == find_me)
		found();

	    if (float_pixels)
	    {
		float fr = ((float *)p)[0];
		float fg = ((float *)p)[1];
		float fb = ((float *)p)[2];
		pbuf.r = fr >= 1.0 ? 255 : fr <= 0.0 ? 0 :
					(unsigned char)(255 * fr);
		pbuf.g = fg >= 1.0 ? 255 : fg <= 0.0 ? 0 :
					(unsigned char)(255 * fg);
		pbuf.b = fb >= 1.0 ? 255 : fb <= 0.0 ? 0 :
					(unsigned char)(255 * fb);

		if (NULL == (tree = InsertTree(tree, &pbuf, 0)))
		    goto error;
	    }
	    else
		if (NULL == (tree = InsertTree(tree, (Color)p, 0)))
		    goto error;

	    while (nLeaves > nColors)
		if (! ReduceTree())
		    goto error;
	}
    }

    return tree;

error: 
    return NULL;
}

TreeNode
AddFieldToTree(TreeNode tree, Pointer pixdata, int knt,
				int float_pixels, int nColors)
{
    struct color pbuf;
    int skipsize;
    ubyte *u_pixdata = (ubyte *)pixdata;
    int i, j;
    int r = 0;

    if (float_pixels)
	skipsize = skip*3*sizeof(float);
    else
	skipsize = skip*sizeof(struct color);

    for (j = 0; j < skip; j++)
    {
	ubyte *p;

	if (float_pixels)
	    p = u_pixdata + j*3*sizeof(float);
	else
	    p = u_pixdata + j*sizeof(struct color);

	for (i = j; i < knt; i += skip, p += skipsize)
	{
	    if (i == find_me)
		found();

	    if (float_pixels)
	    {
		float fr = ((float *)p)[0];
		float fg = ((float *)p)[1];
		float fb = ((float *)p)[2];
		pbuf.r = fr >= 1.0 ? 255 : fr <= 0.0 ? 0 :
					(unsigned char)(255 * fr);
		pbuf.g = fg >= 1.0 ? 255 : fg <= 0.0 ? 0 :
					(unsigned char)(255 * fg);
		pbuf.b = fb >= 1.0 ? 255 : fb <= 0.0 ? 0 :
					(unsigned char)(255 * fb);

		if (NULL == (tree = InsertTree(tree, &pbuf, 0)))
		    goto error;
	    }
	    else
		if (NULL == (tree = InsertTree(tree, (Color)p, 0)))
		    goto error;

	    while (nLeaves > nColors)
		if (! ReduceTree())
		    goto error;
	}
    }

    return tree;

error: 
    return NULL;
}

Error
CreateTable(TreeNode node, Color table, int nColors, int *next)
{
    if (node->leaf)
    {
	float recip = 1.0 / node->knt;
	Color c = table + (*next);

	if ((*next) < nColors)
	{
	    c->r = node->r * recip;
	    c->g = node->g * recip;
	    c->b = node->b * recip;

	    node->knt = (*next);
	}

	*next = *next + 1;
    }
    else
    {
	int i;
	TreeNode child;

	for (i = 0; i < 8; i++)
	    if (NULL != (child = node->kids[i]))
		if (! CreateTable(child, table, nColors, next))
		    return ERROR;
    }

    return OK;
}

Error
CreateQuantPixels(TreeNode tree,
	Pointer input, unsigned char *output, int knt, int float_pixels)
{
    int i;
    unsigned char *s = (unsigned char *)input;
    unsigned char *d = output;
    int skipsize;
    struct color pbuf;

    skipsize = float_pixels ? 3*sizeof(float) : sizeof(struct color);

    for (i = 0; i < knt; i++, s += skipsize, d++)
    {
	int q;

	if (i == find_me)
	    found();

	    if (float_pixels)
	    {
		float fr = ((float *)s)[0];
		float fg = ((float *)s)[1];
		float fb = ((float *)s)[2];
		pbuf.r = fr >= 1.0 ? 255 : fr <= 0.0 ? 0 :
					(unsigned char)(255 * fr);
		pbuf.g = fg >= 1.0 ? 255 : fg <= 0.0 ? 0 :
					(unsigned char)(255 * fg);
		pbuf.b = fb >= 1.0 ? 255 : fb <= 0.0 ? 0 :
					(unsigned char)(255 * fb);

		q = SearchTree(tree, (Color)&pbuf, 0);
	    }
	    else
		q = SearchTree(tree, (Color)s, 0);

	if (q < 0)
	    return ERROR;
	
	*d = q;
    }

    return 1;
}
