#include "stdafx.h"
#include "Element_2D.h"
#include "FEMGrid.h"
#include <cmath>

int Element_2D::el_id = 0;
extern FEMGrid *grid;

Element_2D::Element_2D()
{
	this->iid = el_id;
	el_id++;
}

vector< double > Element_2D::get_P()
{
	return this->local_P;
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
	std::cout << "Element id = " << this->iid << " -> ";
	for (int i = 0; i < 4; ++i)
	{
		std::cout << this->ID[i] << " ";
	}
	//std::cout << this->ID[3] << " " << this->ID[2] << std::endl;
	//std::cout << this->ID[0] << " " << this->ID[1] << std::endl;
	std::cout << std::endl;
}


void Element_2D::setId(int i, int j)
{
	/* Assing IDs of nodes */
	/*ID[0] = i + (j - 1)*GlobalData::numberOfNodes_H_2D;
	ID[1] = ID[0] + GlobalData::numberOfNodes_H_2D;
	ID[2] = ID[1] + 1;
	ID[3] = ID[0] + 1;  */


	// Testing NEW version 0 2 3 1 
	/*ID[0] = GlobalData::numberOfNodes_H_2D*i + j;
	ID[1] = GlobalData::numberOfNodes_H_2D*(i+1)+j;
	ID[2] = GlobalData::numberOfNodes_H_2D*(i+1)+(j+1);
	ID[3] = GlobalData::numberOfNodes_H_2D*i + (j+1);*/
	ID[0] = i + (j*GlobalData::numberOfNodes_H_2D);
	ID[1] = ID[0] + GlobalData::numberOfNodes_H_2D;
	ID[2] = ID[1] + 1;
	ID[3] = ID[0] + 1;

}

int Element_2D::getId()
{
	return this->iid;
}

int* Element_2D::get_element_node_ID()
{
	return this->ID;
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

	n1_new.resize(matrix_size);
	n2_new.resize(matrix_size);

	init_bound_cond();
	//print_boundry();
	init_length();
	vector<double> eta;
	vector<double> ksi;
	vector<double> n1(2);  //sizes should be 2 
	vector<double> n2(2);
	double local[4][2][2];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int m = 0; m < 2; m++)
			{
				local[i][j][m] = 0;
			}
		}
	}

	if (bound_cond[0] == 1)
	{
		eta.push_back(-1);
		eta.push_back(-1);
		ksi.push_back(-1 / sqrt(3));
		ksi.push_back(1 / sqrt(3));
		for (int i = 0; i < n1.size(); i++)
		{
			n1[i] = 0.25*(1 - ksi[i])*(1 - eta[i]);
			n2[i] = 0.25*(1 + ksi[i])*(1 - eta[i]);

			n1_new[0] = n1[i];
			n2_new[0] = n2[i];
		}
		for (int i = 0; i < n1.size(); i++)
		{
			for (int j = 0; j < n1.size(); j++)
			{
				local[0][i][j] = ((n1[i] * n1[j] * GlobalData::alfa) + (n2[i] * n2[j] * GlobalData::alfa))*length[0] / 2;
				
			}
		}
		eta.clear();
		ksi.clear();
	}
	if (bound_cond[1] == 1)
	{
		// Careful.. might not be working part I
		eta.push_back(-1/sqrt(3));
		eta.push_back(1/sqrt(3));
		ksi.push_back(1);
		ksi.push_back(1);
		for (int i = 0; i < n1.size(); i++)
		{
			n1[i] = 0.25*(1 + ksi[i])*(1 - eta[i]);
			n2[i] = 0.25*(1 + ksi[i])*(1 + eta[i]);

			n1_new[1] = n1[i];
			n2_new[1] = n2[i];
		}

		for (int i = 0; i < n1.size(); i++)
		{
			for (int j = 0; j < n1.size(); j++)
			{
				local[1][i][j] = ((n1[i] * n1[j] * GlobalData::alfa) + (n2[i] * n2[j] * GlobalData::alfa))*length[1] / 2;
			}
		}
		eta.clear();
		ksi.clear();
	}
	if (bound_cond[2] == 1)
	{
		// Pray to god it works part II..
		eta.push_back(1);
		eta.push_back(1);
		ksi.push_back(1 / sqrt(3));
		ksi.push_back(-1 / sqrt(3));
		for (int i = 0; i < n1.size(); i++)
		{
			n1[i] = 0.25*(1 + ksi[i])*(1 + eta[i]);
			n2[i] = 0.25*(1 - ksi[i])*(1 + eta[i]);

			n1_new[2] = n1[i];
			n2_new[2] = n2[i];
		}

		for (int i = 0; i < n1.size(); i++)
		{
			for (int j = 0; j < n1.size(); j++)
			{
				local[2][i][j] = ((n1[i] * n1[j] * GlobalData::alfa) + (n2[i] * n2[j] * GlobalData::alfa))*length[2] / 2;
			}
		}
		eta.clear();
		ksi.clear();
	}
	if (bound_cond[3] == 1)
	{
		// Still might not work Part III  and god is nowhere to be found..
		eta.push_back(1 / sqrt(3));
		eta.push_back(-1 / sqrt(3));
		ksi.push_back(-1);
		ksi.push_back(-1);

		for (int i = 0; i < n1.size(); i++)
		{
			n1[i] = 0.25*(1 - ksi[i])*(1 - eta[i]);
			n2[i] = 0.25*(1 - ksi[i])*(1 + eta[i]);

			n1_new[3] = n1[i];
			n2_new[3] = n2[i];
		}

		for (int i = 0; i < n2.size(); i++)
		{
			for (int j = 0; j < n2.size(); j++)
			{
				local[3][i][j] = ((n1[i] * n1[j] * GlobalData::alfa) + (n2[i] * n2[j] * GlobalData::alfa))*length[3] / 2;
			}
		}
	}
	

	//TODO Calculate new N Properly..
	// possiblity change res of N to 4x2?

	//GlobalData::printVector1D(ksi, "new Ksi");
	//GlobalData::printVector1D(eta, "new Eta");

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			bound_cond_H[i][j] += local[0][i][j];
			bound_cond_H[1 + i][1 + j] += local[1][i][j];
			bound_cond_H[2 + i][2 + j] += local[2][i][j];
			bound_cond_H[3 * i][3 * j] += local[3][i][j]; 
		}
	}


	// Adding H to bound_cond_H
	for (int i = 0; i < matrix_size; ++i)
	{
		for (int j = 0; j < matrix_size; ++j)
		{
			local_H[i][j] += bound_cond_H[i][j];
		}
	}


}

void Element_2D::init_length()
{
	vector< double > x;
	vector< double > y;
	for (int i = 0; i < matrix_size; i++)
	{
		// BE CAREFUL HERE !! set to ID position not i POSITION!!
		// TODO FIX IT GOD DAMIT
		//x[ID[i]] = grid->getNode_2D(ID[i])->getX();
		//y[ID[i]] = grid->getNode_2D(ID[i])->getY();
		x.push_back(grid->getNode_2D(ID[i])->getX());
		y.push_back(grid->getNode_2D(ID[i])->getY());
		//x[i] = grid->getNode_2D(ID[i])->getX();
		//y[i] = grid->getNode_2D(ID[i])->getY();
	}
	for (int i = 0; i < matrix_size - 1; i++)
	{
		length.push_back(sqrt(pow((x[i + 1] - x[i]), 2) + pow((y[i + 1] - y[i]), 2)));
	}
	length.push_back(sqrt(pow((x[3] - x[0]), 2) + pow((y[3] - y[0]), 2)));

	std::cout << std::endl;
	print();
	//GlobalData::printVector1D(length, "Length vector of element = " + std::to_string(this->iid));
	//GlobalData::printVector1D(x, " X cords of element = " + std::to_string(this->iid));
	//GlobalData::printVector1D(y, " Y cords of element = " + std::to_string(this->iid));
}

void Element_2D::init_bound_cond()
{
	// 4 walls of element since its rectangle atm..
	// TODO Prolly will need to be fixed later on


	// Yep i know how it looks, god has abandon me, however its pretty simple
	// Its wall 1 check if statuses are equal and if they are 1 (meaning condition applied) then gives wall[0] value of 1
	// Walls are set up like IDs of element
	int state0 = grid->getNode_2D(ID[0])->getStatus();
	int state1 = grid->getNode_2D(ID[1])->getStatus();
	int state2 = grid->getNode_2D(ID[2])->getStatus();
	int state3 = grid->getNode_2D(ID[3])->getStatus();

	if (state0 == state1 && state1 == 1)
		bound_cond[0] = 1;
	else
		bound_cond[0] = 0;
	if (state1 == state2 && state1 == 1)
		bound_cond[1] = 1;
	else
		bound_cond[1] = 0;
	if (state2 == state3 && state2 == 1)
		bound_cond[2] = 1;
	else
		bound_cond[2] = 0;
	if (state3 == state0 && state0 == 1)
		bound_cond[3] = 1;
	else
		bound_cond[3] = 0; 
}


void Element_2D::calculate_P(double* det_J)
{
	local_P.clear();
	local_P.resize(matrix_size);


	//double delta = GlobalData::b_2D / GlobalData::numberOfNodes_B_2D;      // Possibly wrong delta

	for (int i = 0; i < matrix_size; ++i)
	{ 
		/*for (int j = 0; j < matrix_size; ++j) {
			//local_P[i] += bound_cond_H[i][j];
		} */
		//local_P[i] = local_P[i] * GlobalData::alfa * GlobalData::GlobalData::amb_temp * length[i];//delta/2; //matrix_C[i][j]; 0.25*(1 + ksi[i])*(1 + eta[i]) ??
		local_P[i] += (n1_new[i] + n2_new[i]) * GlobalData::alfa * GlobalData::amb_temp * length[i];
		
		//GlobalData::alfa*GlobalData::GlobalData::amb_temp
	}
	//std::cout << "Element ID: " << this->iid;
	//GlobalData::printVector1D(local_P, " Local P ");
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

int Element_2D::getNodeID(int index)
{
	return ID[index];
}

void Element_2D::print_boundry()
{
	std::cout << "Element id test boundry " << iid << std::endl;
	std::cout << "    " << bound_cond[2] << std::endl;
	std::cout << " ****** " << std::endl;
	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
			std::cout << bound_cond[3] << "*    *" << bound_cond[1] << std::endl;
		else
			std::cout << " *    * " << std::endl;
	}
	std::cout << " ****** " << std::endl;
	std::cout << "    " << bound_cond[0] << std::endl;

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
