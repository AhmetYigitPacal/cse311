#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "matrixmult.h"

int main(int argc, char** argv) {
	if(argc < 3) {
		printf("Not enough arguments!\n");
		return 1;
	}

  int algorithm = atoi(argv[1]);
	int row = atoi(argv[2]), col = atoi(argv[2]);

	Matrix mat1 = createRandomMatrix(row, col, 103792742);
	Matrix mat2 = createRandomMatrix(row, col, 932047248);

  switch(algorithm) {
    case 0: 
      freeMatrix(bfMult(mat1, mat2));
      break;

    case 1:
      freeMatrix(dncMult(mat1, mat2));
      break;

    case 2:
      freeMatrix(strassensMult(mat1, mat2));
      break;

    default: 
      printf("Invalid algorithm choice");
      break;
  }

  freeMatrix(mat1);
  freeMatrix(mat2);

  return 0;
}

