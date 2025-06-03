#pragma once
#include "Layer.h"

class InputLayer : public Layer {
    double* neurons;
    int num_inputs;

public:
    InputLayer(int num_inputs);
    ~InputLayer();
    
    int get_num_neurons_input() override { return num_inputs; }
    int get_num_neurons_output() override { return num_inputs; }
    inline const double* get_hidden_neurons() override { return neurons; }

    void set_neurons(const double* input);

    inline void process_layer(Layer* prev_layer) override { return; }
};
