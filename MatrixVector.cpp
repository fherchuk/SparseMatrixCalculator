#include "MatrixVector.h"

MatrixVector::MatrixVector() {
}

MatrixVector::MatrixVector(std::string file) {
    readFileVector(file);
}

void MatrixVector::readFileVector(std::string file_name) {
    // Create the input filestream - opens the file & prepares it for reading
    std::ifstream file(file_name);

    // Creates a temporary vector to represent one row
    std::vector<int> new_row;

    // Temporary string to hold a single line of the file
    std::string str;

    // Reads all lines in the file, 1 at at time
    while (std::getline(file, str)) {
        // Converts our string into a stringstream
        std::istringstream ss(str);
        // Temp double to store a converted value from a line
        int token;

        // Reads all values from the stringstream (current row), converts to double
        while (ss >> token) {
            // Adds the converted value to the row
            new_row.push_back(token);
        }
        // Pushes our constructed vector of doubles to the 2D vector
        matrix.push_back(new_row);
        new_row.clear();
    }
}

MatrixVector MatrixVector::operator*(MatrixVector two) {
    MatrixVector result;
    if (this->matrix[0].size() != two.matrix.size()) {
        std::cout << "Matrix dimensions are not compatible";
        return result;
    }
    for (int i = 0; i < this->matrix.size(); i++) {
        std::vector<int> temp;
        for (int j = 0; j < two.matrix[i].size(); j++) {
            int sum = 0;
            for (int k = 0; k < this->matrix[i].size(); k++) {
                sum += this->matrix[i][k] * two.matrix[k][j];
            }
            temp.push_back(sum);
        }
        result.matrix.push_back(temp);
    }
    return result;
}

MatrixVector MatrixVector::operator+(MatrixVector two) {
    MatrixVector result;
    if (this->matrix[0].size() != two.matrix[0].size() && this->matrix.size() != two.matrix.size()) {
        std::cout << "Matrix dimensions are not compatible";
        return result;
    }
    for (int i = 0; i < this->matrix.size(); i++) {
        std::vector<int> temp;
        for (int j = 0; j < this->matrix[0].size(); j++) {
            temp.push_back(this->matrix[i][j] + two.matrix[i][j]);
        }
        result.matrix.push_back(temp);
    }
    return result;
}

void MatrixVector::printMatrixVector() {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void MatrixVector::writeFileVector(std::string file_name) {
    // Opens the outfile file, prepares it for writing
    std::ofstream output_file(file_name);

    // Loop rows
    for (unsigned int i = 0; i < matrix.size(); i++) {
        // Loop columns
        for (unsigned int j = 0; j < matrix[i].size(); j++) {
            // Output each value and a space
            output_file << matrix[i][j] << " ";
        }
        // Output a newline character after every row
        output_file << std::endl;
    }
}