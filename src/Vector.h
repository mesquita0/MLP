#pragma once
#include <vector>

class Activation;
class Matrix;

class Vector {
    int size = 0;
    double* vec = nullptr;

public:
    Vector() = default;
    Vector(int size);
    Vector(const Vector& vector);
    Vector(const std::vector<double>& vector);
    ~Vector();

    int getSize() const { return size; }

    double inner(const Vector& other_vec) const;
    Vector hadamard(const Vector& other_vec) const;
    Matrix outer(const Vector& other_vec) const;

    void apply(double (*func)(double));

    void copy(const Vector& other_vec);
    void copy(const std::vector<double>& other_vec);

    inline double* begin() { return &this->vec[0]; }
    inline const double* begin() const { return &this->vec[0]; }
    inline double* end() { return &this->vec[size]; }
    inline const double* end() const { return &this->vec[size]; }

    Vector& operator=(const Vector& v);
    double  operator[](int i) const { return vec[i]; }
    double& operator[](int i) { return vec[i]; }
    Vector  operator+(const Vector& other_vec) const;
    Vector  operator-() const { return (*this) * -1; }
    Vector  operator-(const Vector& other_vec) const { return (*this) + (-other_vec); }
    Vector  operator*(double x) const;
};
