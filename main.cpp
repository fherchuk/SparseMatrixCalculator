#include <iostream>
#include "Matrix.h"

int main(){
    Matrix m;
    m.readFile("test.txt");
    m.printMatrix();
}