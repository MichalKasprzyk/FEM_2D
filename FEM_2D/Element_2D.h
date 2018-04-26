#pragma once
#include "Node_2D.h"
#include <iostream>
#include <vector>

using std::vector;

class Element_2D
{
private:

	//Node nodeArray[4];
	int ID[4];

	static int id;
	int iid;

	double** local_H;
	
	const int matrix_size = 4;
	vector< vector <double> > matrix_C;
	vector< vector <double> > bound_cond_H;

public:

	void init_H();
	void calculate_H(double** dN_dX, double** dN_dY,double * det_J);
	void calculate_C(double** N, double* det_J);
	void calculate_boundries(double **N,double* det_J);

	void print();
	int getId();
	double** get_H();
	vector< vector <double> > get_C();
	vector< vector <double> > get_bound_cond_H();
	int get_matrix_size();
	void setId(int i, int j);
	Element_2D();
	~Element_2D();
};

