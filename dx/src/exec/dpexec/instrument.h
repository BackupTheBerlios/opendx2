/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

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

extern Instrumentation	*exInstrument;
extern int		exDoInstrumentation;
#define IFINSTRUMENT(x) do {if(exDoInstrumentation) {x;}} while (0)

void ExAllocateInstrument (int);
void ExPrintInstrument (void);
void ExFreeInstrument (void);
void ExResetInstrument(void);

#else

#define IFINSTRUMENT(x)

#endif
#endif /* __INSTRUMENT_H_ */
