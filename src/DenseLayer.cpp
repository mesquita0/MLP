#include "DenseLayer.h"
#include <random>

DenseLayer::DenseLayer(int num_outputs, const Activation& activation) : activation(activation) {
    this->num_inputs = 0;
    this->num_outputs = num_outputs;

    hidden_neurons = new double[num_outputs];
    bias	       = new double[num_outputs];
    weights        = nullptr;
}

DenseLayer::~DenseLayer() {
    delete hidden_neurons;
    delete bias;
    delete weights;
}

void DenseLayer::setNumInputs(int num_inputs) {
    this->num_inputs = num_inputs;
    weights = new double[num_inputs * num_outputs];
}

void DenseLayer::randomizeWeights() {
    double lower_bound = -1;
    double upper_bound = 1;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;

    // Initialize random weights and bias
    for (int i = 0; i < num_outputs; i++) {
        bias[i] = unif(re);
        double* weights_output = &weights[i * num_outputs];

        for (int j = 0; j < num_inputs; j++) {
            weights_output[j] = unif(re);
        }
    }
}

void DenseLayer::process_layer(Layer* prev_layer) {
    const double* input  = prev_layer->get_hidden_neurons();
    double* output       = hidden_neurons;

    for (int i = 0; i < num_outputs; i++) {
        output[i] = bias[i];
        double* weights_output = &weights[i * num_outputs];

        for (int j = 0; j < num_inputs; j++) {
            output[i] += input[j] * weights_output[j];
        }

        output[i] = activation.activation(output[i]);
    }
}
