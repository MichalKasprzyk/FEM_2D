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

public:

	void print();
	int getId();
	void setId(int i, int j);
	Element_2D();
	~Element_2D();
};

