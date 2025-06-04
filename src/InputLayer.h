#pragma once
#include "Layer.h"
#include "Vector.h"

class InputLayer : public Layer {
    Vector neurons;

public:
    InputLayer(int num_inputs);
    
    int get_num_neurons_input() override { return neurons.getSize(); }
    int get_num_neurons_output() override { return neurons.getSize(); }
    inline const Vector& get_hidden_neurons() override { return neurons; }

    void set_neurons(const Vector& input);

    inline void process_layer(Layer* prev_layer) override { return; }

    inline void backpropagate(Layer* prev_layer, Layer* next_layer, const Vector& hessian, double learning_rate) { return; }
};
