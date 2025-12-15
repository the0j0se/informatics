#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\Admin\source\repos\ananas\ananas\Logic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
    TEST_CLASS(MathFunctionsTests)
    {
    public:

        TEST_METHOD(TestR_Zero)
        {
            float x = 0.0f;
            float y = 0.0f;
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(1.0f, R, 0.001f, L"R(0) = cos(0) = 1");
            Assert::AreEqual(0.0f, S, 0.001f, L"S(0) = log2(1) = 0");
            Assert::AreEqual(1.0f, C, 0.001f, L"C = max(1, 0) = 1");
        }

        TEST_METHOD(TestR_PI2)
        {
            float x = 1.0f;
            float y = 0.0f;
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(0.0f, R, 0.001f, L"R(1) = cos(π/2) = 0");
        }

        TEST_METHOD(TestR_PI4)
        {
            float x = 0.5f;
            float y = 0.0f;
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(0.707f, R, 0.001f, L"R(0.5) = cos(π/4) ≈ 0.707");
        }

        TEST_METHOD(TestS_Values)
        {
            float x = 0.0f;
            float y = 1.0f;
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(1.0f, S, 0.001f, L"S(1) = log2(2) = 1");
        }

        TEST_METHOD(TestC_MaxR)
        {
            float x = 0.0f;  // R = 1.0
            float y = -1.0f; // S = -1.0
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(1.0f, C, 0.001f, L"C = max(1.0, -1.0) = 1.0");
        }

        TEST_METHOD(TestC_MaxS)
        {
            float x = 1.0f;  // R = 0.0
            float y = 2.0f;  // S = 2.0
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(2.0f, C, 0.001f, L"C = max(0, 2) = 2.0");
        }

        TEST_METHOD(TestNegativeY)
        {
            float x = 0.0f;
            float y = -1.0f;
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(-1.0f, S, 0.001f, L"S(-1) = log2(0.5) = -1");
            Assert::AreEqual(1.0f, C, 0.001f, L"C = max(1, -1) = 1");
        }

        TEST_METHOD(TestLargeValues)
        {
            float x = 0.0f;
            float y = 10.0f;
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(10.0f, S, 0.001f, L"S(10) = log2(2^10) = 10");
            Assert::AreEqual(10.0f, C, 0.001f, L"C = max(1, 10) = 10");
        }
    };
}
