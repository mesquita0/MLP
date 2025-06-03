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

void Model::fit(const double* x_train, const double* y_train, int num_training_examples, int num_epochs) {
    for (int i = 0; i < num_epochs; i++) {
        for (int j = 0; i < num_training_examples; i++) {
            const double* x_example = x_train + j * num_training_examples;
            const double* y_example = y_train + j * num_training_examples;

            evaluate(x_example);
            
            double error = getError(last_layer->get_hidden_neurons(), y_example, 1);

            // TODO: Backpropagation

        }
    }
}

std::vector<double> Model::evaluate(const double* input) {
    first_layer->set_neurons(input);
    first_layer->process_layer(nullptr);

    for (int i = 1; i < layers.size(); i++) {
        layers[i]->process_layer(layers[i - 1]);
    }

    const double* neurons = last_layer->get_hidden_neurons();

    std::vector<double> result(neurons, neurons + last_layer->get_num_neurons_output());

    return result;
}

void Model::setErrorFunction(double (*error_func)(double, int)) {
    this->error_func = error_func;
}

double Model::getError(const double* predicted, const double* expected, int num_examples) {
    double error = 0;
    
    for (int i = 0; i < num_examples; i++) {
        int n = last_layer->get_num_neurons_output();
        const double* pred_example = predicted + i * n;
        const double* expt_example = expected  + i * n;

        // ||y_i - y^_i||**2 = <(y_i - y^_i), (y_i - y^_i)>
        double error_example = 0;
        for (int j = 0; j < n; j++)
            error_example += pow((pred_example - expt_example), 2);
        
        error += error_func(error_example, num_examples);
    }

    return error;
}

double MSE(double error, int n) {
    return pow(error, 2) / n;
}

double MAE(double error, int n) {
    return abs(error) / n;
}
