/*  Open Visualization Data Explorer Source File */


#ifndef Float_H
#define Float_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#define XmRDouble "double"
#if (XmVersion < 1002)
    #define XmRFloat "float"
#endif

extern void XmAddFloatConverters();

typedef struct {
    double value;
    int reason;		/*  Typically mode in which value was set	   */
    Boolean accepted;	/*  Called routine should check value and respond  */
} XmDoubleCallbackStruct;

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif


#endif
