#include "DenseLayer.h"
#include "InputLayer.h"
#include "Model.h"
#include "Vector.h"
#include <algorithm>
#include <array>
#include <bitset>
#include <format>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

constexpr int num_inputs  = 1;
constexpr int num_outputs = 3;
constexpr int epochs      = 100'000;

int main() {
    Sigmoid activation = Sigmoid();

    std::vector<Layer*> layers = {{
        new InputLayer(num_inputs),
        new DenseLayer(7, activation),
        new DenseLayer(num_outputs, activation),
    }};
    Model model = Model(layers);
    model.setLearningRate(0.1);

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

    double error = 0;
    for (Vector& vec : x_train) {
        Vector result = model.evaluate(vec);

         std::string result_str = std::accumulate(
            std::next(result.begin()),
            result.end(),
            std::format("{:.1f}", result[0]),
            [](const std::string& acc, double x) {
                return acc + ", " + std::format("{:.1f}", x);
            }
         );

         double error_example = model.getError(result, y_train[vec[0]]);
         error += pow(error_example, 2) / 8;

         std::cout << vec[0] << ": [ " << result_str << " ], error: " << error_example << '\n';
    }

    std::cout << "MSE: " << error << '\n';
}
