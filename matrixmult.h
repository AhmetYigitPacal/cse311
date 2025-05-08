#ifndef MATRIX_MULT_H_
#define MATRIX_MULT_H_

#include "matrix.h"

Matrix add(Matrix matA, Matrix matB);
Matrix substract(Matrix matA, Matrix matB);

Matrix bfMult(Matrix matA, Matrix matB);

void divide(Matrix mat, Matrix* mat11, Matrix* mat12, Matrix* mat21, Matrix* mat22);
Matrix merge(Matrix mat11, Matrix mat12, Matrix mat21, Matrix mat22);

Matrix dncMult(Matrix matA, Matrix matB);

Matrix strassensMult(Matrix matA, Matrix matB);

#endif //MATRIX_MULT_H_
