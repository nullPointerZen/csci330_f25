#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

class SortingAlgorithms {
public:
    // TODO: Implement bubble sort algorithm
    static void bubbleSort(std::vector<int>& arr);
    
    // TODO: Implement selection sort algorithm
    static void selectionSort(std::vector<int>& arr);
    
    // TODO: Implement insertion sort algorithm
    static void insertionSort(std::vector<int>& arr);
    
    // TODO: Create a function to generate random array
    static std::vector<int> generateRandomArray(int size, int min = 1, int max = 1000);
    
    // TODO: Create a function to measure sorting time
    template<typename SortFunc>
    static double measureSortTime(SortFunc sortFunction, std::vector<int> arr);
    
    // TODO: Create a function to verify if array is sorted
    static bool isSorted(const std::vector<int>& arr);
};

int main() {
    // TODO: Create arrays of different sizes (100, 1000, 5000)
    
    // TODO: Test all three sorting algorithms on each array size
    
    // TODO: Measure and compare execution times
    
    // TODO: Display results in a formatted table
    
    // TODO: Verify that each sorted array is correctly sorted
    
    // BONUS TODO: Implement quicksort and add to comparison
    
    return 0;
}