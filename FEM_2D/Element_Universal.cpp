#include "stdafx.h"
#include "Element_Universal.h"
#include <cmath>



int Element_Universal::get_matrix_size()
{
	return matrix_size;
}

double** Element_Universal::getDn_dEta()
{
	return dN_dEta;
}
double** Element_Universal::getN()
{
	return N;
}
double** Element_Universal::getDn_dKsi()
{
	return dN_dKsi;
}
void Element_Universal::init_Ksi_Eta()
{
	ksi = new double[matrix_size];
	eta = new double[matrix_size];
	eta[0] = -1.0 / sqrt(3);  ksi[0] = -1.0 / sqrt(3);
	eta[1] =  -1.0 / sqrt(3);  ksi[1] = 1.0 / sqrt(3);
	eta[2] =  1.0 / sqrt(3);  ksi[2] =  1.0 / sqrt(3);
	eta[3] = 1.0 / sqrt(3);  ksi[3] =  -1.0 / sqrt(3);

}


void Element_Universal::init_d_EtaMatrix()
{
	dN_dEta = new double*[matrix_size];
	for (int i = 0; i < matrix_size; i++)
		dN_dEta[i] = new double[matrix_size];

	for (int i = 0; i < matrix_size; i++)
	{
		//dN_dEta[i] = new double[matrix_size];
		dN_dEta[0][i] = -0.25 * (1.0 - ksi[i]);
		dN_dEta[1][i] =  -0.25 * (1.0 + ksi[i]);
		dN_dEta[2][i] =  0.25 * (1.0 + ksi[i]);
		dN_dEta[3][i] = 0.25 * (1.0 - ksi[i]);
	}
}

void Element_Universal::init_d_KsiMatrix()
{
	dN_dKsi = new double*[matrix_size];
	for (int i = 0; i < matrix_size; i++)
		dN_dKsi[i] = new double[matrix_size];


	for (int i = 0; i < matrix_size; i++)
	{
		//dN_dKsi[i] = new double[matrix_size];
		dN_dKsi[0][i] = -0.25 * (1.0 - eta[i]);
		dN_dKsi[1][i] =  0.25 * (1.0 - eta[i]);
		dN_dKsi[2][i] =  0.25 * (1.0 + eta[i]);
		dN_dKsi[3][i] = -0.25 * (1.0 + eta[i]);
	}
}


void Element_Universal::init_N_Matrix()
{
	N = new double*[matrix_size];

	for (int i = 0; i < matrix_size; i++)
	{
		N[i] = new double[matrix_size];
		N[i][0] = 0.25 * (1.0 - ksi[i]) * (1.0 - eta[i]);
		N[i][1] = 0.25 * (1.0 + ksi[i]) * (1.0 - eta[i]);
		N[i][2] = 0.25 * (1.0 + ksi[i]) * (1.0 + eta[i]);
		N[i][3] = 0.25 * (1.0 - ksi[i]) * (1.0 + eta[i]);
	}
}

Element_Universal::Element_Universal()
{
	init_Ksi_Eta();
	init_d_EtaMatrix();
	init_d_KsiMatrix();
	init_N_Matrix();
}

Element_Universal::~Element_Universal()
{
}
