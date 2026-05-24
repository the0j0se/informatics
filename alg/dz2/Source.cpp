#include <iostream>
#include <iomanip>
#include "Header.h"

int main() {
    double answer = 1.0;
    double a = 3.0;
    double b = 5.0;
    int arr[] = { 2, 3, 4, 5, 6, 8, 10, 50, 80, 100, 150, 200, 500, 1000 };

    std::cout << "Priblizhenoe znachenie ploshadi pri" << std::endl;
    for (int n : arr) {
        double result = simpson_rule(integral, a, b, n);
        std::cout << "n = " << n << " -> " << result << " pogreshonst: " 
            << std::fixed << std::setprecision(6) << result - answer << std::endl;
    }
    std::cout << "Pravilnoe znachenie: " << answer << std::endl;

    return 0;
}