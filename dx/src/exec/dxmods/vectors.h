/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/vectors.h,v 1.1 1999/03/24 15:18:32 gda Exp $:
 */

#define vector_length		_dxfvector_length_3D
#define vector_length_squared	_dxfvector_length_squared_3D
#define vector_normalize	_dxfvector_normalize_3D
#define vector_add		_dxfvector_add_3D
#define vector_subtract		_dxfvector_subtract_3D
#define vector_scale		_dxfvector_scale_3D
#define vector_dot		_dxfvector_dot_3D
#define vector_cross		_dxfvector_cross_3D
#define vector_angle		_dxfvector_angle_3D
#define vector_zero		_dxfvector_zero_3D

float        _dxfvector_length_3D(Vector *);
float        _dxfvector_length_squared_3D(Vector *);
Error        _dxfvector_normalize_3D(Vector *, Vector *);
Error        _dxfvector_add_3D(Vector *, Vector *, Vector *);
Error        _dxfvector_subtract_3D(Vector *, Vector *, Vector *);
Error        _dxfvector_scale_3D(Vector *, float, Vector *);
float        _dxfvector_dot_3D(Vector *, Vector *);
Error        _dxfvector_cross_3D(Vector *, Vector *, Vector *);
float        _dxfvector_angle_3D(Vector *, Vector *);
int          _dxfvector_zero_3D(Vector *);

float        _dxfvector_length_2D(Vector *);
float        _dxfvector_length_squared_2D(Vector *);
Error        _dxfvector_normalize_2D(Vector *, Vector *);
Error        _dxfvector_add_2D(Vector *, Vector *, Vector *);
Error        _dxfvector_subtract_2D(Vector *, Vector *, Vector *);
Error        _dxfvector_scale_2D(Vector *, float, Vector *);
float        _dxfvector_dot_2D(Vector *, Vector *);
Error        _dxfvector_cross_2D(Vector *, Vector *, Vector *);
float        _dxfvector_angle_2D(Vector *, Vector *);
int          _dxfvector_zero_2D(Vector *);
