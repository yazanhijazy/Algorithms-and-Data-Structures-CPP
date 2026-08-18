#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using Clock = std::chrono::high_resolution_clock;

void insertionSort(std::vector<int>& values) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        const int key = values[i];
        std::size_t j = i;

        while (j > 0 && values[j - 1] > key) {
            values[j] = values[j - 1];
            --j;
        }
        values[j] = key;
    }
}

void heapify(std::vector<int>& values, std::size_t heapSize, std::size_t root) {
    std::size_t largest = root;
    const std::size_t left = 2 * root + 1;
    const std::size_t right = 2 * root + 2;

    if (left < heapSize && values[left] > values[largest]) {
        largest = left;
    }
    if (right < heapSize && values[right] > values[largest]) {
        largest = right;
    }

    if (largest != root) {
        std::swap(values[root], values[largest]);
        heapify(values, heapSize, largest);
    }
}

void heapSort(std::vector<int>& values) {
    const std::size_t n = values.size();
    if (n < 2) {
        return;
    }

    for (std::size_t i = n / 2; i-- > 0;) {
        heapify(values, n, i);
    }

    for (std::size_t i = n; i-- > 1;) {
        std::swap(values[0], values[i]);
        heapify(values, i, 0);
    }
}

std::vector<int> generateRandomArray(std::size_t size, std::mt19937& generator) {
    std::uniform_int_distribution<int> distribution(0, 9999);
    std::vector<int> values(size);

    for (int& value : values) {
        value = distribution(generator);
    }
    return values;
}

std::vector<int> generateSortedArray(std::size_t size) {
    std::vector<int> values(size);
    std::iota(values.begin(), values.end(), 0);
    return values;
}

template <typename SortFunction>
double measureMilliseconds(std::vector<int> values, SortFunction sortFunction) {
    const auto start = Clock::now();
    sortFunction(values);
    const auto stop = Clock::now();

    if (!std::is_sorted(values.begin(), values.end())) {
        throw std::runtime_error("Sorting algorithm produced an invalid result.");
    }

    return std::chrono::duration<double, std::milli>(stop - start).count();
}

void testSortingPerformance(const std::vector<std::size_t>& sizes, bool sortedInput,
                            std::mt19937& generator) {
    std::cout << std::left << std::setw(14) << "Input Size"
              << std::setw(27) << "Insertion Sort (ms)"
              << "Heap Sort (ms)\n";
    std::cout << std::string(58, '-') << '\n';

    for (const std::size_t size : sizes) {
        const std::vector<int> input = sortedInput
            ? generateSortedArray(size)
            : generateRandomArray(size, generator);

        const double insertionTime = measureMilliseconds(input, insertionSort);
        const double heapTime = measureMilliseconds(input, heapSort);

        std::cout << std::left << std::setw(14) << size
                  << std::setw(27) << std::fixed << std::setprecision(3) << insertionTime
                  << heapTime << '\n';
    }
}

int main() {
    const std::vector<std::size_t> sizes = {10, 100, 1000, 10000, 100000};
    std::mt19937 generator(42); // Fixed seed keeps benchmark input reproducible.

    std::cout << "Testing on random arrays:\n";
    testSortingPerformance(sizes, false, generator);

    std::cout << "\nTesting on already sorted arrays:\n";
    testSortingPerformance(sizes, true, generator);

    return 0;
}
