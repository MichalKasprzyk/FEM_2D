#pragma once
#include "Element_Universal.h"
class Jacobian
{
	Element_Universal *element_universal;
	double *dX_dEta;
	double *dX_dKsi;
	
	double *dY_dEta;
	double *dY_dKsi;

	double ***jacobian;


	double **dN_dX;
	double **dN_dY;

	const int matrix_size = 4;
	const int jacobian_size = 2;
	const int numberOfLocalJacobians = 4;
public:

	void calculate_Jacobians();
	void initDx_DEta(double x1, double x2, double x3, double x4);
	void initDx_DKsi(double x1, double x2, double x3, double x4);
	void initDy_DEta(double y1, double y2, double y3, double y4);
	void initDy_DKsi(double y1, double y2, double y3, double y4);
	void printDx_DKsi();
	void printDx_DEta();
	void printDy_DKsi();
	void printDy_DEta();
	void print_jacobian();
	Jacobian();
	~Jacobian();
};

