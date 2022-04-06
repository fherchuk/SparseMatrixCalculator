#include "Matrix.h"
#include <iostream>

//Hi

//Node constructor
Node::Node(int data, int row, int col, Node* next, Node* previous) {
    this->data = data;
    this->next = next;
    this->previous = previous;
    this->row = row;
    this->col = col;
    this->below = nullptr;
}

//Matrix constructor
Matrix::Matrix() {
    this->head = nullptr;
    this->head_vertical = nullptr;
    this->tail = nullptr;
    this->list_size = 0;
    this->max_row_index = 0;
    this->max_col_index = 0;
}

//Getter for number of non-zero matrix elements
int Matrix::getSize() {
    return this->list_size;
}

//Setter for row length
void Matrix::setMaxRow(int row) {
    this->max_row_index = row;
}

//Setter for column length
void Matrix::setMaxCol(int col) {
    this->max_col_index = col;
}

//Function to add an element
void Matrix::addElement(int data, int row, int col) {

    //Set the new 
    if (row > max_row_index) {
        setMaxRow(row);
    }

    if (col > max_col_index) {
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
    if (curr->row * 10 + curr->col == new_node->row * 10 + new_node->col) {
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
    else if (curr->row * 10 + curr->col >= new_node->row * 10 + new_node->col) {
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

    Node* temp1 = this->head;
    this->head_vertical = this->head;
    while (temp1 != nullptr) {
        Node* temp2 = this->head;
        while (temp2 != nullptr) {
            if (temp2->row + temp2->col * 10 > temp1->row + temp1->col * 10 && (temp1->below == nullptr || temp2->row + temp2->col * 10 < temp1->below->row + temp1->below->col * 10)) {
                temp1->below = temp2;
            }
            if (temp2->row + temp2->col * 10 < this->head_vertical->row + this->head_vertical->col * 10) {
                this->head_vertical = temp2;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}

void Matrix::printMatrix() {
    Node* curr = this->head;
    curr = this->head;

    for (int i = 0; i <= this->max_row_index; i++) {
        for (int j = 0; j <= this->max_col_index; j++) {
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

    setMaxRow(i - 1);
    setMaxCol(j - 1);
}

int Matrix::getMaxRow() {
    return this->max_row_index + 1;
}

int Matrix::getMaxCol() {
    return this->max_col_index + 1;
}

Matrix MatrixOp::matrixMultiply(Matrix one, Matrix two) {
    Matrix result;
    if (one.max_col_index != two.max_row_index) {
        std::cout << "Matrix dimensions do not match.";
        return result;
    }
    else {
        Node* curr_one = one.head;
        Node* curr_two = two.head_vertical;
        for (int i = 0; i <= one.max_row_index; i++) {
            for (int j = 0; j <= two.max_col_index; j++) {
                if (curr_one == nullptr || curr_two == nullptr) {
                    break;
                }
                Node* curr_one_a = curr_one;
                int sum = 0;
                Node* curr_two_a = curr_two;
                for (int k = 0; k <= one.max_col_index; k++) {
                    if (curr_one_a != nullptr && curr_two_a != nullptr && curr_one_a->row == i && curr_one_a->col == k && curr_two_a->row == k && curr_two_a->col == j) {
                        sum += curr_one_a->data * curr_two_a->data;
                        curr_one_a = curr_one_a->next;
                        curr_two_a = curr_two_a->below;
                    }
                    if (curr_one_a != nullptr && curr_two_a != nullptr) {
                        if (curr_one_a->col <= k) {
                            curr_one_a = curr_one_a->next;
                        }
                        if (curr_two_a->row <= k) {
                            curr_two_a = curr_two_a->below;
                        }
                    }
                    else {
                        break;
                    }
                }
                while (curr_two != nullptr && curr_two->col != j + 1) {
                    curr_two = curr_two->below;
                }
                if (sum > 0) {
                    result.addElement(sum, i, j);
                }
            }
            while (curr_one != nullptr && curr_one->row != i + 1) {
                curr_one = curr_one->next;
            }
            curr_two = two.head_vertical;
        }
    }

    return result;
}