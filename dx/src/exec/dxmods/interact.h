/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dx/dx.h>
#if !defined(os2) && !defined(DXD_WIN)
#include <values.h>
#endif
#include <math.h>

#define CLAMP(c,a,b) ((c < a) ? a: ((c > b) ? b: c))
#define CLAMPMIN(c,a) ((c < a) ? a: c)
#define CLAMPMAX(c,b) ((c > b) ? b: c)
#define OUTOFRANGE(c,a,b) ((c < a) ? 1: ((c > b) ? 1: 0))
#define MAXPRINT 7
/* MAX_MSGLEN should be less than or equal to MSG_BUFLEN in dpexec/distp.h */
#define MAX_MSGLEN 4000
#define SLOP 64
#define AtEnd(p) ((p)->atend)

#define NUMBER_CHARS 16   	/* number of print characters for each number*/
#define NAME_CHARS   10		/* number of print characters for each name */
#define METHOD_CHARS 10     	/* number of print characters for method */

#if  defined(DXD_WIN) && defined(ABSOLUTE)
#undef	ABSOLUTE
#endif

typedef enum {
        PERCENT_ROUND = 1,
        PERCENT = 2,
        ABSOLUTE = 3
} method_type;

struct einfo {
    int maxlen;
    int atend;
    char *mp;
    char *msgbuf;
};

extern
Error _dxfinteract_float(char *, Object,float *, float *,
                         float *,int *,char *,int,method_type,int *,int *);
extern
Error _dxfprint_message(Pointer ,struct einfo *,Type ,int ,int *,int);
extern
int _dxfcheck_obj_cache(Object ,char *,int ,Object);
