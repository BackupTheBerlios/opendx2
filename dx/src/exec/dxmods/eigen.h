/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/
/*
 * eigen.h - header file for eigenvalue routines in eigen.c
 */

#include <dxconfig.h>


#define SHAPE 3

typedef struct stress_tensor {
	float tau[3][3];
} Stress_Tensor;
typedef struct stress_tensor2 {
	float tau[2][2];
} Stress_Tensor2;

Error
_dxfEigen(float **a, int n, float d[], float **v);

float *_dxfEigenVector(int start_vector, int end_vector);

float **_dxfEigenMatrix(int start_matrix_row, int end_matrix_row, 
	int start_matrix_col, int end_matrix_col);

void _dxfEigenFreeVector(float *v, int start_vector);

void _dxfEigenFreeMatrix(float **m, int start_matrix_row, int end_matrix_row, 
	int start_matrix_col);

float **_dxfEigenConvertMatrix(float *a, int start_matrix_row, int end_matrix_row, 
	int start_matrix_col, int end_matrix_col);

void _dxfEigenFreeConvertMatrix(float**b, int start_matrix_row);
