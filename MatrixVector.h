#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class MatrixVector
{
private:
	std::vector<std::vector<int>> matrix;
	void readFileVector(std::string);
public:
	MatrixVector();
	MatrixVector(std::string);
	MatrixVector operator*(MatrixVector);
	MatrixVector operator+(MatrixVector);
	void printMatrixVector();
	void writeFileVector(std::string file);
};