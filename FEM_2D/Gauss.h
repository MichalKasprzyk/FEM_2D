#pragma once
#include <iostream>
#include <time.h>

class Gauss
{
public:


	double ** randomizeArray(int dimension);
	void solve(double **matrix, int dimension);
	void showMatrix(double **matrix, int dimension);
	Gauss();
	~Gauss();
};

