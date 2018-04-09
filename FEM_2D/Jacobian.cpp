#include "stdafx.h"
#include "Jacobian.h"



Jacobian::Jacobian()
{
	element_universal = new Element_Universal();
	element_universal->print_dEta();
	element_universal->print_dKsi();
	element_universal->print_N();
}

void Jacobian::calculate_Jacobians()
{
	jacobian = new double**[numberOfLocalJacobians]();

	for (int i = 0; i < jacobian_size; i++)
	{
		jacobian[i] = new double*[jacobian_size]();
		for (int j = 0; j < jacobian_size; j++)
			jacobian[i][j] = new double[jacobian_size]();

	}

	for (int i = 0; i < numberOfLocalJacobians; i++)
	{
		jacobian[0][0][i] = dX_dKsi[i];
		jacobian[0][1][i] = dY_dKsi[i];
		jacobian[1][0][i] = dX_dEta[i];
		jacobian[1][1][i] = dY_dEta[i];
	}
	/*
	jacobian[0][0] = dX_dKsi[0];
	jacobian[0][1] = dY_dKsi[0];
	jacobian[1][0] = dX_dEta[0];
	jacobian[1][1] = dY_dEta[0]; */
}
void Jacobian::print_jacobian()
{
	printf("\n");
	for (int i = 0; i < numberOfLocalJacobians; i++)
	{
		printf("Jacobian %i\n", i);
		for (int j = 0; j < jacobian_size; j++)
		{
			for (int k = 0; k < jacobian_size; k++)
			{
				// WARNING! BE CAREFUL WHICH INDEX IS FIRST, j swapped with k!
				printf("%.8f ", jacobian[j][k][i]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
void Jacobian::initDy_DEta(double y1, double y2, double y3, double y4)
{
	dY_dEta = new double[matrix_size];
	for (int i = 0; i < matrix_size; i++)
	{
		dY_dEta[i] = 0;
	}
	double y[4] = { y1,y2,y3,y4 };
	for (int i = 0; i < matrix_size; i++)
	{

		dY_dEta[i] += element_universal->getDn_dEta()[0][i] * y[0];
		dY_dEta[i] += element_universal->getDn_dEta()[1][i] * y[1];
		dY_dEta[i] += element_universal->getDn_dEta()[2][i] * y[2];
		dY_dEta[i] += element_universal->getDn_dEta()[3][i] * y[3];

	}
}

void Jacobian::initDy_DKsi(double y1, double y2, double y3, double y4)
{
	dY_dKsi = new double[matrix_size];
	for (int i = 0; i < matrix_size; i++)
	{
		dY_dKsi[i] = 0;
	}
	double y[4] = { y1,y2,y3,y4 };
	for (int i = 0; i < matrix_size; i++)
	{

		dY_dKsi[i] += element_universal->getDn_dKsi()[0][i] * y[0];
		dY_dKsi[i] += element_universal->getDn_dKsi()[1][i] * y[1];
		dY_dKsi[i] += element_universal->getDn_dKsi()[2][i] * y[2];
		dY_dKsi[i] += element_universal->getDn_dKsi()[3][i] * y[3];
	}
}

void Jacobian::initDx_DEta(double x1, double x2, double x3, double x4) {
	dX_dEta = new double[matrix_size];
	for (int i = 0; i < matrix_size; i++)
	{
		dX_dEta[i] = 0;
	}
	double x[4] = { x1,x2,x3,x4 };
	for (int i = 0; i < matrix_size; i++)
	{

		dX_dEta[i] += element_universal->getDn_dEta()[0][i] * x[0];
		dX_dEta[i] += element_universal->getDn_dEta()[1][i] * x[1];
		dX_dEta[i] += element_universal->getDn_dEta()[2][i] * x[2];
		dX_dEta[i] += element_universal->getDn_dEta()[3][i] * x[3];

	}
}

void Jacobian::initDx_DKsi(double x1, double x2, double x3,double x4)
{
	dX_dKsi = new double[matrix_size];
	double x[4] = { x1,x2,x3,x4 };
	for (int i = 0; i < matrix_size; i++)
	{
		dX_dKsi[i] = 0;
	}
	for (int i = 0; i < matrix_size; i++)
	{
		dX_dKsi[i] += element_universal->getDn_dKsi()[0][i] * x[0];
		dX_dKsi[i] += element_universal->getDn_dKsi()[1][i] * x[1];
		dX_dKsi[i] += element_universal->getDn_dKsi()[2][i] * x[2];
		dX_dKsi[i] += element_universal->getDn_dKsi()[3][i] * x[3];

	}
}


void Jacobian::printDx_DEta()
{	
	printf("\n");
	printf("Matrix dX / dEta \n");
	for (int i = 0; i < matrix_size; i++)
	{
		printf("  %.8f  ", dX_dEta[i]);
	}
	printf("\n");
}

void Jacobian::printDx_DKsi()
{
	printf("\n");
	printf("Matrix dX / dKsi \n");
	for (int i = 0; i < matrix_size; i++)
	{
		printf("  %.8f  ", dX_dKsi[i]);
	}
	printf("\n");
}

void Jacobian::printDy_DKsi()
{
	printf("\n");
	printf("Matrix dY / dKsi \n");
	for (int i = 0; i < matrix_size; i++)
	{
		printf("  %.8f  ", dY_dKsi[i]);
	}
	printf("\n");
}

void Jacobian::printDy_DEta()
{
	printf("\n");
	printf("Matrix dY / dEta \n");
	for (int i = 0; i < matrix_size; i++)
	{
		printf("  %.8f  ", dY_dEta[i]);
	}
	printf("\n");
}
Jacobian::~Jacobian()
{
}
