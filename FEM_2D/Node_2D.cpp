#include "stdafx.h"
#include "Node_2D.h"


Node_2D::Node_2D() : Node()
{
	this->status = 0;
}

int Node_2D::getStatus()
{
	return this->status;
}

Node_2D::Node_2D(double x, double y) : Node(x)
{
	this->y = y;
	this->status = 0;
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
	std::cout << "id = " << this->iid;
	printf(" x = %4.2f", this->x);
	printf(" y = %4.2f", this->y);
	printf(" status = %d\n", this->status);
}

Node_2D::~Node_2D()
{
}
