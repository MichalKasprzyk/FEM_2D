#pragma once
#include "GlobalData.h"


class Node
{

protected:
	static int id;
	int iid;

	// odeglosc od ukladu wspolrzednych..
	double x;
	int status;

public:

	double getX();
	int getStatus();
	int getId();
	
	void setX(double x);


	void setStatus();
	void showStatus();
	void print();

	Node();
	Node(double x);
	~Node();
};

