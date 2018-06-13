#include "stdafx.h"
#include "FEMGrid.h"



void FEMGrid::init_temp()
{
	//temp_0.resize(4 * GlobalData::numberOfNodes_H_2D);
	//temp_1.resize(4 * GlobalData::numberOfNodes_H_2D);
	
	temp_0.resize(GlobalData::numberOfNodes_2D);
	temp_1.resize(GlobalData::numberOfNodes_2D);
	
	for (int i = 0; i < temp_0.size(); i++)
	{
		// Global temperature vector, by default for the task it is set to 100 C 
		temp_0[i] = 100;
	}

	        /*                                                
		    temp_0[0] = 365.81547;
			temp_0[1] = 249.01534;
			temp_0[2] = 249.01534;
			temp_0[3] = 365.81547;
			temp_0[4] = 249.01534;
			temp_0[5] = 110.03798;
			temp_0[6] = 110.03798;
			temp_0[7] = 249.01534;
			temp_0[8] = 249.01534;
			temp_0[9] = 110.03798;
			temp_0[10] = 110.03798;
			temp_0[11] = 249.01534;
			temp_0[12] = 365.81547;
			temp_0[13] = 249.01534;
			temp_0[14] = 249.01534;
			temp_0[15] = 365.81547; 
			*/
	

}


void FEMGrid::addBoundries(vector<int> walls)
{
	// Potentially very harmful functions but who cares.. im too dumb for it anyway..
	// walls in order
	/*
			3
		   __ 
		4 |  | 2
		   --
		   1
	*/
	if (walls[3] == 1)
	{
		for (int i = 0; i < GlobalData::numberOfNodes_H_2D; ++i)
		{
			nodeArray[i].setStatus(1);
		}
	}
	
	if (walls[2] == 1)
	{
		for (int i = GlobalData::numberOfNodes_H_2D - 1; i < GlobalData::numberOfNodes_2D; i += GlobalData::numberOfNodes_B_2D)
		{
			nodeArray[i].setStatus(1);
		}
	}

	if (walls[1] == 1)
	{
		for (int i = GlobalData::numberOfNodes_2D - GlobalData::numberOfNodes_B_2D; i < GlobalData::numberOfNodes_2D; ++i)
		{
			nodeArray[i].setStatus(1);
		}
	}

	if (walls[0] == 1)
	{
		for (int i = 0; i < GlobalData::numberOfNodes_2D; i += GlobalData::numberOfNodes_B_2D)
		{
			nodeArray[i].setStatus(1);
		}
	}

	std::cout << "Nodes with boundries: " << std::endl;
	for (int i = 0; i < GlobalData::numberOfNodes_2D; ++i)
	{
		nodeArray[i].print();
	} 

}

void FEMGrid::recalculateP() {
	//global_P.resize(4 * GlobalData::numberOfNodes_H_2D);
	global_P.resize(GlobalData::numberOfNodes_2D);
		for (int i = 0; i < GlobalData::numberOfElements_2D; ++i)
	{
		for(int j = 0; j < 4 ; ++j)
		{
			global_P[elementArray[i].ID[j]] += elementArray[i].get_P()[j];
			//std::cout << " Adding element " << i << " with ID[" << j << "] = " << elementArray[i].ID[j] << " of value = " << elementArray[i].get_P()[j] << std::endl;
		}
	}

	for (int i = 0; i < GlobalData::numberOfNodes_2D; ++i)
	{
		double test = 0;
		for(int j = 0; j < global_C[i].size(); ++j)
			test += (global_C[i][j] / GlobalData::tau_step_time) * temp_0[i];
		global_P[i] += test;
	}  
	GlobalData::printVector1D(global_P, "Global P");
}

void FEMGrid::iteration()
{
	// TO DO FIX IT < WARNING > GLOBAL_H COMES WITH BOUND CONDITIONS ALREADY IN PLACE !!!!! !

	//global_sum.resize(4 * GlobalData::numberOfNodes_H_2D);
	global_sum.resize(GlobalData::numberOfNodes_2D);
	for (int i = 0; i < global_sum.size(); i++)
	{
		//global_sum[i].resize(4 * GlobalData::numberOfNodes_B_2D);
		global_sum[i].resize(GlobalData::numberOfNodes_2D);
	}
	int i(0);

	for (int i = 0; i < global_sum.size(); ++i)
	{
		for (int j = 0; j < global_sum[i].size(); ++j)
		{
			global_sum[i][j] = global_H[i][j] + global_C[i][j] / GlobalData::tau_step_time;
		}
	}


	
	//GlobalData::printVector1D(temp_1, "Pierwsza iteracja, hopefully dzialajaca");
	//temp_1 = Gauss::gauss(global_sum,global_P);
	bool test = false;
	double MAX(0);
	double MIN(0);
	while (GlobalData::tau_time>0) //GlobalData::tau_time >= 0	
	{

		std::cout << "============== Iteration " << i << " ==============" << std::endl;
		//GlobalData::printVector(global_sum, " {H} + {C}/dT");
		//recalculateP();
		generate_P(test);
		//temp_0 = Gauss::gauss(global_sum, global_P);
		temp_0 = Gauss::gaussMagdy(global_sum, global_P);
		test = true;
		//GlobalData::printVector1D(temp_0, "Temperature vector");
		GlobalData::findMinMax(temp_0, MAX, MIN);

		std::cout << "MAX = " << MAX << " MIN = " << MIN << std::endl;
		++i;
		global_P.clear();

		GlobalData::tau_time = GlobalData::tau_time - GlobalData::tau_step_time;
	}
}


void FEMGrid::generate_P(bool test)
{
	// TODO FIX IT 
	//global_P.resize(4 * GlobalData::numberOfNodes_H_2D);
	global_P.resize(GlobalData::numberOfNodes_2D);
	if(test == false)
		for (int i = 0; i < GlobalData::numberOfElements_2D; ++i)
		{
			elementArray[i].calculate_P(jacobian[i].get_det_J());
		}

	for (int i = 0; i < GlobalData::numberOfElements_2D; ++i)
	{
		for(int j = 0; j < 4 ; ++j)
		{
		
			//std::cout << " Adding element " << i << " with ID[" << j << "] = " << elementArray[i].ID[j] << " of value = " << elementArray[i].get_P()[j] << std::endl;
			global_P[elementArray[i].ID[j]] += elementArray[i].get_P()[j];
		}	
		//GlobalData::printVector1D(elementArray[i].get_P(), "P local test");
	}

	for (int i = 0; i < GlobalData::numberOfNodes_2D; ++i)
	{
		double test = 0;
		for(int j = 0; j < global_C[i].size(); ++j)
			test += (global_C[i][j] / GlobalData::tau_step_time) * temp_0[j];
		global_P[i] += test;
		//std::cout << "Global data tau step time = " << GlobalData::tau_step_time << std::endl;
	}  
	//GlobalData::printVector1D(global_P, "Global P");
	//GlobalData::printVector(global_C, "Global C");
	//GlobalData::printVector1D(temp_0, "Temp test");
}

void FEMGrid::generate_C_H()
{

	//global_C.resize(4 * GlobalData::numberOfNodes_H_2D);
	//global_H.resize(4 * GlobalData::numberOfNodes_H_2D);

	global_C.resize(GlobalData::numberOfNodes_2D);
	global_H.resize(GlobalData::numberOfNodes_2D);

	for (int i = 0; i < global_C.size(); i++)
	{
		//global_C[i].resize(4 * GlobalData::numberOfNodes_B_2D);
		//global_H[i].resize(4 * GlobalData::numberOfNodes_B_2D);
	
		global_C[i].resize(GlobalData::numberOfNodes_2D);
		global_H[i].resize(GlobalData::numberOfNodes_2D);
	}

	for (int k = 0; k < GlobalData::numberOfElements_2D; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				global_C[elementArray[k].ID[i]][elementArray[k].ID[j]] += elementArray[k].get_C()[i][j];
				global_H[elementArray[k].ID[i]][elementArray[k].ID[j]] += elementArray[k].get_H()[i][j];
			}
		}
	}



	//GlobalData::printVector(global_H, "Global H");
	//GlobalData::printVector(global_C, "Global C");
}

void FEMGrid::generate_local_H()
{
	// TODO Introduce more elements cmon homie..
	//elementArray[0].calculate_H(jacobian->getdN_dX(), jacobian->getdN_dY(),jacobian->get_det_J());
	//GlobalData::printArray(elementArray[0].get_H(), elementArray[0].get_matrix_size(), elementArray[0].get_matrix_size(), "H local");


	// Introduced boundary condition on Surface 1 (Hopefully)
	//getNode_2D(0)->setStatus(0); getNode_2D(2)->setStatus(0);
	//getNode_2D(1)->setStatus(1); getNode_2D(3)->setStatus(1);
	//getNode_2D(0)->setStatus(1); getNode_2D(4)->setStatus(1);
	//getNode_2D(1)->setStatus(1); getNode_2D(5)->setStatus(1);

	// REKTORSKIE PRZEROBKI 

	/*getNode_2D(0)->setX(0);
	getNode_2D(4)->setX(0.333333);
	getNode_2D(5)->setX(0.333333);
	getNode_2D(1)->setX(0);

	getNode_2D(0)->setY(0);
	getNode_2D(4)->setY(0);
	getNode_2D(5)->setY(0.333333);
	getNode_2D(1)->setY(0.333333); */



	addBoundries({ 1,1,1,1 });

	//elementArray[0].calculate_boundries(jacobian->getElement_universal()->getN(),jacobian->get_det_J());
	for (int i = 0; i < GlobalData::numberOfElements_2D; ++i) {
		elementArray[i].init_bound_cond();
		//elementArray[i].print_boundry();
		elementArray[i].calculate_H(jacobian[i].getdN_dX(), jacobian[i].getdN_dY(), jacobian[i].get_det_J());
		elementArray[i].calculate_boundries(jacobian[i].getElement_universal()->getN(), jacobian[i].get_det_J());    
	}




	//elementArray[0].calculate_boundries(jacobian[0].getElement_universal()->getN(), jacobian[0].get_det_J());

}

void FEMGrid::generate_local_C()
{
	for (int i = 0; i < GlobalData::numberOfElements_2D; ++i) {
		elementArray[i].calculate_C(jacobian[i].getElement_universal()->getN(), jacobian[i].get_det_J());
		//GlobalData::printVector(elementArray[i].get_C(), " C ");
	}
	/*elementArray[0].calculate_C(jacobian->getElement_universal()->getN(), jacobian->get_det_J());
	GlobalData::printVector(elementArray[0].get_C(), " C "); */
}
void FEMGrid::init_Jacobian()
{
	jacobian = new Jacobian[GlobalData::numberOfElements_2D];
	//jacobian = new Jacobian();
	generate_Dx_Dksi();
}

void FEMGrid::generate_Dx_Dksi()
{
	
	// TODO fix that god damn function finally..
	//getNode_2D(0)->setX(0.0);	getNode_2D(0)->setY(0.0);
	//getNode_2D(1)->setX(0.025); getNode_2D(1)->setY(0.0);
	//getNode_2D(2)->setX(0.025); getNode_2D(2)->setY(0.025);
	//getNode_2D(3)->setX(0.0);	getNode_2D(3)->setY(0.025);

	std::cout << "Nodes: " << std::endl;
	for (int i = 0; i < GlobalData::numberOfNodes_2D; ++i)
	{
		getNode_2D(i)->print();
	} 


	// Possibly change order of points being added, from 1 6 7 2 to 1 2 6 7, not sure though..
	//jacobian->initDx_DEta(getNode_2D(0)->getX(), getNode_2D(1)->getX(), getNode_2D(2)->getX(), getNode_2D(3)->getX());





	//TUTAJ PRACUJEMY OBECNIE UWAGA
	// bledem jest tutaj kolejnosc przesylania node do jacobiana, przyjmuje zle id stad sa zle wartosci
	// ============!!!!!!!!!!!!!!!!!!!!!!==================
	// potencjalny blad z liczeniem jacobianow!!!!!!!! UWAGA !!! 


	vector<double> x;
	vector<double> y;
	vector<double> id_vector;

	for (int i = 0; i < GlobalData::numberOfElements_2D; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			id_vector.push_back(elementArray[i].get_element_node_ID()[j]);

			// TODO UWAGA, bardzo durny myk z sortowaniem go zeby ID byly wrzucone po kolei i poprawnie liczylo dx_dEta
			//std::sort(id_vector.begin(), id_vector.end());
		}
		//GlobalData::printVector1D(id_vector, "Testowy vector ID");

		for (int j = 0; j < 4; ++j)
		{
			x.push_back(getNode_2D(id_vector[j])->getX());
			y.push_back(getNode_2D(id_vector[j])->getY());
		}
		//GlobalData::printVector1D(x, "Testowy vector x");
		//GlobalData::printVector1D(y, "Testowy vector y");

		std::cout << "Jacobian iteration i = " << i << std::endl;
		jacobian[i].initDx_DEta(x);
		jacobian[i].initDx_DKsi(x);
		jacobian[i].initDy_DEta(y);
		jacobian[i].initDy_DKsi(y);
		//GlobalData::printArray(jacobian[i].get_dY_dEta(), jacobian[i].get_matrix_size(), "dY_dEta");
		//GlobalData::printArray(jacobian[i].get_dX_dKsi(), jacobian[i].get_matrix_size(), "dX_dKsi");
		//GlobalData::printArray(jacobian[i].get_dX_dEta(), jacobian[i].get_matrix_size(), "dX_dEta");
		//GlobalData::printArray(jacobian[i].get_dY_dKsi(), jacobian[i].get_matrix_size(), "dY_dKsi");


		jacobian[i].calculate_Jacobians();
		//jacobian[i].print_jacobian();
		jacobian[i].initDN_Matrixes();

		//GlobalData::printArray(jacobian[i].getdN_dX(), jacobian[i].get_matrix_size(), jacobian[i].get_matrix_size(), "dN_dX");
		//GlobalData::printArray(jacobian[i].getdN_dY(), jacobian[i].get_matrix_size(), jacobian[i].get_matrix_size(), "dN_dY");

		// clean up for next operation
		id_vector.clear();
		x.clear();
		y.clear();
	}

	//***************DEBUG PURPOSES******************************
	/*jacobian[0].print_jacobian();
	GlobalData::printArray(jacobian[0].get_dY_dEta(), jacobian[0].get_matrix_size(), "dY_dEta");
	GlobalData::printArray(jacobian[0].get_dX_dKsi(), jacobian[0].get_matrix_size(), "dX_dKsi");
	GlobalData::printArray(jacobian[0].get_dX_dEta(), jacobian[0].get_matrix_size(), "dX_dEta");
	GlobalData::printArray(jacobian[0].get_dY_dKsi(), jacobian[0].get_matrix_size(), "dY_dKsi");
	GlobalData::printArray(jacobian[0].getdN_dX(), jacobian[0].get_matrix_size(), jacobian[0].get_matrix_size(), "dN_dX");
	GlobalData::printArray(jacobian[0].getdN_dY(), jacobian[0].get_matrix_size(), jacobian[0].get_matrix_size(), "dN_dY"); */

	/*for (int i = 0; i < 4; ++i)
	{
		//x.push_back(getNode_2D(i)->getX());
		//y.push_back(getNode_2D(i)->getY());
	} */


	/*jacobian->initDx_DEta(x);
	jacobian->initDx_DKsi(x);
	jacobian->initDy_DEta(y);
	jacobian->initDy_DKsi(y); */

	//jacobian->initDx_DEta(getNode_2D(0)->getX(), getNode_2D(1)->getX(), getNode_2D(2)->getX(), getNode_2D(3)->getX());
	//jacobian->initDx_DKsi(getNode_2D(0)->getX(), getNode_2D(1)->getX(), getNode_2D(2)->getX(), getNode_2D(3)->getX());
	//jacobian->initDy_DEta(getNode_2D(0)->getY(), getNode_2D(1)->getY(), getNode_2D(2)->getY(), getNode_2D(3)->getY());
	//jacobian->initDy_DKsi(getNode_2D(0)->getY(), getNode_2D(1)->getY(), getNode_2D(2)->getY(), getNode_2D(3)->getY());


	/*GlobalData::printArray(jacobian->get_dY_dEta(), jacobian->get_matrix_size(), "dY_dEta");
	GlobalData::printArray(jacobian->get_dX_dKsi(), jacobian->get_matrix_size(), "dX_dKsi");
	GlobalData::printArray(jacobian->get_dX_dEta(), jacobian->get_matrix_size(), "dX_dEta");
	GlobalData::printArray(jacobian->get_dY_dKsi(), jacobian->get_matrix_size(), "dY_dKsi");


	jacobian->calculate_Jacobians();
	jacobian->print_jacobian();
	jacobian->initDN_Matrixes();

	GlobalData::printArray(jacobian->getdN_dX(), jacobian->get_matrix_size(), jacobian->get_matrix_size(), "dN_dX");
	GlobalData::printArray(jacobian->getdN_dY(), jacobian->get_matrix_size(), jacobian->get_matrix_size(), "dN_dY"); */
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
	// FOR TEST PURPOSES CHANGING IDS to 0! (i = 0 instead of i=1 and j = 0 instead of j = 1)
	// It has to have -1 numberOfNodes_B and _H condition too if you want it to work
	int k = 0;
		for (int j = 0; j < GlobalData::numberOfNodes_B_2D-1; j++)
		{
			for (int i = 0; i < GlobalData::numberOfNodes_H_2D-1; i++)
			{
				elementArray[k].setId(i, j);
				k++;
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

	return nodeArray;
	//return this->nodeArray;
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
