#include "stdafx.h"
#include "Element_2D.h"


int Element_2D::id = 0;

Element_2D::Element_2D()
{
	this->iid = id;
	id++;
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
		for (int j = 0; j < matrix_size; j++)
			local_H[i][j] = 0;
}

void Element_2D::calculate_H(double** dN_dX, double** dN_dY)
{
	init_H();
	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j < matrix_size; j++)
		{
			local_H[i][j] = dN_dX[i][i] * dN_dX[j][i]; //+ dN_dY[i][j] * dN_dY[i][j];
		}
	}
}


void Element_2D::print_H()
{
	printf("\n");
	printf("Element H (nodes %i,%i,%i,%i)\n",ID[0],ID[1],ID[2],ID[3]);
	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j<matrix_size; j++)
			printf("  %.8f", local_H[i][j]);
		printf("\n");
	}
}
Element_2D::~Element_2D()
{
}
