#pragma once

class Layer {
public:
    virtual const double*  get_hidden_neurons()              = 0;
    virtual int            get_num_neurons_input()           = 0;
    virtual int            get_num_neurons_output()          = 0;
    virtual void           process_layer(Layer* prev_layer)  = 0;
};
