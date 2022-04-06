#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

class Node
{
private:
    //The data members of Node consist of a piece of data, their row and column, and next and previous pointers.
    int data;
    int row;
    int col;
    Node* next;
    Node* previous;
    Node* below;
public:
    //The only constructor takes in parameters to fully define all data members of a Node.
    Node(int data, int row, int col, Node* next, Node* previous);

    friend class Matrix;
    friend class MatrixOp;
};

class Matrix
{
private:
    //The data members of Matrix (Linked List) are head and tail pointers and a size variable.
    Node* head;
    Node* head_vertical;
    Node* tail;
    int list_size;
    int max_row_index;
    int max_col_index;

    //Made these private since they are only needed in the context of the public member functions
    void setMaxRow(int row);
    void setMaxCol(int col);

public:
    //The only and default constructor does not take in parameters.
    Matrix();

    //Returns the size of non-zero elements in the spare matrix
    int getSize();
    int getMaxRow();
    int getMaxCol();

    //Method to add an element to the matrix linked list
    void addElement(int data, int row, int col);

    //Prints the matrix in a 2d format in output
    void printMatrix();

    //Reads a text file
    void readFile(std::string file);

    //Checks to see if two matrices can be multiplied and returns result if possible

    friend class MatrixOp;
};

class MatrixOp
{
public:
    Matrix matrixMultiply(Matrix one, Matrix two);
};