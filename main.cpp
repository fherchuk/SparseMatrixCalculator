#include "Matrix.h"

int main() {
	Matrix m("test1.txt"), result;
	//m.printMatrix();
	//n.printMatrix();
	result = m + m;
	result.writeFile("out1.txt");
}