/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#define CIRCLE6PTS 6 
#define CIRCLE6TRS 4 
static Point points[CIRCLE6PTS] = {
 {  0.4999999702,      0.8660254478,      0.0000000000 },
 { -0.5000000596,      0.8660253882,      0.0000000000 },
 { -1.0000000000,     -0.0000000874,      0.0000000000 },
 { -0.4999999106,     -0.8660254478,      0.0000000000 },
 {  0.4999999106,     -0.8660254478,      0.0000000000 },
 {  1.0000000000,      0.0000000000,      0.0000000000 }
};
static Triangle triangles[] = {
 {   0,     1,     2 },
 {   0,     2,     3 },
 {   0,     3,     4 },
 {   0,     4,     5 }
};
