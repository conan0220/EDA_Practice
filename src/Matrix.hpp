#pragma once

#include <vector>
#include <iostream>

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
        : matrix_(matrix) {}

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

private:
    std::vector<std::vector<T>> matrix_;
};