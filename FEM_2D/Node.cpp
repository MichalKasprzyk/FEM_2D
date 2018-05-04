#include "stdafx.h"
#include "Node.h"
#include <iostream>

int Node::id = 0;

double Node::getX()
{
	return this->x;
}

int Node::getStatus()
{
	return this->status;
}

void Node::setX(double x)
{
	this->x = x;
}


Node::Node(double x)
{
	this->iid = id;
	id++;
	this->x = x;
	//this->status = 0;
}


void Node::print()
{
	std::cout << " X = " << this->x << std::endl;
	//showStatus();
}


int Node::getId()
{
	return this->iid;
}

Node::Node()
{
	this->iid = id;
	id++;
}

void Node::setStatus(int status)
{
	this->status = status;
}

Node::~Node()
{
}
