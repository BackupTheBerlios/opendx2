/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#define BOXPTS 24 
#define BOXTRS 12 
static Point points[BOXPTS] = {
 { -1.0000000000F,     -1.0000000000F,     -1.0000000000F },
 { -1.0000000000F,     -1.0000000000F,      1.0000000000F },
 { -1.0000000000F,      1.0000000000F,     -1.0000000000F },
 { -1.0000000000F,      1.0000000000F,      1.0000000000F },
 {  1.0000000000F,     -1.0000000000F,     -1.0000000000F },
 {  1.0000000000F,     -1.0000000000F,      1.0000000000F },
 {  1.0000000000F,      1.0000000000F,     -1.0000000000F },
 {  1.0000000000F,      1.0000000000F,      1.0000000000F },
 { -1.0000000000F,     -1.0000000000F,     -1.0000000000F },
 { -1.0000000000F,      1.0000000000F,     -1.0000000000F },
 {  1.0000000000F,     -1.0000000000F,     -1.0000000000F },
 {  1.0000000000F,      1.0000000000F,     -1.0000000000F },
 { -1.0000000000F,     -1.0000000000F,      1.0000000000F },
 { -1.0000000000F,      1.0000000000F,      1.0000000000F },
 {  1.0000000000F,     -1.0000000000F,      1.0000000000F },
 {  1.0000000000F,      1.0000000000F,      1.0000000000F },
 { -1.0000000000F,     -1.0000000000F,     -1.0000000000F },
 { -1.0000000000F,     -1.0000000000F,      1.0000000000F },
 {  1.0000000000F,     -1.0000000000F,     -1.0000000000F },
 {  1.0000000000F,     -1.0000000000F,      1.0000000000F },
 { -1.0000000000F,      1.0000000000F,     -1.0000000000F },
 { -1.0000000000F,      1.0000000000F,      1.0000000000F },
 {  1.0000000000F,      1.0000000000F,     -1.0000000000F },
 {  1.0000000000F,      1.0000000000F,      1.0000000000F }
};

#include <dxconfig.h>

 
static Point normals[BOXPTS] = {
 { -1.0000000000F,      0.0000000000F,      0.0000000000F },
 { -1.0000000000F,      0.0000000000F,      0.0000000000F },
 { -1.0000000000F,      0.0000000000F,      0.0000000000F },
 { -1.0000000000F,      0.0000000000F,      0.0000000000F },
 {  1.0000000000F,      0.0000000000F,      0.0000000000F },
 {  1.0000000000F,      0.0000000000F,      0.0000000000F },
 {  1.0000000000F,      0.0000000000F,      0.0000000000F },
 {  1.0000000000F,      0.0000000000F,      0.0000000000F },
 {  0.0000000000F,      0.0000000000F,     -1.0000000000F },
 {  0.0000000000F,      0.0000000000F,     -1.0000000000F },
 {  0.0000000000F,      0.0000000000F,     -1.0000000000F },
 {  0.0000000000F,      0.0000000000F,     -1.0000000000F },
 {  0.0000000000F,      0.0000000000F,      1.0000000000F },
 {  0.0000000000F,      0.0000000000F,      1.0000000000F },
 {  0.0000000000F,      0.0000000000F,      1.0000000000F },
 {  0.0000000000F,      0.0000000000F,      1.0000000000F },
 {  0.0000000000F,     -1.0000000000F,      0.0000000000F },
 {  0.0000000000F,     -1.0000000000F,      0.0000000000F },
 {  0.0000000000F,     -1.0000000000F,      0.0000000000F },
 {  0.0000000000F,     -1.0000000000F,      0.0000000000F },
 {  0.0000000000F,      1.0000000000F,      0.0000000000F },
 {  0.0000000000F,      1.0000000000F,      0.0000000000F },
 {  0.0000000000F,      1.0000000000F,      0.0000000000F },
 {  0.0000000000F,      1.0000000000F,      0.0000000000F }
};

static Triangle triangles[] = {
 {   0,     3,     2 },
 {   0,     1,     3 },
 {   4,     7,     5 },
 {   4,     6,     7 },
 {   8,     9,    11 },
 {   8,    11,    10 },
 {  12,    15,    13 },
 {  12,    14,    15 },
 {  16,    18,    17 },
 {  17,    18,    19 },
 {  21,    22,    20 },
 {  21,    23,    22 }
};
