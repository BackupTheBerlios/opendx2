
/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/widgets/Color.h,v 1.1 1999/03/24 15:17:34 gda Exp $
 * $Log: Color.h,v $
 * Revision 1.1  1999/03/24 15:17:34  gda
 * Initial revision
 *
 * Revision 1.1.1.1  1999/03/19 20:59:40  gda
 * Initial CVS
 *
 * Revision 10.1  1999/02/24 13:22:43  gda
 * OpenDX Baseline
 *
 * Revision 9.1  1997/05/22 18:46:46  svs
 * Copy of release 3.1.4 code
 *
 * Revision 8.0  1995/10/03  18:48:58  nsc
 * Copy of release 3.1 code
 *
 * Revision 7.1  1994/01/18  19:02:08  svs
 * changes since release 2.0.1
 *
 * Revision 6.1  93/11/16  10:50:22  svs
 * ship level code, release 2.0
 * 
 * Revision 1.3  93/09/22  14:31:24  jvergo
 * Colormaps on 24 bit visuals.
 * 
 * Revision 1.2  93/02/17  10:46:03  danz
 * Added compilation flag for C++.
 * 
 * Revision 1.1  93/02/15  13:37:43  danz
 * Initial revision
 * 
 * Revision 1.1  90/10/05  10:28:41  jgv
 * Initial revision
 * 
 */
#ifndef _Color_h
#define _Color_h

#include "Image.h"
#include "ImageP.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif


typedef struct ControlColorRec
{
    XmImageWidget	w;
    int		screen_number;
    Display*	display;
    Visual*	visual;
    Colormap	default_colormap;
    Colormap	colormap;
    short	depth;
    short	map_size;
    short	num_cells;
    short	start;
    XColor	undithered_cells[256]; /* RGB - valid; 0 <= rgb <= 255 */
    XColor	opacity_corrected_cells[256]; /* RGB - valid; 0 <= rgb <= 255 */
    XColor	rgb[5][9][5];	       /* Pixel - valid */
} ControlColor;


typedef struct ColorBarRec
{
    Widget		frame;
    XmImageWidget	w;
    XmColorMapEditorWidget parent;
    ControlColor	*color;
    XImage*		ximage;
    XColor*		index_line;  /* Undithered column height x CELL_SIZE */ 
    XColor*		dithered_cells;/* Dithered column height x CELL_SIZE */
    GC			gc;
    short		width;
    short		height;
    short		image_width;
    short		image_height;
    short		margin;
    short		min;
    short		max;
    Boolean		vertical;
    Boolean		descend;
    int			depth;
    int			background_style;
} ColorBar;


ColorBar* CreateColorBar( XmColorMapEditorWidget parent,
			  int margin, int min_val, 
			  int max_val, ControlColor *color);
ControlColor* CreateColorMap( Widget w, int num_cells,
			      Boolean reserve_new_map );
void SetControlColor( ControlColor* color,
		      double hue[], double saturation[], double value[] );

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
