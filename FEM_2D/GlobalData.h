#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

class GlobalData
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
	static int ro;
	static int c;
	static int alfa;

	void print_2D();
	void readGridFromFile();
	void calculateRestOfGlobalData_2D();

	static void printArray(double *array, double arr_length, std::string arr_name);
	static void printArray(double **array, double columns, double rows, std::string arr_name);

	template<typename T>
	static void printVector(const std::vector< std::vector<T> > array, std::string arr_name)
	{
		std::cout << std::endl << "Matrix " << arr_name << std::endl << std::endl;
		std::cout.precision(8);
		for (auto &innerVector : array)
		{
			for (int i = 0; i < innerVector.size(); i++)
			{
				if (innerVector[i]<0)
					std::cout << std::left << "   " << innerVector[i];
				else
					std::cout << std::left << "    " << innerVector[i];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	template<typename T>
	static void printVector1D(const std::vector<T> array, std::string arr_name)
	{
		std::cout << std::endl << "Matrix " << arr_name << std::endl << std::endl;
		std::cout.precision(8);
		for (int i = 0; i<array.size(); i++)
		{
			if (array[i]<0)
				std::cout << std::left << "   " << array[i];
			else
				std::cout << std::left << "    " << array[i];
		}
		std::cout << std::endl;
	};

	static void initVector(std::vector < std::vector<double> > &array, int size);

	GlobalData();
	~GlobalData();
};

