#pragma once
#include "Vector.h"

class Matrix {
    int num_rows, num_columns;
    double* matrix;

public:
    Matrix() = default;
    Matrix(int num_rows, int num_columns);
    Matrix(Vector vector);
    ~Matrix();

    Matrix transpose();

    double  operator()(int i, int j) const;
    double& operator()(int i, int j);
    Vector  operator*(const Vector& vec);
};
