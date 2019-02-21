#include <iostream>
#include "matrix.hpp"

using namespace std;

void combAlg(int**  _matrix, int**  _near, int**  _far, const int& _k_max);
void printA(const char* title, int** m, const int& k_max, const int& n_max = 3);

int main()
{
	//init matrix
	int** rMatrix = new int*[3];
	int** bNear = new int*[3];
	int** bFar = new int*[3];
    for(int n=0; n<3; n++)
	{
		rMatrix[n] = new int[K_max];
		bNear[n] = new int[K_max-1];
		bFar[n] = new int[K_max-1];
	}
	
	//copy matrix
	for(int n=0; n<3; n++)
	{
		rMatrix[n][0] = M[n][0];
		for(int k=0; k<K_max-1; k++)
		{
			rMatrix[n][k+1] = M[n][k+1];
			bNear[n][k] = Gr_blizn[n][k];
			bFar[n][k] = Gr_daln[n][k];
		}
	}

	printA("Matrix", rMatrix, K_max);
	printA("Near", bNear, K_max-1);
	printA("Far", bFar, K_max-1);
	
	cout << endl << "using algirithm of combination regions" << endl;
	combAlg(rMatrix, bNear, bFar, K_max);
	
	printA("Matrix", rMatrix, K_max);
	printA("Near", bNear, K_max-1);
	printA("Far", bFar, K_max-1);
	
	//free memory
	for(int n=0; n<3; n++)
	{
		delete rMatrix[n];
		delete bNear[n];
		delete bFar[n];
	}
	delete [] rMatrix;
	delete [] bNear;
	delete [] bFar;
	
	return 0;
}

void combAlg(int**  _matrix, int**  _near, int**  _far, const int& _k_max)
{
	for(int n=0, c=0; n<3; n++)
	{
		for(int k=1; k < _k_max-1; k++)
		{
			while(  (_matrix[n][k+1] > 0) &	//next region not empty
			(_matrix[n][k] >= 3 || _matrix[n][k+1] >= 3) &	//N >= 3  (from task)
				(_near[n][k]-1 - _far[n][k-1] <= 2))	//MIN_D <= 2  (from task) 
			{
				_far[n][k-1] = _far[n][k];
				_matrix[n][(k+1)-1] =_far[n][k-1] - _near[n][k-1] +1; // recalc region lenth
					
				for(int i=k; i<_k_max-1; i++) // shift far border and region lenth
				{
					_far[n][i] = _far[n][i+1];
					_near[n][i] = _near[n][i+1];
					_matrix[n][i+1] = _matrix[n][i+2];
				}
				_far[n][_k_max-2] = 0;	// clear last
				_near[n][_k_max-2] = 0;
				_matrix[n][_k_max-1] = 0;
				c++; 
			}
		}
		_matrix[n][0] -= c;
		c = 0;
	}
}									

void printA(const char* title, int**  m, const int& k_max, const int& n_max)
{
	cout << title << endl;
	for(int n = 0; n < n_max; n++)
	{
		for(int k = 0; k < k_max; k++)
			cout << m[n][k] << ' ';
		cout << endl;
	}
}

