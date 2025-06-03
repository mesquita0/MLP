#pragma once
#include "InputLayer.h"
#include "Layer.h"
#include <array>
#include <cstdint>
#include <vector>

double MSE(double error, int n);
double MAE(double error, int n);

class Model {
    std::vector<Layer*> layers;
    InputLayer*         first_layer;
    Layer*              last_layer;

    double (*error_func)(double, int) = MSE;

public:
    Model() = default;
    Model(std::vector<Layer*>& layers);
    ~Model();

    void add(Layer* layer);

    void fit(const double* x_train, const double* y_train, int num_training_examples, int num_epochs);

    std::vector<double> evaluate(const double* input);

    void setErrorFunction(double (*error_func)(double, int));
    double getError(const double* predicted, const double* expected, int num_examples);
};
