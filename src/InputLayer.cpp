#include "InputLayer.h"

InputLayer::InputLayer(int num_inputs) {
    neurons = Vector(num_inputs);
}

void InputLayer::set_neurons(const Vector& input) {
    for (int i = 0; i < neurons.getSize(); i++) {
        neurons[i] = input[i];
    }
}
