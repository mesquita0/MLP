#include "Vector.h"

Vector::Vector(int size) : size(size) {
    vec = new double[size];
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

void Vector::apply(const Activation& activation) {
    for (int i = 0; i < size; i++) {
        vec[i] = activation.activation(vec[i]);
    }
}

void Vector::apply(double (*func)(double)) {
    for (int i = 0; i < size; i++) {
        vec[i] = func(vec[i]);
    }
}

Vector Vector::operator+(const Vector& other_vec) const {
    Vector new_vec = Vector(size);

    for (int i = 0; i < size; i++) {
        new_vec[i] = vec[i] + other_vec[i];
    }

    return new_vec;
}

Vector Vector::operator*(double x) const {
    Vector new_vec = Vector(size);

    for (int i = 0; i < size; i++) {
        new_vec[i] = vec[i] * x;
    }

    return new_vec;
}
