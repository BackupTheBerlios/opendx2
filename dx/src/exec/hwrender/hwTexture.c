/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>



#include "hwDeclarations.h"
#include "hwXfield.h"
#include "hwMatrix.h"
#include "hwMemory.h"
#include "hwPortLayer.h"
#include "hwWindow.h"
#include "hwObjectHash.h"

#define String dxString
#define Object dxObject
#define Angle dxAngle
#define Matrix dxMatrix
#define Screen dxScreen
#define Boolean dxBoolean
#include "internals.h"
#undef String
#undef Object
#undef Angle
#undef Matrix
#undef Screen
#undef Boolean

#include "hwDebug.h"

typedef struct _texture
{
    int       width, height;
    ubyte     *pixels;
    dxObject  textureObj;
    int       myPixels;
} *Texture;

static Error _getTexture_Field(Texture);
static Error _getTexture_CompositeField(Texture);

static Error
_deleteTexture(Pointer p)
{
    if (p)
    {
	Texture t = (Texture)p;
	if (t->myPixels)
	    DXFree((Pointer)t->pixels);
	if (t->textureObj)
	    DXDelete(t->textureObj);
    }
    return OK;
}

static dxObject
_newTexture(dxObject obj)
{
    dxObject txo = NULL;
    Texture texture = (Texture)DXAllocateZero(sizeof(struct _texture));
    if (! texture)
	goto error;

    texture->textureObj = DXReference(obj);

    if (DXGetObjectClass(obj) == CLASS_FIELD)
    {
	if (! _getTexture_Field(texture))
	    goto error;
    }
    else if (DXGetObjectClass(obj) == CLASS_GROUP &&
	    DXGetGroupClass((Group)obj) == CLASS_COMPOSITEFIELD)
    {
	if (! _getTexture_CompositeField(texture))
	    goto error;
    }
    else
    {
	DXSetError(ERROR_INVALID_DATA, "invalid object type for texture");
	goto error;
    }

    txo = (dxObject)DXNewPrivate((Pointer)texture, _deleteTexture);
    if (! txo)
	goto error;

    return txo;

error:
    _deleteTexture((Pointer)texture);
    return ERROR;
}

Error
_XTexture(Field f, xfieldT* xf, void *globals)
{
    DEFGLOBALDATA(globals);
    Type  type;
    Category cat;
    int   n, rank, shape[32], counts[2];
    dxObject attr, texture = _dxf_xfieldAttributes(xf)->texture;
    dxObject txo;

    if (texture)
    {
	Texture txp;

	xf->uv_array = (Array)DXGetComponentValue(f, "uv");
	if (! xf->uv_array)
	{
	    DXSetError(ERROR_INVALID_DATA,
		"texture attribute but no uv component");
	    goto error;
	}

	DXGetArrayInfo(xf->uv_array, NULL, &type, NULL, &rank, shape);

	if (type != TYPE_FLOAT || rank != 1 || shape[0] != 2)
	{
	    DXSetError(ERROR_INVALID_DATA, 
		"uv component must contain float 2-vectors");
		goto error;
	}

	attr = DXGetAttribute((dxObject)xf->uv_array, "dep");
	if (DXGetObjectClass(attr) != CLASS_STRING)
	{
	    DXSetError(ERROR_INVALID_DATA, 
		"uv dep attribute must be a DXString object");
	    goto error;
	}

	if (strcmp(DXGetString((dxString)attr), "positions"))
	{
	    DXSetError(ERROR_INVALID_DATA, 
		"uv must be dep on positions");
	    goto error;
	}

	xf->uv = DXCreateArrayHandle(xf->uv_array);
	if (! xf->uv)
	    goto error;
    
	DXReference((dxObject)xf->uv_array);

	txo = _dxf_QueryObject(TEXTUREHASH, texture);
	if (! txo)
	{
	    txo = _newTexture(texture);
	    if (! txo)
		goto error;

	    _dxf_InsertObject(TEXTUREHASH, texture, txo);
	}

	xf->texture_field = DXReference(txo);
	txp = (Texture)DXGetPrivateData((Private)txo);

	xf->textureWidth  = txp->width;
	xf->textureHeight = txp->height;
	xf->texture       = txp->pixels;
    }
    else
    {
	xf->texture_field = NULL;
	xf->uv_array      = NULL;
	xf->texture       = NULL;
    }

    return OK;

error:
    if (xf->texture_field)
	DXDelete((dxObject)xf->texture_field);
    if (xf->uv_array)
	DXDelete((dxObject)xf->uv_array);

    xf->texture_field = NULL;
    xf->texture = NULL;
    xf->uv_array = NULL;
    xf->uv = NULL;
    xf->myTextureData = 0;

    return ERROR;
}

static Error
_getTexture_Field(Texture t)
{
    Type  type;
    Category cat;
    int   n, rank, shape[32], counts[2];
    Array tmp;
    int i, sizeError = 0, s0, s1;
    dxObject attr;
    Field tf = (Field)t->textureObj;

    tmp = (Array)DXGetComponentValue(tf, "connections");
    if (! tmp)
    {
	DXSetError(ERROR_INVALID_DATA, 
	    "texture field has no connections");
	goto error;
    }

    if (! DXQueryGridConnections(tmp, &n, counts))
    {
	DXSetError(ERROR_INVALID_DATA, 
	    "texture field must have regular connections");
	goto error;
    }

    if (n != 2)
    {
	DXSetError(ERROR_INVALID_DATA, 
	    "texture field must be 2-d regular connections");
	goto error;
    }

    t->width  = counts[1];
    t->height = counts[0];

    if (counts[0] < 64 || counts[1] < 64)
    {
	DXSetError(ERROR_INVALID_DATA,
	    "texture map resolution must be at least 64x64");
	goto error;
    }
	    
    for (s0 = s1 = 0, i = 1; i && s0 < 2 && s1 < 2; i <<= 1)
    {
	s0 += (counts[0] & i) ? 1 : 0;
	s1 += (counts[1] & i) ? 1 : 0;
    }

    if (i)
    {
	DXSetError(ERROR_INVALID_DATA,
	    "texture map resolution must be powers of 2");
	goto error;
    }

    tmp = (Array)DXGetComponentValue(tf, "colors");
    if (! tmp)
	tmp = (Array)DXGetComponentValue(tf, "data");
    if (! tmp)
    {
	DXSetError(ERROR_INVALID_DATA, 
	    "texture has neither colors nor data");
	return ERROR;
    }

    DXGetArrayInfo(tmp, &n, &type, &cat, &rank, shape);

    if (type == TYPE_UBYTE && rank == 1 && shape[0] == 3)
    {
	t->pixels = (ubyte *)DXGetArrayData(tmp);
	t->myPixels = 0;
    }
    else
    {
	t->pixels = (ubyte *)tdmAllocate(3*n*sizeof(ubyte));
	if (! t->pixels)
	    goto error;
	t->myPixels = 1;
    
	if (type == TYPE_FLOAT && rank == 1 && shape[0] == 3)
	{
	    int i;
	    ubyte *dst = t->pixels;
	    float *src = (float *)DXGetArrayData(tmp);
	    for (i = 0; i < 3*n; i++)
	    {
		float c = *src++;
		if (c < 0)        *dst++ = 0;
		else if (c > 1.0) *dst++ = 255;
		else              *dst++ = (ubyte)(c * 255);
	    }
	}
	else if (type == TYPE_UBYTE &&
	    (rank == 0 || rank == 1 && shape[0] == 1))
	{
	    int i, m;
	    ubyte *dst = t->pixels;
	    ubyte *src = (ubyte *)DXGetArrayData(tmp);
	    Array cmap_array;
	    ubyte map_array[768];
	    ubyte *map;

	    cmap_array = (Array)DXGetComponentValue(tf, "color map");
	    if (! cmap_array)
	    {   
		DXSetError(ERROR_MISSING_DATA, 
		    "texture map contains scalar bytes but no color map");
		    goto error;
	    }

	    DXGetArrayInfo(cmap_array, &m, &type, NULL, &rank, shape);

	    if (type == TYPE_FLOAT && rank == 1 && shape[0] == 3)
	    {
		float *map_src = (float *)DXGetArrayData(cmap_array);

		for (i = 0; i < 3*m; i++)
		{
		    float c = *map_src++;
		    if      (c < 0.0) map_array[i] = 0;
		    else if (c > 1.0) map_array[i] = 255;
		    else 	      map_array[i] = (ubyte)(c * 255);
		}
		map = map_array;
	    }
	    else if (type == TYPE_UBYTE && rank == 1 && shape[0] == 3)
	    {
		map = (ubyte *)DXGetArrayData(cmap_array);
	    }
	    else
	    {
		DXSetError(ERROR_INVALID_DATA,
		    "invalid colormap type in texture");
		goto error;
	    }

	    for (i = 0; i < n; i++)
	    {
		ubyte *c = map + 3 * *src++;
		*dst++ = *c++;
		*dst++ = *c++;
		*dst++ = *c++;
	    }
	}
	else
	{ 
	    DXSetError(ERROR_INVALID_DATA,
		"texture must be float or ubyte 3-vectors or %s",
		"contain scalar ubytes and have a color map");
	    goto error;
	}
    }
	
    return OK;

error:
    return ERROR;
}

static Error
_getTexture_CompositeField(Texture t)
{
    Type  type;
    Category cat;
    int   n, rank, shape[32], counts[2];
    int i, sizeError = 0, s0, s1;
    dxObject attr;
    Group cf = (Group)t->textureObj;
    int nMembers;

    DXGetMemberCount(cf, &nMembers);

    counts[0] = counts[1] = 0;

    for (i = 0; i < nMembers; i++)
    {
	Field member;
	Array grid;
	int memberCounts[2], memberOffsets[2], nDim, cnt;

	member = (Field)DXGetEnumeratedMember(cf, i, NULL);
	grid = (Array)DXGetComponentValue(member, "connections");

	if (!DXQueryGridConnections(grid, &nDim, memberCounts) ||
	    !DXGetMeshOffsets((MeshArray)grid, memberOffsets))
	{
	    DXSetError(ERROR_INVALID_DATA, 
		"texture field must have regular connections");
	    goto error;
	}

	if (nDim != 2)
	{
	    DXSetError(ERROR_INVALID_DATA, "texture fields must be 2-D");
	    goto error;
	}

	if ((cnt = memberOffsets[0] + memberCounts[0]) > counts[0])
	    counts[0] = cnt;

	if ((cnt = memberOffsets[1] + memberCounts[1]) > counts[1])
	    counts[1] = cnt;
    }

    t->width  = counts[1];
    t->height = counts[0];

    if (counts[0] < 64 || counts[1] < 64)
    {
	DXSetError(ERROR_INVALID_DATA,
	    "texture map resolution must be at least 64x64");
	goto error;
    }
	    
    for (s0 = s1 = 0, i = 1; i && s0 < 2 && s1 < 2; i <<= 1)
    {
	s0 += (counts[0] & i) ? 1 : 0;
	s1 += (counts[1] & i) ? 1 : 0;
    }

    if (i)
    {
	DXSetError(ERROR_INVALID_DATA,
	    "texture map resolution must be powers of 2");
	goto error;
    }

    n = counts[0] * counts[1];

    t->pixels = (ubyte *)tdmAllocate(3*n*sizeof(ubyte));
    if (! t->pixels)
	goto error;
    t->myPixels = 1;

    for (i = 0; i < nMembers; i++)
    {
	Field member;
	Array texture;
	Array grid;
	int memberCounts[2], memberOffsets[2], nDim, cnt;

	member = (Field)DXGetEnumeratedMember(cf, i, NULL);
	grid = (Array)DXGetComponentValue(member, "connections");

	texture = (Array)DXGetComponentValue(member, "colors");
	if (! texture)
	    texture = (Array)DXGetComponentValue(member, "data");
	if (! texture)
	{
	    DXSetError(ERROR_INVALID_DATA, 
		"texture has neither colors nor data");
	    return ERROR;
	}

	DXQueryGridConnections(grid, NULL, memberCounts);
	DXGetMeshOffsets((MeshArray)grid, memberOffsets);

	DXGetArrayInfo(texture, NULL, &type, &cat, &rank, shape);

	if (type == TYPE_UBYTE && rank == 1 && shape[0] == 3)
	{
	    int j, k;
	    ubyte *src = (ubyte *)DXGetArrayData(texture);
	    ubyte *dst = t->pixels + 3*((memberOffsets[0]*counts[1])
					     + memberOffsets[1]);
	    int src_stride = 3*counts[1];
	    int dst_stride = 3*memberCounts[1];

	    int cpy_length = src_stride;

	    for (j = 0; j < memberCounts[0]; j++)
	    {
		memcpy(dst, src, cpy_length);
		dst += dst_stride;
		src += src_stride;
	    }
	}
	else if (type == TYPE_FLOAT && rank == 1 && shape[0] == 3)
	{
	    int j, k;
	    float *src = (float *)DXGetArrayData(texture);
	    ubyte *dst = t->pixels + 3*((memberOffsets[0]*counts[1])
					     + memberOffsets[1]);
	    int dst_stride = 3*(counts[1] - memberCounts[1]);

	    for (j = 0; j < memberCounts[0]; j++)
	    {
		for (k = 0; k < memberCounts[1]; k++)
		{
		    float c = *src++;
		    if (c < 0)        *dst++ = 0;
		    else if (c > 1.0) *dst++ = 255;
		    else              *dst++ = (ubyte)(c * 255);
		}
		dst += dst_stride;
	    }
	}
	else if (type == TYPE_UBYTE &&
	    (rank == 0 || rank == 1 && shape[0] == 1))
	{
	    int j, k, m;
	    Array cmap_array;
	    ubyte map_array[768];
	    ubyte *map;
	    ubyte *src = (ubyte *)DXGetArrayData(texture);
	    int dst_stride = 3*(counts[1] - memberCounts[1]);
	    ubyte *dst = t->pixels + 3*((memberOffsets[0]*counts[1])
					     + memberOffsets[1]);

	    cmap_array = (Array)DXGetComponentValue(member, "color map");
	    if (! cmap_array)
	    {   
		DXSetError(ERROR_MISSING_DATA, 
		    "texture map contains scalar bytes but no color map");
		    goto error;
	    }

	    DXGetArrayInfo(cmap_array, &m, &type, NULL, &rank, shape);

	    if (type == TYPE_FLOAT && rank == 1 && shape[0] == 3)
	    {
		float *map_src = (float *)DXGetArrayData(cmap_array);

		for (j = 0; j < 3*m; j++)
		{
		    float c = *map_src++;
		    if      (c < 0.0) map_array[j] = 0;
		    else if (c > 1.0) map_array[j] = 255;
		    else 	      map_array[j] = (ubyte)(c * 255);
		}
		map = map_array;
	    }
	    else if (type == TYPE_UBYTE && rank == 1 && shape[0] == 3)
	    {
		map = (ubyte *)DXGetArrayData(cmap_array);
	    }
	    else
	    {
		DXSetError(ERROR_INVALID_DATA,
		    "invalid colormap type in texture");
		goto error;
	    }

	    for (j = 0; j < memberCounts[0]; j++)
	    {
		for (k = 0; k < memberCounts[1]; k++)
		{
		    ubyte *c = map + (3 * *src);
		    *dst++ = *c++;
		    *dst++ = *c++;
		    *dst++ = *c++;
		    src ++;
		}
		dst += dst_stride;
	    }
	}
	else
	{ 
	    DXSetError(ERROR_INVALID_DATA,
		"texture must be float or ubyte 3-vectors or %s",
		"contain scalar ubytes and have a color map");
	    goto error;
	}
    }
	
    return OK;

error:
    return ERROR;
}
