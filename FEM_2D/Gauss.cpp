#include "stdafx.h"
#include "Gauss.h"


std::vector<double> Gauss::gaussMagdy(std::vector<std::vector<double> > Hprim, std::vector< double > P)
{
	int nn = Hprim.size();
	for (int i = 0; i < nn - 1; i++)
	{
		//std::cout << " ---- MAGDUS <3 GAUSS ITERATION LOOP 1 ---- " << i << std::endl;
		for (int j = i + 1; j < nn; j++)
		{
			double l = Hprim[j][i] / Hprim[i][i];
			P[j] -= P[i] * l;
			for (int k = 0; k < nn; k++)
			{
				Hprim[j][k] -= Hprim[i][k] * l;
			}
		}
	}

	//double* t = new double[nn];
	std::vector<double> t;
	t.resize(nn);
	for (int j = nn - 1; j >= 0; j--)
	{
		//std::cout << " ---- MAGDUS <3 GAUSS ITERATION LOOP 2 ---- " << j << std::endl;
		t[j] = P[j]; //tu byl minus.. po co?
		for (int k = j + 1; k < nn; k++)
		{
			t[j] -= Hprim[j][k] * t[k];
		}
		t[j] /= Hprim[j][j];
	}
	return t;
}

void Gauss::solveVector(std::vector< std::vector < double > > &arr)
{

	double m;

	double THRESHOLD = 0.000000000000001;
	double DEBUG;
	int n, i, j, k;


	for (i = 0; i <  arr.size() - 1; i++)
	{
		std::cout << "    --- GAUSS ITERATION --- " << i << std::endl;
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

void Gauss::print(std::vector< std::vector<double> > A) {
	int n = A.size();
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n + 1; j++) {
			std::cout << A[i][j] << "\t";
			if (j == n - 1) {
				std::cout << "| ";
			}
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

std::vector<double> Gauss::gauss( const std::vector< std::vector<double> > &A1, std::vector<double> B) {
	
	
	//GlobalData::printVector(A, "Test from GAUSS A");
	std::vector< std::vector < double > > A = A1;
	
	for (int i = 0; i < A.size(); ++i)
	{
		A[i].push_back(B[i]);
	}
	
	//GlobalData::printVector(A, "Test from GAUSS A AFTER ADDING B");
	
	
	int n = A.size();





	for (int i = 0; i<n; i++) {
		// Search for maximum in this column
		//std::cout << "    --- GAUSS ITERATION --- " << i << std::endl;
		double maxEl = abs(A[i][i]);
		int maxRow = i;
		for (int k = i + 1; k<n; k++) {
			if (abs(A[k][i]) > maxEl) {
				maxEl = abs(A[k][i]);
				maxRow = k;
			}
		}

		// Swap maximum row with current row (column by column)
		for (int k = i; k<n + 1; k++) {
			double tmp = A[maxRow][k];
			A[maxRow][k] = A[i][k];
			A[i][k] = tmp;
		}

		// Make all rows below this one 0 in current column
		for (int k = i + 1; k<n; k++) {
			double c = -A[k][i] / A[i][i];
			for (int j = i; j<n + 1; j++) {
				if (i == j) {
					A[k][j] = 0;
				}
				else {
					A[k][j] += c * A[i][j];
				}
			}
		}
	}

	// Solve equation Ax=b for an upper triangular matrix A
	std::vector<double> x(n);
	for (int i = n - 1; i >= 0; i--) {
		x[i] = A[i][n] / A[i][i];
		for (int k = i - 1; k >= 0; k--) {
			A[k][n] -= A[k][i] * x[i];
		}
	}
	return x;
}
Gauss::Gauss()
{
}


Gauss::~Gauss()
{
}
