#pragma once
#include "Activation.h"
#include "Layer.h"
#include <cstdint>

class DenseLayer : public Layer {
    const Activation& activation;
    double*           hidden_neurons;
    double*           bias;
    double*           weights;
    int		          num_inputs, num_outputs;

public:
    DenseLayer(int num_outputs, const Activation& activation = Linear());
    ~DenseLayer();

    void setNumInputs(int num_inputs);
    void randomizeWeights();

    int get_num_neurons_input() override { return num_inputs; }
    int get_num_neurons_output() override { return num_outputs; }
    const double* get_hidden_neurons() override { return hidden_neurons; }

    void process_layer(Layer* prev_layer);
};
