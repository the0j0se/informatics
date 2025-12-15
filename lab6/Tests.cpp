#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\Admin\source\repos\ananas\ananas\Logic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyTests
{
    TEST_CLASS(MathFunctionsTests)
    {
    public:

        TEST_METHOD(TestR_Zero)
        {
            float x = 0.0f, y = 0.0f;
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(1.0f, R, 0.001f, L"R(0) = 1");
            Assert::AreEqual(0.0f, S, 0.001f, L"S(0) = 0");
            Assert::AreEqual(1.0f, C, 0.001f, L"C = max(1,0) = 1");
        }

        TEST_METHOD(TestR_PI2)
        {
            float x = 1.0f, y = 0.0f;
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(0.0f, R, 0.001f, L"R(1) = 0");
        }

        TEST_METHOD(TestS_One)
        {
            float x = 0.0f, y = 1.0f;
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(1.0f, S, 0.001f, L"S(1) = 1");
        }

        TEST_METHOD(TestC_MaxS)
        {
            float x = 1.0f, y = 2.0f;  // R=0, S=2
            float R = 0.0f, S = 0.0f, C = 0.0f;

            Calculate(x, y, R, S, C);

            Assert::AreEqual(2.0f, C, 0.001f, L"C = max(0,2) = 2");
        }
    };
}
