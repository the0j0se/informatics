#include <iostream>
#include <vector>
#include <chrono>

double scalar_product(const std::vector<double>& a,
    const std::vector<double>& b)
{
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i)
        sum += a[i] * b[i];
    return sum;
}

void measure_iterations(long long iterations,
    const std::vector<double>& a,
    const std::vector<double>& b)
{
    using clock = std::chrono::high_resolution_clock;

    auto start = clock::now();

    for (long long i = 0; i < iterations; ++i)
    {
        volatile double res = scalar_product(a, b);
        (void)res;
    }

    auto end = clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Iterations: " << iterations << '\n';
    std::cout << "All time: " << diff.count() << " second\n";
    std::cout << "-----------------------------\n";
}

int main()
{
    std::vector<double> a{ 1.0, 2.0, 3.0 };
    std::vector<double> b{ 4.0, 5.0, 6.0 };

    measure_iterations(1'000'000, a, b);
    measure_iterations(10'000'000, a, b);
    measure_iterations(100'000'000, a, b);

    return 0;
}
