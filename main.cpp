#include "Matrix.h"
#include "MatrixVector.h"
#include <ctime>
#include <iomanip>

int main() {


    unsigned long c_start, c_end;
    float time;
    std::ofstream myfile;
    myfile.open("matrixAddition.csv");
    myfile << "input" << "," << "time" << '\n';

    Matrix result;
    for (int i = 1; i < 50000; i+=200) {
        Matrix x,y;
        x.randomMatrix(i, i, 100, 200, i);
        x.writeFile("outt.txt");
        y.readFile("outt.txt");
        c_start = std::clock();
        result = y + y;
        c_end = std::clock();
        time = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
        myfile << i << "," << std::fixed << std::setprecision(4) << time<<'\n';
        std::cout << time << std::endl;
    }

    
    int t = 0;
	std::cin >> t;
    
}