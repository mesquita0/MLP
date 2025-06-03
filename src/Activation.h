#pragma once

class Activation {
public:
    virtual double activation(double x) const = 0;
    virtual double derivative(double x) const = 0;
};

class Linear : public Activation {
    double activation(double x) const { return x; }
    double derivative(double x) const { return 1; }
};
