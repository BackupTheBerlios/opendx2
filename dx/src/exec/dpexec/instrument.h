/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/instrument.h,v 1.5 2000/08/11 15:28:12 davidt Exp $
 */

#include <dxconfig.h>


#ifndef __INSTRUMENT_H_
#define __INSTRUMENT_H_

#define INSTRUMENT
#undef INSTRUMENT

#ifdef INSTRUMENT

typedef struct {
    int tasks;
    int modules;
    int numSlaveTry;
    int numMasterTry;
} Instrumentation;

extern Instrumentation	*exInstrument; /* defined in instrument.c */
extern int		exDoInstrumentation; /* defined in instrument.c */
#define IFINSTRUMENT(x) do {if(exDoInstrumentation) {x;}} while (0)

void ExAllocateInstrument (int);
void ExPrintInstrument (void);
void ExFreeInstrument (void);
void ExResetInstrument(void);

#else

#define IFINSTRUMENT(x)

#endif
#endif /* __INSTRUMENT_H_ */
