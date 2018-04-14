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
	const double matrix_size = 4;

public:

	void init_H();
	void calculate_H(double** dN_dX, double** dN_dY);

	void print_H();
	void print();
	int getId();
	void setId(int i, int j);
	Element_2D();
	~Element_2D();
};

