#include "MatrixVector.h"




// Default constructor that simply instantiates the object
MatrixVector::MatrixVector() {
}




// Overloaded constructor that reads a given text directly into the matrix
MatrixVector::MatrixVector(std::string file) {
    readFileVector(file);
}




// Prints the 2d matrix
void MatrixVector::printMatrixVector() {

    // Iterate through the vector and print its contents to the terminal
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}




// Overloaded matrix multiplication method that reads in a second matrix to multiply with this->matrix
MatrixVector MatrixVector::operator*(MatrixVector two) {

    // Declare a result matrix
    MatrixVector result;

    // If the matrix sizes are incompatible, throw an error and return the empty result matrix
    if (this->matrix[0].size() != two.matrix.size()) {
        std::cout << "Matrix dimensions are not compatible";
        return result;
    }

    // Iterate through the rows
    for (int i = 0; i < this->matrix.size(); i++) {

        // Declare a temp vector to store cell data to push it onto the 2d vector all at once
        std::vector<int> temp;

        // Iterate through the columns
        for (int j = 0; j < two.matrix[i].size(); j++) {

            // Declare a sum variable as data is multiplied to find what the data at a cell should be
            int sum = 0;

            // Loop through the row and column that need to be multiplied element-wise and update sum variable accordingly
            for (int k = 0; k < this->matrix[i].size(); k++) {
                sum += this->matrix[i][k] * two.matrix[k][j];
            }

            // Push back the sum variable to the temp row vector
            temp.push_back(sum);
        }

        // Push back the temp row vector to the matrix
        result.matrix.push_back(temp);
    }

    // Return the resulting matrix
    return result;
}




// Overload matrix addition method that reads in a second matrix to add to this->matrix
MatrixVector MatrixVector::operator+(MatrixVector two) {

    // Declare a result matrix
    MatrixVector result;

    // If the matrix dimensions do not match for addition, throw an error and return the empty result matrix
    if (this->matrix[0].size() != two.matrix[0].size() && this->matrix.size() != two.matrix.size()) {
        std::cout << "Matrix dimensions are not compatible";
        return result;
    }

    // Iterate through the cells, add the elements at those indices in both matrices, and add it to a temp row vector
    for (int i = 0; i < this->matrix.size(); i++) {

        // Declare the temp row vector
        std::vector<int> temp;

        // Perform the additions for a row
        for (int j = 0; j < this->matrix[0].size(); j++) {

            // Push back each addition result to the temp row vector
            temp.push_back(this->matrix[i][j] + two.matrix[i][j]);
        }

        // Push back the temp row vector to the result matrix
        result.matrix.push_back(temp);
    }

    // Return the result matrix
    return result;
}




// Writes the matrix to a text file that is generated with the given name
void MatrixVector::writeFileVector(std::string file_name) {

    // If the matrix is empty, stop
    if (this->matrix.empty()) {
        std::cout << "Please check matrix. It is empty." << std::endl;
        return;
    }

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




// Reads a text file matrix from the given file name
void MatrixVector::readFileVector(std::string file_name) {

    // Delete matrix contents before reading in new file
    this->matrix.clear();

    // Create the input filestream - opens the file & prepares it for reading
    std::ifstream file(file_name);

    // If there is no file with the given name to read, stop
    if (!file) {
        std::cout << "Invalid file name provided." << std::endl;
        return;
    }

    // Creates a temporary vector to represent one row
    std::vector<int> new_row;

    // Temporary string to hold a single line of the file
    std::string str;

    // Reads all lines in the file, 1 at at time
    while (std::getline(file, str)) {

        // Converts our string into a stringstream
        std::istringstream ss(str);

        // Temp int to store a converted value from a line
        int token;

        // Reads all values from the stringstream (current row), converts to int
        while (ss >> token) {

            // Adds the converted value to the row
            new_row.push_back(token);
        }

        // Pushes our constructed row vector to the 2D vector
        matrix.push_back(new_row);
        new_row.clear();
    }
}




// Creates a random matrix based on given dimensions, bounds for data, and number of nonzero elements
// Great improvement could be made by sorting the coords vector, but this is supplementary so did not spend time to optimize it.
void MatrixVector::randomMatrixVector(int rows, int columns, int lower_bound, int upper_bound, int nonzero) {

    // Delete matrix contents before overwriting it with a new random matrix
    this->matrix.clear();

    // Declare a vector of pairs to store randomly-generated coordinates for nonzero elements
    std::vector<std::pair<int, int>> coords;

    // Initialize a seed, random engine, and uniform distributions for the x and y coordinates and data
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> x_distr(0, columns - 1);
    std::uniform_int_distribution<int> y_distr(0, rows - 1);
    std::uniform_int_distribution<int> data_distr(lower_bound, upper_bound);

    // Add elements based on the amount of nonzero elements desired
    for (int i = 0; i < nonzero - 1; i++) {

        // Declare a flag to signal when a unique pair of coordinates have been generated
        int unique_coord_flag = 1;

        // Repeat this loop until a unique pair of coordinates are generated
        while (unique_coord_flag) {

            // Declare a pair of ints with randomly-generated x-y coordinates
            std::pair<int, int> candidate_coord = std::make_pair(x_distr(generator), y_distr(generator));

            // Iterate through the current list of generated coordinates to see if the candidate_coord already exists
            for (int j = 0; j < coords.size(); j++) {

                // If the candidate_coord already exists in the coords vector, break out to generate a new candidate_coord and set the unique_coord_flag to not found (1)
                if (coords[j].first == candidate_coord.first && coords[j].second == candidate_coord.second) {
                    unique_coord_flag = 1;
                    break;
                }

                // If the candidate_coord is unique, set the unique_coord_flag to found (0)
                else {
                    unique_coord_flag = 0;
                }
            }

            // Push back the generated coordinates to the coords vector
            coords.push_back(candidate_coord);
        }
    }

    // Resize the this->matrix to the given dimensions
    this->matrix.resize(rows);
    for (int i = 0; i < rows; i++) {
        this->matrix[i].resize(columns);
    }

    // Iterate through the matrix to add data and especially nonzero elements where applicable
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            // Declare a candidate_data variable
            int candidate_data = 0;

            // Iterate through the coords vector to see if the current cell matches any of the coordinates in the coords vector
            for (int k = 0; k < coords.size(); k++) {

                // If the current cell does match, generate candidate_data
                if (coords[k].first == j && coords[k].second == i) {

                    // Make sure that candidate_data is nonzero and break out of iteration through the coords vector
                    while (candidate_data == 0) {
                        candidate_data = data_distr(generator);
                    }
                    break;
                }
            }

            // Initialize the current cell of the matrix to the candidate_data
            this->matrix[i][j] = candidate_data;
        }
    }
}
