#pragma once
#include "Vector.h"

class Matrix {
    int num_rows = 0, num_columns = 0;
    double* matrix = nullptr;

public:
    Matrix() = default;
    Matrix(int num_rows, int num_columns);
    Matrix(const Vector& vector);
    Matrix(const Matrix& mat);
    ~Matrix();

    Matrix transpose() const;

    inline double* begin() { return &this->matrix[0]; }
    inline const double* begin() const { return &this->matrix[0]; }
    inline double* end() { return &this->matrix[num_rows * num_columns]; }
    inline const double* end() const { return &this->matrix[num_rows * num_columns]; }

    Matrix& operator=(const Matrix& m);
    double  operator()(int i, int j) const;
    double& operator()(int i, int j);
    Matrix  operator+(const Matrix& other_mat) const;
    Matrix  operator-() const { return (*this) * -1; }
    Matrix  operator-(const Matrix& other_mat) const { return (*this) + (-other_mat); }
    Vector  operator*(const Vector& vec) const;
    Matrix  operator*(const Matrix& mat) const;
    Matrix  operator*(double x) const;
};
