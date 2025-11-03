#include <iostream>
#include <vector>

// Comparison function type - returns true if first should come before second
typedef bool (*Comparator)(int a, int b);

// Comparison functions
bool ascending(int a, int b) {
    return a < b;
}

bool descending(int a, int b) {
    return a > b;
}

// Simple bubble sort with custom comparator
void sort_with_comparator(std::vector<int>& data, Comparator comp) {
    int n = data.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!comp(data[j], data[j + 1])) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

void print_vector(const std::vector<int>& data) {
    for (int n : data) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};

    std::cout << "Original: ";
    print_vector(numbers);

    std::vector<int> asc = numbers;
    sort_with_comparator(asc, ascending);
    std::cout << "Sorted Ascending: ";
    print_vector(asc);

    std::vector<int> desc = numbers;
    sort_with_comparator(desc, descending);
    std::cout << "Sorted Descending: ";
    print_vector(desc);

    return 0;
}