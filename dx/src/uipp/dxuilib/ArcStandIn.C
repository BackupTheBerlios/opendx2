//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// ArcStandIn.C -								    //
//                                                                          //
// ArcStandIn Class methods and other related functions/procedures.		    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ArcStandIn.C,v 1.1 1999/03/24 15:17:38 gda Exp $
 */


#include "defines.h"
#include "ArcStandIn.h"
#include "../widgets/WorkspaceW.h"

//
// Print a representation of the stand in on a PostScript device.  We
// assume that the device is in the same coordinate space as the parent
// of this uicomponent (i.e. we send the current geometry to the 
// PostScript output file).  
//
boolean ArcStandIn::printAsPostScript(FILE *f)
{
    int i, *x = NULL, *y = NULL;

    if (this->line) {
	int points = XmWorkspaceLineGetPath(this->line,&x,&y);
	if (points > 1) {
	    for (i=0 ; i<points  ; i++) {
		if (fprintf(f,"%d %d ",x[i],y[i]) <= 0)
		    goto error;
		if (i == 0) { 
		    if (fprintf(f,"moveto ") <= 0)
			goto error;
		} else {
		    if (fprintf(f,"lineto ") <= 0)
			goto error;
		}
	    }
	    
	    if (fprintf(f,"stroke\n") <= 0)
		goto error;
	}

	if (x) XtFree((char*)x);
	if (y) XtFree((char*)y);
    }

    return TRUE;

error:
    if (x) XtFree((char*)x);
    if (y) XtFree((char*)y);

    return FALSE;
}

