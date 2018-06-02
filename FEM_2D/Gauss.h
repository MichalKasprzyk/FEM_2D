#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include "GlobalData.h"

class Gauss
{
public:


	double ** randomizeArray(int dimension);
	void solve(double **matrix, int dimension);
	static void solveVector(std::vector< std::vector < double > > &arr);
	void showMatrix(double **matrix, int dimension);
	Gauss();
	~Gauss();
};

