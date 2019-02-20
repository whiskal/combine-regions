#include <malloc.h>
#include <stdlib.h>
#include "matrix.h"

void printA(int **a, int k, int n);

int main(int argc, char *argv[]) 
{
	int n, k, c;
    int **Matrix;
    int **bNear;
    int **bFar;
    
    Matrix = (int**)malloc(3 * sizeof(int*));
    bNear = (int**)malloc(3 * sizeof(int*));
    bFar = (int**)malloc(3 * sizeof(int*));
  
	for(n=0; n<3; n++)
	{
		Matrix[n] = (int*)malloc(K_max * sizeof(int));
		bNear[n] = (int*)malloc(K_max-1 * sizeof(int));
		bFar[n] = (int*)malloc(K_max-1 * sizeof(int));
		Matrix[n][0] = M[n][0];
		for(k=0; k<K_max-1; k++)
		{
			Matrix[n][k+1] = M[n][k+1];
			bNear[n][k] = Gr_blizn[n][k];
			bFar[n][k] = Gr_daln[n][k];
		}
	}
	
	combAlg(Matrix, bNear, bFar, K_max);
	
	printf("Matrix\n"); printA(Matrix, K_max, 3);
	printf("Near\n"); printA(bNear, K_max-1, 3);
	printf("Far\n"); printA(bFar, K_max-1, 3);

	for(n=0; n<3; n++)
	{
		free(Matrix[n]);
		free(bNear[n]);
		free(bFar[n]);
	}
	free(Matrix);
	free(bNear);
	free(bFar);

	
	return 0;
}

void printA(int **a, int k, int n)
{
	int i, j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<k; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}

