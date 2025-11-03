#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

class StatisticsAccumulator {
private:
    int count;
    double sum;
    double sum_squares;
    double min_val;
    double max_val;

public:
    StatisticsAccumulator()
        : count(0), sum(0.0), sum_squares(0.0), min_val(INFINITY), max_val(-INFINITY) {}

    void operator()(double value) {
        ++count;
        sum += value;
        sum_squares += value * value;
        if (value < min_val) min_val = value;
        if (value > max_val) max_val = value;
    }

    double get_mean() const {
        return count > 0 ? sum / count : 0.0;
    }

    double get_variance() const {
        return count > 0 ? (sum_squares / count) - std::pow(get_mean(), 2) : 0.0;
    }

    double get_std_dev() const {
        return std::sqrt(get_variance());
    }

    double get_min() const { return min_val; }
    double get_max() const { return max_val; }
    int get_count() const { return count; }

    void reset() {
        count = 0;
        sum = 0.0;
        sum_squares = 0.0;
        min_val = INFINITY;
        max_val = -INFINITY;
    }
};

class HistogramBuilder {
private:
    double min_val;
    double max_val;
    int num_bins;
    std::vector<int> bins;

public:
    HistogramBuilder(double min_val, double max_val, int num_bins)
        : min_val(min_val), max_val(max_val), num_bins(num_bins), bins(num_bins, 0) {}

    void operator()(double value) {
        if (value < min_val || value > max_val) return;
        int bin_index = static_cast<int>((value - min_val) / (max_val - min_val) * num_bins);
        if (bin_index == num_bins) bin_index = num_bins - 1;
        ++bins[bin_index];
    }

    void print_histogram() const {
        double bin_width = (max_val - min_val) / num_bins;
        for (int i = 0; i < num_bins; ++i) {
            double bin_start = min_val + i * bin_width;
            double bin_end = bin_start + bin_width;
            std::cout << std::fixed << std::setprecision(1)
                      << "[" << bin_start << ", " << bin_end << "): "
                      << std::string(bins[i], '*') << " (" << bins[i] << ")\n";
        }
    }
};

int main() {
    std::vector<double> data = {
        23.5, 45.2, 12.8, 67.1, 34.6, 89.3, 56.7, 78.9,
        43.2, 29.1, 65.4, 87.6, 54.3, 32.8, 76.5
    };

    std::cout << "Processing " << data.size() << " data points:\n";

    StatisticsAccumulator stats;
    std::for_each(data.begin(), data.end(), std::ref(stats));

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nStatistics:\n";
    std::cout << "Count: " << stats.get_count() << "\n";
    std::cout << "Mean: " << stats.get_mean() << "\n";
    std::cout << "Variance: " << stats.get_variance() << "\n";
    std::cout << "Standard Deviation: " << stats.get_std_dev() << "\n";
    std::cout << "Min: " << stats.get_min() << "\n";
    std::cout << "Max: " << stats.get_max() << "\n";

    HistogramBuilder histogram(0, 100, 10);
    std::for_each(data.begin(), data.end(), std::ref(histogram));

    std::cout << "\nHistogram:\n";
    histogram.print_histogram();

    return 0;
}