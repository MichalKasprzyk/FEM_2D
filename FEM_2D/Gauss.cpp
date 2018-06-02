#include "stdafx.h"
#include "Gauss.h"



void Gauss::solveVector(std::vector< std::vector < double > > &arr)
{

	double m;

	double THRESHOLD = 0.000000000000001;
	double DEBUG;
	int n, i, j, k;


	for (i = 0; i <  arr.size() - 1; i++)
	{
		k = i + 1;
		while (k < arr.size())
		{
			m = arr[k][i] / arr[i][i];
			j = 0;
			while (j < arr.size())
			{

				//	DEBUG = tab[k][j];
				//	printf("i = %d  , k = %d , j = %d \n \n", i, k, j);
				arr[k][j] = arr[k][j] - m * arr[i][j];

				// DODANY THRESHHOLD UWAGA
				if (std::abs(arr[k][j]) < THRESHOLD)
				{
					arr[k][j] = 0;
				}
				//	printf("Subtracting %4.2f - %4.2f * %4.2f = %4.2f  \n \n ", DEBUG, m, tab[i][j], tab[k][j]);

				j++;
			}
			//showMatrix(tab, dimension);
			k++;
		}

	}



	double determinant = arr[0][0];
	for (int i = 1; i < arr.size(); i++)
	{
		if(arr[i][i] == 0)
		{
			determinant = 0;
			break;
		}
		determinant = determinant * arr[i][i];
	}
	//printf(" Its determinant = %4.2f \n", determinant);

}
double ** Gauss::randomizeArray(int dimension)
{
	srand(time(NULL));

	double ** matrix = new double *[dimension];
	for (int i = 0; i<dimension; i++)
		matrix[i] = new double[dimension];

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			matrix[i][j] = rand() % 10;
			if (matrix[i][j] == 0)
				j--;
		}
	}
	return matrix;
}

void Gauss::solve(double ** matrix, int dimension)
{
	std::cout << " Matrix before: " << std::endl;
	showMatrix(matrix, dimension);
	double m;

	double DEBUG;
	int n, i, j, k;

	for (i = 0; i < dimension - 1; i++)
	{
		k = i + 1;
		while (k < dimension)
		{
			m = matrix[k][i] / matrix[i][i];
			j = 0;
			while (j < dimension)
			{

				//	DEBUG = tab[k][j];
				//	printf("i = %d  , k = %d , j = %d \n \n", i, k, j);
				matrix[k][j] = matrix[k][j] - m*matrix[i][j];
				//	printf("Subtracting %4.2f - %4.2f * %4.2f = %4.2f  \n \n ", DEBUG, m, tab[i][j], tab[k][j]);

				j++;
			}
			std::cout << std::endl;
			//showMatrix(tab, dimension);
			k++;
		}

	}


	std::cout << std::endl;
	std::cout << " Finished Matrix: " << std::endl;
	showMatrix(matrix, dimension);


	double determinant = 1;
	for (int i = 0; i < dimension; i++)
	{
		if (matrix[i][i] == 0)
		{
			determinant = 0;
			break;
		}
		determinant = determinant * matrix[i][i];
	}
	printf(" Its determinant = %4.2f \n", determinant);



}

void Gauss::showMatrix(double ** matrix, int dimension)
{
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			printf(" %4.2f", matrix[i][j]);
			for (int k = 0; k<dimension; k++)
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}

Gauss::Gauss()
{
}


Gauss::~Gauss()
{
}
