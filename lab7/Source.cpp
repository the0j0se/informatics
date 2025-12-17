#include "pch.h"
#include "Header.h"
#include <cmath>

#ifdef _WIN32
#define DOTPRODUCT_EXPORTS
#endif

double scalarProduct(const double* a, const double* b, int n) {
    if (a == nullptr || b == nullptr || n <= 0) {
        return 0.0;
    }

    double result = 0.0;
    for (int i = 0; i < n; ++i) {
        result += a[i] * b[i];
    }
    return result;
}