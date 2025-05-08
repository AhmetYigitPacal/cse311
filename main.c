#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "matrixmult.h"

#define RUN_COUNT 10

int main(int argc, char** argv) {
	if(argc < 3) {
		printf("Not enough arguments!\n");
		return 1;
	}

	struct timespec start, end;
	double t;

  int algorithm = atoi(argv[1]);
	int row = atoi(argv[2]), col = atoi(argv[2]);

	printf("Creating random matrices...\n");
	Matrix mat1 = createRandomMatrix(row, col, 103792742);
	Matrix mat2 = createRandomMatrix(row, col, 932047248);

	for(int i = 0; i < RUN_COUNT; i++) {
		timespec_get(&start, TIME_UTC);

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

	  timespec_get(&end, TIME_UTC);
  	t = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) * 1e-9; 
  	printf("Time it took: %f s\n", t);		
  }

  freeMatrix(mat1);
  freeMatrix(mat2);

  return 0;
}


