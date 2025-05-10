#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "matrix.h"
#include "matrixmult.h"

int main(int argc, char** argv) {
	if(argc < 3) {
		printf("Not enough arguments!\n");
		return 1;
	}

  int algorithm = atoi(argv[1]);
	int row = atoi(argv[2]), col = atoi(argv[2]);

  struct timeval start, end;

	Matrix mat1 = createRandomMatrix(row, col, 103792742);
	Matrix mat2 = createRandomMatrix(row, col, 932047248);

  switch(algorithm) {
  case 0: 
    gettimeofday(&start, NULL);
    freeMatrix(bfMult(mat1, mat2));
    break;

  case 1:
    gettimeofday(&start, NULL);
    freeMatrix(dncMult(mat1, mat2));
    break;

  case 2:
    gettimeofday(&start, NULL);
    freeMatrix(strassensMult(mat1, mat2));
    break;

  default: 
    printf("Invalid algorithm choice");
    return 1;
  }

  gettimeofday(&end, NULL);
  double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
  printf("Time it took: %f seconds\n", elapsed);

  FILE *csv = fopen("times.csv", "a");
  const char* algoString = (algorithm == 0) ? "brute-force"
                         : (algorithm == 1) ? "divide-conquer"
                         : "strassens";

  fprintf(csv, "%s,%d,%f\n", algoString, row, elapsed);

  freeMatrix(mat1);
  freeMatrix(mat2);

  return 0;
}

