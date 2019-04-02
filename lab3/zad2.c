#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>

void naive(double **A, double **B, double **C, int size) {
    int i,j,k;
    for (i=0; i < size; i++) {
        for (j=0; j < size; j++) {
            for (k=0; k < size; k++) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

void better(double **A, double **B, double **C, int size) {
        int i,j,k;
    for (i=0; i < size; i++) {
        for (k=0; k < size; k++) {
            for (j=0; j < size; j++) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

void gsl_m(double *A, double *B, double *C, int size) {

    gsl_matrix_view AM = gsl_matrix_view_array(A, size, size);
    gsl_matrix_view BM = gsl_matrix_view_array(B, size, size);
    gsl_matrix_view CM = gsl_matrix_view_array(C, size, size);

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &AM.matrix, &BM.matrix, 0.0, &CM.matrix);
}


int main()
{
	struct timespec  start, end;
	srand(time(NULL));
	FILE *file = fopen("dane.csv", "w");
	fprintf(file, "\"size\";\"naive\";\"better\";\"blas\"\n");

	int i=100;
	for (; i <= 800; i = i + 100) 
	{
		int z =0;
		for (;z<3; z++)
		{
			double **A = calloc((size_t) i, sizeof(double *));
			double **B = calloc((size_t) i, sizeof(double *));
			double **C = calloc((size_t) i, sizeof(double *));

			double *A_ptr = calloc((size_t) (i * i), sizeof(double));
			double *B_ptr = calloc((size_t) (i * i), sizeof(double));
			double *C_ptr = calloc((size_t) (i * i), sizeof(double));

			int j = 0;
			for (; j < i; j++) {
				A[j] = calloc((size_t) i, sizeof(double));
				B[j] = calloc((size_t) i, sizeof(double));
				C[j] = calloc((size_t) i, sizeof(double));
			}

			j=0;
			int k=0;
			for (; j < i; j++) {
				for (; k < i; k++) {
					A[j][k] = (double) rand() / RAND_MAX;
					B[j][k] = (double) rand() / RAND_MAX;
				}
			}

					j=0;
			for (; j < i * i; j++) {
				A_ptr[j] = (double) rand() / RAND_MAX;
				B_ptr[j] = (double) rand() / RAND_MAX;
			}

			clock_gettime(CLOCK_MONOTONIC, &start);
			naive(A, B, C, i);
			clock_gettime(CLOCK_MONOTONIC, &end);
			fprintf(file, "%d;%f;", i, ((end.tv_sec-start.tv_sec) + (end.tv_nsec - start.tv_nsec)*1e-9));

			printf("koniec naive\n");
			clock_gettime(CLOCK_MONOTONIC, &start);
			better(A, B, C, i);
			clock_gettime(CLOCK_MONOTONIC, &end);
			fprintf(file, "%f;", ((end.tv_sec-start.tv_sec) + (end.tv_nsec - start.tv_nsec)*1e-9));
			printf("koniec better\n");
			
			clock_gettime(CLOCK_MONOTONIC, &start);
			gsl_m(A_ptr, B_ptr, C_ptr, i);
			clock_gettime(CLOCK_MONOTONIC, &end);
			fprintf(file, "%f;\n", ((end.tv_sec-start.tv_sec) + (end.tv_nsec - start.tv_nsec)*1e-9));
		}
	}
    fclose(file);

    return 0;
}
