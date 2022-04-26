#include "Matrix.h"

int main() {
	Matrix m;
	m.randomMatrix(8,8,-9,9,5);
	m.printMatrix();
	m.writeFile("out.txt");
	int a;
	std::cin >> a;
}