/*
 * (C) COPYRIGHT International Business Machines Corp. 1995
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, 
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in 
 * supporting documentation, and that the name of IBM not be
 * used in advertising or publicity pertaining to distribution of the
 * software without specific prior written permission. 
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,       
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY        
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.       
 *
 * IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT
 * OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOFTWARE.
 */


#include <stdlib.h>
#include <stdio.h>

#include "dxf.h"

/*
 * Note: This colormap was snarfed from the internet.  Only the
 * first eight entiries are quaranteed to be correct for any
 * given DXF file becuase these are the only ones the AutoCAD
 * specifically defines.
 */
static RGBColor color_list[] = {
  {1.0,      0.0,      0.0 },
  {1.0,      1.0,      0.0 },
  {0.0,      1.0,      0.0 },
  {0.0,      1.0,      1.0 },
  {0.0,      0.0,      1.0 },
  {1.0,      0.0,      1.0 },
  {0.0,      0.0,      0.0 },
  {0.0,      0.0,      0.0 },
  {0.0,      0.0,      0.0 },
  {1.0,      0.0,      0.0 },
  {1.0,      0.5,      0.5 },
  {0.65,     0.0,      0.0 },
  {0.65,     0.325,    0.325 },
  {0.5,      0.0,      0.0 },
  {0.5,      0.25,     0.25 },
  {0.3,      0.0,      0.0 },
  {0.3,      0.15,     0.15 },
  {0.15,     0.0,      0.0 },
  {0.15,     0.075,    0.075 },
  {1.0,      0.25,     0.0 },
  {1.0,      0.625,    0.5 },
  {0.65,     0.1625,   0.0 },
  {0.65,     0.4063,   0.325 },
  {0.5,      0.125,    0.0 },
  {0.5,      0.3125,   0.25 },
  {0.3,      0.075,    0.0 },
  {0.3,      0.1875,   0.15 },
  {0.15,     0.0375,   0.0 },
  {0.15,     0.0938,   0.075 },
  {1.0,      0.5,      0.0 },
  {1.0,      0.75,     0.5 },
  {0.65,     0.325,    0.0 },
  {0.65,     0.4875,   0.325 },
  {0.5,      0.25,     0.0 },
  {0.5,      0.375,    0.25 },
  {0.3,      0.15,     0.0 },
  {0.3,      0.225,    0.15 },
  {0.15,     0.075,    0.0 },
  {0.15,     0.1125,   0.075 },
  {1.0,      0.75,     0.0 },
  {1.0,      0.875,    0.5 },
  {0.65,     0.4875,   0.0 },
  {0.65,     0.5688,   0.325 },
  {0.5,      0.375,    0.0 },
  {0.5,      0.4375,   0.25 },
  {0.3,      0.225,    0.0 },
  {0.3,      0.2625,   0.15 },
  {0.15,     0.1125,   0.0 },
  {0.15,     0.1313,   0.075 },
  {1.0,      1.0,      0.0 },
  {1.0,      1.0,      0.5 },
  {0.65,     0.65,     0.0 },
  {0.65,     0.65,     0.325 },
  {0.5,      0.5,      0.0 },
  {0.5,      0.5,      0.25 },
  {0.3,      0.3,      0.0 },
  {0.3,      0.3,      0.15 },
  {0.15,     0.15,     0.0 },
  {0.15,     0.15,     0.075 },
  {0.75,     1.0,      0.0 },
  {0.875,    1.0,      0.5 },
  {0.4875,   0.65,     0.0 },
  {0.5688,   0.65,     0.325 },
  {0.375,    0.5,      0.0 },
  {0.4375,   0.5,      0.25 },
  {0.225,    0.3,      0.0 },
  {0.2625,   0.3,      0.15 },
  {0.1125,   0.15,     0.0 },
  {0.1313,   0.15,     0.075 },
  {0.5,      1.0,      0.0 },
  {0.75,     1.0,      0.5 },
  {0.325,    0.65,     0.0 },
  {0.4875,   0.65,     0.325 },
  {0.25,     0.5,      0.0 },
  {0.375,    0.5,      0.25 },
  {0.15,     0.3,      0.0 },
  {0.225,    0.3,      0.15 },
  {0.075,    0.15,     0.0 },
  {0.1125,   0.15,     0.075 },
  {0.25,     1.0,      0.0 },
  {0.625,    1.0,      0.5 },
  {0.1625,   0.65,     0.0 },
  {0.4063,   0.65,     0.325 },
  {0.125,    0.5,      0.0 },
  {0.3125,   0.5,      0.25 },
  {0.075,    0.3,      0.0 },
  {0.1875,   0.3,      0.15 },
  {0.0375,   0.15,     0.0 },
  {0.0938,   0.15,     0.075 },
  {0.0,      1.0,      0.0 },
  {0.5,      1.0,      0.5 },
  {0.0,      0.65,     0.0 },
  {0.325,    0.65,     0.325 },
  {0.0,      0.5,      0.0 },
  {0.25,     0.5,      0.25 },
  {0.0,      0.3,      0.0 },
  {0.15,     0.3,      0.15 },
  {0.0,      0.15,     0.0 },
  {0.075,    0.15,     0.075 },
  {0.0,      1.0,      0.25 },
  {0.5,      1.0,      0.625 },
  {0.0,      0.65,     0.1625 },
  {0.325,    0.65,     0.4063 },
  {0.0,      0.5,      0.125 },
  {0.25,     0.5,      0.3125 },
  {0.0,      0.3,      0.075 },
  {0.15,     0.3,      0.1875 },
  {0.0,      0.15,     0.0375 },
  {0.075,    0.15,     0.0938 },
  {0.0,      1.0,      0.5 },
  {0.5,      1.0,      0.75 },
  {0.0,      0.65,     0.325 },
  {0.325,    0.65,     0.4875 },
  {0.0,      0.5,      0.25 },
  {0.25,     0.5,      0.375 },
  {0.0,      0.3,      0.15 },
  {0.15,     0.3,      0.225 },
  {0.0,      0.15,     0.075 },
  {0.075,    0.15,     0.1125 },
  {0.0,      1.0,      0.75 },
  {0.5,      1.0,      0.875 },
  {0.0,      0.65,     0.4875 },
  {0.325,    0.65,     0.5688 },
  {0.0,      0.5,      0.375 },
  {0.25,     0.5,      0.4375 },
  {0.0,      0.3,      0.225 },
  {0.15,     0.3,      0.2625 },
  {0.0,      0.15,     0.1125 },
  {0.075,    0.15,     0.1313 },
  {0.0,      1.0,      1.0 },
  {0.5,      1.0,      1.0 },
  {0.0,      0.65,     0.65 },
  {0.325,    0.65,     0.65 },
  {0.0,      0.5,      0.5 },
  {0.25,     0.5,      0.5 },
  {0.0,      0.3,      0.3 },
  {0.15,     0.3,      0.3 },
  {0.0,      0.15,     0.15 },
  {0.075,    0.15,     0.15 },
  {0.0,      0.75,     1.0 },
  {0.5,      0.875,    1.0 },
  {0.0,      0.4875,   0.65 },
  {0.325,    0.5688,   0.65 },
  {0.0,      0.375,    0.5 },
  {0.25,     0.4375,   0.5 },
  {0.0,      0.225,    0.3 },
  {0.15,     0.2625,   0.3 },
  {0.0,      0.1125,   0.15 },
  {0.075,    0.1313,   0.15 },
  {0.0,      0.5,      1.0 },
  {0.5,      0.75,     1.0 },
  {0.0,      0.325,    0.65 },
  {0.325,    0.4875,   0.65 },
  {0.0,      0.25,     0.5 },
  {0.25,     0.375,    0.5 },
  {0.0,      0.15,     0.3 },
  {0.15,     0.225,    0.3 },
  {0.0,      0.075,    0.15 },
  {0.075,    0.1125,   0.15 },
  {0.0,      0.25,     1.0 },
  {0.5,      0.625,    1.0 },
  {0.0,      0.1625,   0.65 },
  {0.325,    0.4063,   0.65 },
  {0.0,      0.125,    0.5 },
  {0.25,     0.3125,   0.5 },
  {0.0,      0.075,    0.3 },
  {0.15,     0.1875,   0.3 },
  {0.0,      0.0375,   0.15 },
  {0.075,    0.0938,   0.15 },
  {0.0,      0.0,      1.0 },
  {0.5,      0.5,      1.0 },
  {0.0,      0.0,      0.65 },
  {0.325,    0.325,    0.65 },
  {0.0,      0.0,      0.5 },
  {0.25,     0.25,     0.5 },
  {0.0,      0.0,      0.3 },
  {0.15,     0.15,     0.3 },
  {0.0,      0.0,      0.15 },
  {0.075,    0.075,    0.15 },
  {0.25,     0.0,      1.0 },
  {0.625,    0.5,      1.0 },
  {0.1625,   0.0,      0.65 },
  {0.4063,   0.325,    0.65 },
  {0.125,    0.0,      0.5 },
  {0.3125,   0.25,     0.5 },
  {0.075,    0.0,      0.3 },
  {0.1875,   0.15,     0.3 },
  {0.0375,   0.0,      0.15 },
  {0.0938,   0.075,    0.15 },
  {0.5,      0.0,      1.0 },
  {0.75,     0.5,      1.0 },
  {0.325,    0.0,      0.65 },
  {0.4875,   0.325,    0.65 },
  {0.25,     0.0,      0.5 },
  {0.375,    0.25,     0.5 },
  {0.15,     0.0,      0.3 },
  {0.225,    0.15,     0.3 },
  {0.075,    0.0,      0.15 },
  {0.1125,   0.075,    0.15 },
  {0.75,     0.0,      1.0 },
  {0.875,    0.5,      1.0 },
  {0.4875,   0.0,      0.65 },
  {0.5688,   0.325,    0.65 },
  {0.375,    0.0,      0.5 },
  {0.4375,   0.25,     0.5 },
  {0.225,    0.0,      0.3 },
  {0.2625,   0.15,     0.3 },
  {0.1125,   0.0,      0.15 },
  {0.1313,   0.075,    0.15 },
  {1.0,      0.0,      1.0 },
  {1.0,      0.5,      1.0 },
  {0.65,     0.0,      0.65 },
  {0.65,     0.325,    0.65 },
  {0.5,      0.0,      0.5 },
  {0.5,      0.25,     0.5 },
  {0.3,      0.0,      0.3 },
  {0.3,      0.15,     0.3 },
  {0.15,     0.0,      0.15 },
  {0.15,     0.075,    0.15 },
  {1.0,      0.0,      0.75 },
  {1.0,      0.5,      0.875 },
  {0.65,     0.0,      0.4875 },
  {0.65,     0.325,    0.5688 },
  {0.5,      0.0,      0.375 },
  {0.5,      0.25,     0.4375 },
  {0.3,      0.0,      0.225 },
  {0.3,      0.15,     0.2625 },
  {0.15,     0.0,      0.1125 },
  {0.15,     0.075,    0.1313 },
  {1.0,      0.0,      0.5 },
  {1.0,      0.5,      0.75 },
  {0.65,     0.0,      0.325 },
  {0.65,     0.325,    0.4875 },
  {0.5,      0.0,      0.25 },
  {0.5,      0.25,     0.375 },
  {0.3,      0.0,      0.15 },
  {0.3,      0.15,     0.225 },
  {0.15,     0.0,      0.075 },
  {0.15,     0.075,    0.1125 },
  {1.0,      0.0,      0.25 },
  {1.0,      0.5,      0.625 },
  {0.65,     0.0,      0.1625 },
  {0.65,     0.325,    0.4063 },
  {0.5,      0.0,      0.125 },
  {0.5,      0.25,     0.3125 },
  {0.3,      0.0,      0.075 },
  {0.3,      0.15,     0.1875 },
  {0.15,     0.0,      0.0375 },
  {0.15,     0.075,    0.0938 },
  {0.33,     0.33,     0.33 },
  {0.464,    0.464,    0.464 },
  {0.598,    0.598,    0.598 },
  {0.732,    0.732,    0.732 },
  {0.866,    0.866,    0.866 },
  {1.0,      1.0,      1.0 }
};
int nColors = sizeof(color_list)/sizeof(RGBColor);


/*
 * To find a color:
 *
 *	Assume it's white
 *	if the entity's color index is '0' (BYBLOCK) look for the color
 *		in the entities block (if it has one).
 *	if the entity's color index is '256' (BYLAYER) look for the
 *		color in the entities layer table.
 *	else get the color directly.
 */
int find_color(Entity *e, RGBColor *color)
{
  RGBColor col;
  int i = ((Common *)e->data)->color;

  /* Assume white by default */
  *color = color_list[nColors-1];

  /* A block may want to get it's color BY_LAYER so do this first */
  if (i == 0 && e->block) {
    i = ((Common *)e->block->data)->color;
  }

  if (i == 256 && ((Common *)e->data)->layer[0] != '\0') {
    i = get_int_from_table(T_LAYER, ((Common *)e->data)->layer, VAL_COLOR);
  }

  if (i < 0 || i > 256) {
    /* invalid index so just return */
    return 0;
  }

  *color = color_list[i];
  return 1;
}
