/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*****************************************************************************/
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/widgets/findcolor.h,v 1.1 1999/03/24 15:17:37 gda Exp $
 */
#ifndef _findcolor_h
#define _findcolor_h

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern
void find_color(Widget w, XColor *target);

extern
void find_color_ronly(Widget w, XColor *target, char *dontuse);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif

