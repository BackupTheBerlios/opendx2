///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/enums.h,v 1.1 1999/03/24 15:17:49 gda Exp $
 */
#ifndef _enums_h
#define _enums_h

//
// The following are passed into the xxxPrintNode routines, specifying
// the type of printing to be done.  These are used by both Network
// and Node.
//
     enum PrintType {
                PrintExec = 0,     // Destination: exec
                PrintFile,         // Destination: file
                PrintCut,          // Destination: cut/paste
                PrintCPBuffer      // Destination: cut/paste
     };

//
// For ImageWindow and ImageNode 
//
enum DirectInteractionMode
{
    NONE,
    CAMERA,
    CURSORS,
    PICK,
    NAVIGATE,
    PANZOOM,
    ROAM,
    ROTATE,
    ZOOM
};

#endif
