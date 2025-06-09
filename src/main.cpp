#include "DenseLayer.h"
#include "InputLayer.h"
#include "Model.h"
#include "Vector.h"
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

constexpr int num_inputs  = 1;
constexpr int num_outputs = 3;
constexpr int epochs      = 100000;

int main() {
    std::vector<Layer*> layers = {{
        new InputLayer(num_inputs),
        new DenseLayer(8, Sigmoid()),
        new DenseLayer(num_outputs, Sigmoid()),
    }};
    Model model = Model(layers);
    model.setLearningRate(0.05);

    std::vector<Vector> x_train = {};
    std::vector<Vector> y_train = {};

    std::vector<double> tmp = {};
    for (int i = 0; i < 8; i++) {
        // Add input example
        Vector x(1);
        x[0] = i;
        x_train.push_back(x);

        // Add output example
        std::bitset<num_outputs> bs(i);
        for (int j = 0; j < num_outputs; j++) tmp.push_back(bs[j]);
        y_train.emplace_back(tmp);

        tmp.clear();
    }

    model.fit(x_train, y_train, epochs);

    for (Vector& vec : x_train) {
        Vector result = model.evaluate(vec);

         std::string result_str = std::accumulate(
            std::next(result.begin()),
            result.end(),
            std::to_string(result[0]),
            [](const std::string& acc, double x) {
                return acc + ", " + std::to_string(x);
            }
        );

         std::cout << vec[0] << ": [ " << result_str << " ], error: " << model.getError(result, y_train[vec[0]]) << '\n';
    }
}
