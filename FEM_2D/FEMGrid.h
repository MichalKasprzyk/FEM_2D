#pragma once
#include "GlobalData.h"
#include "Node.h"
#include "Node_2D.h"
#include "Element_2D.h"
#include "Jacobian.h"
#include "Gauss.h"
#include <algorithm>

//static Node_2D *nodeArray;

static class FEMGrid
{

private:


	/* Case 2D */
	Node_2D *nodeArray;
	Element_2D *elementArray;
	Jacobian *jacobian;
	vector< vector< double > > global_H;
	vector< vector< double > > global_C;
	vector< vector< double > > global_sum;
	vector< double > global_P;




public:

	void init_Jacobian();
	void generate_Dx_Dksi();

	void generate_local_H();
	void generate_local_C();
	void generate_C_H();
	void generate_P();
	void iteration();






	void addBoundries(vector<int> walls);

	void calculateElementArray_2D();
	void calculateNodeArray_2D();
	void generaterArray_2D();
	Node_2D* getNode_2D(int index);
	Node_2D* getNodeArray_2D();
	Element_2D* getElement_2D(int index);
	Element_2D* getElementArray_2D();




	FEMGrid();
	~FEMGrid();
};

