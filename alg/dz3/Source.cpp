#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <type_traits>

using namespace std;

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args)
-> typename enable_if<!is_void<decltype(func(forward<Args>(args)...))>::value, long long>::type
{
    auto start_time = chrono::high_resolution_clock::now();
    auto result = func(forward<Args>(args)...);
    auto end_time = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    return duration.count();
}

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args)
-> typename enable_if<is_void<decltype(func(forward<Args>(args)...))>::value, long long>::type
{
    auto start_time = chrono::high_resolution_clock::now();
    func(forward<Args>(args)...);
    auto end_time = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    return duration.count();
}

vector<int>& InsertionSort(vector<int>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        int current = vec[i];
        int j = static_cast<int>(i) - 1;

        while (j >= 0 && vec[j] > current) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = current;
    }
    return vec;
}

vector<int>& RadixSort(vector<int>& vec) {
    if (vec.empty()) return vec;

    int maxValue = *max_element(vec.begin(), vec.end());
    vector<vector<int>> buckets(10);

    for (int Rad = 1; maxValue / Rad > 0; Rad *= 10) {
        for (int value : vec) {
            buckets[(value / Rad) % 10].push_back(value);
        }
        size_t index = 0;
        for (auto& bucket : buckets) {
            for (int value : bucket) {
                vec[index++] = value;
            }
            bucket.clear();
        }
    }
    return vec;
}

int Partition(vector<int>& vec, int low, int high) {
    int pivot = vec[high];
    int i = low;

    for (int j = low; j < high; ++j) {
        if (vec[j] <= pivot) {
            swap(vec[i], vec[j]);
            ++i;
        }
    }
    swap(vec[i], vec[high]);
    return i;
}

void QuickSort(vector<int>& vec, int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(vec, low, high);
        QuickSort(vec, low, pivotIndex - 1);
        QuickSort(vec, pivotIndex + 1, high);
    }
}

vector<int> make_vector(size_t n) {
    vector<int> vec(n);
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = rand() % 1000000;
    }
    return vec;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    size_t sizes[] = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };

    cout << "--- Insertion Sort ---" << endl;
    for (size_t n : sizes) {
        vector<int> vec = make_vector(n);
        auto time_ms = measure_execution_time(InsertionSort, vec);
        cout << "Razmer " << n << ": " << time_ms << " mc" << endl;
    }

    cout << "\n--- Radix Sort ---" << endl;
    for (size_t n : sizes) {
        vector<int> vec = make_vector(n);
        auto time_ms = measure_execution_time(RadixSort, vec);
        cout << "Razmer " << n << ": " << time_ms << " mc" << endl;
    }

    cout << "\n--- Quick Sort ---" << endl;
    for (size_t n : sizes) {
        vector<int> vec = make_vector(n);
        auto time_ms = measure_execution_time([&]() {
            if (!vec.empty()) {
                QuickSort(vec, 0, static_cast<int>(vec.size()) - 1);
            }
            });
        cout << "Razmer " << n << ": " << time_ms << " mc" << endl;
    }

    return 0;
}