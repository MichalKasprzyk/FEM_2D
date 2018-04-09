#include "stdafx.h"
#include "FEMGrid.h"


void FEMGrid::init_Jacobian()
{
	jacobian = new Jacobian();
	generate_Dx_Dksi();
}

void FEMGrid::generate_Dx_Dksi()
{
	getNode_2D(0)->setX(0.0);	getNode_2D(0)->setY(0.0);
	getNode_2D(1)->setX(0.2); getNode_2D(1)->setY(0.0);
	getNode_2D(2)->setX(0.2); getNode_2D(2)->setY(0.15);
	getNode_2D(3)->setX(0.0);	getNode_2D(3)->setY(0.1);


	getNode_2D(0)->print();
	getNode_2D(1)->print();
	getNode_2D(2)->print();
	getNode_2D(3)->print();

	// Possibly change order of points being added, from 1 6 7 2 to 1 2 6 7, not sure though..
	jacobian->initDx_DEta(getNode_2D(0)->getX(), getNode_2D(1)->getX(), getNode_2D(2)->getX(), getNode_2D(3)->getX());
	jacobian->printDx_DEta();
	jacobian->initDx_DKsi(getNode_2D(0)->getX(), getNode_2D(1)->getX(), getNode_2D(2)->getX(), getNode_2D(3)->getX());
	jacobian->printDx_DKsi();
	jacobian->initDy_DEta(getNode_2D(0)->getY(), getNode_2D(1)->getY(), getNode_2D(2)->getY(), getNode_2D(3)->getY());
	jacobian->printDy_DEta();
	jacobian->initDy_DKsi(getNode_2D(0)->getY(), getNode_2D(1)->getY(), getNode_2D(2)->getY(), getNode_2D(3)->getY());
	jacobian->printDy_DKsi();
	jacobian->calculate_Jacobians();
	jacobian->print_jacobian();
}

void FEMGrid::generaterArray_2D()
{
	calculateElementArray_2D();
	calculateNodeArray_2D();
}

Node_2D* FEMGrid::getNode_2D(int index)
{
	if (index <= GlobalData::numberOfNodes_2D && index >= 0)
		return &nodeArray[index];
	else
		return nullptr;
}



void FEMGrid::calculateNodeArray_2D()
{

	/* Init array of nodes of length given by GlobalData and
	   calculate coordinates of each node.
	*/
	double x(0);
	double y(0);
	int id(0);


	
	nodeArray = new Node_2D[GlobalData::numberOfNodes_2D];
	for (int i = 0; i < GlobalData::numberOfNodes_B_2D; i++)
	{
		for (int j = 0; j < GlobalData::numberOfNodes_H_2D; j++)
		{
			nodeArray[id].setX(x);
			nodeArray[id].setY(y);
			y = y + GlobalData::delta_y_2D;
			id++;
		}
		x = x + GlobalData::delta_x_2D;
		y = 0;
	}
	std::cout << std::endl;
}


void FEMGrid::calculateElementArray_2D()
{
	/* Init array of elements, then assign each element set of 4 IDs, each of those
	   coresponding to specific node of said ID.
	*/

	elementArray = new Element_2D[GlobalData::numberOfElements_2D];
	int k = 0;
		for (int j = 1; j < GlobalData::numberOfNodes_B_2D; j++)
		{
			for (int i = 1; i < GlobalData::numberOfNodes_H_2D; i++)
			{
				elementArray[k++].setId(i, j);
			}
		}

	std::cout << std::endl;
}


Element_2D * FEMGrid::getElementArray_2D()
{
	return this->elementArray;
}

Node_2D * FEMGrid::getNodeArray_2D()
{

	return this->nodeArray;
}

Element_2D* FEMGrid::getElement_2D(int index)
{
	if (index <= GlobalData::numberOfElements_2D && index >= 0)
		return &elementArray[index];
	else
		return nullptr;
}


FEMGrid::FEMGrid()
{
}


FEMGrid::~FEMGrid()
{
	//delete[] jacobian;
	//delete[] nodeArray;
	//delete[] elementArray;
}
