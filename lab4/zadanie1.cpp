#include <iostream>

void countNegativeElements(const int* arr, int size, int& count) {
    count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            count++;
        }
    }
}

void printArraysByNegativeCount(const int* arrA, const int* arrB, int size) {
    int countA = 0, countB = 0;

    countNegativeElements(arrA, size, countA);
    countNegativeElements(arrB, size, countB);

    if (countA <= countB) {
        std::cout << "Массив A: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrA[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Массив B: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrB[i] << " ";
        }
    }
    else {
        std::cout << "Массив B: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrB[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Массив A: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrA[i] << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    const int SIZE = 5;

    int A[SIZE];
    int B[SIZE];

    std::cout << "Введите " << SIZE << " элементов для массива A:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        std::cin >> A[i];
    }

    std::cout << "Введите " << SIZE << " элементов для массива B:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        std::cin >> B[i];
    }

    printArraysByNegativeCount(A, B, SIZE);

    return 0;
}