#pragma once
#include "Element_Universal.h"
#include "GlobalData.h"

class Jacobian
{
	Element_Universal *element_universal;
	double *dX_dEta;
	double *dX_dKsi;
	
	double *dY_dEta;
	double *dY_dKsi;

	double *det_J;
	double ***jacobian;
	double ***rev_jacobian;

	double **dN_dX;
	double **dN_dY;

	const int matrix_size = 4;
	const int jacobian_size = 2;
	const int numberOfLocalJacobians = 4;



public:

	double** getdN_dX();
	double** getdN_dY();
	double* get_det_J();

	double* get_dX_dEta();
	double* get_dX_dKsi();
	double* get_dY_dEta();
	double* get_dY_dKsi();

	Element_Universal* getElement_universal();

	int get_matrix_size();
	int get_jacobian_size();



	void initDN_Matrixes();
	void calculate_Jacobians();
	void initDx_DEta(double x1, double x2, double x3, double x4);
	void initDx_DKsi(double x1, double x2, double x3, double x4);
	void initDy_DEta(double y1, double y2, double y3, double y4);
	void initDy_DKsi(double y1, double y2, double y3, double y4);


	void print_jacobian();
	Jacobian();
	~Jacobian();
};

