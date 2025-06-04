#include "DenseLayer.h"
#include <random>

DenseLayer::DenseLayer(int num_outputs, const Activation& activation) : activation(activation) {
    this->num_inputs = 0;
    this->num_outputs = num_outputs;

    hidden_neurons = Vector(num_outputs);
    bias	       = Vector(num_outputs);
    weights        = Matrix();
}

void DenseLayer::setNumInputs(int num_inputs) {
    this->num_inputs = num_inputs;
    weights = Matrix(num_inputs, num_outputs);
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
    hidden_neurons = weights * prev_layer->get_hidden_neurons() + bias;
    hidden_neurons.apply(activation);
}

void backpropagate(Layer* prev_layer, Layer* next_layer, const Vector& hessian, double learning_rate) {

}
