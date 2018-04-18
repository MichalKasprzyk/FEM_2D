#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

static class GlobalData
{

public:

	/*  Case 2D  */
	static double h_2D;
	static double b_2D;
	static int numberOfElements_2D;
	static int numberOfNodes_2D;
	static int numberOfNodes_H_2D;
	static int numberOfNodes_B_2D;
	static double delta_x_2D;
	static double delta_y_2D;
	static double k;

	void print_2D();
	void readGridFromFile();
	void calculateRestOfGlobalData_2D();

	GlobalData();
	~GlobalData();
};

