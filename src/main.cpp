#include<iostream>
#include <sstream>
#include "node.h"
#include "matrix.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {

		Matrix m("test1.txt");
		Matrix n("test2.txt");


		(n+m).printMatrix();



	return 0;
}
