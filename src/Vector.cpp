#include "Vector.h"
#include "Matrix.h"
#include <algorithm>

Vector::Vector(int size) : size(size) {
    vec = new double[size];
}

Vector::Vector(const Vector& vector) : size(vector.size) {
    vec = new double[vector.getSize()];

    this->copy(vector);
}

Vector::Vector(const std::vector<double>& vector) : size(vector.size()) {
    vec = new double[vector.size()];

    this->copy(vector);
}

Vector::~Vector() {
    if (vec) delete[] vec;
}

double Vector::inner(const Vector& other_vec) const {
    double result = 0;
    
    for (int i = 0; i < size; i++) {
        result += vec[i] * other_vec[i];
    }

    return result;
}

Vector Vector::hadamard(const Vector& other_vec) const {
    Vector result(size);

    for (int i = 0; i < size; i++) {
        result[i] = vec[i] * other_vec[i];
    }

    return result;
}

Matrix Vector::outer(const Vector& other_vec) const {
    return Matrix(*this) * Matrix(other_vec).transpose();
}

void Vector::apply(double (*func)(double)) {
    for (int i = 0; i < size; i++) {
        vec[i] = func(vec[i]);
    }
}

void Vector::copy(const Vector& other_vec) {
    std::copy(other_vec.begin(), other_vec.end(), vec);
}

void Vector::copy(const std::vector<double>& other_vec) {
    std::copy(other_vec.begin(), other_vec.end(), vec);
}

Vector& Vector::operator=(const Vector& v) {
    if (this == &v) return *this;

    if (size != v.size) {
        size = v.size;
        if (vec) delete[] vec;

        vec = new double[size];
    }
    this->copy(v);

    return *this;
}

Vector Vector::operator+(const Vector& other_vec) const {
    Vector new_vec(size);

    for (int i = 0; i < size; i++) {
        new_vec[i] = vec[i] + other_vec[i];
    }

    return new_vec;
}

Vector Vector::operator*(double x) const {
    Vector new_vec(size);

    for (int i = 0; i < size; i++) {
        new_vec[i] = vec[i] * x;
    }

    return new_vec;
}
