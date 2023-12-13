#include<iostream>
#include <sstream>
#include "node.h"
#include "matrix.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {

		Matrix m("test/matrix1.txt");
		Matrix n("test/matrix2.txt");


		(n+m).printMatrix();



	return 0;
}
