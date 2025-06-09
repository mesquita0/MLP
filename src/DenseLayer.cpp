#include "DenseLayer.h"
#include <random>

DenseLayer::DenseLayer(int num_outputs, const Activation& activation) : activation(activation) {
    this->num_inputs = 0;
    this->num_outputs = num_outputs;

    hidden_neurons  = Vector(num_outputs);
    pre_act_neurons = Vector(num_outputs);
    bias	        = Vector(num_outputs);
    weights         = Matrix();
}

void DenseLayer::setNumInputs(int num_inputs) {
    this->num_inputs = num_inputs;
    weights = Matrix(num_outputs, num_inputs);
}

void DenseLayer::randomizeWeights() {
    std::uniform_real_distribution<double> unif(-1, 1);
    std::default_random_engine re;

    // Initialize random weights and bias
    for (int i = 0; i < num_outputs; i++) {
        bias[i] = unif(re);

        for (int j = 0; j < num_inputs; j++) {
            weights(i, j) = unif(re);
        }
    }
}

void DenseLayer::process_layer(Layer* prev_layer) {
    pre_act_neurons = weights * prev_layer->get_hidden_neurons() + bias;
    hidden_neurons.copy(pre_act_neurons);
    activation.applyActivation(hidden_neurons);
}

void DenseLayer::backpropagate(Layer* prev_layer, Layer* next_layer, Vector& hessian, double learning_rate) {
    DenseLayer* next_dlayer;
    if ((next_dlayer = dynamic_cast<DenseLayer*>(next_layer)) != nullptr) {
        hessian = next_dlayer->getWeights().transpose() * hessian;
    }

    activation.applyDerivative(pre_act_neurons);
    hessian = hessian.hadamard(pre_act_neurons);

    // Update bias
    bias = bias - hessian * learning_rate;

    // Update weights
    Matrix delta = hessian.outer(prev_layer->get_hidden_neurons());
    weights = weights - delta * learning_rate;
}
