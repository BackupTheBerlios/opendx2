/*********************************************************************/
/*                     I.B.M. CONFIENTIAL                           */
/*********************************************************************/

#include <dxconfig.h>


/*---------------------------------------------------------------------------*\
 $Source: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/hwrender/starbase/hwTriDrawSB.c,v $
  Author: Mark Hood
\*---------------------------------------------------------------------------*/

#define _HP_FAST_MACROS 1
#include <starbase.c.h>
#include "hwDeclarations.h"
#include "hwPortSB.h"
#include "hwXfield.h"
#include "hwMemory.h"
#include "hwCacheUtilSB.h"

#include "hwDebug.h"

#define Polygon                 Tri
#define PolygonSize             3
#define CpfPolygon             "CpfTri"
#define CpcPolygon             "CpcTri"
#define CpvPolygon             "CpvTri"
#define tdmPolygonDraw          _dxfTriDraw

#include "hwPolygonDrawSB.c.h"
