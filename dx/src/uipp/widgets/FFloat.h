/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/widgets/FFloat.h,v 1.1 1999/03/24 15:17:35 gda Exp $
 */

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
