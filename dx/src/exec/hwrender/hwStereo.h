#ifndef _STEREO_H_
#define _STEREO_H_

#define DX_STEREO_LEFT  1
#define DX_STEREO_RIGHT 2

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

Error _dxfInitializeStereoSystemMode(void *, dxObject);
Error _dxfExitStereoSystemMode(void *);

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


Error _dxfInitializeStereoCameraMode(void *, dxObject);
Error _dxfExitStereoCameraMode(void *);
Error _dxfCreateStereoCameras(void *,
				 int, float, float,
				 float *, float *, float *, float, float,
				 float *, float *, float *, float **,
				 float *, float *, float *, float **);
Error _dxfMapStereoXY(void *, Window, Window, WindowInfo, int, int, int*, int*);

#endif
