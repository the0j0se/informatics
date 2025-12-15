#pragma once
#include <cmath>
#include <algorithm>

using namespace std;

inline void Calculate(float x, float y, float& R, float& S, float& C) {
    const double PI = 3.14159265358979323846;
    R = static_cast<float>(cos(PI / 2 * x));
    S = static_cast<float>(log2(pow(2, y)));
    C = max(R, S);
}