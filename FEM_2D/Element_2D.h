#pragma once
#include "Node_2D.h"
#include <iostream>

class Element_2D
{
private:

	//Node nodeArray[4];
	int ID[4];

	static int id;
	int iid;

	double** local_H;
	const int matrix_size = 4;

public:

	void init_H();
	void calculate_H(double** dN_dX, double** dN_dY,double * det_J);

	void print();
	int getId();
	double** get_H();
	int get_matrix_size();
	void setId(int i, int j);
	Element_2D();
	~Element_2D();
};

