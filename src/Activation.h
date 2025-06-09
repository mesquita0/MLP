#pragma once
#include "Vector.h"

class Activation {
public:
    virtual double activation(double x)            const = 0;
    virtual void   applyActivation(Vector& vector) const = 0;
    virtual double derivative(double x)            const = 0;
    virtual void   applyDerivative(Vector& vector) const = 0;
};

class Linear : public Activation {
    static constexpr double (*func)(double)  = [](double x) { return x; };
    static constexpr double (*deriv)(double) = [](double x) { return 1.0; };

    double activation(double x) const { return func(x); }
    void   applyActivation(Vector& vector) const { vector.apply(func); }
    double derivative(double x) const { return deriv(x); }
    void   applyDerivative(Vector& vector) const { return vector.apply(deriv); }
};

class Sin : public Activation {
    static constexpr double (*func)(double)  = [](double x) { return sin(x); };
    static constexpr double (*deriv)(double) = [](double x) { return cos(x); };

    double activation(double x) const { return func(x); }
    void   applyActivation(Vector& vector) const { vector.apply(func); }
    double derivative(double x) const { return deriv(x); }
    void   applyDerivative(Vector& vector) const { return vector.apply(deriv); }
};

class Sigmoid : public Activation {
    static constexpr double (*func)(double)  = [](double x) { return (1.0 / (1.0 + exp(-x))); };
    static constexpr double (*deriv)(double) = [](double x) { return func(x) * (1 - func(x)); };

    double activation(double x) const { return func(x); }
    void   applyActivation(Vector& vector) const { vector.apply(func); }
    double derivative(double x) const { return deriv(x); }
    void   applyDerivative(Vector& vector) const { return vector.apply(deriv); }
};
