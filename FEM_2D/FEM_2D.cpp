// FEM_2D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GlobalData.h"
#include "FEMGrid.h"
#include "Gauss.h"
#include "Node_2D.h"
#include "Element_Universal.h"

int main()
{
	GlobalData* data = new GlobalData();
	data->print_2D();

	std::cout << std::endl;


	/*    Case 2D  */
	FEMGrid* grid = new FEMGrid();
	grid->calculateElementArray_2D();
	//for (int i = 0; i < GlobalData::numberOfElements_2D; i++)
		//grid->getElement_2D(i)->print();

	grid->calculateNodeArray_2D();
	//for (int i = 0; i < GlobalData::numberOfNodes_2D; i++)
		//grid->getNode_2D(i)->print();

	grid->init_Jacobian();
	//Element_Universal* universal = new Element_Universal();
	//universal->print_N();
	//universal->print_dEta();
	//universal->print_dKsi();
	grid->generate_local_H();
	grid->generate_C();
	getchar();
	return 0;
}

