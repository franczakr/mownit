#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <time.h>
#include <stdlib.h>

int main()
{
		FILE * fp;
		fp = fopen ("dane.csv","w");
		fprintf(fp, "\"size\";\"time\";\"type\"\n");
        srand(time(NULL));
		int length = 1000;
		for(;length<=10000; length+=1000)
		{
			gsl_vector *A = gsl_vector_calloc(length);
			gsl_vector *B = gsl_vector_calloc(length);

			int j=0;
			for(;j<11;j++)
			{

				int i=0;
				for(; i< length; i++)
				{
						gsl_vector_set( A, i, rand());
						gsl_vector_set( B, i, rand());
				}

				double result;

				struct timespec tstart={0,0}, tend={0,0};
				clock_gettime(CLOCK_MONOTONIC, &tstart);

				gsl_blas_ddot( A, B, &result);

				clock_gettime(CLOCK_MONOTONIC, &tend);

				if(j>0)	fprintf(fp, "%d;%ld;1\n", length,
				(long)((tend.tv_sec*1e9 + tend.tv_nsec) -
				(tstart.tv_sec*1e9 + tstart.tv_nsec)));

			}
			
			
		}
		length = 1000;
		for(;length<=10000; length+=1000)
		{
			int k,l;
			gsl_matrix *A = gsl_matrix_alloc (length, length);
			gsl_vector *B = gsl_vector_calloc(length);

			int j=0;
			for(;j<11;j++)
			{


				for(k = 0; k < length; k++)
				{
						for (l = 0; l < length; l++)
						{
								gsl_matrix_set (A, k, l, rand());
						}
						gsl_vector_set(B, k, rand());
				}

				gsl_vector *result = gsl_vector_calloc(length);

				struct timespec tstart={0,0}, tend={0,0};
				clock_gettime(CLOCK_MONOTONIC, &tstart);

				gsl_blas_dgemv( CblasNoTrans, 1.0, A, B, 0.0, result);

				clock_gettime(CLOCK_MONOTONIC, &tend);

				if(j>0) fprintf(fp, "%d;%ld;2\n", length,
				(long)((tend.tv_sec*1e9 + tend.tv_nsec) -
				(tstart.tv_sec*1e9 + tstart.tv_nsec)));

			}
			
			
		}
		fclose (fp);
        return 0;

}

