#pragma once
#include "Vector.h"

class Layer {
public:
    virtual const Vector&  get_hidden_neurons()             = 0;
    virtual int            get_num_neurons_input()          = 0;
    virtual int            get_num_neurons_output()         = 0;
    virtual void           process_layer(Layer* prev_layer) = 0;
    virtual void           backpropagate(Layer* prev_layer, Layer* next_layer, const Vector& hessian, double learning_rate) = 0;
};
