#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matrix.h"

Matrix createMatrix(int row, int col) {
  int* data = (int*)(calloc(row * col, sizeof(int)));
  if(data == NULL) {
    printf("Memory allocation failed!\n");
    exit(EXIT_FAILURE);
  }
  Matrix matrix = {data, row, col};
  return matrix;
}

void splitString(char* str, const char* delim, char** tokens, int tokensSize) {
  char* token;
  int count = 0;

  token = strtok(str, delim);
  while(token != NULL && count < tokensSize) {
    tokens[count] = token;
    count++;
    token = strtok(NULL, delim);
  }
}

Matrix createRandomMatrix(int row, int col, int seed) {
	srand(seed);

	Matrix mat = createMatrix(row, col);

	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			setEntry(mat, i, j, rand());
		}
	}

	return mat;
}

void freeMatrix(Matrix mat) {	
	free(mat.data);
}

int getEntry(Matrix mat, int i, int j) {
	if(i > mat.row || j > mat.col){
		printf("Cannot access (%d, %d) element of the matrix", i, j);
		exit(EXIT_FAILURE);
	}
	return mat.data[i * mat.row + j];	
}

void setEntry(Matrix mat, int i, int j, int x) {
	if(i > mat.row || j > mat.col){
		printf("Cannot access (%d, %d) element of the matrix", i, j);
		exit(EXIT_FAILURE);
	}
	mat.data[i * mat.row + j] = x;	
}

void printMatrix(Matrix mat) {
	for(int i = 0; i < mat.row; i++) {
		for(int j = 0; j < mat.col; j++) {
			printf("%3d ", getEntry(mat, i, j));	
		}
		printf("\n");
	}	
}

