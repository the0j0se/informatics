#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

int getPivotIndex(vector<int>& data, int start, int end) {
    int pivotValue = data[end];
    int marker = start - 1;

    for (int current = start; current < end; current++) {
        if (data[current] <= pivotValue) {
            marker++;
            swap(data[marker], data[current]);
        }
    }

    swap(data[marker + 1], data[end]);
    return marker + 1;
}

void singleQuickSort(vector<int>& data, int start, int end) {
    if (start < end) {
        int mid = getPivotIndex(data, start, end);
        singleQuickSort(data, start, mid - 1);
        singleQuickSort(data, mid + 1, end);
    }
}

void multiQuickSort(vector<int>& data, int start, int end, int totalThreads) {
    if (totalThreads <= 1 || end - start < 1000) {
        singleQuickSort(data, start, end);
        return;
    }

    if (start < end) {
        int mid = getPivotIndex(data, start, end);
        int allocatedThreads = totalThreads / 2;

        thread leftWorker(multiQuickSort, ref(data), start, mid - 1, allocatedThreads);
        thread rightWorker(multiQuickSort, ref(data), mid + 1, end, allocatedThreads);

        leftWorker.join();
        rightWorker.join();
    }
}

vector<int> createRandomVector(int totalElements) {
    vector<int> result(totalElements);
    for (int idx = 0; idx < totalElements; idx++) {
        result[idx] = rand() % 100000;
    }
    return result;
}

int main() {
    cout << fixed << setprecision(6);

    vector<int> benchmarkSizes = { 100, 1000, 10000, 20000, 30000, 40000, 50000 };
    cout << "Razmer\t" << "Obichnaya\t" << "\t" << "2 potoka\t" << "4 potoka\t" << "8 potokov" << endl;

    for (int currentSize : benchmarkSizes) {
        double avgSingle = 0, avgTwo = 0, avgFour = 0, avgEight = 0;
        const int iterations = 100;

        for (int iter = 0; iter < iterations; iter++) {
            vector<int> source = createRandomVector(currentSize);

            vector<int> targetSingle = source;
            auto tStart = high_resolution_clock::now();
            singleQuickSort(targetSingle, 0, targetSingle.size() - 1);
            auto tEnd = high_resolution_clock::now();
            avgSingle += duration<double>(tEnd - tStart).count();

            vector<int> targetTwo = source;
            tStart = high_resolution_clock::now();
            multiQuickSort(targetTwo, 0, targetTwo.size() - 1, 2);
            tEnd = high_resolution_clock::now();
            avgTwo += duration<double>(tEnd - tStart).count();

            vector<int> targetFour = source;
            tStart = high_resolution_clock::now();
            multiQuickSort(targetFour, 0, targetFour.size() - 1, 4);
            tEnd = high_resolution_clock::now();
            avgFour += duration<double>(tEnd - tStart).count();

            vector<int> targetEight = source;
            tStart = high_resolution_clock::now();
            multiQuickSort(targetEight, 0, targetEight.size() - 1, 8);
            tEnd = high_resolution_clock::now();
            avgEight += duration<double>(tEnd - tStart).count();
        }

        avgSingle /= iterations;
        avgTwo /= iterations;
        avgFour /= iterations;
        avgEight /= iterations;

        cout << currentSize << "\t" << avgSingle << "\t" << avgTwo << "\t" << avgFour << "\t" << avgEight << endl;
    }

    return 0;
}