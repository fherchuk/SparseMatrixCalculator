#include "Matrix.h"
#include <iostream>


//Node constructor
Node::Node(int data, int row, int col, Node* next, Node* previous){
    this->data = data;
    this->next = next;
    this->previous = previous;
    this->row = row;
    this->col = col;
}

//Matrix constructor
Matrix::Matrix(){
    this->head = nullptr;
    this->tail = nullptr;
    this->list_size = 0;
    this->max_rows = 0;
    this->max_cols = 0;
}

//Getter for number of non-zero matrix elements
int Matrix::getSize(){
    return this->list_size;
}

//Setter for row length
void Matrix::setMaxRow(int row) {
    this->max_rows = row;
}

//Setter for column length
void Matrix::setMaxCol(int col) {
    this->max_cols = col;
}

//Function to add an element
void Matrix::addElement(int data, int row, int col){

    //Set the new 
    if (row > max_rows) {
        setMaxRow(row);
    }

    if (col > max_cols) {
        setMaxCol(col);
    }

    Node* new_node = new Node(data, row, col, nullptr, nullptr);
    if (this->head == nullptr) {
        this->head = new_node;
        this->list_size++;
        return;
    }
    Node* curr = this->head;
    while (curr->next != nullptr && (curr->row * 10 + curr->col < new_node->row * 10 + new_node->col)) {
        curr = curr->next;
    }
    if (curr->row*10+curr->col == new_node->row*10+new_node->col) {
        if (curr->previous != nullptr) {
            curr->previous->next = new_node;
        }
        if (curr->next != nullptr) {
            curr->next->previous = new_node;
            new_node->next = curr->next;
        }
        if (curr->previous != nullptr) {
            new_node->previous = curr->previous;
        }
        if (new_node->next == nullptr) {
            this->tail = new_node;
        }
    }
    else if (curr->row*10+curr->col >= new_node->row*10+new_node->col) {
        if (curr->previous != nullptr) {
            curr->previous->next = new_node;
            new_node->previous = curr->previous;
        }
        new_node->next = curr;
        curr->previous = new_node;
        this->list_size++;
    }
    else {
        new_node->previous = curr;
        curr->next = new_node;
        this->tail = new_node;
        this->list_size++;
    }
}

void Matrix::printMatrix() {
    Node* curr = this->head;
    for (int i = 0; i <= this->max_rows; i++) {
        for (int j = 0; j <= this->max_cols; j++) {
            if (curr->row == i && curr->col == j) {
                std::cout << curr->data << " ";
                if (curr->next != nullptr) {
                    curr = curr->next;
                }
            }
            else {
                std::cout << 0 << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Matrix::readFile(std::string file_name) {
    // Create the input filestream - opens the file & prepares it for reading
    std::ifstream file(file_name);

    // Creates a temporary vector to represent one row
    //std::vector<double> new_row;

    // Temporary string to hold a single line of the file
    std::string str;
    
    int i = 0;
    int j;
    // Reads all lines in the file, 1 at at time
    while (std::getline(file, str)) {
        // Converts our string into a stringstream
        std::istringstream ss(str);
        // Temp double to store a converted value from a line
        int token;

        // Reads all values from the stringstream (current row), converts to double
        j = 0;
        while (ss >> token) {
            // Adds the converted value to the row
            if (token > 0) {
                addElement(token, i, j);
            }
            j++;
        }
        i++;
    }

    setMaxRow(i-1);
    setMaxCol(j-1);
}
