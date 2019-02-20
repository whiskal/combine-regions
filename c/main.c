#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "matrix.h"

//void combAlg(int **_matrix, int **_near, int **_far, int K_max);
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
		Matrix[n] = (int*)malloc(5 * sizeof(int));
		bNear[n] = (int*)malloc(4 * sizeof(int));
		bFar[n] = (int*)malloc(4 * sizeof(int));
		Matrix[n][0] = M[n][0];
		for(k=0; k<4; k++)
		{
			Matrix[n][k+1] = M[n][k+1];
			bNear[n][k] = Gr_blizn[n][k];
			bFar[n][k] = Gr_daln[n][k];
		}
	}
	
	combAlg(Matrix, bNear, bFar, 5);
	
	printf("Matrix\n"); printA(Matrix, 5, 3);
	printf("Near\n"); printA(bNear, 4, 3);
	printf("Far\n"); printA(bFar, 4, 3);

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
/*
void combAlg(int **_matrix, int **_near, int **_far, int K_max)
{
	int n,k,c,i;
	for(n=0; n<3; n++)
	{
		printf("Current n = %d\n", n);
		c=0;
		for(k=1; k < K_max-1; k++)
		{
			while(  (_matrix[n][k+1] > 0) &
			(_matrix[n][k] >= 3 || _matrix[n][k+1] >= 3) &	//N >= 3  
				(_near[n][k]-1 - _far[n][k-1] <= 2))	//MIN_D <= 2 
			{
				_far[n][k-1] = _far[n][k];
				_matrix[n][(k+1)-1] =_far[n][k-1] - _near[n][k-1] +1; // recalc region lenth
					
				for(i=k; i<K_max-1; i++) // shift far border and region lenth
				{
					_far[n][i] = _far[n][i+1];
					_near[n][i] = _near[n][i+1];
					_matrix[n][i+1] = _matrix[n][i+2];
				}
				_far[n][K_max-2] = 0;	// nill last
				_near[n][K_max-2] = 0;
				_matrix[n][K_max-1] = 0;
				c += 1;
			}
		}
		_matrix[n][0] -= c; 
	}
}
*/

