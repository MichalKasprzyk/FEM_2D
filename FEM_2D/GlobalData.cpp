#include "stdafx.h"
#include "GlobalData.h"

using std::vector;

/* Init przypadku 2D */
double GlobalData::h_2D = 0;
double GlobalData::b_2D = 0;
int GlobalData::numberOfElements_2D = 0;
int GlobalData::numberOfNodes_2D = 0;
int GlobalData::numberOfNodes_H_2D = 0;
int GlobalData::numberOfNodes_B_2D = 0;
double GlobalData::delta_x_2D = 0;
double GlobalData::delta_y_2D = 0;
double GlobalData::k = 0;
int GlobalData::c = 0;
int GlobalData::ro = 0;
int GlobalData::alfa = 0;
int GlobalData::amb_temp = 1200;
int GlobalData::tau_step_time = 50; // also seconds
int GlobalData::tau_time = 500; // given in seconds


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
			case 'k':
				GlobalData::k = varValue;
				break;
			case 'c':
				GlobalData::c = varValue;
				break;
			case 'r':
				GlobalData::ro = varValue;
				break;
			case 'a':
				GlobalData::alfa = varValue;
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
	std::cout << "K = " << this->k << std::endl;
	std::cout << "c = " << this->c << std::endl;
	std::cout << "ro = " << this->ro << std::endl;
	std::cout << "alfa = " << this->alfa << std::endl;
	std::cout << "amb temp = " << this->amb_temp << std::endl;
	std::cout << "tau_time = " << this->tau_time<< std::endl;
	std::cout << "tau_step_time = " << this->tau_step_time << std::endl;
	std::cout << "============================" << std::endl;
}

void GlobalData::initVector(std::vector< vector<double> > &array, int size)
{
	array.resize(size);
	for (int i = 0; i < array.size(); i++)
	{
		array[i].resize(size);
	}
}



void GlobalData::printArray(double **array, double columns, double rows, std::string arr_name)
{
	if (array == nullptr) {
		std::cerr << arr_name << " has not been initialized yet" << std::endl;
		return;
	}
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
	if (array == nullptr) {
		std::cerr << arr_name << " has not been initialized yet" << std::endl;
		return;
	}
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