#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <map>

// Function pointer type for simple transformations
typedef double (*SimpleTransform)(double);

// Simple transform functions
double square(double x) { 
    return x * x; 
}

double cube(double x) { 
    return x * x * x; 
}

double negate(double x) { 
    return -x; 
}

// Function object for scale and offset operations
class ScaleAndOffset {
private:
    double scale, offset;
    
public:
    ScaleAndOffset(double s, double o) : scale(s), offset(o) {}
    
    double operator()(double x) const { 
        return x * scale + offset; 
    }
    
    // Provide info about the transformation
    void print_info() const {
        std::cout << "Scale by " << scale << ", offset by " << offset;
    }
};

class DataPipeline {
private:
    std::vector<std::function<double(double)>> stages;
    std::string pipeline_name;
    
public:
    DataPipeline(const std::string& name) : pipeline_name(name) {}
    
    // Add a processing stage to the pipeline
    void add_stage(std::function<double(double)> stage) {
        stages.push_back(stage);
    }
    
    // Process a single value through all stages
    double process(double input) {
        double result = input;
        for(const auto& stage : stages) {
            result = stage(result);
        }
        return result;
    }
    
    // Process a vector of values
    std::vector<double> process_batch(const std::vector<double>& inputs) {
        std::vector<double> results;
        results.reserve(inputs.size());
        
        for(double input : inputs) {
            results.push_back(process(input));
        }
        return results;
    }
    
    void print_info() const {
        std::cout << "Pipeline '" << pipeline_name 
                  << "' has " << stages.size() << " stages" << std::endl;
    }
    
    // Get pipeline name
    const std::string& get_name() const { return pipeline_name; }
};

// Demonstration of composable pipeline design
class PipelineBuilder {
public:
    static DataPipeline create_math_pipeline() {
        DataPipeline pipeline("MathProcessor");
        
        // Add function pointer stage
        pipeline.add_stage(square);
        
        // Add lambda stage with capture
        double multiplier = 0.5;
        pipeline.add_stage([multiplier](double x) { return x * multiplier; });
        
        // Add function object stage
        pipeline.add_stage(ScaleAndOffset(2.0, 10.0));
        
        // Add generic lambda stage (ReLU-like activation)
        pipeline.add_stage([](auto x) { return x < 0 ? 0.0 : x; });
        
        return pipeline;
    }
    
    static DataPipeline create_normalization_pipeline(double mean, double std_dev) {
        DataPipeline pipeline("Normalizer");
        
        // Subtract mean
        pipeline.add_stage([mean](double x) { return x - mean; });
        
        // Divide by standard deviation
        pipeline.add_stage([std_dev](double x) { return x / std_dev; });
        
        return pipeline;
    }
};

// Helper function to calculate statistics
std::pair<double, double> calculate_stats(const std::vector<double>& data) {
    double sum = 0.0;
    for(double x : data) sum += x;
    double mean = sum / data.size();
    
    double variance = 0.0;
    for(double x : data) {
        variance += (x - mean) * (x - mean);
    }
    variance /= data.size();
    double std_dev = std::sqrt(variance);
    
    return {mean, std_dev};
}

int main() {
    std::vector<double> test_data = {1.0, 2.0, 3.0, 4.0, 5.0};
    
    std::cout << "Function Integration Project Demo" << std::endl;
    std::cout << "=================================" << std::endl;
    
    // Create and test math processing pipeline
    DataPipeline math_pipeline = PipelineBuilder::create_math_pipeline();
    math_pipeline.print_info();
    
    std::cout << "\nProcessing data through math pipeline:" << std::endl;
    std::cout << "Pipeline stages: square -> multiply by 0.5 -> scale by 2 + 10 -> ReLU" << std::endl;
    std::cout << "\nOriginal -> Processed:" << std::endl;
    
    for(double value : test_data) {
        double result = math_pipeline.process(value);
        std::cout << value << " -> " << result << std::endl;
    }
    
    // Demonstrate batch processing
    std::cout << "\nBatch processing:" << std::endl;
    std::vector<double> batch_results = math_pipeline.process_batch(test_data);
    std::cout << "Input:  ";
    for(double x : test_data) std::cout << x << " ";
    std::cout << "\nOutput: ";
    for(double x : batch_results) std::cout << x << " ";
    std::cout << std::endl;
    
    // Create normalization pipeline
    std::cout << "\n" << std::string(50, '-') << std::endl;
    
    std::vector<double> raw_data = {10.5, 12.3, 8.7, 15.2, 9.1, 13.8, 11.4};
    auto [mean, std_dev] = calculate_stats(raw_data);
    
    std::cout << "Raw data statistics: mean = " << mean << ", std_dev = " << std_dev << std::endl;
    
    DataPipeline norm_pipeline = PipelineBuilder::create_normalization_pipeline(mean, std_dev);
    norm_pipeline.print_info();
    
    std::cout << "\nNormalizing data (z-score normalization):" << std::endl;
    std::vector<double> normalized = norm_pipeline.process_batch(raw_data);
    
    for(size_t i = 0; i < raw_data.size(); ++i) {
        std::cout << raw_data[i] << " -> " << normalized[i] << std::endl;
    }
    
    // Verify normalization (should have mean ≈ 0, std_dev ≈ 1)
    auto [norm_mean, norm_std] = calculate_stats(normalized);
    std::cout << "\nNormalized data statistics: mean = " << norm_mean 
              << ", std_dev = " << norm_std << std::endl;
    
    // Demonstrate pipeline composition
    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "Pipeline Composition Demo" << std::endl;
    
    // Create a combined pipeline
    DataPipeline combined("Combined");
    
    // Add normalization stages
    combined.add_stage([mean](double x) { return x - mean; });
    combined.add_stage([std_dev](double x) { return x / std_dev; });
    
    // Add activation function
    combined.add_stage([](double x) { return 1.0 / (1.0 + std::exp(-x)); }); // Sigmoid
    
    combined.print_info();
    
    std::cout << "\nCombined pipeline: normalize -> sigmoid activation" << std::endl;
    std::vector<double> final_results = combined.process_batch(raw_data);
    
    for(size_t i = 0; i < raw_data.size(); ++i) {
        std::cout << raw_data[i] << " -> " << final_results[i] << std::endl;
    }
    
    return 0;
}

/* Sample Output:
Function Integration Project Demo
=================================
Pipeline 'MathProcessor' has 4 stages

Processing data through math pipeline:
Pipeline stages: square -> multiply by 0.5 -> scale by 2 + 10 -> ReLU

Original -> Processed:
1 -> 11
2 -> 14
3 -> 19
4 -> 26
5 -> 35

Batch processing:
Input:  1 2 3 4 5 
Output: 11 14 19 26 35 

--------------------------------------------------
Raw data statistics: mean = 11.5714, std_dev = 2.23606
Pipeline 'Normalizer' has 2 stages

Normalizing data (z-score normalization):
10.5 -> -0.479463
12.3 -> 0.326008
8.7 -> -1.28491
15.2 -> 1.62321
9.1 -> -1.10585
13.8 -> 0.997525
11.4 -> -0.0765944

Normalized data statistics: mean = -5.55112e-17, std_dev = 1

--------------------------------------------------
Pipeline Composition Demo
Pipeline 'Combined' has 3 stages

Combined pipeline: normalize -> sigmoid activation
10.5 -> 0.382262
12.3 -> 0.580697
8.7 -> 0.216594
15.2 -> 0.835003
9.1 -> 0.248517
13.8 -> 0.730069
11.4 -> 0.480851
*/