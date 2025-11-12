#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

void findSymmetricDifferenceAndOddElements(const std::set<int>& setA, const std::set<int>& setB) {
    std::vector<int> symmetricDiff;

    for (int elem : setA) {
        if (setB.find(elem) == setB.end()) {
            symmetricDiff.push_back(elem);
        }
    }

    for (int elem : setB) {
        if (setA.find(elem) == setA.end()) {
            symmetricDiff.push_back(elem);
        }
    }

    std::cout << "sim raznitsa: ";
    for (int elem : symmetricDiff) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "nechet element: ";
    bool hasOdd = false;
    for (int elem : symmetricDiff) {
        if (elem % 2 != 0) {
            std::cout << elem << " ";
            hasOdd = true;
        }
    }

    if (!hasOdd) {
        std::cout << "otsutstvuyt";
    }
    std::cout << std::endl;
}

int main() {

    int sizeA, sizeB;

    std::cout << "Vvedite razmer mnozhestva A: ";
    std::cin >> sizeA;

    std::cout << "Vvedite razmer mnozhestva B: ";
    std::cin >> sizeB;

    std::set<int> A;
    std::set<int> B;

    std::cout << "Vvedte " << sizeA << " elementov dlya mnozhestva A:" << std::endl;
    for (int i = 0; i < sizeA; i++) {
        int element;
        std::cin >> element;
        A.insert(element);
    }

    std::cout << "Vvedte " << sizeB << " elementov dlya mnozhestva B:" << std::endl;
    for (int i = 0; i < sizeB; i++) {
        int element;
        std::cin >> element;
        B.insert(element);
    }

    findSymmetricDifferenceAndOddElements(A, B);

    return 0;
}