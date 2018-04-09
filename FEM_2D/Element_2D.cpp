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

Element_2D::~Element_2D()
{
}
