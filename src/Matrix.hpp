#pragma once

#include <vector>
#include <iostream>
#include <gtest/gtest.h>

template <typename T>
class Matrix {
public:
    /**
     * @brief Constructor for the Matrix class using a 2D vector.
     * 
     * This constructor initializes the matrix with the values from the provided 2D vector.
     * It directly copies the 2D vector to the internal matrix representation of the Matrix class.
     *
     * @param matrix A 2D vector of type T representing the matrix values.
     */
    Matrix(const std::vector<std::vector<T>>& matrix)
    : matrix_(matrix) {
        if (!IsMatrixLegal(matrix_)) {
            throw std::invalid_argument("Matrix is illegal.");
        }
    }

    /**
     * @brief Constructor for the Matrix class from a 1D array.
     * 
     * This constructor creates a matrix with the specified number of rows and columns. 
     * It initializes the matrix with values from a 1D array, mapping these values into a 2D matrix format.
     * The mapping is done such that the 1D array is treated as a row-major order representation of the matrix.
     *
     * @param matrix A pointer to a 1D array of type T. This array contains the elements to fill the matrix.
     * @param row The number of rows in the matrix.
     * @param column The number of columns in the matrix.
     */
    Matrix(const T* matrix, size_t row, size_t column) {
        matrix_.resize(row);
        for (int i = 0; i < row; i++) {
            matrix_[i].resize(column);
            for (int j = 0; j < column; j++) {
                matrix_[i][j] = matrix[i * column + j];
            }
        }
        if (!IsMatrixLegal(matrix_)) {
            throw std::invalid_argument("Matrix is illegal.");
        }
    }

    /**
     * @brief Print the elements of the matrix.
     * 
     * Iterates through each row of the matrix and prints each element followed by a space.
     * After printing all elements of a row, a newline character is printed to start a new line for the next row.
     */
    void Print() const {
        for (const std::vector<T>& row : matrix_) {
            for (const T& element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::vector<T>> GetMatrix_() const { return matrix_; }

    /**
     * @brief Transpose the matrix.
     * 
     * This function flips the rows and columns of the matrix. It creates a new matrix where each row
     * is formed from the corresponding column of the original matrix and vice versa. This operation
     * is commonly known as matrix transposition. The function is templated to work with any data type 'T'
     * that can be stored in a std::vector.
     * 
     * @return A new 2D vector of type 'T', representing the transposed matrix.
     */
    std::vector<std::vector<T>> FlipMatrixRowColumn() const {
        std::vector<std::vector<T>> result;
        result.resize(matrix_[0].size());
        for (int i = 0; i < matrix_[0].size(); i++) {
            result[i].resize(matrix_.size());
            for (int j = 0; j < matrix_.size(); j++) {
                result[i][j] = matrix_[j][i];
            }
        }
        return result;
    }

    std::vector<std::vector<T>> InverseMatrix() const {
        std::vector<std::vector<T>> result;

    }


    /**
     * @brief Overloads the subscript operator to access elements of the matrix.
     * 
     * This function provides read-only access to the rows of the matrix. It returns the row at the specified index.
     * 
     * @param index The index of the row to access.
     * @return std::vector<T> The row at the given index.
     * 
     * @note Since it returns a copy of the row, any modifications to the returned vector will not affect the original matrix.
     */
    std::vector<T> operator[](const size_t& index) const { return matrix_[index]; }

    /**
     * @brief Compare two matrices for equality.
     * 
     * This function overloads the equality operator (==) to compare two matrices. It checks if both
     * matrices have the same dimensions (number of rows and columns) and then compares each corresponding
     * element. If all elements are equal, the matrices are considered equal. The function is templated
     * to work with any data type 'T' that supports the equality operator.
     * 
     * @param other A constant reference to another Matrix object of the same type 'T'.
     * @return A boolean value: 'true' if the matrices are equal, 'false' otherwise.
     */
    bool operator==(const Matrix<T>& other) const {
        if (this->matrix_.size() == other.matrix_.size() and this-> matrix_[0].size() == other.matrix_[0].size()) {
            for (int i = 0; i < this->matrix_.size(); i++) {
                for (int j = 0; j < this->matrix_[0].size(); j++) {
                    if (this->matrix_[i][j] != other.matrix_[i][j]) {
                        return false;
                    }
                }
            }
        }
        else {
            return false;
        }
        return true;
    }

private:

    FRIEND_TEST(Matrix_Test, IsMatrixLegal);
    /**
     * Checks if the given matrix is legal by verifying its structure.
     * 
     * A matrix is considered legal if it is not empty and all its rows have the same number of columns.
     * 
     * @param matrix A reference to a vector of vectors representing the matrix to check.
     * @return bool True if the matrix is legal, false otherwise.
     */
    static bool IsMatrixLegal(const std::vector<std::vector<T>>& matrix) {
        if (matrix.empty()) {
            return false;
        }
        size_t columnCount = matrix[0].size();
        for (const std::vector<T>& row : matrix) {
            if (row.size() != columnCount) {
                return false;
            }
        }
        return true;
    }

    
    std::vector<std::vector<T>> matrix_;
};