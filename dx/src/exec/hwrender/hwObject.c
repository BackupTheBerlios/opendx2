/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


#include "hwDeclarations.h"
#include "hwDebug.h"


dxObject
_dxf_newHwObject(hwClass class, Pointer item, Error (*delete)())
{
  hwObjectP gPriv;

  ENTRY(("_dxf_newHwObject(0x%x, 0x%x, 0x%x)",
	 class, item, delete));
  
  gPriv = (hwObjectP)DXAllocateZero(sizeof(hwObjectT));
  if (! gPriv)
    return NULL;

  gPriv->class = class;
  gPriv->item = item;
  gPriv->delete = delete;

  EXIT(("OK"));
  return (dxObject)DXNewPrivate((Pointer)gPriv,_dxf_deleteHwObject);
}

Error
_dxf_deleteHwObject(Pointer p)  
{
  hwObjectP gPriv = (hwObjectP)p;

  ENTRY(("_dxf_deleteHwObject(0x%x)", p));
  
  if(gPriv && gPriv->delete)
  {
    (*gPriv->delete)(gPriv->item);
    gPriv->item = NULL;
  }

  if(gPriv->item)
    DXFree(gPriv->item);

  DXFree(gPriv);
  
  EXIT(("OK"));
  return OK;
}

Pointer
_dxf_getHwObjectData(dxObject p)
{
    hwObjectP gPriv;

    if (! p)
	return NULL;
    
    gPriv = (hwObjectP)DXGetPrivateData((Private)p);

    if (! gPriv)
	return NULL;
    
    return gPriv->item;
}

hwClass
_dxf_getHwClass(dxObject p)
{
    hwObjectP gPriv;

    if (! p)
	return CLASS_DELETED;
    
    gPriv = DXGetPrivateData((Private)p);

    if (! gPriv)
	return CLASS_DELETED;
    
    return gPriv->class;
}


