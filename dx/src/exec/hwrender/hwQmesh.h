/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#ifndef tdmQmesh_h
#define tdmQmesh_h
/*
 *
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/hwrender/hwQmesh.h,v 1.1 1999/03/24 15:18:33 gda Exp $
 */


/*
^L
 *===================================================================
 *      Structure Definitions and Typedefs
 *===================================================================
 */



#if defined(alphax)
#define MaxQstripSize 60
#else
#define MaxQstripSize 100
#endif
#define MinQstripAvg   5


#define Down  0
#define Up    1
#define Left  2
#define Right 3

typedef struct _Qstrip
  {
  int points;
  int *point;
  } Qstrip;


typedef struct _Qmesh
  {
  int qstrips;
  Qstrip **qstrip;
  } Qmesh;



#endif 

