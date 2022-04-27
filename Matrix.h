#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Node.h"

// Linked list matrix class
class Matrix
{
private:

    // Head and head_vertical pointers initialize position depending on row-wise or column-wise traversal. Tail pointer is superfluous for now.
    Node* head;
    Node* head_vertical;
    // Node* tail;

    // List_size keeps track of the number of non-zero elements in the list matrix
    int list_size;

    // Max_row_index and max_col_index keep track of the size of the matrix list, regardless of actual list size.
    int max_row_index;
    int max_col_index;

    // Precedence_factor helps determine positioning of a node in the list matrix based on a 2d representation of the list matrix.
    // Will be multiplied by row or column based on the direction that positioning is being considered, across rows first and down columns second or vice versa.
    // This multiplication product plus the other coordinate, row or column, gives a node a "numerical precedence" in list order.
    int precedence_factor;

    // Private setters are called when a new element is added
    void setMaxRow(int row);
    void setMaxCol(int col);

    // Method to add an element to the list matrix
    void addElement(int data, int row, int col);

    // Deletes the contents of a matrix list recursively
    void deleteMatrix(Node* temp);

public:
    // The default constructor exists to declare a result matrix
    Matrix();

    // Overloaded constructor initializes all data members to account for an empty list matrix and then reads in a file into the matrix object
    Matrix(std::string file);

    // Destructor
    //~Matrix();

    // Returns the size of non-zero elements in the list matrix
    int getSize();

    // Getters are not used but can be used to check max list matrix dimensions
    int getMaxRow();
    int getMaxCol();

    // Prints the list matrix in a 2d format in output
    void printMatrix();

    // Overloaded "*" operator checks if this list matrix can be multiplied by one passed in and returns result if possible in the form of a Matrix object
    Matrix operator*(Matrix two);

    // Overloaded "+" operator checks if this list matrix can be added to one passed in and returns result if possible in the form of a Matrix object
    Matrix operator+(Matrix two);

    // Writes list matrix to a text file
    void writeFile(std::string file);

    // Reads a text file into the matrix object
    void readFile(std::string file);

    // Generates a random list matrix based on user inputs for dimensions, bounds on the data, and number of nonzero elements
    void randomMatrix(int rows, int columns, int lower_bound, int upper_bound, int nonzero);
};