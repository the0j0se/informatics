#include "Header.h"
#include <cmath>

double simpson_rule(double (*f)(double), double a, double b, int n) {
    if (n % 2 == 1) n++;
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i += 2)
        sum += 4 * f(a + i * h);
    for (int i = 2; i < n - 1; i += 2)
        sum += 2 * f(a + i * h);
    return (h / 3) * sum;
}

double integral(double x) {
    double minimum = 3.0;
    return upper_bound(x) - minimum;
}


double upper_bound(double x) {
    if (x <= 4) return x;
    return -x + 8;
}
