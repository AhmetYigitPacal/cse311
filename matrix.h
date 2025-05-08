#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct {
	int* data;
	int row;
	int col;
} Matrix;

Matrix createMatrix(int row, int col);
Matrix createRandomMatrix(int row, int col, int seed);

void freeMatrix(Matrix mat);

int getEntry(Matrix mat, int i, int j);
void setEntry(Matrix mat, int i, int j, int x);

void printMatrix(Matrix mat);

#endif //MATRIX_H_
