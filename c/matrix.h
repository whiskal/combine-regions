#ifndef _MATRIX_H_
#define _MATRIX_H_

const int K_max = 5;

int M[3][5] = {	{4, 1, 3, 1, 3},
				{2, 1, 5, 0, 0},
				{3, 1, 3, 2, 0}};
				
int Gr_blizn[3][4] = {	{1, 3, 8, 10},
						{5, 7, 0, 0},
						{2, 4, 11, 0}};

int Gr_daln[3][4] = {	{1, 5, 8, 12},
						{5, 11, 0, 0},
						{2, 6, 12, 0}};

int Delta[3][3] = {	{1, 2, 1},
					{1, 0, 0},
					{1, 4, 0}};
					
void combAlg(int **_matrix, int **_near, int **_far, int _k_max)
{
	int n,k,c,i;
	for(n=0; n<3; n++)
	{
		printf("Current n = %d\n", n);
		c=0; //counter of combination
		for(k=1; k < _k_max-1; k++)
		{
			while(  (_matrix[n][k+1] > 0) &
			(_matrix[n][k] >= 3 || _matrix[n][k+1] >= 3) &	//N >= 3  
				(_near[n][k]-1 - _far[n][k-1] <= 2))	//MIN_D <= 2 
			{
				_far[n][k-1] = _far[n][k];
				_matrix[n][(k+1)-1] =_far[n][k-1] - _near[n][k-1] +1; // recalc region lenth
					
				for(i=k; i<_k_max-1; i++) // shift far border and region lenth
				{
					_far[n][i] = _far[n][i+1];
					_near[n][i] = _near[n][i+1];
					_matrix[n][i+1] = _matrix[n][i+2];
				}
				_far[n][_k_max-2] = 0;	// nill last
				_near[n][_k_max-2] = 0;
				_matrix[n][_k_max-1] = 0;
				c += 1; 
			}
		}
		_matrix[n][0] -= c; 
	}
}									
#endif
