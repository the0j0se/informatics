#include <iostream>
#include "Logic.h"

using namespace std;

int main()
{
    float x, y, R, S, C;

    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;

    Calculate(x, y, R, S, C);

    cout << "R = " << R << endl;
    cout << "S = " << S << endl;
    cout << "C = " << C << endl;

    system("pause");
    return 0;
}
