#pragma once

#ifdef DOTPRODUCT_EXPORTS
#define DOTPRODUCT_API __declspec(dllexport)
#else
#define DOTPRODUCT_API __declspec(dllimport)
#endif

extern "C" {
    DOTPRODUCT_API double scalarProduct(const double* a, const double* b, int n);
    DOTPRODUCT_API const char* getVersion();
}
