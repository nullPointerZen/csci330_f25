#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    // Generic lambda for printing with custom format
    auto printer = [](const auto& item, const std::string& prefix = "") {
        std::cout << prefix << item << " ";
    };

    // Generic lambda for comparison
    auto less_than = [](const auto& a, const auto& b) {
        return a < b;
    };

    // Generic lambda for transformation (works for numbers and strings)
    auto doubler = [](auto item) {
        if constexpr (std::is_arithmetic_v<decltype(item)>) {
            return item * 2;
        } else {
            return item + item;
        }
    };

    // Test with integers
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Original numbers: ";
    std::for_each(numbers.begin(), numbers.end(),
                  [&printer](const auto& n) { printer(n); });
    std::cout << "\n";

    std::vector<int> doubled_numbers;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(doubled_numbers), doubler);
    std::cout << "Doubled numbers: ";
    std::for_each(doubled_numbers.begin(), doubled_numbers.end(),
                  [&printer](const auto& n) { printer(n); });
    std::cout << "\n";

    // Test with strings
    std::vector<std::string> words = {"hello", "world", "cpp", "lambda"};
    std::cout << "Original words: ";
    std::for_each(words.begin(), words.end(),
                  [&printer](const auto& w) { printer(w); });
    std::cout << "\n";

    std::vector<std::string> doubled_words;
    std::transform(words.begin(), words.end(), std::back_inserter(doubled_words), doubler);
    std::cout << "Doubled words: ";
    std::for_each(doubled_words.begin(), doubled_words.end(),
                  [&printer](const auto& w) { printer(w); });
    std::cout << "\n";

    // Test comparison with different types
    std::cout << "5 < 10: " << less_than(5, 10) << "\n";
    std::cout << "hello < world: " << less_than(std::string("hello"), std::string("world")) << "\n";

    // Use generic comparison with std::sort
    std::sort(numbers.begin(), numbers.end(), less_than);
    std::cout << "Sorted numbers: ";
    std::for_each(numbers.begin(), numbers.end(),
                  [&printer](const auto& n) { printer(n); });
    std::cout << "\n";

    std::sort(words.begin(), words.end(), less_than);
    std::cout << "Sorted words: ";
    std::for_each(words.begin(), words.end(),
                  [&printer](const auto& w) { printer(w); });
    std::cout << "\n";

    return 0;
}