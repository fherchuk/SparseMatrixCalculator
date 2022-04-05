#include <string>
#include <fstream>
#include <sstream>

class Node
{
    private:
        //The data members of Node consist of a piece of data, their row and column, and next and previous pointers.
        int data;
        int row;
        int col;
        Node* next;
        Node* previous;
    public:
        //The only constructor takes in parameters to fully define all data members of a Node.
        Node(int data, int row, int col, Node* next, Node* previous);

    friend class Matrix;
};

class Matrix
{
    private:
        //The data members of Matrix (Linked List) are head and tail pointers and a size variable.
        Node* head;
        Node* tail;
        int list_size;
        int max_rows;
        int max_cols;
    public:
        //The only and default constructor does not take in parameters.
        Matrix();

        int getSize();

        //Method to add an element to the matrix linked list
        void addElement(int data, int row, int col);

        void printMatrix();
        void readFile(std::string file);

        void setMaxRow(int row);
        void setMaxCol(int col);
};
