/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/_isosurface.h,v 1.1 1999/03/24 15:18:24 gda Exp $
 */


#ifndef  _ISOSURFACE_H_
    /* Begin header file conditional */

#define  _ISOSURFACE_H_


/* requires inclusion of <dx/dx.h> */

extern float *_dxd_user_def_values;

typedef enum { ISOSURFACE, BAND }
     iso_module_types;

typedef enum { DATA_LOW, DATA_HIGH, ORIGINAL_DATA }
     band_remap_types;

typedef enum { NO_NORMALS, GRADIENT_NORMALS, NORMALS_COMPUTED }
     iso_norm_types;


typedef struct
{
    iso_module_types module;
    iso_norm_types   normal_type;
    int              normal_direction;
    Interpolator     gradient_interpolator;
    band_remap_types remap;
        /*
         * if ( number == 1 && use_mean )
         *     default to mean, else default using min/max
         */
    Object      self;
    char        *member_name;
    int         is_grown;
    int         use_mean;
    int         number;
    int         series_ordinal;
    float       series_FP_val;
    float       *isovals;
    int         have_minmax;
    float       band_min_cf;
    float       band_max_cf;
    Object      *parent;
    int         task_counter;
}
iso_arg_type; 


static iso_arg_type ISO_ARG_INITIALIZER =
            { ISOSURFACE, NO_NORMALS,
              -1, NULL, ORIGINAL_DATA, NULL, NULL, 0, 0, 0,
              -1, -1.0, NULL, 0, DXD_MAX_FLOAT, -DXD_MAX_FLOAT, NULL, 0 };


/*-------------------------------------------------------------------------*
 *  Body of these routines are located in file:
 *     _isosurface.c
 *
 * XXX - externs not declared here: 
 *          _dxf_IsFlippedTet_3x3_method, _dxf_IsFlippedTet_4x4_method
 */

/* 
 * Special traverser for isosurface.
 */
extern Object _dxf_IsosurfaceObject ( iso_arg_type iso_arg );


    /* End header file conditional */
#endif
