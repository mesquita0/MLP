#pragma once
#include "InputLayer.h"
#include "Layer.h"
#include <array>
#include <cstdint>
#include <vector>

class Model {
    std::vector<Layer*> layers;
    InputLayer*         first_layer;
    Layer*              last_layer;
    double              learning_rate = 0.01;

public:
    Model() = default;
    Model(std::vector<Layer*>& layers);
    ~Model();

    void add(Layer* layer);

    void fit(const std::vector<Vector>& x_train, const std::vector<Vector>& y_train, int num_epochs);

    Vector evaluate(const Vector& input);

    void setLearningRate(double learning_rate);

    double getError(const Vector& predicted, const Vector& expected);
    double getError(const std::vector<Vector>& predicted, const std::vector<Vector>& expected);
};
