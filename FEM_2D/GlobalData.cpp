#include "stdafx.h"
#include "GlobalData.h"


/* Init przypadku 2D */
double GlobalData::h_2D = 0;
double GlobalData::b_2D = 0;
int GlobalData::numberOfElements_2D = 0;
int GlobalData::numberOfNodes_2D = 0;
int GlobalData::numberOfNodes_H_2D = 0;
int GlobalData::numberOfNodes_B_2D = 0;
double GlobalData::delta_x_2D = 0;
double GlobalData::delta_y_2D = 0;
double GlobalData::k = 25;


GlobalData::GlobalData()
{
	readGridFromFile();
	calculateRestOfGlobalData_2D();
}


void GlobalData::readGridFromFile()
{
	std::string line;
	std::fstream file1;

	file1.open("grid.txt", std::ios::in);
	if (file1.good() == true)
	{
		while (!file1.eof())
		{
			std::string var;
			double varValue;
			file1 >> var >> varValue;
			//std::cout << var << varValue << std::endl;
			switch (var[0])
			{
			case 'b':
				GlobalData::b_2D = varValue;
				break;
			case 'h':
				GlobalData::h_2D = varValue;
				break;
			case 'B':
				GlobalData::numberOfNodes_B_2D = varValue;
				break;
			case 'H':
				GlobalData::numberOfNodes_H_2D = varValue;
				break;
			}

		}
		file1.close();
	}
}

void GlobalData::calculateRestOfGlobalData_2D()
{
	GlobalData::numberOfElements_2D = (GlobalData::numberOfNodes_H_2D - 1)*(GlobalData::numberOfNodes_B_2D - 1);
	GlobalData::numberOfNodes_2D = GlobalData::numberOfNodes_H_2D * GlobalData::numberOfNodes_B_2D;
	GlobalData::delta_x_2D = GlobalData::b_2D / (GlobalData::numberOfNodes_B_2D - 1);
	GlobalData::delta_y_2D = GlobalData::h_2D / (GlobalData::numberOfNodes_H_2D - 1);
	std::cout << std::endl;
}

GlobalData::~GlobalData()
{
}


void GlobalData::print_2D()
{
	/* Case 2D */
	std::cout << "=============================" << std::endl;
	std::cout << "H = " << this->h_2D << std::endl;
	std::cout << "B = " << this->b_2D << std::endl;
	std::cout << "Total number of nodes = " << this->numberOfNodes_2D << std::endl;
	std::cout << "Number of nodes in B = " << this->numberOfNodes_B_2D << std::endl;
	std::cout << "Number of nodes in H = " << this->numberOfNodes_H_2D << std::endl;
	std::cout << "Number of elements = " << this->numberOfElements_2D << std::endl;
	std::cout << "Delta x = " << this->delta_x_2D << std::endl;
	std::cout << "Delta y = " << this->delta_y_2D << std::endl;
	std::cout << "============================" << std::endl;
}


void GlobalData::printArray(double **array, double columns, double rows, std::string arr_name)
{
	std::cout << std::endl << "Matrix " << arr_name << std::endl << std::endl;
	std::cout.precision(8);
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++) {
			if(array[i][j]<0)
				std::cout << std::left << "   " << array[i][j];
			else
				std::cout << std::left << "    " << array[i][j];
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;
}


void GlobalData::printArray(double *array, double arr_length, std::string arr_name)
{
	std::cout << std::endl << "Matrix " << arr_name << std::endl << std::endl;
	std::cout.precision(8);
	for (int i = 0; i < arr_length; i++)
	{
		if (array[i]<0)
			std::cout << std::left << "   " << array[i];
		else
			std::cout << std::left << "    " << array[i];
	}
	std::cout << std::endl;
}