#pragma once
#include "Node_2D.h"
#include <iostream>
#include <vector>

using std::vector;


class Element_2D
{
private:

	//Node nodeArray[4];


	int bound_cond[4];

	static int el_id;
	int iid;

	double** local_H;
	
	const int matrix_size = 4;
	vector< vector <double> > matrix_C;
	vector< double > local_P;
	vector< vector <double> > bound_cond_H;
	vector< double > length;
	vector< double > n1_new;
	vector< double > n2_new; 

public:

	int ID[4];
	void init_H();
	void calculate_H(double** dN_dX, double** dN_dY,double * det_J);
	void calculate_C(double** N, double* det_J);
	void calculate_P(double * det_J);


	void calculate_boundries(double **N,double* det_J);


	void init_length();
	void print_boundry();
	void init_bound_cond();
	void print();
	int getNodeID(int index);
	int getId();
	double** get_H();
	int* get_element_node_ID();
	vector< double > get_P();
	vector< vector <double> > get_C();
	vector< vector <double> > get_bound_cond_H();
	int get_matrix_size();
	void setId(int i, int j);
	Element_2D();
	~Element_2D();
};

