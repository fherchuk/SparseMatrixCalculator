#include "Matrix.h"
#include <iostream>

// Default constructor initializes empty list matrix
Matrix::Matrix() {
    this->head = nullptr;
    this->head_vertical = nullptr;
    //this->tail = nullptr;
    this->list_size = 0;
    this->max_row_index = 0;
    this->max_col_index = 0;
    this->precedence_factor = 0;
}

// Overloaded constructor initializes empty list matrix and then reads in a text file to the list matrix
Matrix::Matrix(std::string file) {
    this->head = nullptr;
    this->head_vertical = nullptr;
    //this->tail = nullptr;
    this->list_size = 0;
    this->max_row_index = 0;
    this->max_col_index = 0;
    this->precedence_factor = 0;
    readFile(file);
}

// Returns the size of non-zero elements in the list matrix
int Matrix::getSize() {
    return this->list_size;
}

 Node* Matrix::getHead() {
    return this-> head;
}


// Private setter for row length
void Matrix::setMaxRow(int row) {
    this->max_row_index = row;
}

// Private setter for column length
void Matrix::setMaxCol(int col) {
    this->max_col_index = col;
}

// Adds element to list matrix
void Matrix::addElement(int data, int row, int col) {

    // Set the new row size based on new node
    if (row > max_row_index) {
        setMaxRow(row);
    }

    // Set the new column size based on new node
    if (col > max_col_index) {
        setMaxCol(col);
    }

    // Set the precedence factor based on the higher of row and column size plus one to ensure precedence is always large enough
    if (this->max_col_index > this->max_row_index) {
        this->precedence_factor = this->max_col_index + 1;
    }
    else {
        this->precedence_factor = this->max_row_index + 1;
    }

    // Declare a new_node to be added to the list matrix
    Node* new_node = new Node(data, row, col, nullptr, nullptr);

    // Set a curr node pointer to point to the list matrix head
    Node* curr = this->head;

    // If the list matrix is empty, make the new_node the head and return
    if (curr == nullptr) {
        this->head = new_node;
        this->list_size++;
        return;
    }

    // Iterate through list matrix across rows first and down columns second to find the spot the new_node belongs based on its numerical precedence.
    // If end of list is reached, add the new_node to the end of the list matrix.
    while (curr->next != nullptr && (curr->row * this->precedence_factor + curr->col < new_node->row * this->precedence_factor + new_node->col)) {
        curr = curr->next;
    }

    // If the curr and new_node nodes have equal precedence (same coordinates), replace the curr node with the new_node
    if (curr->row * this->precedence_factor + curr->col == new_node->row * this->precedence_factor + new_node->col) {
        if (curr->previous != nullptr) {
            curr->previous->next = new_node;
            new_node->previous = curr->previous;
        }
        if (curr->next != nullptr) {
            curr->next->previous = new_node;
            new_node->next = curr->next;
        }
        if (new_node->next == nullptr) {
            //this->tail = new_node;
        }
    }

    // If the precedence of the curr node is larger than the new_node, squeeze the new_node in right behind the curr node
    else if (curr->row * this->precedence_factor + curr->col > new_node->row * this->precedence_factor + new_node->col) {
        if (curr->previous != nullptr) {
            curr->previous->next = new_node;
            new_node->previous = curr->previous;
        }
        new_node->next = curr;
        curr->previous = new_node;
        this->list_size++;
    }

    // If the end of the list has been reached, simply add the new_node at the end
    else {
        new_node->previous = curr;
        curr->next = new_node;
        //this->tail = new_node;
        this->list_size++;
    }
}


// Prints the list matrix
void Matrix::printMatrix() {

    // Curr node pointer points to head
    Node* curr = this->head;
    curr = this->head;

    // Iterate through list and print next node.data when its coordinates are reached with the loop control variables.
    // Otherwise, print 0.
    for (int i = 0; i <= this->max_row_index; i++) {
        for (int j = 0; j <= this->max_col_index; j++) {
            if (curr != nullptr && curr->row == i && curr->col == j) {
                std::cout << curr->data << " ";
                curr = curr->next;
            }
            else {
                std::cout << 0 << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Reads in a text file matrix into a Matrix object
void Matrix::readFile(std::string file_name) {

    // Add delete function for previous matrix

    // Create the input filestream - opens the file & prepares it for reading
    std::ifstream file(file_name);

    // Temporary string to hold a single line of the file
    std::string str;

    // Index variables to keep track of indices of elements being added
    int i = 0;
    int j = 0;

    // Reads all lines in the file, 1 at at time
    while (std::getline(file, str)) {

        // Converts our string into a stringstream
        std::istringstream ss(str);

        // Temp double to store a converted value from a line
        int token;

        //Reset j to 0
        j = 0;

        // Reads all values from the stringstream (current row), converts to int and adds it to list matrix
        while (ss >> token) {

            // Adds the converted value to the list matrix with its indices using the i and j index variables
            if (token != 0) {
                addElement(token, i, j);
            }

            // Increment j every time a token is read in
            j++;
        }

        // Increment i every time a row is read in
        i++;
    }

    // Set the row and column sizes again to ensure rows with only "0" are accounted for in the list matrix dimensions
    setMaxRow(i - 1);
    setMaxCol(j - 1);

    // Set below (Node) and head_vertical (Matrix) pointers to facilitate matrix multiplication.
    // These will allow for traversal down and then to the right.
    // Set a temp1 node pointer to head. The below pointer of temp1 will be determined as the list matrix is iterated
    Node* temp1 = this->head;

    // Set the head_vertical as the normal head
    this->head_vertical = this->head;

    // Traverse through each node, setting its below pointer.
    while (temp1 != nullptr) {

        // Set a temp2 node pointer to head as well to traverse through the rest of the list to find which node is below the temp1 node
        Node* temp2 = this->head;

        // Use the precedence_factor again but in terms of down and then to the right.
        while (temp2 != nullptr) {

            // If the temp2 node has a higher precedence (below and to the right) then temp1 AND temp1 does not have a below node or temp2 is closer (up and to the left) than temp1's current below node, set temp2 as temp1's below node.
            if (temp2->row + temp2->col * this->precedence_factor > temp1->row + temp1->col * this->precedence_factor && (temp1->below == nullptr || temp2->row + temp2->col * this->precedence_factor < temp1->below->row + temp1->below->col * this->precedence_factor)) {
                temp1->below = temp2;
            }

            // If the temp2 node is closer to the start (up and to the left) than the current head_vertical, set temp2 as the head_vertical.
            if (temp2->row + temp2->col * this->precedence_factor < this->head_vertical->row + this->head_vertical->col * this->precedence_factor) {
                this->head_vertical = temp2;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}

// Unused getter for row dimension of list matrix
int Matrix::getMaxRow() {
    return this->max_row_index + 1;
}

// Unused getter for column dimension of list matrix
int Matrix::getMaxCol() {
    return this->max_col_index + 1;
}

// Returns the resultant matrix when this Matrix is multiplied by a Matrix two
// Operation will be referred to as Matrix one times Matrix two.
Matrix Matrix::operator*(Matrix two) {

    // Declare an empty result Matrix
    Matrix result;

    // If the matrix dimensions do not match for one and two, return the empty result matrix and notify user
    if (max_col_index != two.max_row_index) {
        std::cout << "Matrix dimensions do not match.";
        return result;
    }

    // Otherwise, do the multiplication
    else {

        // Set the result dimensions based on the multiplicands' dimensions
        result.setMaxRow(this->max_row_index);
        result.setMaxCol(two.max_col_index);

        // Declare a curr_one node pointer to track movement along rows of Matrix one
        Node* curr_one = this->head;

        // Declare a curr_two node pointer to track movement down columns of Matrix two
        Node* curr_two = two.head_vertical;

        // Iterate through matrix dimensions to perform operations and add nodes to result Matrix where necessary
        for (int i = 0; i <= this->max_row_index; i++) {
            for (int j = 0; j <= two.max_col_index; j++) {

                // If either curr_one or curr_two trackers have reached the end of the list matrix in their corresponding directions, break out of the current j loop and continue to the next row
                if (curr_one == nullptr || curr_two == nullptr) {
                    break;
                }

                // Declare a secondary curr_one_a node pointer to traverse across a row as a cell is being calculated
                Node* curr_one_a = curr_one;

                // Declare a secondary curr_two_a node pointer to traverse down a column as a cell is being calculated
                Node* curr_two_a = curr_two;

                // Declare a sum variable to add together the necessary multiplications as a cell is being calculated
                int sum = 0;

                // Iterate through corresponding rows in Matrix one and columns in Matrix two to calculate each cell in result
                for (int k = 0; k <= this->max_col_index; k++) {

                    // If neither curr_one_a or curr_two_a are nullptrs and they are both at the corresponding indices to be added to the sum for the current cell, multiply their data and traverse to their next nodes.
                    if (curr_one_a != nullptr && curr_two_a != nullptr && curr_one_a->row == i && curr_one_a->col == k && curr_two_a->row == k && curr_two_a->col == j) {
                        sum += curr_one_a->data * curr_two_a->data;
                        curr_one_a = curr_one_a->next;
                        curr_two_a = curr_two_a->below;
                    }

                    // If neither curr_one_a or curr_two_a are nullptrs and they have not passed into the next row or column, check if traversal is needed for either of them.
                    if (curr_one_a != nullptr && curr_two_a != nullptr && curr_one_a->row == i && curr_two_a->col == j) {

                        // If curr_one_a's column index is less than or equal to the k control variable, traverse to the next node.
                        if (curr_one_a->col <= k) {
                            curr_one_a = curr_one_a->next;
                        }

                        // If curr_two_a's row index is less than or equal to the k control variable, traverse to the next node.
                        if (curr_two_a->row <= k) {
                            curr_two_a = curr_two_a->below;
                        }
                    }

                    // Otherwise, break out and calculate the next cell.
                    else {
                        break;
                    }
                }

                // Traverse to the first cell in the next column with curr_two.
                while (curr_two != nullptr && curr_two->col <= j) {
                    curr_two = curr_two->below;
                }

                // If the sum > 0, add it to the list matrix.
                if (sum != 0) {
                    result.addElement(sum, i, j);
                }
            }
            // Traverse to the next row with curr_one
            while (curr_one != nullptr && curr_one->row <= i) {
                curr_one = curr_one->next;
            }

            //Reset curr_two to the head_vertical of Matrix two to start it all over
            curr_two = two.head_vertical;
        }
    }
    return result;
}

Matrix Matrix::operator+(Matrix two) {
    Matrix result;
    if (this->max_row_index != two.max_row_index || this->max_col_index != two.max_col_index) {
        std::cout << "Matricies are different sizes" << std::endl;
        return result;
    }
    else {
        result.setMaxRow(this->max_row_index);
        result.setMaxCol(this->max_col_index);
        Node* curr_one = head;
        Node* curr_two = two.head;
        for (int i = 0; i <= max_row_index; i++) {
            for (int j = 0; j <= max_col_index; j++) {
                int sum = 0;
                if (curr_one->row == i && curr_one->col == j && curr_two->row == i && curr_two->col == j) {
                    sum = curr_one->data + curr_two->data;
                    if (curr_one->next != nullptr) {
                        curr_one = curr_one->next;
                    }
                    if (curr_two->next != nullptr) {
                        curr_two = curr_two->next;
                    }
                }
                else if ((curr_one->row == i && curr_one->col == j) && (curr_two->row != i || curr_two->col != j)) {
                    sum = curr_one->data;
                    if (curr_one->next != nullptr) {
                        curr_one = curr_one->next;
                    }
                }
                else if ((curr_one->row != i || curr_one->col != j) && curr_two->row == i && curr_two->col == j) {
                    sum = curr_two->data;
                    if (curr_two->next != nullptr) {
                        curr_two = curr_two->next;
                    }
                }
                if (sum > 0) {
                    result.addElement(sum, i, j);
                }
            }
        }
        return result;
    }
}

// Writes a list matrix to a text file
void Matrix::writeFile(std::string file) {
   // std::cout << max_row_index << " " << max_col_index;
    // Open the outfile file and prepare it for writing
    std::ofstream output_file(file);

    // Declare a temp node pointer to traverse through list matrix
    Node* temp = this->head;

    // Loop rows
    for (unsigned int i = 0; i <= this->max_row_index; i++) {
        // Loop columns
        for (unsigned int j = 0; j <= this->max_col_index; j++) {

            // Output the next node's data if the i and j loop control variables represent the indices of the node.
            if (temp != nullptr && temp->row == i && temp->col == j) {
                output_file << temp->data << " ";
                temp = temp->next;
            }

            // Otherwise, output "0"
            else {
                output_file << "0 ";
            }
        }

        // Output a newline character after every row
        output_file << std::endl;
    }
}