#include <iostream>
#include <cmath>

int main()
{
    float x, y;
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;
    const double PI = 3.14159265358979323846;
    double R = cos(PI/2 * x);
    double S = log2(pow(2, y));
    std::cout << "R = " << R << std::endl;
    std::cout << "S = " << S << std::endl;
    double C = std::max(R, S);
    std::cout << "C = " << C << std::endl;

    system("pause");
    
    return 0;
}