#pragma once
#include "Node.h"
#include "Jacobian.h"
class Node_2D :
	public Node
{

private:
	double y;

public:
	double getY();
	void print();
	void setY(double y);
	Node_2D();
	int getStatus();

	Node_2D(double x, double y);
	~Node_2D();
};

