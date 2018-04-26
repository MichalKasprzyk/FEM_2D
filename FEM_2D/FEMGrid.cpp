#include "stdafx.h"
#include "FEMGrid.h"



void FEMGrid::generate_local_H()
{
	// TODO Introduce more elements cmon homie..
	elementArray[0].calculate_H(jacobian->getdN_dX(), jacobian->getdN_dY(),jacobian->get_det_J());
	elementArray[0].calculate_boundries(jacobian->getElement_universal()->getN(),jacobian->get_det_J());
	GlobalData::printArray(elementArray[0].get_H(), elementArray[0].get_matrix_size(), elementArray[0].get_matrix_size(), "H local");
	GlobalData::printVector(elementArray[0].get_bound_cond_H()," H boundry condition");
}

void FEMGrid::generate_C()
{
	//TODO Fix to make it about more elements
	elementArray[0].calculate_C(jacobian->getElement_universal()->getN(),jacobian->get_det_J());
	GlobalData::printVector(elementArray[0].get_C(), " C ");
}
void FEMGrid::init_Jacobian()
{
	jacobian = new Jacobian();
	generate_Dx_Dksi();
}

void FEMGrid::generate_Dx_Dksi()
{
	// TODO fix that god damn function finally..
	getNode_2D(0)->setX(0.0);	getNode_2D(0)->setY(0.0);
	getNode_2D(1)->setX(0.025); getNode_2D(1)->setY(0.0);
	getNode_2D(2)->setX(0.025); getNode_2D(2)->setY(0.025);
	getNode_2D(3)->setX(0.0);	getNode_2D(3)->setY(0.025);


	getNode_2D(0)->print();
	getNode_2D(1)->print();
	getNode_2D(2)->print();
	getNode_2D(3)->print();

	// Possibly change order of points being added, from 1 6 7 2 to 1 2 6 7, not sure though..
	jacobian->initDx_DEta(getNode_2D(0)->getX(), getNode_2D(1)->getX(), getNode_2D(2)->getX(), getNode_2D(3)->getX());

	GlobalData::printArray(jacobian->get_dX_dEta(), jacobian->get_matrix_size(), "dX_dEta");
	jacobian->initDx_DKsi(getNode_2D(0)->getX(), getNode_2D(1)->getX(), getNode_2D(2)->getX(), getNode_2D(3)->getX());
	GlobalData::printArray(jacobian->get_dX_dKsi(), jacobian->get_matrix_size(), "dX_dKsi");
	jacobian->initDy_DEta(getNode_2D(0)->getY(), getNode_2D(1)->getY(), getNode_2D(2)->getY(), getNode_2D(3)->getY());
	GlobalData::printArray(jacobian->get_dY_dEta(), jacobian->get_matrix_size(), "dY_dEta");
	jacobian->initDy_DKsi(getNode_2D(0)->getY(), getNode_2D(1)->getY(), getNode_2D(2)->getY(), getNode_2D(3)->getY());
	GlobalData::printArray(jacobian->get_dY_dKsi(), jacobian->get_matrix_size(), "dY_dKsi");


	jacobian->calculate_Jacobians();
	jacobian->print_jacobian();
	jacobian->initDN_Matrixes();

	GlobalData::printArray(jacobian->getdN_dX(), jacobian->get_matrix_size(), jacobian->get_matrix_size(), "dN_dX");
	GlobalData::printArray(jacobian->getdN_dY(), jacobian->get_matrix_size(), jacobian->get_matrix_size(), "dN_dY");
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
}
