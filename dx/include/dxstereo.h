/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#ifndef _DXSTEREO_H_
#define _DXSTEREO_H_

typedef struct
{
    int xOffset, yOffset;
    int xSize, ySize;
    float aspect;
} WindowInfo;
    
typedef int   (*InitializeStereoSystemMode)(Display *, Window);
typedef int   (*CreateStereoWindows)(Display *, Window,
				Window *, WindowInfo *,
				Window *, WindowInfo *);
typedef int   (*ExitStereo)(Display *, Window, Window, Window);

typedef struct 
{
    InitializeStereoSystemMode 	initializeStereoSystemMode;
    CreateStereoWindows 	createStereoWindows;
    ExitStereo          	exitStereo;
} StereoSystemMode;

typedef void *(*InitializeStereoCameraMode)(void *, dxObject);
typedef int   (*ExitStereoCameraMode)(void *);
typedef int   (*CreateStereoCameras)(void *,
				int, float, float,
				float *, float *, float *, float, float,
				float *, float *, float *, float **,
				float *, float *, float *, float **);
typedef int   (*MapStereoXY)(void *, Window, Window, WindowInfo, 
				int, int, int*, int*);

typedef struct 
{
    InitializeStereoCameraMode  initializeStereoCameraMode;
    ExitStereoCameraMode  	exitStereoCameraMode;
    CreateStereoCameras     	createStereoCameras;
    MapStereoXY			mapStereoXY;
} StereoCameraMode;

#endif
