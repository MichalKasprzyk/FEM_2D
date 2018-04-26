#include "stdafx.h"
#include "Element_2D.h"


int Element_2D::id = 0;

Element_2D::Element_2D()
{
	this->iid = id;
	id++;
}

int Element_2D::get_matrix_size()
{
	return matrix_size;
}

double** Element_2D::get_H()
{
	return local_H;
}

void Element_2D::print()
{
	std::cout << "Element id = " << this->iid << std::endl;
	std::cout << this->ID[3] << " " << this->ID[2] << std::endl;
	std::cout << this->ID[0] << " " << this->ID[1] << std::endl;
	std::cout << std::endl;
}


void Element_2D::setId(int i, int j)
{
	/* Assing IDs of nodes */
	ID[0] = i + (j - 1)*GlobalData::numberOfNodes_H_2D;
	ID[1] = ID[0] + GlobalData::numberOfNodes_H_2D;
	ID[2] = ID[1] + 1;
	ID[3] = ID[0] + 1; 

}

int Element_2D::getId()
{
	return this->iid;
}




void Element_2D::init_H()
{
	local_H = new double*[matrix_size];
	for (int i = 0; i < matrix_size; i++)
	{
		local_H[i] = new double[matrix_size];
	}

	for (int i = 0; i < matrix_size; i++)
		for (int j = 0; j < matrix_size; j++) {
			local_H[i][j] = 0;
		}
}

void Element_2D::calculate_boundries(double **N,double *det_J)
{
	//Careful about which nodes have heat condition in them
	GlobalData::initVector(bound_cond_H, matrix_size);
	vector<double> eta{ -1,-1 };
	vector<double> ksi{ -0.57,0.57 };
	//GlobalData::printVector1D(ksi, " ksi ");

	vector< vector<double> > new_N;
	GlobalData::initVector(new_N, matrix_size);



	for (int i = 0; i < bound_cond_H.size(); i++)
	{
		for (int j = 0; j < bound_cond_H.size(); j++)
		{
			for (int k = 0; k < matrix_size; k++) {
				bound_cond_H[i][j] = GlobalData::alfa* N[i][k] * N[j][k] * det_J[j];
			}
		}
	}


}

void Element_2D::calculate_H(double** dN_dX, double** dN_dY, double* det_J)
{
	init_H();

	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j < matrix_size; j++)
		{
			//local_H[i][j] = dN_dX[i][0] * dN_dX[j][0]; <- dn/DX 1PC 
			//local_H[i][j] = dN_dX[i][1] * dN_dX[j][1]; <- dn/DX 2PC
			//local_H[i][j] = dN_dX[i][2] * dN_dX[j][2]; <- dn/DX 3PC
			//local_H[i][j] = dN_dX[i][3] * dN_dX[j][3]; <- dn/DX 4PC
			
			
			//local_H[i][j] = dN_dY[i][0] * dN_dY[j][0]; <- dn/DY 1PC
			//local_H[i][j] = dN_dY[i][1] * dN_dY[j][1]; <- dn/DY 2PC
			//local_H[i][j] = dN_dY[i][2] * dN_dY[j][2]; <- dn/DY 3PC
			//local_H[i][j] = dN_dY[i][3] * dN_dY[j][3]*det_J[j];  <- dN/DY 4PC with optional Det_J 
			for(int k=0; k<matrix_size;k++)
				local_H[i][j] += GlobalData::k*(dN_dY[i][k] * dN_dY[j][k] * det_J[j] + dN_dX[i][k] * dN_dX[j][k] * det_J[j]);
		}
	}
}

void Element_2D::calculate_C(double **N,double* det_J)
{
	
	GlobalData::initVector(matrix_C, matrix_size);

	for (int i = 0; i < matrix_C.size(); i++)
	{
		for (int j = 0; j < matrix_C.size(); j++)
		{
			for (int k = 0; k < matrix_size; k++) {
				matrix_C[i][j] += GlobalData::ro * GlobalData::c * N[i][k] * N[j][k]*det_J[j];
			}
		}
	}

}

vector< vector <double> > Element_2D::get_C()
{
	return matrix_C;
}

vector < vector <double> > Element_2D::get_bound_cond_H()
{
	return bound_cond_H;
}

Element_2D::~Element_2D()
{
}
