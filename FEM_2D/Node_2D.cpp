#include "stdafx.h"
#include "Node_2D.h"


Node_2D::Node_2D() : Node()
{
}

Node_2D::Node_2D(double x, double y) : Node(x)
{
	this->y = y;
}


void Node_2D::setY(double y)
{
	this->y = y;
}

double Node_2D::getY()
{
	return this->y;
}

void Node_2D::print()
{
	std::cout << " Node_2D id = " << this->iid << std::endl;
	printf("	x = %4.2f \n ", this->x);
	printf("	y = %4.2f \n ", this->y);
}

Node_2D::~Node_2D()
{
}