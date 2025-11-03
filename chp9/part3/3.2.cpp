#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <map>

// Function pointer type for simple transformations
typedef double (*SimpleTransform)(double);

// Simple transform functions
double square(double x) { return x * x; }
double cube(double x) { return x * x * x; }
double negate(double x) { return -x; }

// Pipeline stage function object
class ScaleAndOffset {
private:
    double scale, offset;

public:
    ScaleAndOffset(double s, double o) : scale(s), offset(o) {}
    double operator()(double x) const {
        return x * scale + offset;
    }
};

class DataPipeline {
private:
    std::vector<std::function<double(double)>> stages;
    std::string pipeline_name;

public:
    DataPipeline(const std::string& name) : pipeline_name(name) {}

    void add_stage(std::function<double(double)> stage) {
        stages.push_back(stage);
    }

    double process(double input) {
        double result = input;
        for (const auto& stage : stages) {
            result = stage(result);
        }
        return result;
    }

    std::vector<double> process_batch(const std::vector<double>& inputs) {
        std::vector<double> results;
        for (double val : inputs) {
            results.push_back(process(val));
        }
        return results;
    }

    void print_info() const {
        std::cout << "Pipeline '" << pipeline_name
                  << "' has " << stages.size() << " stages\n";
    }
};

int main() {
    std::vector<double> test_data = {1.0, 2.0, 3.0, 4.0, 5.0};

    DataPipeline pipeline("MathProcessor");

    // Add function pointer stage
    pipeline.add_stage(square);

    // Add lambda stage
    double multiplier = 0.5;
    pipeline.add_stage([multiplier](double x) { return x * multiplier; });

    // Add function object stage
    pipeline.add_stage(ScaleAndOffset(2.0, 10.0));

    // Add generic lambda stage
    pipeline.add_stage([](auto x) { return x < 0 ? 0 : x; }); // ReLU-like

    pipeline.print_info();

    std::cout << "\nProcessing data through pipeline:\n";

    std::cout << "\nOriginal -> Processed:\n";
    for (double value : test_data) {
        double result = pipeline.process(value);
        std::cout << value << " -> " << result << "\n";
    }

    return 0;
}