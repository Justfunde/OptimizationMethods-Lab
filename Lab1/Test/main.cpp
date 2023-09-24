#include <iostream>
#include <cstdint>
#include <cmath>
#include <string>
#include <fstream>
#include <memory>

#include <gtest/gtest.h>

#include "Methods.hpp"

constexpr double eps = 0.001;
constexpr double etalonMin = -4.82057;

static
double
InMathFunc(double x)
{
   return x * sin(x) + 2 * cos(x);
}


TEST(MinFunctionCalcTest_Brute, BruteForceMethod)
{
   BruteForce solver(InMathFunc, {-6, -4}, eps);
   const auto yMin = solver.GetMin();

   EXPECT_NEAR(etalonMin, yMin, eps);
}

TEST(MinFunctionCalcTest_Dichotomy, DichotomyMethod)
{
   Dichotomy solver(InMathFunc, {-6, -4}, eps);
   const auto yMin = solver.GetMin();

   EXPECT_NEAR(etalonMin, yMin, eps);
}

TEST(MinFunctionCalcTest_GoldenSec, GoldenSecMethod)
{
   GoldenSection solver(InMathFunc, {-6, -4}, eps);
   const auto yMin = solver.GetMin();

   EXPECT_NEAR(etalonMin, yMin, eps);
}

TEST(MinFunctionCalcTest_Bitwise, BitwiseMethod)
{
   Bitwise solver(InMathFunc, {-6, -4}, eps);
   const auto yMin = solver.GetMin();

   EXPECT_NEAR(etalonMin, yMin, eps);
}
int32_t main(int32_t argc, char** argv)
{

   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}