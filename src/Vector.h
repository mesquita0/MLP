#pragma once
#include "Activation.h"

class Vector {
    int size;
    double* vec;

public:
    Vector() = default;
    Vector(int size);
    ~Vector();

    int getSize() const { return size; }

    double inner(const Vector& other_vec) const;

    void apply(const Activation& activation);
    void apply(double (*func)(double));

    inline double* begin() { return &this->vec[0]; }
    inline const double* begin() const { return &this->vec[0]; }
    inline double* end() { return &this->vec[size]; }
    inline const double* end() const { return &this->vec[size]; }

    double  operator[](int i) const { return vec[i]; }
    double& operator[](int i) { return vec[i]; }
    Vector  operator+(const Vector& other_vec) const;
    Vector  operator-() const { return (*this) * -1; }
    Vector  operator-(const Vector& other_vec) const { return (*this) + (-other_vec); }
    Vector  operator*(double x) const;
};

