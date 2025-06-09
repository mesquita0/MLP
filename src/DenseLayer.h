#pragma once
#include "Activation.h"
#include "Layer.h"
#include "Matrix.h"
#include "Vector.h"
#include <cstdint>

class DenseLayer : public Layer {
    const Activation& activation;
    Vector            hidden_neurons;
    Vector            pre_act_neurons;
    Vector            bias;
    Matrix            weights;
    int		          num_inputs, num_outputs;

public:
    DenseLayer(int num_outputs, const Activation& activation = Linear());

    void setNumInputs(int num_inputs);
    void randomizeWeights();

    int get_num_neurons_input() override { return num_inputs; }
    int get_num_neurons_output() override { return num_outputs; }
    const Vector& get_hidden_neurons() override { return hidden_neurons; }
    const Matrix& getWeights() { return weights; }

    void process_layer(Layer* prev_layer);

    void backpropagate(Layer* prev_layer, Layer* next_layer, Vector& hessian, double learning_rate);
};
