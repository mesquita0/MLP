#include "Matrix.h"
#include "Vector.h"
#include <algorithm>

Matrix::Matrix(int num_rows, int num_columns) : num_rows(num_rows), num_columns(num_columns) {
    matrix = new double[num_columns * num_rows];
}

Matrix::Matrix(Vector vector) {
    this->num_rows = vector.getSize();
    this->num_columns = 1;

    matrix = new double[num_columns * num_rows];
    std::copy(vector.begin(), vector.end(), matrix);
}

Matrix::~Matrix() {
    if (matrix) delete[] matrix;
}

Matrix Matrix::transpose() {
    Matrix result = Matrix(num_columns, num_rows);

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_rows; j++) {
            result(i, j) = (*this)(j, i);
        }
    }

    return result;
}

double Matrix::operator()(int i, int j) const {
    return matrix[i * num_columns + j];
}

double& Matrix::operator()(int i, int j) {
    return matrix[i * num_columns + j];
}

Vector Matrix::operator*(const Vector& vec) {
    Vector result = Vector(num_rows);

    for (int i = 0; i < num_rows; i++) {
        result[i] = 0;

        for (int j = 0; j < num_columns; j++) {
            result[i] += (*this)(i, j) * vec[j];
        }
    }

    return result;
}
