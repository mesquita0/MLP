#include "Model.h"
#include "InputLayer.h"
#include "DenseLayer.h"
#include <vector>

Model::Model(std::vector<Layer*>& layers) {
    this->layers = {};

    for (Layer* layer : layers) {
        add(layer);
    }
}

Model::~Model() {
    for (Layer* layer : layers)
        delete layer;
}

void Model::add(Layer* layer) {
    // First layer (only) must be input layer
    if (
        layers.size() == 0 && dynamic_cast<InputLayer*>(layer) == nullptr ||
        layers.size() != 0 && dynamic_cast<InputLayer*>(layer) != nullptr
    ) {
        throw;
    }

    if (layers.size() == 0) {
        first_layer = dynamic_cast<InputLayer*>(layer);
    }
    else {
        DenseLayer* dense_layer = dynamic_cast<DenseLayer*>(layer);
        dense_layer->setNumInputs(last_layer->get_num_neurons_output());
        dense_layer->randomizeWeights();
    }

    last_layer = layer;

    this->layers.push_back(layer);
}

void Model::fit(const std::vector<Vector>& x_train, const std::vector<Vector>& y_train, int num_epochs) {
    for (int i = 0; i < num_epochs; i++) {
        for (int j = 0; j < x_train.size(); j++) {
            const Vector x_example = x_train[j];
            const Vector y_example = y_train[j];

            evaluate(x_example);
            
            // Backpropagation
            // J(y, y^)  = ||y - y^||**2
            // => dJ/dy^ = -2(y - y^) = 2(y^ - y) 
            Vector hessian = (last_layer->get_hidden_neurons() - y_example) * 2;

            last_layer->backpropagate(layers[layers.size() - 2], nullptr, hessian, learning_rate);

            for (int k = layers.size() - 2; k > 0; k--) {
                layers[k]->backpropagate(layers[k - 1], dynamic_cast<DenseLayer*>(layers[k + 1]), hessian, learning_rate);
            }
        }
    }
}

Vector Model::evaluate(const Vector& input) {
    first_layer->set_neurons(input);
    first_layer->process_layer(nullptr);

    for (int i = 1; i < layers.size(); i++) {
        layers[i]->process_layer(layers[i - 1]);
    }

    return last_layer->get_hidden_neurons();
}

void Model::setLearningRate(double learning_rate) {
    this->learning_rate = learning_rate;
}

double Model::getError(const Vector& predicted, const Vector& expected) {
    // ||y_i - y^_i||**2 = <(y_i - y^_i), (y_i - y^_i)>
    Vector diff = expected - predicted;
    return diff.inner(diff);
}

double Model::getError(const std::vector<Vector>& predicted, const std::vector<Vector>& expected) {
    double error = 0;

    for (int i = 0; i < predicted.size(); i++) {
        error += getError(predicted[i], expected[i]);
    }

    return error;
}
