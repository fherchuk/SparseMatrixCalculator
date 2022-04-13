
output: main.o Matrix.o
	g++ main.o Matrix.o -o matrix_app

main.o: main.cpp
	g++ -c main.cpp

Matrix.o: Matrix.cpp Matrix.h
	g++ -c Matrix.cpp

clean:
	rm *.o matrix_app