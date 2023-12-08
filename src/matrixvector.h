#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <chrono>
#include <tuple>

// Vector matrix class
class MatrixVector
{
private:

	// Private 2d vector for matrix
	std::vector<std::vector<int>> matrix;

public:

	// Default matrix constructor
	MatrixVector();

	// Overloaded constructor that reads in a text file directly
	MatrixVector(std::string);

	// Prints the 2d matrix
	void printMatrixVector();

	// Overloaded matrix multiplication method that reads in a second matrix to multiply with this->matrix
	MatrixVector operator*(MatrixVector);

	// Overload matrix addition method that reads in a second matrix to add to this->matrix
	MatrixVector operator+(MatrixVector);

	// Writes the matrix to a text file that is generated with the given name
	void writeFileVector(std::string file);

	// Reads a text file matrix from the given file name
	void readFileVector(std::string);

	// Creates a random matrix based on given dimensions, bounds for data, and number of nonzero elements
	void randomMatrixVector(int rows, int columns, int lower_bound, int upper_bound, int nonzero);
};
