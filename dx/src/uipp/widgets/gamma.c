/*****************************************************************************o
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*****************************************************************************/
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/widgets/gamma.c,v 1.1 1999/03/24 15:17:37 gda Exp $
 */

#include <math.h>
#include <X11/Xlib.h>

void gamma_correct(XColor *cell_def)
{
unsigned int red255, green255, blue255;

    red255   =  cell_def->red >> 8;
    green255 =  cell_def->green >> 8;
    blue255  =  cell_def->blue >> 8;

    red255 =sqrt(red255/256.0) * 256.0;
    green255 = sqrt(green255/256.0) * 256.0;
    blue255 = sqrt(blue255/256.0) * 256.0;

    cell_def->red = red255 << 8;
    cell_def->green = green255 << 8;
    cell_def->blue = blue255 << 8;
}

