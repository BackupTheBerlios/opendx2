/*  Open Visualization Data Explorer Source File */

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

