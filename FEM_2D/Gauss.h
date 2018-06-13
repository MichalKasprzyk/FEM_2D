#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include "GlobalData.h"

class Gauss
{
public:


	double ** randomizeArray(int dimension);
	static std::vector<double> gaussMagdy(std::vector<std::vector < double > > A, std::vector<double> P);
	void solve(double **matrix, int dimension);
	static void solveVector(std::vector< std::vector < double > > &arr);
	static std::vector<double> gauss(const std::vector< std::vector<double> > &A1, std::vector<double> B);
	static void print(std::vector < std::vector < double > > A);

	void showMatrix(double **matrix, int dimension);
	Gauss();
	~Gauss();
};

