/*********************************************************************/
/*                     I.B.M. CONFIENTIAL                            */
/*********************************************************************/

/*---------------------------------------------------------------------------*\
 $Source: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/hwrender/starbase/hwTetraDrawSB.c,v $
  Author: Mark Hood
\*---------------------------------------------------------------------------*/

#define _HP_FAST_MACROS 1
#include <starbase.c.h>
#include "hwDeclarations.h"
#include "hwPortSB.h"
#include "hwMemory.h"
#include "hwCacheUtilSB.h"

#include "hwDebug.h"

#define Polyhedra                 Tetra
#define CpfPolyhedra             "CpfTetra"
#define CpcPolyhedra             "CpcTetra"
#define CpvPolyhedra             "CpvTetra"
#define tdmPolyhedraDraw          _dxfTetraDraw

#define PolyhedraSize             4
#define FacetsPerPolyhedron       4
#define VerticesPerFacet          3

#include "hwPolyhedraDrawSB.c.h"
