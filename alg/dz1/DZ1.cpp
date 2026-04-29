#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <utility>

// Функция для замера времени выполнения другой функции
template <typename Func, typename... Args>
auto measureExecutionTime(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();
    auto result = func(std::forward<Args>(args)...);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    return std::make_pair(result, duration.count());
}

// Добавляем элемент в конец массива n раз
long long appendQueueVector(int n) {
    std::vector<int> q;
    size_t head = 0;
    for (int i = 0; i < n; ++i) {
        q.push_back(i);
    }
    return q.capacity() * sizeof(int);
}


int main() {
    std::vector<int> sizes = { 10, 100, 1000, 10000, 100000, 1000000, 10000000, 50000000, 100000000, 500000000, 1000000000 };

    // Выравниваем
    std::cout << std::left;
    std::cout << std::setw(15) << "Size"
        << std::setw(15) << "Total (sec)"
        << std::setw(15) << "Per op (ns)"
        << std::setw(20) << "Memory (bytes)"
        << std::endl;

    std::cout << std::string(65, '-') << std::endl;

    for (int size : sizes) {
        auto [mem, t] = measureExecutionTime(appendQueueVector, size);
        double totalSec = t / 1e9;
        double perOpNs = static_cast<double>(t) / size;

        std::cout << std::setw(15) << size << std::setw(15) << std::fixed << std::setprecision(6) << totalSec 
            << std::setw(15) << std::setprecision(3) << perOpNs << std::setw(15) << mem << std::endl;
    }

    return 0;
}