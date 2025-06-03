#include "InputLayer.h"
#include <algorithm>

InputLayer::InputLayer(int num_inputs) {
    this->num_inputs = num_inputs;

    neurons = new double[num_inputs];
}

InputLayer::~InputLayer() {
    delete neurons;
}

void InputLayer::set_neurons(const double* input) {
    std::copy(input, input + num_inputs, neurons);
}
