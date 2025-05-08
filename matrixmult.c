#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix add(Matrix matA, Matrix matB) {
	if(matA.row != matB.row || matA.col != matB.col) {
		puts("Cannot add matrices!");
		exit(EXIT_FAILURE);
	}

	Matrix result = createMatrix(matA.row, matA.col);

	for(int i = 0; i < result.row; i++) {
		for(int j = 0; j < result.col; j++) {
			setEntry(result, i, j, getEntry(matA, i, j) + getEntry(matB, i, j));	
		}
	}

	return result;
}

Matrix substract(Matrix matA, Matrix matB) {
  if(matA.row != matB.row || matA.col != matB.col) {
		puts("Cannot substract matrices!");
		exit(EXIT_FAILURE);
	}

	Matrix result = createMatrix(matA.row, matA.col);

	for(int i = 0; i < result.row; i++) {
		for(int j = 0; j < result.col; j++) {
			setEntry(result, i, j, getEntry(matA, i, j) - getEntry(matB, i, j));	
		}
	}

	return result;
}

Matrix bfMult(Matrix matA, Matrix matB) {
	if(matA.data == NULL || matB.data == NULL || matA.col != matB.row) {
		puts("Cannot multiply matrices!");	
		exit(EXIT_FAILURE);
	}

	Matrix result = createMatrix(matA.row, matB.col);

	for(int i = 0; i < matA.row; i++) {
		for(int j = 0; j < matB.col; j++) {
			int sum = 0;
			for(int k = 0; k < matA.col; k++) {
				sum += getEntry(matA, i, k) * getEntry(matB, k, j);
			}
			setEntry(result, i, j, sum);
		}
	}

	return result;
}

void divide(Matrix mat, Matrix* mat11, Matrix* mat12, Matrix* mat21, Matrix* mat22) {
	int row = mat.row, col = mat.col;

	*mat11 = createMatrix(row / 2, col / 2);
	*mat12 = createMatrix(row / 2, col - col / 2);
	*mat21 = createMatrix(row - row / 2, col / 2);
	*mat22 = createMatrix(row - row / 2, col - col / 2);

	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			int x = getEntry(mat, i, j);
			if(i < row / 2){
				if(j < col / 2)
					setEntry(*mat11, i, j, x);
				else
					setEntry(*mat12, i, j - col / 2, x);
			} else{
				if(j < col / 2)
					setEntry(*mat21, i - row / 2, j, x);
				else
					setEntry(*mat22, i - row / 2, j - col / 2, x);
			}
		}
	}
}

Matrix merge(Matrix mat11, Matrix mat12, Matrix mat21, Matrix mat22) {
  if(mat11.row != mat12.row || mat21.row != mat22.row || mat11.col != mat21.col || mat12.col != mat22.col) {
    puts("Cannot merge matricees!");
    exit(EXIT_FAILURE);
  }

  int row = mat11.row + mat21.row;
  int col = mat11.col + mat12.col;

  Matrix result = createMatrix(row, col);

	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			if(i < row / 2){
				if(j < col / 2)
					setEntry(result, i, j, getEntry(mat11, i, j));
				else
					setEntry(result, i, j, getEntry(mat12, i, j - col / 2));
			} else {
				if(j < col / 2)
					setEntry(result, i, j, getEntry(mat21, i - row / 2, j));
				else
					setEntry(result, i, j, getEntry(mat22, i - row / 2, j - col / 2));
			}
		}
	}

  return result;
}

Matrix dncMult(Matrix matA, Matrix matB) {
	if(matA.row != matA.col || matB.row != matB.col || matA.col != matB.row) {
		puts("Cannot use native divide and conquer!");
		exit(EXIT_FAILURE);
	}
	
	int n = matA.row;

	if(n == 1) {
  Matrix result = createMatrix(n, n);
		setEntry(result, 0, 0, getEntry(matA, 0, 0) * getEntry(matB, 0, 0));	
    return result;
	}

	Matrix matA11, matA12, matA21, matA22,
		   matB11, matB12, matB21, matB22;

	divide(matA, &matA11, &matA12, &matA21, &matA22);
	divide(matB, &matB11, &matB12, &matB21, &matB22);
	
	Matrix matC11 = add(dncMult(matA11, matB11), dncMult(matA12, matB21));
	Matrix matC12 = add(dncMult(matA11, matB12), dncMult(matA12, matB22));
	Matrix matC21 = add(dncMult(matA21, matB11), dncMult(matA22, matB21));
	Matrix matC22 = add(dncMult(matA21, matB12), dncMult(matA22, matB22));

  Matrix result = merge(matC11, matC12, matC21, matC22);  

	freeMatrix(matA11); freeMatrix(matA12); freeMatrix(matA21); freeMatrix(matA22);
	freeMatrix(matB11); freeMatrix(matB12); freeMatrix(matB21); freeMatrix(matB22);
	freeMatrix(matC11); freeMatrix(matC12); freeMatrix(matC21); freeMatrix(matC22);

	return result;
}

Matrix strassensMult(Matrix matA, Matrix matB) {
  	if(matA.row != matA.col || matB.row != matB.col || matA.col != matB.row) {
		puts("Cannot use native divide and conquer!");
		exit(EXIT_FAILURE);
	}
	
	int n = matA.row;

	if(n == 1) {
  Matrix result = createMatrix(n, n);
		setEntry(result, 0, 0, getEntry(matA, 0, 0) * getEntry(matB, 0, 0));	
    return result;
	}

	Matrix matA11, matA12, matA21, matA22,
		   matB11, matB12, matB21, matB22;

	divide(matA, &matA11, &matA12, &matA21, &matA22);
	divide(matB, &matB11, &matB12, &matB21, &matB22);

  Matrix matM1 = strassensMult(add(matA11, matA22), add(matB11, matB22));
  Matrix matM2 = strassensMult(add(matA21, matA22), matB11);
  Matrix matM3 = strassensMult(matA11, substract(matB12, matB22));
  Matrix matM4 = strassensMult(matA22, substract(matB21, matB11));
  Matrix matM5 = strassensMult(add(matA11, matA12), matB22);
  Matrix matM6 = strassensMult(substract(matA21, matA11), add(matB11, matB12));
  Matrix matM7 = strassensMult(substract(matA12, matA22), add(matB21, matB22));

  Matrix matC11 = add(substract(add(matM1, matM4), matM5), matM7);
  Matrix matC12 = add(matM3, matM5);
  Matrix matC21 = add(matM2, matM4);
  Matrix matC22 = add(add(substract(matM1, matM2) , matM3), matM6);

  Matrix result = merge(matC11, matC12, matC21, matC22);

	freeMatrix(matA11); freeMatrix(matA12); freeMatrix(matA21); freeMatrix(matA22);
	freeMatrix(matB11); freeMatrix(matB12); freeMatrix(matB21); freeMatrix(matB22);
  freeMatrix(matC11); freeMatrix(matC12); freeMatrix(matC21); freeMatrix(matC22);
	freeMatrix(matM1); freeMatrix(matM2); freeMatrix(matM3); freeMatrix(matM4);
  freeMatrix(matM5); freeMatrix(matM6); freeMatrix(matM7);

	return result; 
}


