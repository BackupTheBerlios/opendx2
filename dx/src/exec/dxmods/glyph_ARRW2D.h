/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#define ARRW2DPTS 4 
#define ARRW2DLNS 3 

#include <dxconfig.h>


static Point points[ARRW2DPTS] = {
 {  0.0000000000,      0.0000000000,   0.0 }, 
 {  0.0000000000,      1.0000000000,   0.0 },  
 { -0.2500000000,      0.8000000000,   0.0 }, 
 {  0.2500000000,      0.8000000000,   0.0 }
};
   
static Line lines[] = {
  {  0,       1 },       
  {  2,       1 },      
  {  3,       1 }     
};
