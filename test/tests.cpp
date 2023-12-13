#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/matrix.h"

TEST_CASE("Default constructor creates an empty matrix") {
    Matrix matrix;
    REQUIRE(matrix.getSize() == 0);
    REQUIRE(matrix.getMaxRow() == 0);
    REQUIRE(matrix.getMaxCol() == 0);
}

TEST_CASE("Matrix can be constructed from a file") {
    Matrix matrix("test/test_matrix.txt");
    REQUIRE(matrix.getSize() == 8);
    REQUIRE(matrix.getMaxRow() == 4);
    REQUIRE(matrix.getMaxCol() == 5);
}

TEST_CASE("Matrix multiplication works correctly") {
    Matrix matrix1("test/matrix1.txt");
    Matrix matrix2("test/matrix2.txt");
    Matrix result = matrix1 * matrix2;

    // You need to define expected_result matrix based on the multiplication of matrix1 and matrix2
    Matrix expected_result("test/expected_result_multiplication.txt");

    REQUIRE(result.getSize() == expected_result.getSize());
    REQUIRE(result.getMaxRow() == expected_result.getMaxRow());
    REQUIRE(result.getMaxCol() == expected_result.getMaxCol());

    // Check if the elements in the result matrix match the expected values
    // You may need to implement a printMatrix() method to debug and compare matrices
    // REQUIRE(result == expected_result);
}

TEST_CASE("Matrix addition works correctly") {
    Matrix matrix1("test/matrix1.txt");
    Matrix matrix2("test/matrix2.txt");
    Matrix result = matrix1 + matrix2;

    // You need to define expected_result matrix based on the addition of matrix1 and matrix2
    Matrix expected_result("test/expected_result_addition.txt");

    REQUIRE(result.getSize() == expected_result.getSize());
    REQUIRE(result.getMaxRow() == expected_result.getMaxRow());
    REQUIRE(result.getMaxCol() == expected_result.getMaxCol());

    // Check if the elements in the result matrix match the expected values
    // REQUIRE(result == expected_result);
}

TEST_CASE("Writing and reading from a file produces the same matrix") {
    Matrix matrix("test/test_matrix.txt");
    matrix.writeFile("test/output_matrix.txt");

    Matrix read_matrix("test/output_matrix.txt");

    // Check if the read matrix is the same as the original matrix
    REQUIRE(matrix.getSize() == read_matrix.getSize());
    REQUIRE(matrix.getMaxRow() == read_matrix.getMaxRow());
    REQUIRE(matrix.getMaxCol() == read_matrix.getMaxCol());

    // You may need to implement a printMatrix() method to debug and compare matrices
    // REQUIRE(matrix == read_matrix);
}

TEST_CASE("Random matrix generation produces a valid matrix") {
    Matrix matrix;
    int i = 0;
    while (i < 10){
        matrix.randomMatrix(6, 6, 1, 10, 5);
      //  matrix.printMatrix();
        std::cout<<std::endl;
        REQUIRE(matrix.getSize() == 5);
        REQUIRE(matrix.getMaxRow() == 6);
        REQUIRE(matrix.getMaxCol() == 6);
    ++i;
    }
}

// Add more test cases as needed based on the functionality of your Matrix class.
