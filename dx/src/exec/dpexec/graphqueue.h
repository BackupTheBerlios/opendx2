/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>



#ifndef _GRAPHQUEUE_H
#define _GRAPHQUEUE_H

#include "graph.h"

int _dxf_ExGQInit (int ngraphs);
extern void _dxf_ExGQEnqueue (Program *func);
Program *_dxf_ExGQDequeue (void);

extern int *gq_sort;
extern int ngraphs;

#endif /* _GRAPHQUEUE_H */
