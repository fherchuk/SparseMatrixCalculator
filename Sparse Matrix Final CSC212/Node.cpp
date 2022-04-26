#include "Node.h"

//Node constructor
Node::Node(int data, int row, int col, Node* next, Node* previous) {
    this->data = data;
    this->next = next;
    this->previous = previous;
    this->row = row;
    this->col = col;
    this->below = nullptr;
}

Node* Node::getNext() {
    return this->next;
}
int Node::getRow() {
    return this->row;
}
int Node::getCol() {
    return this->col;
}

int Node::getData() {
    return this->data;
}