#include "Matrix.h"
#include "Vector.h"
#include <algorithm>

Matrix::Matrix(int num_rows, int num_columns) : num_rows(num_rows), num_columns(num_columns) {
    matrix = new double[num_columns * num_rows];
}

Matrix::Matrix(const Vector& vector) {
    this->num_rows = vector.getSize();
    this->num_columns = 1;

    matrix = new double[num_columns * num_rows];
    std::copy(vector.begin(), vector.end(), matrix);
}

Matrix::Matrix(const Matrix& mat) : num_rows(mat.num_rows), num_columns(mat.num_columns) {
    matrix = new double[num_columns * num_rows];
    std::copy(mat.begin(), mat.end(), matrix);
}

Matrix::~Matrix() {
    if (matrix) delete[] matrix;
}

Matrix Matrix::transpose() const {
    Matrix result(num_columns, num_rows);

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            result(j, i) = (*this)(i, j);
        }
    }

    return result;
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (this == &m) return *this;

    if (num_rows != m.num_rows || num_columns != m.num_columns) {
        num_rows = m.num_rows;
        num_columns = m.num_columns;
        if (matrix) delete[] matrix;

        matrix = new double[num_columns * num_rows];
    }
    std::copy(m.begin(), m.end(), matrix);

    return *this;
}

double Matrix::operator()(int i, int j) const {
    if (i >= num_rows || j >= num_columns) throw;
    return matrix[i * num_columns + j];
}

double& Matrix::operator()(int i, int j) {
    if (i >= num_rows || j >= num_columns) throw;
    return matrix[i * num_columns + j];
}

Matrix Matrix::operator+(const Matrix& other_mat) const {
    Matrix result(num_rows, num_columns);

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            result(i, j) = (*this)(i, j) + other_mat(i, j);
        }
    }

    return result;
}

Vector Matrix::operator*(const Vector& vec) const {
    Vector result(num_rows);

    for (int i = 0; i < num_rows; i++) {
        result[i] = 0;

        for (int j = 0; j < num_columns; j++) {
            result[i] += (*this)(i, j) * vec[j];
        }
    }

    return result;
}

Matrix Matrix::operator*(const Matrix& mat) const {
    Matrix result(num_rows, mat.num_columns);

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < mat.num_columns; j++) {
            result(i, j) = 0;

            for (int k = 0; k < num_columns; k++) {
                result(i, j) += (*this)(i, k) * mat(k, j);
            }
        }
    }

    return result;
}

Matrix Matrix::operator*(double x) const {
    Matrix result(num_rows, num_columns);

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            result(i, j) = x * (*this)(i, j);
        }
    }

    return result;
}
