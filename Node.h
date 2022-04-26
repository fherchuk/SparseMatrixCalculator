#pragma once

class Node {
private:
    //Data to be stored at a non-zero node representing a cell
    int data;

    //Row and column index of data
    int row;
    int col;

    //Pointers to traverse list. Below facilitates multiplication.
    Node* next;
    Node* previous;
    Node* below;

public:
    //The only constructor takes in parameters to fully define all data members of a Node.
    Node(int data, int row, int col, Node* next, Node* previous);

    Node* getNext();

    int getData();
    int getRow();
    int getCol();

    //Make Node a friend class of Matrix to facilitate vice versa data member usage
    friend class Matrix;
};